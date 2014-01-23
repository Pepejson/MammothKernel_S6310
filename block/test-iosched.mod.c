#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xc9d39ff9, "module_layout" },
	{ 0xfbe05fca, "elv_unregister" },
	{ 0x77f755c, "elv_register" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x7d11c268, "jiffies" },
	{ 0xd5f2172f, "del_timer_sync" },
	{ 0xbc3d21af, "finish_wait" },
	{ 0x1000e51, "schedule" },
	{ 0x69ff5332, "prepare_to_wait" },
	{ 0x5f754e5a, "memset" },
	{ 0xc7729c8e, "__blk_run_queue" },
	{ 0x8834396c, "mod_timer" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xf9a482f9, "msleep" },
	{ 0xbfb3d014, "init_request_from_bio" },
	{ 0x8da34eb6, "bio_alloc" },
	{ 0xe49c15b6, "bio_put" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0xd7d4c7bd, "blk_rq_map_kern" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x5a1b2d4e, "blk_get_request" },
	{ 0x37a0cba, "kfree" },
	{ 0xe1cfa0e, "blk_put_request" },
	{ 0x178ba18c, "_raw_spin_unlock" },
	{ 0xc4097c34, "_raw_spin_lock" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x97750e27, "elv_dispatch_sort" },
	{  0xf1338, "__wake_up" },
	{ 0xb652293f, "kmalloc_caches" },
	{ 0xf97ec4ec, "debugfs_create_u32" },
	{ 0x7322a084, "debugfs_remove_recursive" },
	{ 0x5f1a3f79, "debugfs_create_dir" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0xa7ecf324, "__init_waitqueue_head" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x27e1a049, "printk" },
	{ 0xe00cafb0, "kmem_cache_alloc_trace" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

