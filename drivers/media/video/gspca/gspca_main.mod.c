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
	{ 0x9c2066ed, "video_ioctl2" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xa0b04675, "vmalloc_32" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xbc3d21af, "finish_wait" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x69ff5332, "prepare_to_wait" },
	{ 0x5f754e5a, "memset" },
	{ 0x3bd1b1f6, "msecs_to_jiffies" },
	{ 0xde3b35b6, "module_put" },
	{ 0x999e8297, "vfree" },
	{ 0xf9a482f9, "msleep" },
	{ 0x22890d20, "usb_clear_halt" },
	{ 0x3f9ee230, "usb_set_interface" },
	{ 0xb652293f, "kmalloc_caches" },
	{ 0x7e8a594c, "__video_register_device" },
	{ 0xa7ecf324, "__init_waitqueue_head" },
	{ 0x741962c0, "__mutex_init" },
	{ 0x2ee60a6c, "input_free_device" },
	{ 0x7dab89f1, "input_register_device" },
	{ 0xdd0a2ba2, "strlcat" },
	{ 0xb77691c0, "input_allocate_device" },
	{ 0xe00cafb0, "kmem_cache_alloc_trace" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x4cdb3178, "ns_to_timeval" },
	{ 0xc87c1f84, "ktime_get" },
	{ 0xbca4dfac, "vm_insert_page" },
	{ 0x3d016d21, "vmalloc_to_page" },
	{ 0x6a847e20, "try_module_get" },
	{ 0x4039bee5, "video_devdata" },
	{ 0xb81960ca, "snprintf" },
	{ 0x73e20c1c, "strlcpy" },
	{ 0x9d669763, "memcpy" },
	{ 0x37a0cba, "kfree" },
	{ 0x4e4f0a73, "video_unregister_device" },
	{ 0x36c4465d, "dev_set_drvdata" },
	{ 0xef99ef31, "input_unregister_device" },
	{  0xf1338, "__wake_up" },
	{ 0x1e79aedf, "mutex_lock" },
	{ 0xbc1131d7, "dev_get_drvdata" },
	{ 0x14cb6abc, "usb_kill_urb" },
	{ 0xc6e8a75a, "mutex_unlock" },
	{ 0x54fef42a, "mutex_lock_interruptible" },
	{ 0x2d988b78, "usb_free_urb" },
	{ 0x2fd5ea2c, "usb_free_coherent" },
	{ 0x5dc00b02, "usb_alloc_coherent" },
	{ 0x335df049, "usb_alloc_urb" },
	{ 0x6f263db, "usb_ifnum_to_if" },
	{ 0x72e608d6, "usb_submit_urb" },
	{ 0x27e1a049, "printk" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "FFBCF4BD2374601FE6CCFCE");
