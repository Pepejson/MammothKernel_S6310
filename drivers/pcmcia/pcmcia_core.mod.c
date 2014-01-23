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
	{ 0xaace4550, "sysfs_remove_group" },
	{ 0x862b0e21, "sysfs_create_group" },
	{ 0xe914e41e, "strcpy" },
	{ 0x84b183ae, "strncmp" },
	{ 0x20c55ae0, "sscanf" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0x91715312, "sprintf" },
	{ 0x15692c87, "param_ops_int" },
	{ 0xb75da9a9, "class_unregister" },
	{ 0x6f94c980, "__class_register" },
	{ 0x7ab88a45, "system_freezing_cnt" },
	{ 0x81070f38, "device_unregister" },
	{ 0x4482cdb, "__refrigerator" },
	{ 0x29d7d78a, "freezing_slow_path" },
	{ 0x1000e51, "schedule" },
	{ 0xd2965f6f, "kthread_should_stop" },
	{ 0x9e61bb05, "set_freezable" },
	{ 0x429ebdcb, "dev_warn" },
	{ 0x5bacda9, "device_register" },
	{ 0xbf6850ab, "get_device" },
	{ 0x9c0b5da1, "put_device" },
	{ 0x402b8281, "__request_module" },
	{ 0x43d118d, "kthread_create_on_node" },
	{ 0x741962c0, "__mutex_init" },
	{ 0xa7ecf324, "__init_waitqueue_head" },
	{ 0xe4c91f73, "dev_set_name" },
	{ 0x36c4465d, "dev_set_drvdata" },
	{ 0x2f4ea1ac, "wait_for_completion" },
	{ 0x27b06b76, "up_write" },
	{ 0xa4a94b1d, "down_write" },
	{ 0xe40871ef, "kthread_stop" },
	{ 0xf6bb0afc, "up_read" },
	{ 0x3c1ea6eb, "down_read" },
	{ 0x6aa6c712, "wake_up_process" },
	{ 0x8ddab831, "_raw_spin_unlock_irqrestore" },
	{ 0x1a9b678e, "_raw_spin_lock_irqsave" },
	{ 0x37a0cba, "kfree" },
	{ 0xa7f92105, "add_uevent_var" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xad998077, "complete" },
	{ 0xbc1131d7, "dev_get_drvdata" },
	{ 0xf6901f84, "dev_printk" },
	{ 0xf9a482f9, "msleep" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xc6e8a75a, "mutex_unlock" },
	{ 0x1e79aedf, "mutex_lock" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

