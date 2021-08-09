
#pragma once
#include "FastLED.h" //to have the type CRGB

/*Definition des pixels*/
#define APA102 0
#define HD107 0
#define HD108 2
#define WS2811 4 

#ifndef PIXEL_TYPE
#define PIXEL_TYPE APA102
#endif

struct IndvBrightness{
  uint8_t bred;
  uint8_t bgreen;
  uint8_t bblue;
inline IndvBrightness() __attribute__((always_inline))
    {
    }
inline IndvBrightness( uint8_t ir, uint8_t ig, uint8_t ib)  __attribute__((always_inline))
        : bred(ir), bgreen(ig), bblue(ib)
    {
    }
    inline IndvBrightness( uint8_t ir)  __attribute__((always_inline))
        : bred(ir), bgreen(ir), bblue(ir)
    {
    }
     
};


struct PixelStruct{
    uint8_t block_size;
    uint8_t number_block;
    uint8_t block_order[20];
    uint8_t start_frame_size; //in block_size
    bool end_frame;
    
    uint8_t end_block_value;
    uint8_t dma_size;

inline PixelStruct(uint8_t blocksize,uint8_t numberblock,uint8_t *blockorder,uint8_t startframesize,bool endframe) __attribute__((always_inline)) 
    :block_size(blocksize),number_block(numberblock),start_frame_size(startframesize),end_frame(endframe)
{
    for(int i=0;i<numberblock;i++)
    {
        block_order[i]=blockorder[i];
    }
    dma_size=blocksize*numberblock*8*2; //each block is 8 bit *2 beause we're doing 16 // outputs
}

	inline PixelStruct() __attribute__((always_inline))
    {
    }

};


#if PIXEL_TYPE == WS2811

struct Pixel {
    union {
        uint8_t raw[3];
        struct 
        {
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            
        };
        
    };

    inline Pixel(uint8_t r, uint8_t g,uint8_t b) __attribute__((always_inline))
    :red(r),green(g),blue(b)
{
    //brigthness =0xE0 |(br&31);
}

	inline Pixel() __attribute__((always_inline))
    {

    }

       inline Pixel &operator= (const IndvBrightness& rhs) __attribute__((always_inline))
    {
         //brigthness =0xE0 |(rhs.bred&31);      
        return *this;
    }

inline Pixel &operator= (const CRGB& rhs) __attribute__((always_inline))
    {
        red = rhs.r;
        green = rhs.g;
        blue = rhs.b;
        return *this;
    }
   

inline Pixel (const Pixel& rhs) __attribute__((always_inline))
     {
         //brigthness=rhs.brigthness;
         red=rhs.red;
         green=rhs.green;
         blue=rhs.blue;
     }
     inline Pixel& operator= (const uint32_t colorcode) __attribute__((always_inline))
    {
        red = (colorcode >> 16) & 0xFF;
        green = (colorcode >>  8) & 0xFF;
        blue = (colorcode >>  0) & 0xFF;
        return *this;
    }
        

};


#define B0 1
#define B1 0
#define B2 2
#define B3 0
#define B4 0
#define B5 0
#define B6 0
#define B7 0
#define B8 0
#define B9 0
#define B10 0
#define B11 0
#define B12 0
#define B13 0
#define B14 0
#define B15 0
#define B16 0
#define B17 0
#define B18 0
#define B19 0

#define NUMBER_OF_BLOCK 3
#define START_FRAME_SIZE 3
#define END_FRAME 0


#endif

#if PIXEL_TYPE == APA102

struct Pixel {
    union {
        uint8_t raw[4];
        struct 
        {
            uint8_t brigthness;
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            
        };
        
    };

    inline Pixel(uint8_t br,uint8_t r, uint8_t g,uint8_t b) __attribute__((always_inline))
    :red(r),green(g),blue(b)
{
    brigthness =0xE0 |(br&31);
}

	inline Pixel() __attribute__((always_inline)):brigthness(0xff)
    {

    }

       inline Pixel &operator= (const IndvBrightness& rhs) __attribute__((always_inline))
    {
         brigthness =0xE0 |(rhs.bred&31);      
        return *this;
    }

inline Pixel &operator= (const CRGB& rhs) __attribute__((always_inline))
    {
        red = rhs.r;
        green = rhs.g;
        blue = rhs.b;
        return *this;
    }
   

inline Pixel (const Pixel& rhs) __attribute__((always_inline))
     {
         brigthness=rhs.brigthness;
         red=rhs.red;
         green=rhs.green;
         blue=rhs.blue;
     }
     inline Pixel& operator= (const uint32_t colorcode) __attribute__((always_inline))
    {
        red = (colorcode >> 16) & 0xFF;
        green = (colorcode >>  8) & 0xFF;
        blue = (colorcode >>  0) & 0xFF;
        return *this;
    }
        

};


#define B0 0
#define B1 3
#define B2 2
#define B3 1
#define B4 0
#define B5 0
#define B6 0
#define B7 0
#define B8 0
#define B9 0
#define B10 0
#define B11 0
#define B12 0
#define B13 0
#define B14 0
#define B15 0
#define B16 0
#define B17 0
#define B18 0
#define B19 0

#define NUMBER_OF_BLOCK 4
#define START_FRAME_SIZE 4
#define END_FRAME 1

//static uint8_t f7[4]={0,3,2,1}; //britghness blue green red
//static PixelStruct HD107=PixelStruct(1,4,f7,4,true); //4 blocks of 1*8bits
#endif
#if PIXEL_TYPE == HD108

struct Pixel {
    union {
        uint16_t raw[4];
        struct 
        {
            uint16_t brigthness;
            uint16_t red;
            uint16_t green;
            uint16_t blue;
            
        };
        
    };

inline Pixel(uint8_t br,uint16_t r, uint8_t bg,uint16_t g,uint8_t bb,uint16_t b) __attribute__((always_inline))
    :red(r),green(g),blue(b)
{
    brigthness =0x8000 | ((br&31)<<10)|((bg&31)<<5) |(bb&31);
}

	inline Pixel() __attribute__((always_inline))
    {
    }
     
     inline Pixel (const HD108Led& rhs) __attribute__((always_inline))
     {
         brigthness=rhs.brigthness;
         red=rhs.red;
         green=rhs.green;
         blue=rhs.blue;
     }

	inline Pixel &operator= (const CRGB& rhs) __attribute__((always_inline))
    {
        red = rhs.r;
        green = rhs.g;
        blue = rhs.b;
        return *this;
    }



    inline Pixel &operator= (const IndvBrightness& rhs) __attribute__((always_inline))
    {
        brigthness =0x8000 | ((rhs.bred&31)<<10)|((rhs.bgreen&31)<<5) |(rhs.bblue&31);      
        return *this;
    }
     inline Pixel& operator= (const uint32_t colorcode) __attribute__((always_inline))
    {
        red = (colorcode >> 16) & 0xFF;
        green = (colorcode >>  8) & 0xFF;
        blue = (colorcode >>  0) & 0xFF;
        return *this;
    }

    
};

#define B0 1
#define B1 0
#define B2 3
#define B3 2
#define B4 5
#define B5 4
#define B6 7
#define B7 6
#define B8 0
#define B9 0
#define B10 0
#define B11 0
#define B12 0
#define B13 0
#define B14 0
#define B15 0
#define B16 0
#define B17 0
#define B18 0
#define B19 0

#define NUMBER_OF_BLOCK 8
#define START_FRAME_SIZE 8
#define END_FRAME 0
//static uint8_t f8[8]={1,0,3,2,5,4,7,6}; //brightness,red,green,blue
//static PixelStruct HD108=PixelStruct(2,4,f8,8,false); //4 blocks of 2*8bits
#endif
