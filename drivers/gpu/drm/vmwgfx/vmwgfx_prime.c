// SPDX-License-Identifier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright (c) 2013-2024 Broadcom. All Rights Reserved. The term
 * “Broadcom” refers to Broadcom Inc. and/or its subsidiaries.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
/*
 * Authors:
 *     Thomas Hellstrom <thellstrom@vmware.com>
 *
 */

#include "vmwgfx_drv.h"
#include "vmwgfx_bo.h"
#include "ttm_object.h"
#include <mikux/dma-buf.h>

/*
 * DMA-BUF attach- and mapping methods. No need to implement
 * these until we have other virtual devices use them.
 */

static int vmw_prime_map_attach(struct dma_buf *dma_buf,
				struct dma_buf_attachment *attach)
{
	return -ENOSYS;
}

static void vmw_prime_map_detach(struct dma_buf *dma_buf,
				 struct dma_buf_attachment *attach)
{
}

static struct sg_table *vmw_prime_map_dma_buf(struct dma_buf_attachment *attach,
					      enum dma_data_direction dir)
{
	return ERR_PTR(-ENOSYS);
}

static void vmw_prime_unmap_dma_buf(struct dma_buf_attachment *attach,
				    struct sg_table *sgb,
				    enum dma_data_direction dir)
{
}

const struct dma_buf_ops vmw_prime_dmabuf_ops =  {
	.attach = vmw_prime_map_attach,
	.detach = vmw_prime_map_detach,
	.map_dma_buf = vmw_prime_map_dma_buf,
	.unmap_dma_buf = vmw_prime_unmap_dma_buf,
	.release = NULL,
};

int vmw_prime_fd_to_handle(struct drm_device *dev,
			   struct drm_file *file_priv,
			   int fd, u32 *handle)
{
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	int ret = ttm_prime_fd_to_handle(tfile, fd, handle);

	if (ret)
		ret = drm_gem_prime_fd_to_handle(dev, file_priv, fd, handle);

	return ret;
}

int vmw_prime_handle_to_fd(struct drm_device *dev,
			   struct drm_file *file_priv,
			   uint32_t handle, uint32_t flags,
			   int *prime_fd)
{
	struct vmw_private *vmw = vmw_priv(dev);
	struct ttm_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	struct vmw_bo *vbo;
	int ret;
	int surf_handle;

	if (handle > VMWGFX_NUM_MOB) {
		ret = ttm_prime_handle_to_fd(tfile, handle, flags, prime_fd);
	} else {
		ret = vmw_user_bo_lookup(file_priv, handle, &vbo);
		if (ret)
			return ret;
		if (vbo && vbo->is_dumb) {
			ret = drm_gem_prime_handle_to_fd(dev, file_priv, handle,
							 flags, prime_fd);
		} else {
			surf_handle = vmw_lookup_surface_handle_for_buffer(vmw,
									   vbo,
									   handle);
			if (surf_handle > 0)
				ret = ttm_prime_handle_to_fd(tfile, surf_handle,
							     flags, prime_fd);
			else
				ret = drm_gem_prime_handle_to_fd(dev, file_priv,
								 handle, flags,
								 prime_fd);
		}
		vmw_user_bo_unref(&vbo);
	}

	return ret;
}
