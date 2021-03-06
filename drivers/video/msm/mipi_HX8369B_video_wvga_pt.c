/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "msm_fb.h"
#include "mipi_dsi.h"
#include "mipi_HX8369B.h"

static struct msm_panel_info pinfo;

extern int charging_boot;


#if 0 
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
        /* DSI Bit Clock at 440 MHz, 2 lane, RGB888 */ 
	/* regulator */ 
	{0x03, 0x01, 0x01, 0x00}, 
	/* timing */ 
	{0xb2, 0x8c, 0x1c, 0x00, 0x95, 0x92, 0x1f, 0x8e, 
	0x15, 0x03, 0x04}, 
	/* phy ctrl */ 
	{0x7f, 0x00, 0x00, 0x00}, 
	/* strength */ 
	{0xbb, 0x02, 0x06, 0x00}, 
	/* pll control */ 
	{0x00, 0xb2, 0x31, 0xd2, 0x00, 0x40, 0x37, 0x62, 
	0x01, 0x0f, 0x07, 
	0x05, 0x14, 0x03, 0x0, 0x0, 0x0, 0x20, 0x0, 0x02, 0x0}, 
};
#else
// 2012.10.11 hojini.hwang Caused by RF noise
static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
	/* DSI Bit Clock at 492 MHz, 2 lane, RGB888 */
	/* regulator */
	{0x03, 0x01, 0x01, 0x00},		
	/* timing */
	{0xb8, 0x8d, 0x1f, 0x00, 0x97, 0x94, 0x22, 0x8f,
	0x18, 0x03, 0x04},
	/* phy ctrl */
	{0x7f, 0x00, 0x00, 0x00},
	/* strength */
	{0xbb, 0x02, 0x06, 0x00},	
	/* pll control */
	{0x00, 0xe5, 0x31, 0xd2, 0x00, 0x40, 0x37, 0x62,
	0x01, 0x0f, 0x07,
	0x05, 0x14, 0x03, 0x0, 0x0, 0x0, 0x20, 0x0, 0x02, 0x0},
};
#endif

static int mipi_video_hx8369b_wvga_pt_init(void)
{
	int ret;

	if (msm_fb_detect_client("mipi_video_hx8369b_wvga"))
		return 0;

	pinfo.xres = 480;
	pinfo.yres = 800;
	pinfo.type = MIPI_VIDEO_PANEL;
	pinfo.pdest = DISPLAY_1;
	pinfo.wait_cycle = 0;
	pinfo.bpp = 24;
	
#if defined(CONFIG_MACH_BAFFIN_DUOS_CTC)
	pinfo.lcdc.h_back_porch = 123;
	pinfo.lcdc.h_front_porch = 146;
	pinfo.lcdc.h_pulse_width = 80;
	pinfo.lcdc.v_back_porch = 13;
	pinfo.lcdc.v_front_porch = 8;
	pinfo.lcdc.v_pulse_width = 4;
#elif defined(CONFIG_MACH_DELOS_OPEN)
	pinfo.lcdc.h_back_porch = 135;
	pinfo.lcdc.h_front_porch = 150;
	pinfo.lcdc.h_pulse_width = 32;
	pinfo.lcdc.v_back_porch = 9;
	pinfo.lcdc.v_front_porch = 10;
	pinfo.lcdc.v_pulse_width = 6;
#else
	pinfo.lcdc.h_back_porch = 180;
	pinfo.lcdc.h_front_porch = 150;
	pinfo.lcdc.h_pulse_width = 32;
	pinfo.lcdc.v_back_porch = 22;
	pinfo.lcdc.v_front_porch = 20;
	pinfo.lcdc.v_pulse_width = 2;
#endif
	
	pinfo.lcdc.border_clr = 0;	/* blk */
	pinfo.lcdc.underflow_clr = 0xff;	/* blue */
	/* number of dot_clk cycles HSYNC active edge is
	delayed from VSYNC active edge */
	pinfo.lcdc.hsync_skew = 0;
        pinfo.clk_rate = 492000000;
	pinfo.bl_max = 255; /*16; CHECK THIS!!!*/
	pinfo.bl_min = 1;
	pinfo.fb_num = 2;

	pinfo.mipi.mode = DSI_VIDEO_MODE;
	/* send HSA and HE following VS/VE packet */
	pinfo.mipi.pulse_mode_hsa_he = TRUE;
#if defined(CONFIG_MACH_BAFFIN_DUOS_CTC)
	pinfo.mipi.hfp_power_stop = TRUE; /* LP-11 during the HFP period */
	pinfo.mipi.hbp_power_stop = TRUE; /* LP-11 during the HBP period */
	pinfo.mipi.hsa_power_stop = TRUE; /* LP-11 during the HSA period */
	pinfo.mipi.mdp_trigger = DSI_CMD_TRIGGER_SW;
#else
	pinfo.mipi.hfp_power_stop = FALSE; /* LP-11 during the HFP period */
	pinfo.mipi.hbp_power_stop = FALSE; /* LP-11 during the HBP period */
	pinfo.mipi.hsa_power_stop = FALSE; /* LP-11 during the HSA period */
	pinfo.mipi.mdp_trigger = DSI_CMD_TRIGGER_NONE;
#endif
	/* LP-11 or let Command Mode Engine send packets in
	HS or LP mode for the BLLP of the last line of a frame */
	pinfo.mipi.eof_bllp_power_stop = TRUE;
	/* LP-11 or let Command Mode Engine send packets in
	HS or LP mode for packets sent during BLLP period */
	pinfo.mipi.bllp_power_stop = TRUE;

	pinfo.mipi.traffic_mode = DSI_BURST_MODE;
	pinfo.mipi.dst_format =  DSI_VIDEO_DST_FORMAT_RGB888;
	pinfo.mipi.vc = 0;
	pinfo.mipi.rgb_swap = DSI_RGB_SWAP_RGB; /* RGB */
	pinfo.mipi.data_lane0 = TRUE;
	pinfo.mipi.data_lane1 = TRUE;

	pinfo.mipi.t_clk_post = 0x20;
	pinfo.mipi.t_clk_pre = 0x2f;

	pinfo.mipi.stream = 0; /* dma_p */
	
	pinfo.mipi.dma_trigger = DSI_CMD_TRIGGER_SW;
	pinfo.mipi.frame_rate = 60; /* FIXME */

	pinfo.mipi.dsi_phy_db = &dsi_video_mode_phy_db;
	pinfo.mipi.dlane_swap = 0x01;
	/* append EOT at the end of data burst */
	pinfo.mipi.tx_eot_append = 0x01;

	ret = mipi_hx8369b_device_register(&pinfo, MIPI_DSI_PRIM,
						MIPI_DSI_PANEL_WVGA_PT);

	if (ret)
		pr_err("%s: failed to register device!\n", __func__);

/* Temporary */
	if (charging_boot != 1)
		load_565rle_image(INIT_IMAGE_FILE, 0);

	return ret;
}

module_init(mipi_video_hx8369b_wvga_pt_init);
