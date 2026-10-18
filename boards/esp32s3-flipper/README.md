# ESP32-S3 N16R8 Flipper tự chế (Bruce)

Board Bruce tùy chỉnh cho **ESP32-S3-DevKitC-1 N16R8** + CC1101 + PN532 + màn TFT 1.44" ST7735 + microSD + IR + buzzer + 6 nút.
Env PlatformIO: `esp32s3-flipper`.

## Sơ đồ chân

| Module | Chân module | GPIO |
|---|---|---|
| SPI chung (TFT + CC1101 + microSD) | SCK / MOSI / MISO | 12 / 11 / 13 |
| TFT 1.44" ST7735 128×128 | CS / DC (A0) | 5 / 7 (RST và LED nối 3V3) |
| CC1101 | CSN / GDO0 | 10 / 4 (GDO2 bỏ trống) |
| microSD | CS | 14 |
| I2C (PN532) | SDA / SCL | 8 / 9 |
| PN532 (gạt sang I2C) | địa chỉ | 0x24 |
| IR TX (qua 2N2222) | | 1 |
| IR RX (IR1838) | | 2 |
| Buzzer (qua 2N2222) | | 6 |
| Nút | UP / DOWN / LEFT / RIGHT / OK / BACK | 15 / 16 / 17 / 18 / 21 / 47 |

Nút kéo lên nội bộ: một chân nối GPIO, một chân nối GND.
Mặc định của `ESP-General` đặt GDO0 ở GPIO9, trùng I2C SCL nên ở đây đã đổi sang GPIO4.

## Module nối sau (đã chia sẵn chân)

| Module | Chân | Cách bật |
|---|---|---|
| NRF24L01 | CE = 38, CSN = 39, dùng chung SPI 12/11/13 | đã bật sẵn, chỉ cần cắm |
| GPS | TX/RX = 43/44 (UART) | cắm là dùng |

GPIO 40, 41, 42 còn trống. Chân đo pin (GPIO7) đã nhường cho TFT DC nên chưa có đo pin.

## Nguồn

Pin Li-Po 3.7V → TP4056 (có bảo vệ pin) → công tắc → MT3608 chỉnh **5.0V** (đo bằng đồng hồ trước khi cắm ESP) → chân 5V ESP.
Rail 3V3 của ESP cấp cho TFT (VCC, RST, LED), CC1101, PN532, IR1838. Không cấp 5V cho CC1101.
Tắt công tắc pin khi cắm USB nạp code.

## Build

Push code lên GitHub, workflow `Build ESP32-S3 Flipper` tự chạy. Tải file ở mục **Artifacts**:

- `Bruce-esp32s3-flipper.bin`: bản gộp (merged), nạp ở địa chỉ **0x0**
- `bootloader.bin` (0x0), `partitions.bin` (0x8000), `firmware.bin` (0x10000): nạp riêng nếu cần

Build thủ công: `pio run -e esp32s3-flipper`

## Nạp bằng điện thoại

Dùng app ESP32 flasher qua cáp OTG, chọn chip **ESP32-S3**, nạp file merged ở 0x0.
Nếu không thấy board: giữ BOOT, bấm RST rồi thả ra.

## Lưu ý

- Chưa kiểm chứng trên phần cứng thật, có thể phải chỉnh chân.
- Chưa có mạch đo pin nên phần trăm pin hiển thị 0. Đèn nền TFT nối thẳng 3V3 nên luôn sáng, không chỉnh được độ sáng.
- Màn lệch hình hoặc sai màu: đổi `-DST7735_GREENTAB3` trong file ini thành `GREENTAB`, `GREENTAB2` hoặc `REDTAB` tùy lô màn (và thử bỏ `-DTFT_RGB_ORDER=TFT_BGR`).
- Màn dùng chung bus SPI với CC1101, microSD, NRF24, mỗi module có chân CS riêng.
- Tránh GPIO 26-37 (flash/PSRAM octal) và 0, 3, 45, 46 (strapping).
