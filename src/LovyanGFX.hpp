/*----------------------------------------------------------------------------/
  Lovyan GFX library - ESP32 hardware SPI graphics library .  
  
    for Arduino and ESP-IDF  
  
Original Source:  
 https://github.com/lovyan03/LovyanGFX/  

Licence:  
 [BSD](https://github.com/lovyan03/LovyanGFX/blob/master/license.txt)  

Author:  
 [lovyan03](https://twitter.com/lovyan03)  

Contributors:  
 [ciniml](https://github.com/ciniml)  
 [mongonta0716](https://github.com/mongonta0716)  
 [tobozo](https://github.com/tobozo)  
/----------------------------------------------------------------------------*/
#ifndef LOVYANGFX_HPP_
#define LOVYANGFX_HPP_

#ifdef min
#undef min
#endif

#include "lgfx/lgfx_common.hpp"  // common include (always include)

#if !defined LOAD_GFXFF
#include "lgfx/gfxfont.hpp"      // GFX font support (optional)
#endif

#include "lgfx/utility/lgfx_tjpgd.h" // JPEG decode support (optional)
#include "lgfx/utility/lgfx_pngle.h" // PNG decode support (optional)

#include "lgfx/lgfx_sprite.hpp"   // sprite class (optional)

#include "lgfx/panel/panel_ILI9163.hpp"
#include "lgfx/panel/panel_ILI9341.hpp"   // M5Stack / ODROID-GO / ESP-WROVER-KIT4.1
#include "lgfx/panel/panel_SSD1351.hpp"
#include "lgfx/panel/panel_ST7789.hpp"    // LilyGO TTGO T-Watch
#include "lgfx/panel/panel_ST7735.hpp"    // M5StickC


#if defined (ESP32) || (CONFIG_IDF_TARGET_ESP32)

  #include "lgfx/platforms/lgfx_spi_esp32.hpp"

#elif defined (ESP8266)
// not implemented.
  #include "lgfx/platforms/lgfx_spi_esp8266.hpp"

#elif defined (STM32F7)
// not implemented.
  #include "lgfx/platforms/lgfx_spi_stm32_spi.hpp"

#elif defined (__AVR__)
// not implemented.
  #include "lgfx/platforms/lgfx_spi_avr.hpp"

#endif



namespace lgfx {

#if defined( ARDUINO_M5Stack_Core_ESP32 ) || defined( ARDUINO_M5STACK_FIRE ) // M5Stack

  typedef Panel_M5Stack Panel_default;
  struct LGFX_Config {
    static constexpr spi_host_device_t spi_host = VSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 23;
    static constexpr int spi_miso = 19;
    static constexpr int spi_sclk = 18;
  };

#elif defined( ARDUINO_M5Stick_C ) // M5Stick C

  typedef Panel_M5StickC Panel_default;
  struct LGFX_Config {
    static constexpr spi_host_device_t spi_host = VSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 15;
    static constexpr int spi_miso = 14;
    static constexpr int spi_sclk = 13;
  };

#elif defined( ARDUINO_ODROID_ESP32 ) // ODROID-GO

  typedef Panel_ODROID_GO Panel_default;
  struct LGFX_Config {
    static constexpr spi_host_device_t spi_host = VSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 23;
    static constexpr int spi_miso = 19;
    static constexpr int spi_sclk = 18;
  };

#elif defined( ARDUINO_TTGO_T1 ) // TTGO TS

  typedef Panel_TTGO_TS Panel_default;
  struct LGFX_Config {
    static constexpr spi_host_device_t spi_host = VSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 23;
    static constexpr int spi_miso = -1;
    static constexpr int spi_sclk =  5;
  };

#elif defined( ARDUINO_T ) // TTGO T-Watch

  typedef Panel_TTGO_TWatch Panel_default;
  struct LGFX_Config {
    static constexpr spi_host_device_t spi_host = HSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 19;
    static constexpr int spi_miso = -1;
    static constexpr int spi_sclk = 18;
  };

#elif defined( ARDUINO_D ) || defined( ARDUINO_DDUINO32_XS )

  typedef Panel_DDUINO32_XS Panel_default;
  struct LGFX_Config {
    static constexpr spi_host_device_t spi_host = VSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 26;
    static constexpr int spi_miso = -1;
    static constexpr int spi_sclk = 27;
  };

#elif defined( ARDUINO_LOLIN_D32_PRO ) // LoLin D32 Pro

  typedef Panel_LoLinD32 Panel_default;
  struct LGFX_Config {
    static constexpr spi_host_device_t spi_host = VSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 23;
    static constexpr int spi_miso = 19;
    static constexpr int spi_sclk = 18;
  };

#elif defined( ARDUINO_ESP32_DEV ) // ESP-WROVER-KIT

  // ESP-WROVER-KIT is available in two types of panels. (ILI9341 or ST7789)

  struct Panel_default : public lgfx::Panel_ILI9341 {
    Panel_default(void) {
      spi_3wire = false;
      spi_cs   = 22;
      spi_dc   = 21;
      gpio_rst = 18;
      gpio_bl  = 5;
      pwm_ch_bl = 7;
      freq_write = 40000000;
      freq_read  = 20000000;
      freq_fill  = 80000000;
      backlight_level = false;
    }
  };
  struct Panel_default2 : public lgfx::Panel_ST7789 {
    Panel_default2(void) {
      spi_3wire = false;
      spi_cs   = 22;
      spi_dc   = 21;
      gpio_rst = 18;
      gpio_bl  = 5;
      pwm_ch_bl = 7;
      freq_write = 80000000;
      freq_read  = 20000000;
      freq_fill  = 80000000;
      backlight_level = false;
    }
  };

  struct LGFX_Config {
    static constexpr spi_host_device_t spi_host = VSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 23;
    static constexpr int spi_miso = 25;
    static constexpr int spi_sclk = 19;
  };

#elif defined( ESP32 ) || ( CONFIG_IDF_TARGET_ESP32 ) // ESP-IDF ( or other panel )

  typedef Panel_M5Stack Panel_default;

  struct LGFX_Config {
    static constexpr spi_host_device_t spi_host = VSPI_HOST;
    static constexpr int dma_channel = 1;
    static constexpr int spi_mosi = 23;
    static constexpr int spi_miso = 19;
    static constexpr int spi_sclk = 18;
  };

#endif
}


class LGFX : public lgfx::LGFX_SPI<lgfx::LGFX_Config>
{
public:
  LGFX(void) : lgfx::LGFX_SPI<lgfx::LGFX_Config>()
  {
    static lgfx::Panel_default panel;

    setPanel(&panel);
  }

#if defined( ARDUINO_ESP32_DEV ) // ESP-WROVER-KIT

  void initPanel(void) override {
    if (!_panel) return;
    _panel->init();

    if (readPanelID() > 0) {  // check panel (ILI9341 or ST7789)
      static lgfx::Panel_default2 panel;
      setPanel(&panel);
      ESP_LOGI("LGFX", "[Autodetect] Using Panel_ST7789");
    } else {
      ESP_LOGI("LGFX", "[Autodetect] Using Panel_ILI9341");
    }
    lgfx::LGFX_SPI<lgfx::LGFX_Config>::initPanel();
  }
#endif

};


#endif
