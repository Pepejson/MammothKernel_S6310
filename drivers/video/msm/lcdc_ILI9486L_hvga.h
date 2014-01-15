#ifndef __LCDC_ILI9486L_HVGA_H__
#define __LCDC_ILI9486L_HVGA_H__

struct spi_cmd_desc {
	int dlen;
	char *payload;
	int wait;
};

struct disp_state_type {
	boolean disp_initialized;
	boolean display_on;
	boolean disp_powered_up;
};

static char power_setting_seq1[3] = {
	0xF9,
	0x00, 0x08
};

static char power_setting_seq2[10] = {
	0xF2,
	0x18, 0xA3, 0x12, 0x02, 0xB2, 0x12, 0xFF, 0x10, 0x00
};

static char power_setting_seq3[4] = {
	0xF8,
	0x21, 0x07, 0x02
};

static char power_setting_seq4[3] = {
	0xC0,
	0x07, 0x07
};

static char power_setting_seq5[2] = {
	0xC1,
	0x45
};

static char power_setting_seq6[2] = {
	0xC2,
	0x22
};

static char power_setting_seq7[5] = {
	0x2A,
	0x00, 0x00, 0x01, 0x3F
};

static char power_setting_seq8[5] = {
	0x2B,
	0x00, 0x00, 0x01, 0xDF
};

static char power_setting_seq9[3] = {
	0xB1,
	0xB0, 0x11
};

static char power_setting_seq10[2] = {
	0xB4,
	0x02
};

static char power_setting_seq11[5] = {
	0xB5,
	0x08, 0x0C, 0x10, 0x0A
};

static char power_setting_seq12[4] = {
	0xB6,
	0x30, 0x42, 0x3B
};

static char power_setting_seq13[2] = {
	0xB7,
	0x07
};

static char power_setting_seq14[6] = {
	0xF4,
	0x00, 0x00, 0x08, 0x91, 0x04
};

static char power_setting_seq15[2] = {
	0x36,
	0x08
};

static char power_setting_seq16[2] = {
	0x3A,
	0x66
};

static char power_setting_seq17[16] = {
	0xE0,
	0x01, 0x18, 0x15, 0x0A, 0x0D, 0x08, 0x44, 0x43, 0x35, 0x01, 0x0C, 0x00, 0x11, 0x0A, 0x0F
};

static char power_setting_seq18[16] = {
	0xE1,
	0x0F, 0x2A, 0x23, 0x07, 0x0B, 0x04, 0x42, 0x42, 0x31, 0x04, 0x0E, 0x02, 0x1F, 0x1C, 0x01
};

static char power_setting_seq19[17] = {
	0xE2,
	0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x19, 0x09, 0x09,
	0x09
};

static char power_setting_seq20[65] = {
	0xE3,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x1D, 0x2D, 0x2D, 0x2D, 0x2C, 0x4C,
	0x4D, 0x4D, 0x5D, 0x4D, 0x4E, 0x4D, 0x4D, 0x4D, 0x4D, 0x4D, 0x3C, 0x3C, 0x3C, 0x4B, 0x4B,
	0x4A, 0x3B, 0x3B, 0x43, 0x33, 0x33, 0x33, 0xB3, 0xB3, 0xA3, 0x93, 0x94, 0x84, 0x74, 0x54,
	0x44, 0x33, 0x13, 0x24,    
};


static char sleep_in_seq[1] = { 0x10 };
static char sleep_out_seq[1] = { 0x11 };
static char disp_on_seq[1] = { 0x29 };
static char disp_off_seq[1] = { 0x28 };
static char sw_reset_seq[1] = { 0x01 };


static struct spi_cmd_desc display_on_cmds[] = {
	{sizeof(power_setting_seq1), power_setting_seq1, 0},
	{sizeof(power_setting_seq2), power_setting_seq2, 0},
	{sizeof(power_setting_seq3), power_setting_seq3, 0},
	{sizeof(power_setting_seq4), power_setting_seq4, 0},
	{sizeof(power_setting_seq5), power_setting_seq5, 0},
	{sizeof(power_setting_seq6), power_setting_seq6, 0},
	{sizeof(power_setting_seq7), power_setting_seq7, 0},
	{sizeof(power_setting_seq8), power_setting_seq8, 0},
	{sizeof(power_setting_seq9), power_setting_seq9, 0},
	{sizeof(power_setting_seq10), power_setting_seq10, 0},
	{sizeof(power_setting_seq11), power_setting_seq11, 0},
	{sizeof(power_setting_seq12), power_setting_seq12, 0},
	{sizeof(power_setting_seq13), power_setting_seq13, 0},
	{sizeof(power_setting_seq14), power_setting_seq14, 0},
	{sizeof(power_setting_seq15), power_setting_seq15, 0},
	{sizeof(power_setting_seq16), power_setting_seq16, 0},
	{sizeof(power_setting_seq17), power_setting_seq17, 0},
	{sizeof(power_setting_seq18), power_setting_seq18, 0},
	{sizeof(power_setting_seq19), power_setting_seq19, 0},
	{sizeof(power_setting_seq20), power_setting_seq20, 0},

	{sizeof(sleep_out_seq), sleep_out_seq, 120},
	{sizeof(disp_on_seq), disp_on_seq, 200},
};

static struct spi_cmd_desc display_off_cmds[] = {
	{sizeof(disp_off_seq), disp_off_seq, 10},
	{sizeof(sleep_in_seq), sleep_in_seq, 120},
};

static struct spi_cmd_desc sw_rdy_cmds[] = {
	{sizeof(sw_reset_seq), sw_reset_seq, 0},
};

#endif

