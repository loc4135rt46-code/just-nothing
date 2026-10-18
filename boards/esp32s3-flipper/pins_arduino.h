#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

// ESP32-S3-DevKitC-1 N16R8 (Flipper tu che) - theo so do dau day trong README.md
// Tranh GPIO 26-37 (flash/PSRAM octal) va GPIO 0, 3, 45, 46 (strapping)

#define USB_VID 0x303a
#define USB_PID 0x1001

static const uint8_t TX = 43;
static const uint8_t RX = 44;

// ---------- I2C: PN532 (0x24) ----------
#define GROVE_SDA 8
#define GROVE_SCL 9
#define SYS_I2C_SDA 8
#define SYS_I2C_SCL 9
static const uint8_t SDA = GROVE_SDA;
static const uint8_t SCL = GROVE_SCL;

// ---------- SPI chung: TFT + CC1101 + microSD + NRF24 ----------
#define SPI_SCK_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SS_PIN 10
static const uint8_t SS = SPI_SS_PIN;
static const uint8_t MOSI = SPI_MOSI_PIN;
static const uint8_t MISO = SPI_MISO_PIN;
static const uint8_t SCK = SPI_SCK_PIN;

// ---------- CC1101 433MHz ----------
#define USE_CC1101_VIA_SPI
#define CC1101_SS_PIN 10
#define CC1101_GDO0_PIN 4
#define CC1101_MOSI_PIN SPI_MOSI_PIN
#define CC1101_SCK_PIN SPI_SCK_PIN
#define CC1101_MISO_PIN SPI_MISO_PIN

// ---------- microSD ----------
#define SDCARD_CS 14
#define SDCARD_SCK SPI_SCK_PIN
#define SDCARD_MISO SPI_MISO_PIN
#define SDCARD_MOSI SPI_MOSI_PIN

// ---------- Hong ngoai ----------
#define TXLED 1 // IR TX (qua transistor 2N2222)
#define RXLED 2 // IR RX (IR1838)
#define LED_ON HIGH
#define LED_OFF LOW

// ---------- Buzzer ----------
#define BUZZ_PIN 6

// ---------- 6 nut bam (keo len noi bo, nhan = LOW) ----------
#define HAS_5_BUTTONS
#define UP_BTN 15
#define DW_BTN 16
#define L_BTN 17
#define R_BTN 18
#define SEL_BTN 21
#define BK_BTN 47
#define BTN_ACT LOW
#define BTN_ALIAS "\"OK\""

// ---------- Man hinh TFT 1.44" ST7735 128x128 (SPI, TFT_eSPI) ----------
// Cac co TFT_* (chan, driver, kich thuoc) dat trong esp32s3-flipper.ini.
// Dung chung SPI 11/12/13 voi CC1101, microSD, NRF24. Rieng CS = GPIO5, DC (A0) = GPIO7.
// Chan RST va LED (den nen) cua man noi thang 3V3 nen khong dung GPIO.
#define HAS_SCREEN 1
#define TFT_BUSY_PIN -1
#define ROTATION 0
#define MINBRIGHT (uint8_t)1

// FP/FM/FG (co chu) dat o build_src_flags trong esp32s3-flipper.ini, KHONG define o day
// vi macro FP se pha thu vien FastLED (template <typename FP>).

// ======================= MODULE NOI SAU (da chia san chan) =======================
// NRF24L01 2.4GHz: dung chung SPI 11/12/13, chi them CE + CSN. Da bat san.
#define USE_NRF24_VIA_SPI
#define NRF24_CE_PIN 38
#define NRF24_SS_PIN 39
#define NRF24_MOSI_PIN SPI_MOSI_PIN
#define NRF24_SCK_PIN SPI_SCK_PIN
#define NRF24_MISO_PIN SPI_MISO_PIN

// GPS (UART): TX/RX = GPIO43/44, da khai bao o phan SERIAL ben duoi. Cam GPS la dung.

// Do pin: bo (GPIO7 da dung cho TFT DC).


// GPIO40/41/42 chua dung, con trong cho nhu cau khac (FM, mic...).
// =================================================================================

#define SERIAL_TX TX
#define SERIAL_RX RX
#define BAD_RX SERIAL_RX
#define BAD_TX SERIAL_TX
#define GPS_SERIAL_TX SERIAL_TX
#define GPS_SERIAL_RX SERIAL_RX
#define USB_as_HID 1

#endif /* Pins_Arduino_h */
