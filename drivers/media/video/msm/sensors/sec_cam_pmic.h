
#ifndef _SEC_CAM_PMIC_H
#define _SEC_CAM_PMIC_H
#include "msm_sensor.h"

#define	ON		1
#define	OFF		0
#define LOW		0
#define HIGH		1

#define FLASH_MODE_NONE		0
#define FLASH_MODE_CAMERA		1
#define FLASH_MODE_LIGHT		2

#if defined(CONFIG_S5K5CCGX)
#define S5K5CCGX_CAM_STBY	 96
#define S5K5CCGX_CAM_RESET	 85
#if defined(CONFIG_MACH_INFINITE_DUOS_CTC) || defined(CONFIG_MACH_DELOS_DUOS_CTC)
#define S5K5CCGX_CAM_A_EN	128		//VCAM_A_2.8V
#elif defined(CONFIG_MACH_KYLEPLUS_OPEN)
#define S5K5CCGX_CAM_IO_EN	  4		//VCAM_IO_1.8V
#elif defined(CONFIG_MACH_KYLEPLUS_CTC)
#define S5K5CCGX_CAM_A_EN	128		//VCAM_A_2.8V
#if (CONFIG_MACH_KYLEPLUS_CTC_HWREV == 0x0)
#define S5K5CCGX_CAM_IO_EN	4	//VCAM_IO_1.8V
#elif (CONFIG_MACH_KYLEPLUS_CTC_HWREV == 0x1)
#define S5K5CCGX_CAM_IO_EN	129	//VCAM_IO_1.8V
#endif
#endif
#endif


#if defined (CONFIG_MACH_ARUBA_OPEN) || defined (CONFIG_MACH_ARUBASLIM_OPEN)	// temperary setting
#define ARUBA_CAM_IO_EN	4
#define ARUBA_CAM_C_EN		107
#define ARUBA_CAM_AF_EN	49
#define ARUBA_CAM_STBY		96
#define ARUBA_CAM_RESET	85
#define ARUBA_CAM_FLASH_EN	58
extern unsigned int board_hw_revision;
#define ARUBA_CAM_FLASH_SET	5
#define ARUBA_CAM_FLASH_SET_OLD	86
#define ARUBA_CAM_A_EN	4
#else	//CONFIG_MACH_ARUBA_OPEN
#define ARUBA_CAM_A_EN	128
#if defined (CONFIG_S5K4ECGX)
#define ARUBA_CAM_C_EN	107
#define ARUBA_CAM_AF_EN	129
#define ARUBA_CAM_FLASH_EN	14
#define ARUBA_CAM_FLASH_SET	11
#endif
#define ARUBA_CAM_STBY		96
#define ARUBA_CAM_RESET	85
#if defined (CONFIG_MACH_BAFFIN_DUOS_CTC)
#define FRONT_CAM_C_EN	73
#define FRONT_CAM_STBY 75
#define FRONT_CAM_RESET	80
#endif	//CONFIG_MACH_ARUBA_OPEN
#endif

void cam_ldo_power_on_1(void);
void cam_ldo_power_on_2(void);
void cam_ldo_power_off_1(void);
void cam_ldo_power_off_2(void);
#ifdef CONFIG_S5K4ECGX
void cam_flash_main_on(int flashMode);
void cam_flash_torch_on(int flashMode);
void cam_flash_off(int flashMode);
static int flash_mode = FLASH_MODE_NONE;
#endif

#ifdef CONFIG_MACH_BAFFIN_DUOS_CTC
int32_t msm_sensor_power_up_baffin_duos(struct msm_sensor_ctrl_t *s_ctrl);
int32_t msm_sensor_power_down_baffin_duos(struct msm_sensor_ctrl_t *s_ctrl);
#endif


#if defined (CONFIG_MACH_ARUBA_OPEN) || defined (CONFIG_MACH_ARUBASLIM_OPEN)
int32_t msm_sensor_power_up_aruba_open(struct msm_sensor_ctrl_t *s_ctrl);
int32_t msm_sensor_power_down_aruba_open(struct msm_sensor_ctrl_t *s_ctrl);
#endif
#endif

