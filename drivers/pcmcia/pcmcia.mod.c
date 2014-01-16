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
	{ 0xfa2a45e, "__memzero" },
	{ 0xf6a3cdfc, "_dev_info" },
	{ 0x71c90087, "memcmp" },
	{ 0x9d669763, "memcpy" },
	{ 0xac8f37b2, "outer_cache" },
	{ 0x8b525f8b, "write_to_strongly_ordered_memory" },
	{ 0xc2165d85, "__arm_iounmap" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0x15692c87, "param_ops_int" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x788fe103, "iomem_resource" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0xbe63ee40, "request_resource" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0xa5cef8ad, "release_resource" },
	{ 0x3ef5fd85, "pcmcia_socket_class" },
	{ 0xbdd4f918, "class_interface_unregister" },
	{ 0x4347adfe, "bus_unregister" },
	{ 0xe199a79f, "class_interface_register" },
	{ 0xe6046d21, "__bus_register" },
	{ 0x84b183ae, "strncmp" },
	{ 0x997f114a, "bus_rescan_devices" },
	{ 0x45f49a2f, "driver_create_file" },
	{ 0x87fbe6bd, "driver_register" },
	{ 0x741962c0, "__mutex_init" },
	{ 0x27e1a049, "printk" },
	{ 0x92870bfd, "driver_attach" },
	{ 0x20c55ae0, "sscanf" },
	{ 0x2d8db696, "driver_unregister" },
	{ 0xa3e564f9, "driver_remove_file" },
	{ 0x5bacda9, "device_register" },
	{ 0x429ebdcb, "dev_warn" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x733c3b54, "kasprintf" },
	{ 0xe4c91f73, "dev_set_name" },
	{ 0x9d79d46, "bus_for_each_dev" },
	{ 0x205a3486, "sysfs_create_bin_file" },
	{ 0x8f8d239c, "pcmcia_get_socket" },
	{ 0xf812c7e7, "pcmcia_put_socket" },
	{ 0x5e4d30d3, "sysfs_remove_bin_file" },
	{ 0xc2c9f7ff, "pccard_register_pcmcia" },
	{ 0xbc1131d7, "dev_get_drvdata" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x4a81636f, "release_firmware" },
	{ 0xad8a372b, "request_firmware" },
	{ 0xb652293f, "kmalloc_caches" },
	{ 0x328a05f1, "strncpy" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xe00cafb0, "kmem_cache_alloc_trace" },
	{ 0x37a0cba, "kfree" },
	{ 0xa7f92105, "add_uevent_var" },
	{ 0x6a847e20, "try_module_get" },
	{ 0xbf6850ab, "get_device" },
	{ 0xde3b35b6, "module_put" },
	{ 0x9c0b5da1, "put_device" },
	{ 0x81070f38, "device_unregister" },
	{ 0xf6901f84, "dev_printk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xe914e41e, "strcpy" },
	{ 0x91715312, "sprintf" },
	{ 0xa34f1ef5, "crc32_le" },
	{ 0x97255bdf, "strlen" },
	{ 0x5f754e5a, "memset" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x7e9b8bb9, "pcmcia_parse_uevents" },
	{ 0xc6e8a75a, "mutex_unlock" },
	{ 0x1e79aedf, "mutex_lock" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=pcmcia_core";

