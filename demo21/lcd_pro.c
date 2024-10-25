#include "stdint.h"
#include "rtl876x_if8080.h"
#include "trace.h"
#include "rtl876x_aon_reg.h"
#include "indirect_access.h"
#include "rtl876x_gdma.h"
#include "rtl876x_rcc.h"
#include "rtl876x_nvic.h"
#include "platform_utils.h"
#include "wristband_gui.h"
#include "fmc_api.h"
#include "fmc_api_ext.h"
#include "app_port.h"
#include "gui_qspi_lcd_driver.h"

void lcd_power_on(void)
{
? ? AppLcdWriteCmd(0x11);
? ? platform_delay_ms(120);
? ? AppLcdWriteCmd(0x29);
? ? platform_delay_ms(20);
}

void lcd_power_off(void)
{
? ? AppLcdWriteCmd(0x28);
? ? platform_delay_ms(20);
? ? AppLcdWriteCmd(0x10);
? ? platform_delay_ms(100);
}

void lcd_set_window(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd)
{
? ? uint8_t data[4];
? ? xStart = xStart + 0;
? ? xEnd = xEnd + 0;
? ? yStart = yStart + 0;
? ? yEnd = yEnd + 0;

? ? data[0] = xStart >> 8;
? ? data[1] = xStart & 0xff;
? ? data[2] = xEnd >> 8;
? ? data[3] = xEnd & 0xff;
? ? AppLcdWriteData(0x2A, data, 4);

? ? data[0] = yStart >> 8;
? ? data[1] = yStart & 0xff;
? ? data[2] = yEnd >> 8;
? ? data[3] = yEnd & 0xff;
? ? AppLcdWriteData(0x2B, data, 4);

? ? uint32_t total_count = (xEnd - xStart + 1) * (yEnd - yStart + 1) * PIXEL_BYTES;
? ? rtl_qspi_enter_data_output_mode(total_count);
}

void lcd_tft_init(void)
{
? ? uint8_t data[40] = {0};

? ? data[0] = 0x08;
? ? AppLcdWriteData(0xF0, data, 1);

? ? data[0] = 0x08;
? ? AppLcdWriteData(0xF2, data, 1);

? ? data[0] = 0x51;
? ? AppLcdWriteData(0x9B, data, 1);

? ? data[0] = 0x53;
? ? AppLcdWriteData(0x86, data, 1);

? ? data[0] = 0x80;
? ? AppLcdWriteData(0xF2, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xF0, data, 1);

? ? data[0] = 0x01;
? ? AppLcdWriteData(0xF0, data, 1);

? ? data[0] = 0x01;
? ? AppLcdWriteData(0xF1, data, 1);

? ? data[0] = 0x56;
? ? AppLcdWriteData(0xB0, data, 1);

? ? data[0] = 0x4D;
? ? AppLcdWriteData(0xB1, data, 1);

? ? data[0] = 0x24;
? ? AppLcdWriteData(0xB2, data, 1);

? ? data[0] = 0x66;
? ? AppLcdWriteData(0xB4, data, 1);

? ? data[0] = 0x44;
? ? AppLcdWriteData(0xB5, data, 1);

? ? data[0] = 0x8B;
? ? AppLcdWriteData(0xB6, data, 1);

? ? data[0] = 0x40;
? ? AppLcdWriteData(0xB7, data, 1);

? ? data[0] = 0x05;
? ? AppLcdWriteData(0xB8, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xBA, data, 1);

? ? data[0] = 0x08;
? ? AppLcdWriteData(0xBB, data, 1);

? ? data[0] = 0x08;
? ? AppLcdWriteData(0xBC, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xBD, data, 1);

? ? data[0] = 0x80;
? ? AppLcdWriteData(0xC0, data, 1);

? ? data[0] = 0x08;
? ? AppLcdWriteData(0xC1, data, 1);

? ? data[0] = 0x57;
? ? AppLcdWriteData(0xC2, data, 1);

? ? data[0] = 0x00;
? ? data[1] = 0xA0;
? ? AppLcdWriteData(0x44, data, 2);

? ? data[0] = 0x80;
? ? AppLcdWriteData(0xC3, data, 1);

? ? data[0] = 0x08;
? ? AppLcdWriteData(0xC4, data, 1);

? ? data[0] = 0x57;
? ? AppLcdWriteData(0xC5, data, 1);

? ? data[0] = 0xA9;
? ? AppLcdWriteData(0xC6, data, 1);

? ? data[0] = 0x41;
? ? AppLcdWriteData(0xC7, data, 1);

? ? data[0] = 0x51;
? ? AppLcdWriteData(0xC8, data, 1);

? ? data[0] = 0xA9;
? ? AppLcdWriteData(0xC9, data, 1);

? ? data[0] = 0x41;
? ? AppLcdWriteData(0xCA, data, 1);

? ? data[0] = 0x51;
? ? AppLcdWriteData(0xCB, data, 1);

? ? data[0] = 0xD1;
? ? AppLcdWriteData(0xD0, data, 1);

? ? data[0] = 0x40;
? ? AppLcdWriteData(0xD1, data, 1);

? ? data[0] = 0x82;
? ? AppLcdWriteData(0xD2, data, 1);

? ? data[0] = 0x00;
? ? data[1] = 0xA5;
? ? AppLcdWriteData(0xF5, data, 2);

? ? data[0] = 0x49;
? ? AppLcdWriteData(0xDD, data, 1);

? ? data[0] = 0x49;
? ? AppLcdWriteData(0xDE, data, 1);

? ? data[0] = 0x10;
? ? AppLcdWriteData(0xF1, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xF0, data, 1);

? ? data[0] = 0x02;
? ? AppLcdWriteData(0xF0, data, 1);

? ? data[0] = 0xF0;
? ? data[1] = 0x0A;
? ? data[2] = 0x11;
? ? data[3] = 0x0C;
? ? data[4] = 0x0B;
? ? data[5] = 0x08;
? ? data[6] = 0x3A;
? ? data[7] = 0x54;
? ? data[8] = 0x51;
? ? data[9] = 0x29;
? ? data[10] = 0x16;
? ? data[11] = 0x15;
? ? data[12] = 0x31;
? ? data[13] = 0x34;
? ? AppLcdWriteData(0xE0, data, 14);

? ? data[0] = 0xF0;
? ? data[1] = 0x0A;
? ? data[2] = 0x11;
? ? data[3] = 0x0B;
? ? data[4] = 0x0A;
? ? data[5] = 0x07;
? ? data[6] = 0x39;
? ? data[7] = 0x43;
? ? data[8] = 0x4E;
? ? data[9] = 0x09;
? ? data[10] = 0x15;
? ? data[11] = 0x15;
? ? data[12] = 0x2E;
? ? data[13] = 0x34;
? ? AppLcdWriteData(0xE1, data, 14);

? ? data[0] = 0x10;
? ? AppLcdWriteData(0xF0, data, 1);

? ? data[0] = 0x10;
? ? AppLcdWriteData(0xF3, data, 1);

? ? data[0] = 0x08;
? ? AppLcdWriteData(0xE0, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xE1, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0xE2, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xE3, data, 1);

? ? data[0] = 0xE0;
? ? AppLcdWriteData(0xE4, data, 1);

? ? data[0] = 0x06;
? ? AppLcdWriteData(0xE5, data, 1);

? ? data[0] = 0x21;
? ? AppLcdWriteData(0xE6, data, 1);

? ? data[0] = 0x10;
? ? AppLcdWriteData(0xE7, data, 1);

? ? data[0] = 0x8A;
? ? AppLcdWriteData(0xE8, data, 1);

? ? data[0] = 0x82;
? ? AppLcdWriteData(0xE9, data, 1);

? ? data[0] = 0xE4;
? ? AppLcdWriteData(0xEA, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xEB, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xEC, data, 1);

? ? data[0] = 0x14;
? ? AppLcdWriteData(0xED, data, 1);

? ? data[0] = 0xFF;
? ? AppLcdWriteData(0xEE, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xEF, data, 1);

? ? data[0] = 0xFF;
? ? AppLcdWriteData(0xF8, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xF9, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xFA, data, 1);

? ? data[0] = 0x30;
? ? AppLcdWriteData(0xFB, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xFC, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xFD, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xFE, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xFF, data, 1);

? ? data[0] = 0x50;
? ? AppLcdWriteData(0x60, data, 1);

? ? data[0] = 0x02;
? ? AppLcdWriteData(0x61, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0x62, data, 1);

? ? data[0] = 0x50;
? ? AppLcdWriteData(0x63, data, 1);

? ? data[0] = 0x04;
? ? AppLcdWriteData(0x64, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0x65, data, 1);

? ? data[0] = 0x53;
? ? AppLcdWriteData(0x66, data, 1);

? ? data[0] = 0x08;
? ? AppLcdWriteData(0x67, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0x68, data, 1);

? ? data[0] = 0x53;
? ? AppLcdWriteData(0x69, data, 1);

? ? data[0] = 0x0A;
? ? AppLcdWriteData(0x6A, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0x6B, data, 1);

? ? data[0] = 0x50;
? ? AppLcdWriteData(0x70, data, 1);

? ? data[0] = 0x01;
? ? AppLcdWriteData(0x71, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0x72, data, 1);

? ? data[0] = 0x50;
? ? AppLcdWriteData(0x73, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0x74, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0x75, data, 1);

? ? data[0] = 0x53;
? ? AppLcdWriteData(0x76, data, 1);

? ? data[0] = 0x07;
? ? AppLcdWriteData(0x77, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0x78, data, 1);

? ? data[0] = 0x53;
? ? AppLcdWriteData(0x79, data, 1);

? ? data[0] = 0x09;
? ? AppLcdWriteData(0x7A, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0x7B, data, 1);

? ? data[0] = 0x58;
? ? AppLcdWriteData(0x80, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x81, data, 1);

? ? data[0] = 0x04;
? ? AppLcdWriteData(0x82, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0x83, data, 1);

? ? data[0] = 0x0C;
? ? AppLcdWriteData(0x84, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x85, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x86, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x87, data, 1);

? ? data[0] = 0x58;
? ? AppLcdWriteData(0x88, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x89, data, 1);

? ? data[0] = 0x06;
? ? AppLcdWriteData(0x8A, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0x8B, data, 1);

? ? data[0] = 0x0E;
? ? AppLcdWriteData(0x8C, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x8D, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x8E, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x8F, data, 1);

? ? data[0] = 0x58;
? ? AppLcdWriteData(0x90, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x91, data, 1);

? ? data[0] = 0x08;
? ? AppLcdWriteData(0x92, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0x93, data, 1);

? ? data[0] = 0x10;
? ? AppLcdWriteData(0x94, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x95, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x96, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x97, data, 1);

? ? data[0] = 0x58;
? ? AppLcdWriteData(0x98, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x99, data, 1);

? ? data[0] = 0x0A;
? ? AppLcdWriteData(0x9A, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0x9B, data, 1);

? ? data[0] = 0x12;
? ? AppLcdWriteData(0x9C, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x9D, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x9E, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x9F, data, 1);

? ? data[0] = 0x58;
? ? AppLcdWriteData(0xA0, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xA1, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0xA2, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0xA4, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xA5, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xA6, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xA7, data, 1);

? ? data[0] = 0x58;
? ? AppLcdWriteData(0xA8, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xA9, data, 1);

? ? data[0] = 0x05;
? ? AppLcdWriteData(0xAA, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0xAB, data, 1);

? ? data[0] = 0x0D;
? ? AppLcdWriteData(0xAC, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xAD, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xAE, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xAF, data, 1);

? ? data[0] = 0x58;
? ? AppLcdWriteData(0xB0, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xB1, data, 1);

? ? data[0] = 0x07;
? ? AppLcdWriteData(0xB2, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0xB3, data, 1);

? ? data[0] = 0x0F;
? ? AppLcdWriteData(0xB4, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xB5, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xB6, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xB7, data, 1);

? ? data[0] = 0x58;
? ? AppLcdWriteData(0xB8, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xB9, data, 1);

? ? data[0] = 0x09;
? ? AppLcdWriteData(0xBA, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0xBB, data, 1);

? ? data[0] = 0x11;
? ? AppLcdWriteData(0xBC, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xBD, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xBE, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xBF, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0xC0, data, 1);

? ? data[0] = 0x12;
? ? AppLcdWriteData(0xC1, data, 1);

? ? data[0] = 0xAA;
? ? AppLcdWriteData(0xC2, data, 1);

? ? data[0] = 0x30;
? ? AppLcdWriteData(0xC3, data, 1);

? ? data[0] = 0x21;
? ? AppLcdWriteData(0xC4, data, 1);

? ? data[0] = 0xBB;
? ? AppLcdWriteData(0xC5, data, 1);

? ? data[0] = 0x54;
? ? AppLcdWriteData(0xC6, data, 1);

? ? data[0] = 0x45;
? ? AppLcdWriteData(0xC7, data, 1);

? ? data[0] = 0x76;
? ? AppLcdWriteData(0xC8, data, 1);

? ? data[0] = 0x67;
? ? AppLcdWriteData(0xC9, data, 1);

? ? data[0] = 0x03;
? ? AppLcdWriteData(0xD0, data, 1);

? ? data[0] = 0x12;
? ? AppLcdWriteData(0xD1, data, 1);

? ? data[0] = 0xAA;
? ? AppLcdWriteData(0xD2, data, 1);

? ? data[0] = 0x30;
? ? AppLcdWriteData(0xD3, data, 1);

? ? data[0] = 0x21;
? ? AppLcdWriteData(0xD4, data, 1);

? ? data[0] = 0xBB;
? ? AppLcdWriteData(0xD5, data, 1);

? ? data[0] = 0x54;
? ? AppLcdWriteData(0xD6, data, 1);

? ? data[0] = 0x45;
? ? AppLcdWriteData(0xD7, data, 1);

? ? data[0] = 0x76;
? ? AppLcdWriteData(0xD8, data, 1);

? ? data[0] = 0x67;
? ? AppLcdWriteData(0xD9, data, 1);

? ? data[0] = 0x01;
? ? AppLcdWriteData(0xF3, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xF0, data, 1);

? ? data[0] = 0x01;
? ? AppLcdWriteData(0xF0, data, 1);

? ? data[0] = 0x01;
? ? AppLcdWriteData(0xF1, data, 1);

? ? data[0] = 0x0B;
? ? AppLcdWriteData(0xA0, data, 1);

? ? data[0] = 0x2A;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x2B;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x2C;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x2D;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x2E;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x2F;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x30;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x31;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x32;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x33;
? ? AppLcdWriteData(0xA3, data, 1);

? ? data[0] = 0xC3;
? ? AppLcdWriteData(0xA5, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x09;
? ? AppLcdWriteData(0xA0, data, 1);

? ? data[0] = 0x10;
? ? AppLcdWriteData(0xF1, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0xF0, data, 1);

? ? data[0] = 0x00;
? ? data[1] = 0x00;
? ? data[2] = 0x01;
? ? data[3] = 0x3F;
? ? AppLcdWriteData(0x2A, data, 4);

? ? data[0] = 0x01;
? ? data[1] = 0x81;
? ? data[2] = 0x01;
? ? data[3] = 0x81;
? ? AppLcdWriteData(0x2B, data, 4);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x4D, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x4E, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x4F, data, 1);

? ? data[0] = 0x01;
? ? AppLcdWriteData(0x4C, data, 1);

? ? platform_delay_ms(1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x4C, data, 1);

? ? data[0] = 0x00;
? ? data[1] = 0x00;
? ? data[2] = 0x01;
? ? data[3] = 0x3F;
? ? AppLcdWriteData(0x2A, data, 4);

? ? data[0] = 0x00;
? ? data[1] = 0x00;
? ? data[2] = 0x01;
? ? data[3] = 0x80;
? ? AppLcdWriteData(0x2B, data, 4);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x21, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x35, data, 1);

? ? data[0] = 0x55;
? ? AppLcdWriteData(0x3A, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x11, data, 1);

? ? data[0] = 0x00;
? ? AppLcdWriteData(0x29, data, 1);

? ? platform_delay_ms(20);
}

