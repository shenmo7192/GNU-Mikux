/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _MIKUX_MIKUX_LOGO_H
#define _MIKUX_MIKUX_LOGO_H

/*
 *  Mikux logo to be displayed on boot
 *
 *  Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)
 *  Copyright (C) 1996,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *  Copyright (C) 2001 Greg Banks <gnb@alphalink.com.au>
 *  Copyright (C) 2001 Jan-Benedict Glaw <jbglaw@lug-owl.de>
 *  Copyright (C) 2003 Geert Uytterhoeven <geert@mikux-m68k.org>
 */

#include <mikux/init.h>


#define MIKUX_LOGO_MONO		1	/* monochrome black/white */
#define MIKUX_LOGO_VGA16	2	/* 16 colors VGA text palette */
#define MIKUX_LOGO_CLUT224	3	/* 224 colors */
#define MIKUX_LOGO_GRAY256	4	/* 256 levels grayscale */


struct mikux_logo {
	int type;			/* one of MIKUX_LOGO_* */
	unsigned int width;
	unsigned int height;
	unsigned int clutsize;		/* MIKUX_LOGO_CLUT224 only */
	const unsigned char *clut;	/* MIKUX_LOGO_CLUT224 only */
	const unsigned char *data;
};

extern const struct mikux_logo logo_mikux_mono;
extern const struct mikux_logo logo_mikux_vga16;
extern const struct mikux_logo logo_mikux_clut224;
extern const struct mikux_logo logo_dec_clut224;
extern const struct mikux_logo logo_mac_clut224;
extern const struct mikux_logo logo_parisc_clut224;
extern const struct mikux_logo logo_sgi_clut224;
extern const struct mikux_logo logo_sun_clut224;
extern const struct mikux_logo logo_superh_mono;
extern const struct mikux_logo logo_superh_vga16;
extern const struct mikux_logo logo_superh_clut224;
extern const struct mikux_logo logo_spe_clut224;

extern const struct mikux_logo *fb_find_logo(int depth);
#ifdef CONFIG_FB_LOGO_EXTRA
extern void fb_append_extra_logo(const struct mikux_logo *logo,
				 unsigned int n);
#else
static inline void fb_append_extra_logo(const struct mikux_logo *logo,
					unsigned int n)
{}
#endif

#endif /* _MIKUX_MIKUX_LOGO_H */
