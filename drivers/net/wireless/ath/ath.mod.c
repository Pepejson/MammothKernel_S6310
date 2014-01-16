#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xc9d39ff9, "module_layout" },
	{ 0x49ebacbd, "_clear_bit" },
	{ 0x676bbc0f, "_set_bit" },
	{ 0x9d669763, "memcpy" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0x16b68dda, "wiphy_apply_custom_regulatory" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x5b8c522d, "freq_reg_info" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x396c7763, "__alloc_skb" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x27e1a049, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=cfg80211";

