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
	{ 0x795a92f1, "single_release" },
	{ 0x49d9676b, "seq_read" },
	{ 0xf6068f42, "seq_lseek" },
	{ 0x2f9bab6e, "mmc_unregister_driver" },
	{ 0xa5b5bbf3, "mmc_register_driver" },
	{ 0x1424f59, "sg_copy_to_buffer" },
	{ 0x8371daff, "sg_copy_from_buffer" },
	{ 0xefdd2345, "sg_init_one" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0x66b2a859, "nr_free_buffer_pages" },
	{ 0xd53cd7b5, "membank0_size" },
	{ 0x46ce1a07, "membank1_start" },
	{ 0xf1795190, "mem_map" },
	{ 0xd5152710, "sg_next" },
	{ 0x1ed19662, "page_address" },
	{ 0xf88c3301, "sg_init_table" },
	{ 0xdc779e02, "mmc_wait_for_req" },
	{ 0x50a09774, "mmc_wait_for_cmd" },
	{ 0x5f754e5a, "memset" },
	{ 0xb6b07759, "mmc_start_req" },
	{ 0xf6a3cdfc, "_dev_info" },
	{ 0x46608fa0, "getnstimeofday" },
	{ 0xff9b9a7a, "mmc_can_trim" },
	{ 0xc795edb7, "mmc_erase" },
	{ 0x55992bc3, "mmc_can_erase" },
	{ 0x8c87e62, "dev_err" },
	{ 0x7171522e, "debugfs_remove" },
	{ 0x6ac88311, "debugfs_create_file" },
	{ 0xe53f474, "contig_page_data" },
	{ 0x50a600b9, "mmc_release_host" },
	{ 0xac56e948, "__mmc_claim_host" },
	{ 0x1cd172da, "__alloc_pages_nodemask" },
	{ 0x86a4889a, "kmalloc_order_trace" },
	{ 0x11a13e31, "_kstrtol" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x37a0cba, "kfree" },
	{ 0xdaed334e, "__free_pages" },
	{ 0xbe40f602, "mmc_set_blocklen" },
	{ 0x27e1a049, "printk" },
	{ 0xe6da44a, "set_normalized_timespec" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xb652293f, "kmalloc_caches" },
	{ 0xe00cafb0, "kmem_cache_alloc_trace" },
	{ 0x59e5070d, "__do_div64" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x76daa7a2, "mmc_set_data_timeout" },
	{ 0xfe1096b1, "mmc_can_reset" },
	{ 0x67d3c62e, "mmc_hw_reset_check" },
	{ 0xf7802486, "__aeabi_uidivmod" },
	{ 0xe707d823, "__aeabi_uidiv" },
	{ 0xc6e8a75a, "mutex_unlock" },
	{ 0xd67319, "seq_printf" },
	{ 0x1e79aedf, "mutex_lock" },
	{ 0xeca8bcda, "single_open" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

