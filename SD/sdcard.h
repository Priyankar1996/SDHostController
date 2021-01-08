/*
  This file holds the declarations of the SD card registers 
  and the function prototypes for emulation the SD card 
*/
#include<stdio.h>
#include<stdint.h>

//Physical layer specifications v 3.01 page 104
uint32_t OCR;

typedef struct cid_reg
{
uint8_t MID;      //127:120
uint16_t OID;     //119:104
char PNM[5];      //103:64
uint8_t PRV;      //63:56
uint32_t PSN;     //55:24
//23:20 bits are reserved
uint8_t MDT_y;    //19:12
uint8_t MDT_m;    //11:8 use only lower 4 bits
uint8_t crc;      //7:1 use only lower 7bits
//0th bit is unused
}cid_reg;

//CSD Version 2.0 (high capacity and extended cards)
typedef struct csd{ 
	uint8_t  csd_structure;
	uint8_t  taac;
	uint8_t  nsac;
	uint8_t  tran_speed;
	uint16_t ccc;
	//uint8_t  spec_vers;
	uint8_t  read_bl_len;
	uint8_t  read_bl_partial;
	uint8_t  write_blk_misalign;
	uint8_t  read_blk_misalign;
	uint8_t  dsr_imp;
	uint32_t c_size;
	uint8_t erase_blk_en;
	uint8_t  sector_size;
	uint8_t  wp_grp_size;
	uint8_t  wp_grp_enable;
	uint8_t  r2w_factor;
	uint8_t  write_bl_len;
	uint8_t  write_bl_partial;
	uint8_t  file_format_grp;
	uint8_t  copy;
	uint8_t  perm_write_protect;
	uint8_t  tmp_write_protect;
	uint8_t  file_format;
	uint8_t crc;
	/*uint8_t  vdd_r_curr_min;
	uint8_t  vdd_r_curr_max;
	uint8_t  vdd_w_curr_min;
	uint8_t  vdd_w_curr_max;
	uint8_t  c_size_mult;
	union {
		struct { // MMC system specification version 3.1 
			uint8_t  erase_grp_size;
			uint8_t  erase_grp_mult;
		} v31;
		struct { // MMC system specification version 2.2 
			uint8_t  erase_grp_size;
		} v22;
	} erase;

	uint8_t  default_ecc;

	uint8_t  ecc;*/
}csd;

uint16_t RCA;
uint16_t DSR;

typedef struct scr{
uint8_t SCR_structure;//use only lower 4 bits 63:60
uint8_t SD_spec;			//use only lower 4 bits 59:56
uint8_t DATA_STAT_AFTER_ERASE; //55:55
uint8_t SD_security;	//use only lower 3 bits 54:52
uint8_t SD_buswidth;	//use only lower 4 bits 51:48
uint8_t SD_spec3; //47:47
uint8_t ex_security;	//use only lower 4 bits 46:43
uint8_t cmd_support;	//use only lower 2 bits 33:32
}scr;

uint8_t flash_array[1024];//1 block or 1kByte
