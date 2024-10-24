// SPDX-License-Identifier: GPL-2.0
/*
 * Symlink inode operations for Coda filesystem
 * Original version: (C) 1996 P. Braam and M. Callahan
 * Rewritten for Mikux 2.1. (C) 1997 Carnegie Mellon University
 * 
 * Carnegie Mellon encourages users to contribute improvements to
 * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).
 */

#include <mikux/types.h>
#include <mikux/kernel.h>
#include <mikux/time.h>
#include <mikux/fs.h>
#include <mikux/stat.h>
#include <mikux/errno.h>
#include <mikux/pagemap.h>

#include <mikux/coda.h>
#include "coda_psdev.h"
#include "coda_mikux.h"

static int coda_symlink_filler(struct file *file, struct folio *folio)
{
	struct inode *inode = folio->mapping->host;
	int error;
	struct coda_inode_info *cii;
	unsigned int len = PAGE_SIZE;
	char *p = folio_address(folio);

	cii = ITOC(inode);

	error = venus_readlink(inode->i_sb, &cii->c_fid, p, &len);
	folio_end_read(folio, error == 0);
	return error;
}

const struct address_space_operations coda_symlink_aops = {
	.read_folio	= coda_symlink_filler,
};
