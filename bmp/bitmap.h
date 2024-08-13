#ifndef BITMAP_H_
#define BITMAP_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

#include "common.h"
#include <stdbool.h>

    typedef enum osd_color_fmt
    {
        OSD_COLOR_FMT_RGB444 = 0,
        OSD_COLOR_FMT_RGB4444 = 1,
        OSD_COLOR_FMT_RGB555 = 2,
        OSD_COLOR_FMT_RGB565 = 3,
        OSD_COLOR_FMT_RGB1555 = 4,
        OSD_COLOR_FMT_RGB888 = 6,
        OSD_COLOR_FMT_RGB8888 = 7,
        OSD_COLOR_FMT_BUTT
    } OSD_COLOR_FMT_E;

    typedef struct osd_rgb
    {
        unsigned char u8B;
        unsigned char u8G;
        unsigned char u8R;
        unsigned char u8Reserved;
    } OSD_RGB_S;

    typedef struct osd_surface
    {
        OSD_COLOR_FMT_E enColorFmt; /* color format */
        unsigned char *pu8PhyAddr;  /* physical address */
        unsigned short u16Height;   /* operation height */
        unsigned short u16Width;    /* operation width */
        unsigned short u16Stride;   /* surface stride */
        unsigned short u16Reserved;
    } OSD_SURFACE_S;

    typedef struct osd_logo
    {
        unsigned int width;        /* out */
        unsigned int height;       /* out */
        unsigned int stride;       /* in */
        unsigned char *pRGBBuffer; /* in/out */
    } OSD_LOGO_T;

    typedef struct osd_bitmapinfoheader
    {
        unsigned short biSize;
        unsigned int biWidth;
        int biHeight;
        unsigned short biPlanes;
        unsigned short biBitCount;
        unsigned int biCompression;
        unsigned int biSizeImage;
        unsigned int biXPelsPerMeter;
        unsigned int biYPelsPerMeter;
        unsigned int biClrUsed;
        unsigned int biClrImportant;
    } OSD_BITMAPINFOHEADER;

    typedef struct osd_bitmapfileheader
    {
        unsigned int bfSize;
        unsigned short bfReserved1;
        unsigned short bfReserved2;
        unsigned int bfOffBits;
    } OSD_BITMAPFILEHEADER;

    typedef struct osd_rgbquad
    {
        unsigned char rgbBlue;
        unsigned char rgbGreen;
        unsigned char rgbRed;
        unsigned char rgbReserved;
    } OSD_RGBQUAD;

    typedef struct osd_bitmapinfo
    {
        OSD_BITMAPINFOHEADER bmiHeader;
        OSD_RGBQUAD bmiColors[1];
    } OSD_BITMAPINFO;

    typedef struct osd_comp_info
    {
        int alen;
        int rlen;
        int glen;
        int blen;
    } OSD_COMP_INFO;

#ifndef __SIGMASTAR__
typedef struct MI_RGN_PaletteElement_s
{
    unsigned char u8Alpha;
    unsigned char u8Red;
    unsigned char u8Green;
    unsigned char u8Blue;
}MI_RGN_PaletteElement_t;

typedef struct MI_RGN_PaletteTable_s
{
    MI_RGN_PaletteElement_t astElement[256];
}MI_RGN_PaletteTable_t;

#endif

    int parse_bitmap(const char *filename, OSD_BITMAPFILEHEADER *pBmpFileHeader, OSD_BITMAPINFO *pBmpInfo);
    int CreateSurfaceByBitMap(const char *pszFileName, OSD_SURFACE_S *pstSurface, unsigned char *pu8Virt);

    uint32_t colorDistance8(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2) ;
    uint8_t findClosestPaletteIndex8(uint16_t color, MI_RGN_PaletteTable_t* paletteTable);

    void convertBitmap1555ToI8(
        uint16_t* srcBitmap, uint32_t width, uint32_t height, 
        uint8_t* destBitmap, MI_RGN_PaletteTable_t* paletteTable);
    void Convert1555ToRGBA(unsigned short* bitmap1555, unsigned char* rgbaData, unsigned int width, unsigned int height);
    void convertBitmap1555ToI4(
    uint16_t* srcBitmap, uint32_t width, uint32_t height, 
    uint8_t* destBitmap, MI_RGN_PaletteTable_t* paletteTable);

    void ConvertI8ToRGBA(uint8_t* bitmapI8, uint8_t* rgbaData, uint32_t width, uint32_t height, MI_RGN_PaletteElement_t* palette);

    void ConvertI4ToRGBA(uint8_t* bitmapI4, uint8_t* rgbaData, uint32_t width, uint32_t height, MI_RGN_PaletteElement_t* palette) ;

    void copyRectARGB1555(
        uint16_t* srcBitmap, uint32_t srcWidth, uint32_t srcHeight,
        uint16_t* destBitmap, uint32_t destWidth, uint32_t destHeight,
        uint32_t srcX, uint32_t srcY, uint32_t width, uint32_t height,
        uint32_t destX, uint32_t destY);

    void copyRectI8(
        uint8_t* srcBitmap, uint32_t srcWidth, uint32_t srcHeight,
        uint8_t* destBitmap, uint32_t destWidth, uint32_t destHeight,
        uint32_t srcX, uint32_t srcY, uint32_t width, uint32_t height,
        uint32_t destX, uint32_t destY);

    void copyRectI4(
        uint8_t* srcBitmap, uint32_t srcWidth, uint32_t srcHeight,
        uint8_t* destBitmap, uint32_t destWidth, uint32_t destHeight,
        uint32_t srcX, uint32_t srcY, uint32_t width, uint32_t height,
        uint32_t destX, uint32_t destY) ;     

    // Declaration of global palette table
    extern MI_RGN_PaletteTable_t g_stPaletteTable;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif