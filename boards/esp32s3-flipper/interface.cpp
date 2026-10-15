#include "core/powerSave.h"
#include <interface.h>

/***************************************************************************************
** Function name: _setup_gpio()
** Location: main.cpp
** Description:   initial setup for the device
***************************************************************************************/
void _setup_gpio() {
    pinMode(UP_BTN, INPUT_PULLUP);
    pinMode(DW_BTN, INPUT_PULLUP);
    pinMode(L_BTN, INPUT_PULLUP);
    pinMode(R_BTN, INPUT_PULLUP);
    pinMode(SEL_BTN, INPUT_PULLUP);
    pinMode(BK_BTN, INPUT_PULLUP);

    // Khoa CC1101 va SD de khong tranh bus SPI luc khoi dong
    pinMode(CC1101_SS_PIN, OUTPUT);
    digitalWrite(CC1101_SS_PIN, HIGH);
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);

    bruceConfigPins.rfModule = CC1101_SPI_MODULE;
    bruceConfigPins.rfidModule = PN532_I2C_MODULE;
    bruceConfigPins.irTx = TXLED;
    bruceConfigPins.irRx = RXLED;
}

/***************************************************************************************
** Function name: getBattery()
** Description:   Khong co mach do pin -> tra 0 (chua ho tro)
***************************************************************************************/
int getBattery() { return 0; }

bool isCharging() { return false; }

/*********************************************************************
** Function: setBrightness
** OLED khong co den nen -> bo trong
**********************************************************************/
void _setBrightness(uint8_t brightval) {}

/*********************************************************************
** Function: InputHandler
** Handles the variables PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
**********************************************************************/
void InputHandler(void) {
    static unsigned long tm = 0;
    if (millis() - tm < 200 && !LongPress) return;

    bool _u = digitalRead(UP_BTN);
    bool _d = digitalRead(DW_BTN);
    bool _l = digitalRead(L_BTN);
    bool _r = digitalRead(R_BTN);
    bool _s = digitalRead(SEL_BTN);
    bool _b = digitalRead(BK_BTN);

    if (!_s || !_u || !_d || !_r || !_l || !_b) {
        tm = millis();
        if (!wakeUpScreen()) AnyKeyPress = true;
        else return;
    }
    if (!_l) { PrevPress = true; }
    if (!_r) { NextPress = true; }
    if (!_u) {
        UpPress = true;
        PrevPagePress = true;
    }
    if (!_d) {
        DownPress = true;
        NextPagePress = true;
    }
    if (!_s) { SelPress = true; }
    if (!_b) { EscPress = true; }
}

/*********************************************************************
** Function: powerOff
** Deep sleep, danh thuc bang nut OK (GPIO21 la chan RTC)
**********************************************************************/
void powerOff() {
    esp_sleep_enable_ext0_wakeup((gpio_num_t)SEL_BTN, BTN_ACT);
    esp_deep_sleep_start();
}

/*********************************************************************
** Function: checkReboot
** Giu OK + BACK trong 3 giay de tat may
**********************************************************************/
void checkReboot() {
    int countDown = 0;
    if (digitalRead(SEL_BTN) == BTN_ACT && digitalRead(BK_BTN) == BTN_ACT) {
        uint32_t time_count = millis();
        while (digitalRead(SEL_BTN) == BTN_ACT && digitalRead(BK_BTN) == BTN_ACT) {
            if (millis() - time_count > 500) {
                if (countDown == 0) {
                    int textWidth = tft.textWidth("PWR OFF IN 3/3", 1);
                    tft.fillRect(tftWidth / 2 - textWidth / 2, 7, textWidth, 18, bruceConfig.bgColor);
                }
                tft.setTextSize(1);
                tft.setTextColor(bruceConfig.priColor, bruceConfig.bgColor);
                countDown = (millis() - time_count) / 1000 + 1;
                if (countDown < 4)
                    tft.drawCentreString("PWR OFF IN " + String(countDown) + "/3", tftWidth / 2, 12, 1);
                else {
                    tft.fillScreen(bruceConfig.bgColor);
                    while (digitalRead(SEL_BTN) == BTN_ACT || digitalRead(BK_BTN) == BTN_ACT);
                    delay(200);
                    powerOff();
                }
                delay(10);
            }
        }
        delay(30);
        if (millis() - time_count > 500) {
            tft.fillRect(0, 12, tftWidth, tft.fontHeight(1), bruceConfig.bgColor);
            drawStatusBar();
        }
    }
}
