#include "moy.h"
#include "app_drv_lcd.h"
#include "app_drv_light.h"
#include "app_gpio_config.h"
#include "sdk_app_include.h"
#include "app_app.h"

// clang-format off
static const u8 lcd_init_cmd[] ALIGNED(4) = {
#if 0
    _BEGIN_, 0x11,  _END_,
    _BEGIN_, REGFLAG_DELAY, 20, _END_,
    _BEGIN_, 0x2A, 0x00, 0x00, 0x01, 0xD1, _END_,
    _BEGIN_, 0x2B, 0x00, 0x00, 0x01, 0xD1, _END_,
    _BEGIN_, 0x44, 0x00, 0x0A, _END_,
    _BEGIN_, 0x35, 0x00, _END_,
    _BEGIN_, 0x53, 0x20, _END_,
    _BEGIN_, 0x3A, 0x55, _END_,
    _BEGIN_, REGFLAG_DELAY, 10, _END_,
    _BEGIN_, 0x29, _END_,
#else
    // _BEGIN_, 0xFE, 0x20, _END_,
    // _BEGIN_, 0xF4, 0x5A, _END_,
    // _BEGIN_, 0xF5, 0x59, _END_,
    // _BEGIN_, 0xFE, 0x40, _END_,
    // _BEGIN_, 0x61, 0x01, _END_,
    // _BEGIN_, 0x62, 0xDF, _END_,

    _BEGIN_, 0xFE, 0x20, _END_,
    _BEGIN_, 0xF4, 0x5A, _END_,
    _BEGIN_, 0xF5, 0x59, _END_,
    _BEGIN_, 0xFE, 0x40, _END_,
    _BEGIN_, 0x61, 0x03, _END_,
    _BEGIN_, 0x62, 0xBF, _END_,

    _BEGIN_, 0xFE, 0x00, _END_,                             // V8P
    _BEGIN_, 0xC4, 0x80, _END_,

    // _BEGIN_, REGFLAG_DELAY, 10, _END_,	// delay 120ms
    // _BEGIN_, 0xFE, 0x00, _END_,
    // _BEGIN_, 0xC4, 0x80, _END_,

    _BEGIN_, 0x3A, 0x55, _END_,
    _BEGIN_, 0x35, 0x00, _END_,
    _BEGIN_, 0x53, 0x20, _END_,
    _BEGIN_, 0x51, 0x00, _END_,
    _BEGIN_, 0x63, 0xFF, _END_,
    // _BEGIN_, 0x2A, 0x00, 0x06, 0x01, 0xD7, _END_,
    // _BEGIN_, 0x2B, 0x00, 0x00, 0x01, 0xD1, _END_,
    _BEGIN_, 0x11, _END_,
    _BEGIN_, REGFLAG_DELAY, 100, _END_,	// delay 120ms
    _BEGIN_, 0x29, _END_,

    // _BEGIN_, REGFLAG_DELAY, 20, _END_,	// delay 120ms

#endif
};

void AppDrvLcdCheckEsd()//检查LCD是否收到静电干扰，可能导致异常工作
{
    app_log("\n %s", __func__);
    bool isRet = false;
    uint8_t usRet1[4] = {0}, usRet2[4] = {0}, usRet3[4] = {0};
    lcd_read_cmd(0x0A, usRet1, 1);
    // app_log("---1111111111-------");
    // app_dump(usRet1, 1);
    if (usRet1[0] == 0x00)
    {
        isRet = true;
    }
    if (usRet1[0] == 0x9C)
    {
        isRet = true;
    }
    else
    {
        isRet = false;
        app_log("0x0A执行成功");
        AppLcdReset(); // 屏复位
        AppLcdInit();  // 屏初始化
        return;
    }

    lcd_read_cmd(0x0F, usRet2, 1);
    // app_log("---22222222222-------");
    // app_dump(usRet2, 1);
    if (usRet2[0] != 0xC0)
    {
        isRet = false;
        app_log("0x0F执行成功");
        AppLcdReset(); // 屏复位
        AppLcdInit();  // 屏初始化
        return;
    }
    else
    {
        isRet = true;
    }

    lcd_read_cmd(0x66, usRet3, 1);
    // app_log("---133333333333-------");
    // app_dump(usRet3, 1);
    if (usRet3[0] != 0x00)
    {
        isRet = false;
        app_log("0x66执行成功");
        AppLcdReset(); // 屏复位
        AppLcdInit();  // 屏初始化
        return;
    }
    else
    {
        isRet = true;
    }
}

void BandLcdOff(void)
{
    uint8_t cmd_data = 0x00;
    lcd_write_cmd(0x51, &cmd_data, 1);
    vLcdOff();
}

// clang-format on

void AppLcdInit()
{
    lcd_drv_cmd_list(lcd_init_cmd, sizeof(lcd_init_cmd) / sizeof(lcd_init_cmd[0]));
}

void vLcdOn()
{
    AppLcdReset();//复位
    AppLcdInit();//初始化
}

void vLcdOff()
{
#if LCD_IC_TYPE == LCD_IC_TYPE_FT2388
    lcd_set_param(CMD_MODE, CMD_8BIT);
#endif
    // AppDrvPinSet(GPIO_LCD_RESET);
    uint8_t cmd_data = 0x01;
    lcd_write_cmd(0x28, NULL, 0);//关闭显示
    AppTaskDelayMs(1); // delay 100ms
    lcd_write_cmd(0x10, NULL, 0);//进入低功耗模式
    AppTaskDelayMs(10);
    AppDrvPinClear(GPIO_LCD_EN);
    AppTaskDelayMs(30);
    AppDrvPinClear(GPIO_LCD_RESET);
    // AppTaskDelayMs(10);
    AppDrvPinClear(GPIO_LCD_CLK);
    AppDrvPinClear(GPIO_LCD_IO0);
    AppDrvPinClear(GPIO_LCD_IO1);
    AppDrvPinClear(GPIO_LCD_IO2);
    AppDrvPinClear(GPIO_LCD_IO3);
    AppDrvPinSet(GPIO_LCD_CS);
#ifdef GPIO_LCD_TE
    gpio_set_pull_up(GPIO_LCD_TE, 0);
    gpio_set_pull_down(GPIO_LCD_TE, 0);
    gpio_direction_input(GPIO_LCD_TE);
    gpio_set_die(GPIO_LCD_TE, 0);
#endif
#if LCD_IC_TYPE == LCD_IC_TYPE_FT2388
    lcd_set_param(CMD_MODE, CMD_24BIT);
#endif
}

void AppLcdReset()//GPIO控制：LCD的启用、复位、电源状态通过GPIO引脚控制
{
    AppDrvPinSet(GPIO_LCD_RESET);
    AppDrvPinSet(GPIO_LCD_EN);
    mdelay(30);
    AppDrvPinClear(GPIO_LCD_RESET);
    mdelay(60);
    AppDrvPinSet(GPIO_LCD_RESET);
    mdelay(120);
}

void vLcdLightOn()//调节亮度
{
    extern bool g_BandStart;
    if (!g_BandStart)
        return;
    app_log("\n %s", __func__);
    u8 usData[4] = {0};
    u16 usLvl = 0xD5 * AppDisplayBrightnessLvl() / BRIGHTNESS_MAX;
    usData[0] = usLvl & 0xFF;
    lcd_write_cmd(0x51, usData, 1);
}

REGISTER_LCD_DEVICE(SH8601Z) = {
    .logo = "SH8601Z",
    .row_addr_align = 2,
    .column_addr_align = 2,

    .lcd_cmd = (void *)&lcd_init_cmd,
    .cmd_cnt = sizeof(lcd_init_cmd) / sizeof(lcd_init_cmd[0]),
    .param = (void *)&sLcdParamInfo,

    .reset = NULL, // 没有特殊的复位操作，用内部普通复位函数即可
    .backlight_ctrl = NULL,
    .power_ctrl = AppDrvLightPinCtrl,//控制LCD电源的函数
    .entersleep = vLcdOff,//休眠
    .exitsleep = vLcdOn,//唤醒
};
