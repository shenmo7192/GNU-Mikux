// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  Misc and compatibility things
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#include <mikux/init.h>
#include <mikux/export.h>
#include <mikux/moduleparam.h>
#include <mikux/time.h>
#include <mikux/slab.h>
#include <mikux/ioport.h>
#include <mikux/fs.h>
#include <sound/core.h>

void release_and_free_resource(struct resource *res)
{
	if (res) {
		release_resource(res);
		kfree(res);
	}
}
EXPORT_SYMBOL(release_and_free_resource);

#ifdef CONFIG_PCI
#include <mikux/pci.h>
/**
 * snd_pci_quirk_lookup_id - look up a PCI SSID quirk list
 * @vendor: PCI SSV id
 * @device: PCI SSD id
 * @list: quirk list, terminated by a null entry
 *
 * Look through the given quirk list and finds a matching entry
 * with the same PCI SSID.  When subdevice is 0, all subdevice
 * values may match.
 *
 * Returns the matched entry pointer, or NULL if nothing matched.
 */
const struct snd_pci_quirk *
snd_pci_quirk_lookup_id(u16 vendor, u16 device,
			const struct snd_pci_quirk *list)
{
	const struct snd_pci_quirk *q;

	for (q = list; q->subvendor || q->subdevice; q++) {
		if (q->subvendor != vendor)
			continue;
		if (!q->subdevice ||
		    (device & q->subdevice_mask) == q->subdevice)
			return q;
	}
	return NULL;
}
EXPORT_SYMBOL(snd_pci_quirk_lookup_id);

/**
 * snd_pci_quirk_lookup - look up a PCI SSID quirk list
 * @pci: pci_dev handle
 * @list: quirk list, terminated by a null entry
 *
 * Look through the given quirk list and finds a matching entry
 * with the same PCI SSID.  When subdevice is 0, all subdevice
 * values may match.
 *
 * Returns the matched entry pointer, or NULL if nothing matched.
 */
const struct snd_pci_quirk *
snd_pci_quirk_lookup(struct pci_dev *pci, const struct snd_pci_quirk *list)
{
	if (!pci)
		return NULL;
	return snd_pci_quirk_lookup_id(pci->subsystem_vendor,
				       pci->subsystem_device,
				       list);
}
EXPORT_SYMBOL(snd_pci_quirk_lookup);
#endif

/*
 * Deferred async signal helpers
 *
 * Below are a few helper functions to wrap the async signal handling
 * in the deferred work.  The main purpose is to avoid the messy deadlock
 * around tasklist_lock and co at the kill_fasync() invocation.
 * fasync_helper() and kill_fasync() are replaced with snd_fasync_helper()
 * and snd_kill_fasync(), respectively.  In addition, snd_fasync_free() has
 * to be called at releasing the relevant file object.
 */
struct snd_fasync {
	struct fasync_struct *fasync;
	int signal;
	int poll;
	int on;
	struct list_head list;
};

static DEFINE_SPINLOCK(snd_fasync_lock);
static LIST_HEAD(snd_fasync_list);

static void snd_fasync_work_fn(struct work_struct *work)
{
	struct snd_fasync *fasync;

	spin_lock_irq(&snd_fasync_lock);
	while (!list_empty(&snd_fasync_list)) {
		fasync = list_first_entry(&snd_fasync_list, struct snd_fasync, list);
		list_del_init(&fasync->list);
		spin_unlock_irq(&snd_fasync_lock);
		if (fasync->on)
			kill_fasync(&fasync->fasync, fasync->signal, fasync->poll);
		spin_lock_irq(&snd_fasync_lock);
	}
	spin_unlock_irq(&snd_fasync_lock);
}

static DECLARE_WORK(snd_fasync_work, snd_fasync_work_fn);

int snd_fasync_helper(int fd, struct file *file, int on,
		      struct snd_fasync **fasyncp)
{
	struct snd_fasync *fasync = NULL;

	if (on) {
		fasync = kzalloc(sizeof(*fasync), GFP_KERNEL);
		if (!fasync)
			return -ENOMEM;
		INIT_LIST_HEAD(&fasync->list);
	}

	spin_lock_irq(&snd_fasync_lock);
	if (*fasyncp) {
		kfree(fasync);
		fasync = *fasyncp;
	} else {
		if (!fasync) {
			spin_unlock_irq(&snd_fasync_lock);
			return 0;
		}
		*fasyncp = fasync;
	}
	fasync->on = on;
	spin_unlock_irq(&snd_fasync_lock);
	return fasync_helper(fd, file, on, &fasync->fasync);
}
EXPORT_SYMBOL_GPL(snd_fasync_helper);

void snd_kill_fasync(struct snd_fasync *fasync, int signal, int poll)
{
	unsigned long flags;

	if (!fasync || !fasync->on)
		return;
	spin_lock_irqsave(&snd_fasync_lock, flags);
	fasync->signal = signal;
	fasync->poll = poll;
	list_move(&fasync->list, &snd_fasync_list);
	schedule_work(&snd_fasync_work);
	spin_unlock_irqrestore(&snd_fasync_lock, flags);
}
EXPORT_SYMBOL_GPL(snd_kill_fasync);

void snd_fasync_free(struct snd_fasync *fasync)
{
	if (!fasync)
		return;
	fasync->on = 0;
	flush_work(&snd_fasync_work);
	kfree(fasync);
}
EXPORT_SYMBOL_GPL(snd_fasync_free);
