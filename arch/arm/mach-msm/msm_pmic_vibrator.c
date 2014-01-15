/* include/asm/mach-msm/htc_pwrsink.h
 *
 * Copyright (C) 2008 HTC Corporation.
 * Copyright (C) 2007 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/hrtimer.h>
#include <linux/clk.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/delay.h>

#include <mach/samsung_vibe.h>

#include <mach/gpio.h>
#include <mach/vreg.h>

#include "pmic.h"
#include "timed_output.h"
#include <linux/regulator/consumer.h>

static int msm_vibrator_suspend(struct platform_device *pdev, pm_message_t state);
static int msm_vibrator_resume(struct platform_device *pdev);
static int msm_vibrator_probe(struct platform_device *pdev);
static int msm_vibrator_exit(struct platform_device *pdev);
static int msm_vibrator_power(int power_mode);


static struct hrtimer vibe_timer;

/* for the suspend/resume VIBRATOR Module */
static struct platform_driver msm_vibrator_platdrv = 
{
	.probe   = msm_vibrator_probe,
	.suspend = msm_vibrator_suspend,
	.resume  = msm_vibrator_resume,
	.remove  = msm_vibrator_exit,
	.driver = 
	{
		.name = MODULE_NAME,
		.owner = THIS_MODULE,
	},
};

static int msm_vibrator_suspend(struct platform_device *pdev, pm_message_t state)
{
	printk("[VIB] susepend\n");

	msm_vibrator_power(VIBRATION_OFF);

	return VIBE_S_SUCCESS;
}

static int msm_vibrator_resume(struct platform_device *pdev)
{
	printk("[VIB] resume\n");

	return VIBE_S_SUCCESS;
}

static int msm_vibrator_exit(struct platform_device *pdev)
{
	printk("[VIB] EXIT\n");

	return VIBE_S_SUCCESS;
}

static int msm_vibrator_power(int on)
{
	int ret = 0;
	static int nStatus = 0;
    unsigned int vib_voltage = 0;

	printk("%s on = %d nStatus = %d\n", __func__, on, nStatus);

	if(nStatus == on)	{
		printk("%s set already!\n", __func__);
		return VIBE_E_FAIL;
	}
	else {
		nStatus = on;
	}

    vib_voltage = 3100;

	if(on)	{
		ret = pmic_vib_mot_set_volt(vib_voltage);
	}
	else {
		ret = pmic_vib_mot_set_volt(0);
	}

	printk("%s status = %d\n", __func__, ret);

	return VIBE_S_SUCCESS;
}

static void vibrator_enable(struct timed_output_dev *dev, int value)
{
	unsigned long flags;

	hrtimer_cancel(&vibe_timer);

	if (value == 0) {
		printk("[VIB] OFF\n");
		msm_vibrator_power(VIBRATION_OFF);
		//pmic_vibrator_off();
	}
	else {

		if(value < 0)
			value = ~value;
		printk("[VIB] ON, %d ms\n",value);

		value = (value > 15000 ? 15000 : value);

		msm_vibrator_power(VIBRATION_ON);

		hrtimer_start(&vibe_timer,
			      ktime_set(value / 1000, (value % 1000) * 1000000),
			      HRTIMER_MODE_REL);
	}
}

static int vibrator_get_time(struct timed_output_dev *dev)
{
	if (hrtimer_active(&vibe_timer)) {
		ktime_t r = hrtimer_get_remaining(&vibe_timer);
		struct timeval t = ktime_to_timeval(r);

		return (t.tv_sec * 1000 + t.tv_usec / 1000000);
	}
	return 0;
}


static int vibrator_timer_do_work(struct work_struct *ignored)
{
	unsigned int remain;

	printk("[VIB] %s\n",__func__);

	if(hrtimer_active(&vibe_timer)) {
		ktime_t r = hrtimer_get_remaining(&vibe_timer);
		struct timeval t = ktime_to_timeval(r);
		remain= t.tv_sec * 1000 + t.tv_usec / 1000000;
		if(t.tv_sec < 0) {
			remain = 0;
		}
		printk("[VIB] hrtimer active, remain:%d\n",remain);

		if(!remain)	{
			msm_vibrator_power(VIBRATION_OFF);
		}
	}
	else {
		printk("[VIB] hrtimer not active\n");
		msm_vibrator_power(VIBRATION_OFF);
	}

	return 0;
}


static DECLARE_WORK(vibrator_timer_work, vibrator_timer_do_work);

static enum hrtimer_restart vibrator_timer_func(struct hrtimer *timer)
{
	printk("[VIB] %s\n",__func__);

	schedule_work(&vibrator_timer_work);

		return HRTIMER_NORESTART;
}

static struct timed_output_dev pmic_vibrator = {
	.name = "vibrator",
	.get_time = vibrator_get_time,
	.enable = vibrator_enable,
};

static int msm_vibrator_probe(struct platform_device *pdev)
{
	hrtimer_init(&vibe_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	vibe_timer.function = vibrator_timer_func;

	timed_output_dev_register(&pmic_vibrator);

	return 0;
}

static int __init msm_init_pmic_vibrator(void)
{
	int nRet;

	nRet = platform_driver_register(&msm_vibrator_platdrv);

	printk("[VIB] platform driver register result : %d\n",nRet);
	if (nRet)
	{ 
		printk("[VIB] platform_driver_register failed\n");
	}

	return nRet;

}

void __exit msm_exit_pmic_vibrator(void)
{
	platform_driver_unregister(&msm_vibrator_platdrv);

}

module_init(msm_init_pmic_vibrator);
module_exit(msm_exit_pmic_vibrator);


MODULE_DESCRIPTION("timed output pmic vibrator device");
MODULE_LICENSE("GPL");

