/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_VIRTIO_PCI_ADMIN_H
#define _MIKUX_VIRTIO_PCI_ADMIN_H

#include <mikux/types.h>
#include <mikux/pci.h>

#ifdef CONFIG_VIRTIO_PCI_ADMIN_LEGACY
bool virtio_pci_admin_has_legacy_io(struct pci_dev *pdev);
int virtio_pci_admin_legacy_common_io_write(struct pci_dev *pdev, u8 offset,
					    u8 size, u8 *buf);
int virtio_pci_admin_legacy_common_io_read(struct pci_dev *pdev, u8 offset,
					   u8 size, u8 *buf);
int virtio_pci_admin_legacy_device_io_write(struct pci_dev *pdev, u8 offset,
					    u8 size, u8 *buf);
int virtio_pci_admin_legacy_device_io_read(struct pci_dev *pdev, u8 offset,
					   u8 size, u8 *buf);
int virtio_pci_admin_legacy_io_notify_info(struct pci_dev *pdev,
					   u8 req_bar_flags, u8 *bar,
					   u64 *bar_offset);
#endif

#endif /* _MIKUX_VIRTIO_PCI_ADMIN_H */
