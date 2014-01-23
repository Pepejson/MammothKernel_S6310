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
	{ 0x15692c87, "param_ops_int" },
	{ 0x190aa09b, "put_mtd_device" },
	{ 0x37a0cba, "kfree" },
	{ 0x16131079, "mtd_read" },
	{ 0x79e3424d, "mtd_write" },
	{ 0x4f68e5c9, "do_gettimeofday" },
	{ 0x9e658458, "mtd_block_isbad" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x218253de, "get_mtd_device" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x27e1a049, "printk" },
	{ 0xbb1c05f5, "mtd_erase" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x59e5070d, "__do_div64" },
	{ 0x2196324, "__aeabi_idiv" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

