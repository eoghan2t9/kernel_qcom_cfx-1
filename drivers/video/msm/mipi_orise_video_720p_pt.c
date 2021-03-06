/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
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
#include "mipi_orise.h"

static struct msm_panel_info pinfo;

static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db_1080p = { 
	/* 1920*1200, RGB888, 4 Lane 60 fps video mode */ 
	/* regulator */ 
	{0x09, 0x08, 0x05, 0x00, 0x20},
	/* timing */ 
	{0xe9, 0x5e, 0x2c, 0x00, 0x7b, 0x7c, 0x30, 0x61, 
	0x42, 0x03, 0x04, 0xa0}, 
	/* phy ctrl */ 
	{0x5f, 0x00, 0x00, 0x10}, 
	/* strength */ 
	{0xff, 0x00, 0x06, 0x00}, 
	/* pll control */ 
	{0x0, 0x49, 0x30, 0xc4, 0x00, 0x20, 0x07, 0x62,
	0x41, 0x0f, 0x01, 
	0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 }, 
}; 

static int __init mipi_video_orise_720p_pt_init(void)
{
	int ret;

	if (msm_fb_detect_client("mipi_video_orise_720p"))
		return 0;

	pinfo.xres = 1080;
	pinfo.yres = 1920;
	pinfo.lcdc.xres_pad = 0;
	pinfo.lcdc.yres_pad = 0;

	pinfo.type = MIPI_VIDEO_PANEL;
	pinfo.pdest = DISPLAY_1;
	pinfo.wait_cycle = 0;
	pinfo.bpp = 24;
	pinfo.lcdc.h_back_porch = 101;
	pinfo.lcdc.h_front_porch = 130;
	pinfo.lcdc.h_pulse_width = 8;

	pinfo.lcdc.v_back_porch = 4;
	pinfo.lcdc.v_front_porch = 3;
	pinfo.lcdc.v_pulse_width = 1;

	pinfo.lcdc.border_clr = 0;	/* blk */
	pinfo.lcdc.underflow_clr = 0xff;	/* blue */
	pinfo.lcdc.hsync_skew = 0;
	pinfo.bl_max = 127;
	pinfo.bl_min = 1;
	pinfo.fb_num = 2;
	pinfo.clk_rate = 860000000;

	pinfo.mipi.mode = DSI_VIDEO_MODE;
	pinfo.mipi.pulse_mode_hsa_he = FALSE;
	pinfo.mipi.hfp_power_stop = TRUE;
	pinfo.mipi.hbp_power_stop = FALSE;
	pinfo.mipi.hsa_power_stop = FALSE;
	pinfo.mipi.eof_bllp_power_stop = FALSE;
	pinfo.mipi.bllp_power_stop = FALSE;
	pinfo.mipi.traffic_mode = DSI_BURST_MODE;
	pinfo.mipi.dst_format = DSI_VIDEO_DST_FORMAT_RGB888;
	pinfo.mipi.vc = 0;
	pinfo.mipi.rgb_swap = DSI_RGB_SWAP_RGB;
	pinfo.mipi.data_lane0 = TRUE;
	pinfo.mipi.data_lane1 = TRUE;
	pinfo.mipi.data_lane2 = TRUE;
	pinfo.mipi.data_lane3 = TRUE;
	pinfo.mipi.t_clk_post = 0x25;//0x19;
	pinfo.mipi.t_clk_pre = 0x36;//0x37;
	pinfo.mipi.stream = 0; /* dma_p */
	pinfo.mipi.mdp_trigger = 0;
	pinfo.mipi.dma_trigger = DSI_CMD_TRIGGER_SW;
	pinfo.mipi.frame_rate = 60;
	pinfo.mipi.dsi_phy_db = &dsi_video_mode_phy_db_1080p;
	pinfo.mipi.tx_eot_append = TRUE;
	pinfo.mipi.esc_byte_ratio = 4;

	ret = mipi_orise_device_register(&pinfo, MIPI_DSI_PRIM,
						MIPI_DSI_PANEL_720P_PT);
	if (ret)
		printk(KERN_ERR "%s: failed to register device!\n", __func__);

	return ret;
}

module_init(mipi_video_orise_720p_pt_init);
