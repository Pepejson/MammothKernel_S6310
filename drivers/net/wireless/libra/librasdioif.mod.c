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
	{ 0x1258d9d9, "regulator_disable" },
	{ 0xc3eafe2d, "pmapp_vreg_lpm_pincntrl_vote" },
	{ 0x8a5c7a80, "regulator_enable" },
	{ 0x98cc564a, "regulator_set_voltage" },
	{ 0xfe990052, "gpio_free" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0x3441c3d6, "gpio_set_value_cansleep" },
	{ 0xa3570b67, "pmapp_clock_vote" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x96d9ad8f, "regulator_bulk_get" },
	{ 0x916c004b, "crypto_alloc_ahash" },
	{ 0x7ce064c6, "crypto_ahash_digest" },
	{ 0xd1ffec6d, "crypto_ahash_setkey" },
	{ 0x6c3b010, "crypto_alloc_ablkcipher" },
	{ 0x7a4497db, "kzfree" },
	{ 0xbab62cc5, "crypto_destroy_tfm" },
	{ 0xc9d01c1a, "sdio_unregister_driver" },
	{ 0xf9a482f9, "msleep" },
	{ 0x92fc3727, "sdio_register_driver" },
	{ 0xb463f7b5, "mmc_detect_change" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xb390ee9f, "sdio_set_host_pm_flags" },
	{ 0x9bc5fd52, "sdio_claim_irq" },
	{ 0xae61b834, "sdio_enable_func" },
	{ 0xbfd4cf34, "sdio_set_block_size" },
	{ 0x6eea025b, "sdio_release_irq" },
	{ 0xd060875e, "sdio_disable_func" },
	{ 0x36c4465d, "dev_set_drvdata" },
	{ 0xbc1131d7, "dev_get_drvdata" },
	{ 0x85351517, "sdio_release_host" },
	{ 0x9b76b8a7, "sdio_claim_host" },
	{ 0x35f6b2ea, "sdio_readb" },
	{ 0x2ea0e06d, "sdio_writeb" },
	{ 0xda41a09b, "sdio_readsb" },
	{ 0x34ab105f, "sdio_memcpy_fromio" },
	{ 0x35a52031, "sdio_writesb" },
	{ 0x75e01604, "sdio_memcpy_toio" },
	{ 0x27e1a049, "printk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "86E14E6B44B72C0454C8E91");
