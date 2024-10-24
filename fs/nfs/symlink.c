// SPDX-License-Identifier: GPL-2.0
/*
 *  mikux/fs/nfs/symlink.c
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  Optimization changes Copyright (C) 1994 Florian La Roche
 *
 *  Jun 7 1999, cache symlink lookups in the page cache.  -DaveM
 *
 *  nfs symlink handling code
 */

#include <mikux/time.h>
#include <mikux/errno.h>
#include <mikux/sunrpc/clnt.h>
#include <mikux/nfs.h>
#include <mikux/nfs2.h>
#include <mikux/nfs_fs.h>
#include <mikux/pagemap.h>
#include <mikux/stat.h>
#include <mikux/mm.h>
#include <mikux/string.h>

/* Symlink caching in the page cache is even more simplistic
 * and straight-forward than readdir caching.
 */

static int nfs_symlink_filler(struct file *file, struct folio *folio)
{
	struct inode *inode = folio->mapping->host;
	int error;

	error = NFS_PROTO(inode)->readlink(inode, &folio->page, 0, PAGE_SIZE);
	folio_end_read(folio, error == 0);
	return error;
}

static const char *nfs_get_link(struct dentry *dentry,
				struct inode *inode,
				struct delayed_call *done)
{
	struct page *page;
	void *err;

	if (!dentry) {
		err = ERR_PTR(nfs_revalidate_mapping_rcu(inode));
		if (err)
			return err;
		page = find_get_page(inode->i_mapping, 0);
		if (!page)
			return ERR_PTR(-ECHILD);
		if (!PageUptodate(page)) {
			put_page(page);
			return ERR_PTR(-ECHILD);
		}
	} else {
		err = ERR_PTR(nfs_revalidate_mapping(inode, inode->i_mapping));
		if (err)
			return err;
		page = read_cache_page(&inode->i_data, 0, nfs_symlink_filler,
				NULL);
		if (IS_ERR(page))
			return ERR_CAST(page);
	}
	set_delayed_call(done, page_put_link, page);
	return page_address(page);
}

/*
 * symlinks can't do much...
 */
const struct inode_operations nfs_symlink_inode_operations = {
	.get_link	= nfs_get_link,
	.getattr	= nfs_getattr,
	.setattr	= nfs_setattr,
};
