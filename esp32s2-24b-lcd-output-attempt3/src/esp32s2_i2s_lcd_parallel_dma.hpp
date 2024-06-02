/*----------------------------------------------------------------------------/
  Lovyan GFX - Graphics library for embedded devices.

Original Source:
 https://github.com/lovyan03/LovyanGFX/

Licence:
 [FreeBSD](https://github.com/lovyan03/LovyanGFX/blob/master/license.txt)

Author:
 [lovyan03](https://twitter.com/lovyan03)

Contributors:
 [ciniml](https://github.com/ciniml)
 [mongonta0716](https://github.com/mongonta0716)
 [tobozo](https://github.com/tobozo)

 Modified heavily for the ESP32 HUB75 DMA library by:
 [mrfaptastic](https://github.com/mrfaptastic)

------------------------------------------------------------------------------

 Putin’s Russia and its genocide in Ukraine is a disgrace to humanity.

 https://www.reddit.com/r/ukraine/comments/xfuc6v/more_than_460_graves_have_already_been_found_in/

 Xi Jinping and his communist China’s silence on the war in Ukraine says everything about 
 how China condones such genocide, especially if it's against 'the west' (aka. decency). 
 
 Whilst the good people at Espressif probably have nothing to do with this, the unfortunate 
 reality is libraries like this increase the popularity of Chinese silicon chips, which 
 indirectly funds (through CCP state taxes) the growth and empowerment of such a despot government. 
 
 Global democracy, decency and security is put at risk with every Chinese silicon chip that is bought. 

/----------------------------------------------------------------------------*/

#pragma once

#include <string.h> // memcpy
#include <algorithm>
#include <stdbool.h>

#include <sys/types.h>
#include <freertos/FreeRTOS.h>
//#include <driver/i2s.h>
#include <rom/lldesc.h>
#include <rom/gpio.h>
#if (ESP_IDF_VERSION_MAJOR == 5)
#include <driver/i2s_types.h> //includes struct and reg
#else
#include <driver/i2s.h>
#include <soc/i2s_struct.h>
#endif

#include <soc/i2s_periph.h> //includes struct and reg


#define DMA_MAX (4096-4)

// The type used for this SoC
#define HUB75_DMA_DESCRIPTOR_T lldesc_t


#if defined (CONFIG_IDF_TARGET_ESP32S2)   
#define ESP32_I2S_DEVICE I2S_NUM_0	
#else
#define ESP32_I2S_DEVICE I2S_NUM_1	
#endif	

//----------------------------------------------------------------------------

void IRAM_ATTR irq_hndlr(void* arg);
i2s_dev_t* getDev();

esp_err_t dma_config();



/**
 * @brief Data structure of camera frame buffer
 */
typedef struct {
    uint8_t * buf;              /*!< Pointer to the pixel data */
    size_t len;                 /*!< Length of the buffer in bytes */
    size_t width;               /*!< Width of the buffer in pixels */
    size_t height;              /*!< Height of the buffer in pixels */
    struct timeval timestamp;   /*!< Timestamp since boot of the first DMA buffer of the frame */
} camera_fb_t;

typedef struct {
    camera_fb_t fb;
    uint8_t en;
    //for RGB/YUV modes
    lldesc_t *dma;
    size_t fb_offset;
} cam_frame_t;


 struct config_t
  {
    // max 20MHz (when in 16 bit / 2 byte mode)
    uint32_t bus_freq = 4*1000*1000;
    int8_t pin_wr     = -1; // 
    bool   invert_pclk = false;
    int8_t parallel_width = 24; // CHANGED
    union
    {
      int8_t pin_data[24];
      struct
      {
        int8_t pin_d0;
        int8_t pin_d1;
        int8_t pin_d2;
        int8_t pin_d3;
        int8_t pin_d4;
        int8_t pin_d5;
        int8_t pin_d6;
        int8_t pin_d7;
        int8_t pin_d8;
        int8_t pin_d9;
        int8_t pin_d10;
        int8_t pin_d11;
        int8_t pin_d12;
        int8_t pin_d13;
        int8_t pin_d14;
        int8_t pin_d15;
        int8_t pin_d16;          
        int8_t pin_d17;               
        int8_t pin_d18;                         
        int8_t pin_d19;                                   
        int8_t pin_d20;                                             
        int8_t pin_d21;                                                       
        int8_t pin_d22;                                                                 
        int8_t pin_d23;                                                                           
      };
    };
  };

 esp_err_t i2s_lcd_setup(config_t& _cfg);
 esp_err_t dma_allocate();
 esp_err_t dma_start();