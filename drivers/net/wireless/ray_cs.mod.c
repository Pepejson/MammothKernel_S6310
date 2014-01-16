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
	{ 0x35b6b772, "param_ops_charp" },
	{ 0x15692c87, "param_ops_int" },
	{ 0xf9c18c01, "iw_handler_get_thrspy" },
	{ 0x50551b6, "iw_handler_set_thrspy" },
	{ 0x4332ec1c, "iw_handler_get_spy" },
	{ 0x7e3a55af, "iw_handler_set_spy" },
	{ 0xac01447c, "noop_llseek" },
	{ 0x795a92f1, "single_release" },
	{ 0x49d9676b, "seq_read" },
	{ 0xf6068f42, "seq_lseek" },
	{ 0x2fd7a952, "eth_change_mtu" },
	{ 0x5a9a05d9, "eth_validate_addr" },
	{ 0xd0aba7ed, "eth_mac_addr" },
	{ 0xe1ca8209, "pcmcia_unregister_driver" },
	{ 0xbb1894b6, "remove_proc_entry" },
	{ 0xfac37b0d, "proc_create_data" },
	{ 0x7355091a, "proc_mkdir" },
	{ 0x1e77e5a6, "pcmcia_register_driver" },
	{ 0x62b242a2, "skb_pad" },
	{ 0xaa80830a, "consume_skb" },
	{ 0x51ed35cd, "__netif_schedule" },
	{ 0x2a3aa678, "_test_and_clear_bit" },
	{ 0x56304186, "wireless_spy_update" },
	{ 0xec51902d, "netif_rx" },
	{ 0xdab656ec, "eth_type_trans" },
	{ 0x71c90087, "memcmp" },
	{ 0x8c684258, "skb_pull" },
	{ 0xa2dd2999, "skb_put" },
	{ 0xa7cdd469, "dev_alloc_skb" },
	{ 0x3e48ab7c, "seq_putc" },
	{ 0xd67319, "seq_printf" },
	{ 0xf9b262c2, "seq_puts" },
	{ 0xeca8bcda, "single_open" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x29ab0ba2, "register_netdev" },
	{ 0x11f7ed4c, "hex_to_bin" },
	{ 0x328a05f1, "strncpy" },
	{ 0x9d669763, "memcpy" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0x41495a5, "pcmcia_map_mem_page" },
	{ 0x2c2f585b, "pcmcia_request_window" },
	{ 0xbdc39478, "pcmcia_enable_device" },
	{ 0x7636c05d, "pcmcia_request_irq" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0xf64c21e1, "alloc_etherdev_mqs" },
	{ 0x1ad1f2e7, "_memcpy_fromio" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x5f754e5a, "memset" },
	{ 0x7d11c268, "jiffies" },
	{ 0xbe2c0274, "add_timer" },
	{ 0x27e1a049, "printk" },
	{ 0xb95f98d6, "_memset_io" },
	{ 0x7f63b31e, "_memcpy_toio" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0xac8f37b2, "outer_cache" },
	{ 0x8b525f8b, "write_to_strongly_ordered_memory" },
	{ 0x9d979f64, "pcmcia_dev_present" },
	{ 0xe914e41e, "strcpy" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x97255bdf, "strlen" },
	{ 0x7d298754, "free_netdev" },
	{ 0xb001b1d4, "unregister_netdev" },
	{ 0x667a28ee, "pcmcia_disable_device" },
	{ 0xc2165d85, "__arm_iounmap" },
	{ 0xc996d097, "del_timer" },
	{ 0xfd517b50, "netif_device_detach" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xd1acc801, "netif_device_attach" },
	{ 0x2196324, "__aeabi_idiv" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=pcmcia";

MODULE_ALIAS("pcmcia:m01A6c0000f*fn*pfn*pa*pb*pc*pd*");
