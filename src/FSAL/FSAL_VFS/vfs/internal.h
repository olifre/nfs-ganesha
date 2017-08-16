#ifndef VFS_INTERNAL
#define VFS_INTERNAL

#include "fsal_handle_syscalls.h"

/* pNFS types. */
struct vfs_ds {
	struct fsal_ds_handle ds; /*< Public DS handle */
	vfs_file_handle_t wire; /*< Wire data */
	struct vfs_filesystem *vfs_fs; /*< Related Vfs filesystem */
	bool connected; /*< True if the handle has been connected */
};

/* this needs to be refactored to put ipport inside sockaddr_in */
struct vfs_pnfs_ds_parameter {
	struct glist_head ds_list;
	struct sockaddr_in ipaddr;
	unsigned short ipport;
	unsigned int id;
};

struct vfs_pnfs_parameter {
	struct glist_head ds_list;
};

struct vfs_fsal_module {
	struct fsal_module fsal;
	struct fsal_staticfsinfo_t fs_info;
	struct vfs_pnfs_parameter pnfs_param;
};

/* Methods for pNFS
 */
nfsstat4 vfs_getdeviceinfo(struct fsal_module *fsal_hdl,
			   XDR *da_addr_body,
			   const layouttype4 type,
			   const struct pnfs_deviceid *deviceid);

size_t vfs_fs_da_addr_size(struct fsal_module *fsal_hdl);
void export_ops_pnfs(struct export_ops *ops);
void handle_ops_pnfs(struct fsal_obj_ops *ops);
void vfs_pnfs_ds_ops_init(struct fsal_pnfs_ds_ops *ops);

#endif	/* VFS_INTERNAL */
