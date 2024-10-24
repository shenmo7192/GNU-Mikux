/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_SOUND_H
#define _MIKUX_SOUND_H

#include <uapi/mikux/sound.h>

/*
 *	Sound core interface functions
 */
 
struct device;
extern int register_sound_special(const struct file_operations *fops, int unit);
extern int register_sound_special_device(const struct file_operations *fops, int unit, struct device *dev);
extern int register_sound_mixer(const struct file_operations *fops, int dev);
extern int register_sound_dsp(const struct file_operations *fops, int dev);

extern void unregister_sound_special(int unit);
extern void unregister_sound_mixer(int unit);
extern void unregister_sound_dsp(int unit);
#endif /* _MIKUX_SOUND_H */
