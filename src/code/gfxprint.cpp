#define INTERNAL_SRC_CODE_GFXPRINT_C
#include "global.h"
#include "gfx.h"
#include "gfxprint.h"
#include "def/gfxprint.h"
#include "def/printutils.h"
#include "def/xprintf.h"

// clang off
u16 sGfxPrintFontTLUT[64] = {
    BE16(0x0000), BE16(0xFFFF), BE16(0x0000), BE16(0xFFFF), BE16(0x0000), BE16(0xFFFF), BE16(0x0000), BE16(0xFFFF),
    BE16(0x0000), BE16(0xFFFF), BE16(0x0000), BE16(0xFFFF), BE16(0x0000), BE16(0xFFFF), BE16(0x0000), BE16(0xFFFF),
    BE16(0x0000), BE16(0x0000), BE16(0xFFFF), BE16(0xFFFF), BE16(0x0000), BE16(0x0000), BE16(0xFFFF), BE16(0xFFFF),
    BE16(0x0000), BE16(0x0000), BE16(0xFFFF), BE16(0xFFFF), BE16(0x0000), BE16(0x0000), BE16(0xFFFF), BE16(0xFFFF),
    BE16(0x0000), BE16(0x0000), BE16(0x0000), BE16(0x0000), BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF),
    BE16(0x0000), BE16(0x0000), BE16(0x0000), BE16(0x0000), BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF),
    BE16(0x0000), BE16(0x0000), BE16(0x0000), BE16(0x0000), BE16(0x0000), BE16(0x0000), BE16(0x0000), BE16(0x0000),
    BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF), BE16(0xFFFF),
};
// clang on

u16 sGfxPrintRainbowTLUT[16] = {
    BE16(0xF801), BE16(0xFBC1), BE16(0xFFC1), BE16(0x07C1), BE16(0x0421), BE16(0x003F), BE16(0x803F), BE16(0xF83F),
    BE16(0xF801), BE16(0xFBC1), BE16(0xFFC1), BE16(0x07C1), BE16(0x0421), BE16(0x003F), BE16(0x803F), BE16(0xF83F),
};

u8 sGfxPrintRainbowData[8] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };

u8 sGfxPrintFontData[(16 * 256) / 2] = {
    0x00, 0xDF, 0xFD, 0x00, 0x0A, 0xEE, 0xFF, 0xA0, 0x0D, 0xF2, 0x2D, 0xD0, 0x06, 0x61, 0x1D, 0xC0, 0x01, 0x12, 0x2D,
    0xD0, 0x06, 0x71, 0x99, 0x00, 0x01, 0x1E, 0xED, 0x10, 0x07, 0x7E, 0xF7, 0x00, 0x01, 0x56, 0x29, 0x90, 0x05, 0x58,
    0x97, 0x60, 0x0D, 0xD2, 0x29, 0x90, 0x05, 0x59, 0x97, 0x70, 0x04, 0xDF, 0xFD, 0x40, 0x02, 0x6E, 0xF7, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xBF, 0xFB, 0x00, 0x0E, 0xFF, 0xFF, 0xC0, 0x0B, 0xF0, 0x0F, 0xB0,
    0x0F, 0xF0, 0x03, 0x30, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x02, 0x20, 0x0C, 0xFB, 0xBF, 0x60, 0x0F, 0xFC, 0xCE,
    0x20, 0x0D, 0xD4, 0x4F, 0xF0, 0x0F, 0xF0, 0x02, 0x20, 0x0F, 0xF0, 0x0F, 0xF0, 0x0F, 0xF0, 0x03, 0x30, 0x0C, 0xFB,
    0xBF, 0x40, 0x0E, 0xF7, 0x77, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFD, 0x00, 0x0A,
    0xEE, 0xFF, 0xA0, 0x0D, 0xF2, 0x2D, 0xD0, 0x06, 0x61, 0x1D, 0xC0, 0x01, 0x12, 0x2D, 0xD0, 0x06, 0x71, 0x99, 0x00,
    0x01, 0x1E, 0xED, 0x10, 0x07, 0x7E, 0xF7, 0x00, 0x01, 0x56, 0x29, 0x90, 0x05, 0x58, 0x97, 0x60, 0x0D, 0xD2, 0x29,
    0x90, 0x05, 0x59, 0x97, 0x70, 0x04, 0xDF, 0xFD, 0x40, 0x02, 0x6E, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0xBF, 0xFB, 0x00, 0x00, 0x0D, 0xE0, 0x00, 0x0B, 0xF0, 0x0F, 0xB0, 0x00, 0x5D, 0xE6, 0x00, 0x0F,
    0xF0, 0x0F, 0xF0, 0x05, 0x5C, 0xC6, 0x60, 0x0C, 0xFB, 0xBF, 0x60, 0x77, 0x3F, 0xF3, 0x77, 0x0D, 0xD4, 0x4F, 0xF0,
    0xBB, 0x3F, 0xF3, 0xBB, 0x0F, 0xF0, 0x0F, 0xF0, 0x09, 0x9C, 0xCA, 0xA0, 0x0C, 0xFB, 0xBF, 0x40, 0x00, 0x9D, 0xEA,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0xE0, 0x00, 0x04, 0xC2, 0x2C, 0x40, 0x02, 0x8D, 0x50, 0x20, 0x0C, 0xCA,
    0xAC, 0xC0, 0x21, 0xF9, 0x17, 0x10, 0x04, 0xC2, 0x2C, 0x40, 0x12, 0x49, 0x34, 0x00, 0x00, 0x82, 0x08, 0x00, 0x01,
    0x97, 0x51, 0x10, 0x08, 0x8A, 0x88, 0x80, 0x04, 0x61, 0x52, 0x41, 0x00, 0x80, 0x08, 0x00, 0x43, 0x11, 0x75, 0x30,
    0x00, 0xA2, 0x08, 0x00, 0x60, 0x05, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x40, 0x00, 0x22, 0x11,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x0F, 0xB0, 0x00, 0x00, 0x00, 0x08, 0x80, 0x04, 0x0D, 0xA4, 0x00, 0x00, 0x00,
    0x88, 0x00, 0x08, 0xCD, 0xE8, 0x80, 0x02, 0x2A, 0xA2, 0x20, 0x08, 0xCD, 0xE8, 0x80, 0x02, 0xAA, 0x22, 0x20, 0x04,
    0x0D, 0xA4, 0x00, 0x0C, 0xD1, 0x00, 0x00, 0x00, 0x0F, 0xB0, 0x00, 0x8C, 0x51, 0x00, 0x00, 0x00, 0x22, 0x11, 0x00,
    0x81, 0x10, 0x00, 0x00, 0x00, 0xDF, 0xFD, 0x00, 0x0A, 0xEE, 0xFF, 0xA0, 0x0D, 0xF2, 0x2D, 0xD0, 0x06, 0x61, 0x1D,
    0xC0, 0x01, 0x12, 0x2D, 0xD0, 0x06, 0x71, 0x99, 0x00, 0x01, 0x1E, 0xED, 0x10, 0x07, 0x7E, 0xF7, 0x00, 0x01, 0x56,
    0x29, 0x90, 0x05, 0x58, 0x97, 0x60, 0x0D, 0xD2, 0x29, 0x90, 0x05, 0x59, 0x97, 0x70, 0x04, 0xDF, 0xFD, 0x40, 0x02,
    0x6E, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x00, 0x04, 0x48, 0x99, 0x80,
    0x03, 0x3C, 0xC3, 0x30, 0x00, 0xCD, 0x10, 0x88, 0x03, 0x3C, 0xC3, 0x30, 0x02, 0xBF, 0x62, 0xA8, 0x00, 0x33, 0x33,
    0x20, 0x01, 0x10, 0x4C, 0x80, 0x01, 0x10, 0x03, 0x30, 0x00, 0x15, 0xC8, 0x00, 0x03, 0x3C, 0xC3, 0x30, 0x02, 0x67,
    0x32, 0x20, 0x00, 0x3F, 0xF3, 0x00, 0x04, 0x40, 0x99, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
    0xDF, 0xFD, 0x10, 0x07, 0xFF, 0xFF, 0x60, 0x1C, 0xE0, 0x0E, 0xC1, 0x0F, 0xF0, 0x09, 0x90, 0x1E, 0xE1, 0x16, 0x61,
    0x0F, 0xF0, 0x01, 0x10, 0x1E, 0xF4, 0x56, 0x21, 0x0F, 0xF6, 0x67, 0x10, 0x1E, 0xF2, 0x36, 0x61, 0x0F, 0xF0, 0x89,
    0x90, 0x1E, 0xF1, 0x0F, 0xE1, 0x0F, 0xF0, 0x09, 0x90, 0x16, 0xEC, 0xCE, 0x21, 0x07, 0xFB, 0xBB, 0x20, 0x01, 0x11,
    0x11, 0x10, 0x00, 0x00, 0x00, 0x00, 0x09, 0xB6, 0x6F, 0xD0, 0x27, 0xD8, 0x8E, 0x60, 0x09, 0x92, 0xED, 0x10, 0x2F,
    0xF0, 0x2E, 0xE0, 0x09, 0x9A, 0xE5, 0x10, 0x2F, 0xF6, 0x2E, 0xE0, 0x09, 0x9B, 0x75, 0x10, 0x2F, 0xD6, 0x4E, 0xE0,
    0x0D, 0xDA, 0xE5, 0x10, 0x2F, 0xD0, 0x4E, 0xE0, 0x0D, 0xD2, 0xED, 0x10, 0x2F, 0xD0, 0x0E, 0xE0, 0x09, 0xF6, 0x6F,
    0x90, 0x27, 0xD9, 0x9F, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0x00, 0x8F, 0x71,
    0x1F, 0xF0, 0x2F, 0xD0, 0x0F, 0xF0, 0x8F, 0x71, 0x1F, 0xF0, 0x2F, 0xD0, 0x07, 0x70, 0x8E, 0x61, 0x1E, 0xE0, 0x27,
    0xDD, 0xDF, 0x60, 0x8E, 0x69, 0x1E, 0xE0, 0x27, 0x76, 0x4A, 0xA0, 0x8E, 0xE9, 0x9E, 0xE0, 0x2F, 0xD0, 0x6E, 0x80,
    0x8A, 0xE7, 0xFE, 0xA0, 0x07, 0xFA, 0x8E, 0x60, 0x88, 0x27, 0x7A, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x07, 0x7C, 0xCF, 0xF0, 0x13, 0x26, 0x60, 0x11, 0x07, 0x7C, 0xCF, 0xF0, 0x03, 0x76, 0x65, 0x10, 0x02, 0x39,
    0xD7, 0x20, 0x04, 0x53, 0x35, 0x40, 0x00, 0x2F, 0xF2, 0x00, 0x01, 0x13, 0x31, 0x10, 0x00, 0x5F, 0xB1, 0x00, 0x00,
    0x03, 0x30, 0x00, 0x05, 0x5E, 0xE5, 0x50, 0x01, 0x13, 0x31, 0x10, 0x05, 0x5E, 0xED, 0xD0, 0x02, 0x23, 0x30, 0x00,
    0x00, 0x08, 0x88, 0x80, 0x8A, 0xAB, 0xB8, 0x88, 0x00, 0x00, 0x11, 0x00, 0x00, 0x04, 0x45, 0x10, 0x04, 0x62, 0x33,
    0x20, 0x00, 0x44, 0x01, 0x10, 0x04, 0xC8, 0x9A, 0xA0, 0x00, 0xEE, 0xAB, 0x10, 0x0C, 0xE6, 0x67, 0x20, 0x0E, 0xF5,
    0x5F, 0xB0, 0x0E, 0xE0, 0x06, 0x60, 0x0B, 0xF6, 0x2B, 0x90, 0x0E, 0xE0, 0x06, 0x60, 0x03, 0xFC, 0x89, 0x90, 0x04,
    0xEE, 0xEE, 0xA0, 0x00, 0x77, 0x3B, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x08, 0x88, 0x88, 0x00, 0x09, 0x90, 0x00, 0x00,
    0x00, 0x11, 0x10, 0x00, 0x09, 0x92, 0x24, 0x40, 0x00, 0x01, 0x10, 0x00, 0x09, 0x90, 0x88, 0x00, 0x26, 0xEF, 0xDE,
    0x20, 0x09, 0x9B, 0xB5, 0x40, 0x2E, 0xC3, 0x3C, 0xE2, 0x0D, 0x9A, 0x25, 0x50, 0x2E, 0xC3, 0x3C, 0xE2, 0x0D, 0xDA,
    0xA5, 0x50, 0x2E, 0xC3, 0x3C, 0xE2, 0x09, 0xD6, 0xED, 0x10, 0x26, 0xCB, 0xBC, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00,
    0x05, 0xFB, 0xFF, 0xE0, 0x8E, 0x61, 0x16, 0xE8, 0x0F, 0xF4, 0x03, 0x30, 0x8F, 0x71, 0x17, 0xF8, 0x07, 0xFC, 0x8B,
    0x30, 0x8E, 0x69, 0x96, 0xE8, 0x05, 0x73, 0x3B, 0xA0, 0x8A, 0x6D, 0xD6, 0xA8, 0x0D, 0xD8, 0x8A, 0x20, 0x08, 0xA7,
    0x79, 0xB2, 0x01, 0x10, 0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x8A, 0x01, 0x10, 0x00, 0x00,
    0x00, 0x08, 0x00, 0x80, 0xA1, 0x10, 0x00, 0x07, 0x74, 0x4F, 0x70, 0x80, 0xA9, 0x90, 0x00, 0x02, 0x31, 0xDF, 0x20,
    0x84, 0xE6, 0x00, 0x04, 0x00, 0x27, 0xDA, 0x20, 0xC8, 0xAA, 0x4C, 0x40, 0x00, 0x57, 0x3B, 0x20, 0x00, 0xA1, 0x18,
    0x00, 0x05, 0x54, 0x6F, 0x50, 0x00, 0xA9, 0x98, 0x00, 0x02, 0x22, 0x20, 0x80, 0x02, 0x00, 0x18, 0x88, 0x00, 0x04,
    0x44, 0x40, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x44, 0x40, 0x0C, 0x44, 0x44, 0x00, 0x00, 0x04, 0x40, 0x00, 0x88,
    0xC0, 0x00, 0x00, 0x00, 0x0C, 0xC0, 0x00, 0x0C, 0x46, 0xA4, 0x40, 0x00, 0x0C, 0xC0, 0x00, 0x08, 0x8E, 0xE0, 0x00,
    0x02, 0x08, 0x80, 0x00, 0x80, 0xD0, 0x88, 0x00, 0x28, 0xA8, 0x80, 0x00, 0x88, 0xCD, 0x4C, 0x40, 0x0A, 0x88, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xE0, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x88, 0x00, 0x80, 0x01, 0x06, 0x10, 0x00, 0x56, 0xE7, 0x50, 0x80, 0x02, 0x1F, 0xF1, 0x00, 0x38,
    0x8C, 0xB8, 0x00, 0x0B, 0xF6, 0x0B, 0x00, 0x94, 0xC0, 0x28, 0x00, 0x06, 0x07, 0x6A, 0x00, 0xCB, 0xA6, 0xC8, 0x00,
    0x00, 0x47, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x80, 0x00, 0x00, 0x39, 0x14,
    0x20, 0x02, 0x22, 0x24, 0x00, 0x08, 0xAE, 0xA8, 0x60, 0x04, 0x28, 0x99, 0x70, 0x07, 0x75, 0xD1, 0x04, 0x0F, 0xB3,
    0x33, 0xD0, 0x00, 0xAE, 0xBE, 0xA4, 0x25, 0x15, 0x20, 0xA0, 0x02, 0x61, 0x0C, 0x02, 0x20, 0x42, 0x08, 0x20, 0x2C,
    0x30, 0x14, 0x02, 0x02, 0x28, 0x82, 0x00, 0x03, 0xAC, 0xC1, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x12, 0x00, 0x08, 0x00, 0x28, 0x00, 0x0A, 0xCF, 0xEE, 0x20, 0x0B, 0x62, 0x2E, 0x20, 0x02, 0x10, 0x82,
    0x40, 0x01, 0x44, 0xE4, 0x40, 0x03, 0x00, 0x0E, 0x00, 0x8D, 0xEA, 0xAC, 0x00, 0x02, 0x10, 0x0A, 0x00, 0x01, 0xE0,
    0x24, 0x00, 0x0C, 0x21, 0x02, 0x00, 0x09, 0x42, 0x21, 0x00, 0x00, 0xCC, 0xF4, 0x40, 0x02, 0xBF, 0xD4, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x44, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x44, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x0C, 0xCC, 0xC4, 0x40, 0x00, 0x0C, 0xC0, 0x00, 0x00, 0x02, 0xA0,
    0x40, 0x00, 0x0C, 0xC0, 0x00, 0x04, 0xCE, 0x64, 0x40, 0x02, 0x08, 0x80, 0x00, 0x00, 0x90, 0x00, 0x40, 0x28, 0xA8,
    0x80, 0x00, 0x08, 0x01, 0x04, 0x00, 0x0A, 0x88, 0x80, 0x00, 0x04, 0x44, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x54, 0x44, 0x00,
    0xEE, 0xFE, 0xE0, 0x00, 0x09, 0x3B, 0x3F, 0x00, 0x21, 0xD8, 0x20, 0x00, 0x00, 0x54, 0x4F, 0x00, 0x18, 0x58, 0x20,
    0x00, 0x00, 0x01, 0x86, 0x00, 0xC6, 0x7E, 0x40, 0x00, 0x00, 0xEF, 0x66, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0xC0, 0x20, 0x00, 0xAA, 0xAA, 0xEA, 0x20, 0xEF, 0xFF, 0xFF, 0x00, 0x80,
    0x44, 0x19, 0x30, 0x00, 0x49, 0x24, 0x00, 0xC5, 0x35, 0x1B, 0x10, 0x00, 0x4B, 0x24, 0x00, 0x01, 0x35, 0xA0, 0x00,
    0x8C, 0xA9, 0xAC, 0x80, 0x00, 0x2C, 0x00, 0x00, 0x04, 0x21, 0xA4, 0x00, 0x2A, 0x84, 0x00, 0x00, 0x73, 0x11, 0xF1,
    0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x11, 0x19, 0x00, 0x00, 0x40, 0x00, 0x00, 0x8F, 0xEE,
    0xEF, 0xE0, 0x0B, 0x76, 0x66, 0xD0, 0x1A, 0x00, 0x0B, 0x40, 0x4C, 0x40, 0x02, 0xD0, 0x28, 0x00, 0x1A, 0x40, 0x01,
    0xD0, 0x2C, 0x10, 0x00, 0x00, 0x38, 0x40, 0x00, 0x40, 0x28, 0x10, 0x00, 0x01, 0xA0, 0x40, 0x00, 0x42, 0x83, 0x00,
    0x05, 0xFE, 0x44, 0x40, 0x03, 0xFD, 0x54, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x99, 0x9B,
    0x00, 0x00, 0x10, 0x20, 0x00, 0x07, 0x26, 0x21, 0x40, 0x2A, 0xFE, 0xEE, 0xA0, 0x8D, 0x8C, 0xA9, 0xC0, 0x00, 0x10,
    0x20, 0x80, 0x32, 0x33, 0xB3, 0x60, 0x00, 0x19, 0x28, 0x00, 0x00, 0x00, 0xA1, 0x40, 0x00, 0x10, 0xB1, 0x00, 0x00,
    0x08, 0x34, 0x00, 0x00, 0x1A, 0x08, 0x00, 0x05, 0xF7, 0x40, 0x00, 0x8E, 0xF4, 0x44, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x14, 0x02, 0x80, 0x00, 0x04, 0x00, 0x00, 0x1D, 0x11, 0xDB, 0x00, 0xDD, 0xFD, 0xDD,
    0xD0, 0x0C, 0x88, 0x07, 0x00, 0x02, 0x06, 0x00, 0x90, 0x48, 0x00, 0x34, 0x00, 0x2C, 0x04, 0x2C, 0x10, 0x48, 0x11,
    0x21, 0x40, 0x04, 0x84, 0x83, 0x40, 0x59, 0x03, 0x00, 0x50, 0x40, 0x0C, 0x10, 0x60, 0x42, 0xA9, 0x88, 0xC0, 0x40,
    0x15, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x02, 0x00, 0x40, 0x08, 0x98, 0x88, 0x80,
    0x08, 0xF9, 0x98, 0xC0, 0x06, 0x77, 0x75, 0x50, 0x02, 0x0C, 0x05, 0x00, 0x19, 0x98, 0xA8, 0xD0, 0x0B, 0x99, 0xCA,
    0x80, 0x04, 0x54, 0x65, 0xC0, 0x20, 0x08, 0x50, 0x20, 0x00, 0x10, 0x20, 0xC0, 0x31, 0x1C, 0x04, 0x20, 0x00, 0x01,
    0x28, 0x40, 0x26, 0x63, 0xBB, 0xE0, 0x26, 0xEF, 0xE6, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x02, 0x01, 0x00, 0xC8, 0xC0, 0x00, 0x00, 0x0F, 0x8A, 0x89, 0x80, 0xC3, 0xF3, 0x11, 0x30, 0x0F, 0x02, 0x01, 0x80,
    0xC9, 0xC0, 0x00, 0x30, 0x0F, 0x02, 0x05, 0xA0, 0x00, 0x00, 0x00, 0x30, 0x0E, 0x02, 0x05, 0xA0, 0x00, 0x00, 0x00,
    0x30, 0x0E, 0x02, 0x52, 0x80, 0x00, 0x00, 0x03, 0x00, 0x2C, 0xDF, 0xA8, 0x80, 0x02, 0x33, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x88, 0x00, 0x01, 0x02, 0x80, 0x00, 0x03, 0xFF, 0xF7, 0x00, 0x0F,
    0x26, 0xE4, 0x72, 0xCC, 0x38, 0x00, 0x40, 0x0C, 0x38, 0x99, 0x00, 0x03, 0x0A, 0x31, 0x50, 0x0C, 0xB1, 0x82, 0x80,
    0x03, 0x28, 0x06, 0x00, 0x87, 0x88, 0x2A, 0xA0, 0x01, 0x05, 0xC2, 0x00, 0x85, 0x82, 0xC2, 0x80, 0x10, 0x00, 0x39,
    0x10, 0x08, 0x51, 0xBF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x48, 0x9D,
    0xCC, 0x40, 0xC9, 0xE6, 0x7F, 0x40, 0x40, 0x00, 0x94, 0x00, 0x5B, 0x21, 0x0C, 0xB0, 0x48, 0xAE, 0xCC, 0x40, 0xE1,
    0x30, 0x0C, 0x30, 0x43, 0x01, 0xA4, 0x00, 0xE1, 0x24, 0x5D, 0x30, 0x78, 0x8C, 0xD6, 0x10, 0xF1, 0x60, 0x94, 0x70,
    0xD0, 0x40, 0x9C, 0x70, 0x0B, 0x8C, 0x53, 0x00, 0x0C, 0x9D, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x39, 0x50, 0x00, 0x00, 0x88, 0xF0, 0x00, 0x2E, 0xAF, 0xC6, 0x00, 0x03, 0x01, 0x77, 0x60, 0x04, 0xF0,
    0x41, 0x60, 0x03, 0x92, 0xF8, 0x12, 0x0F, 0xBD, 0x91, 0x40, 0x1B, 0x28, 0x60, 0x92, 0x70, 0xF4, 0x01, 0xF0, 0x0A,
    0xD4, 0x65, 0x82, 0x53, 0xE0, 0x01, 0xE0, 0x04, 0x10, 0x68, 0x60, 0x04, 0x2A, 0xBE, 0x00, 0x00, 0x4F, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3A, 0xEE, 0x00, 0xC8, 0xC0, 0x00, 0x00, 0x0D, 0x84, 0xA5,
    0x00, 0xC1, 0xC2, 0x11, 0x00, 0x45, 0x0E, 0x27, 0x00, 0xD9, 0xC3, 0x00, 0x10, 0x07, 0xF8, 0x8D, 0x20, 0x01, 0x30,
    0x00, 0x10, 0xAC, 0x02, 0x25, 0xA0, 0x01, 0x22, 0x00, 0x10, 0x44, 0x20, 0x16, 0xA0, 0x13, 0x02, 0x00, 0x30, 0x04,
    0x1B, 0xAA, 0x40, 0x21, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// Can be used to set GFXP_FLAG_ENLARGE by default
static u8 sDefaultSpecialFlags;

void GfxPrint_Setup(GfxPrint* pthis) {
    s32 width = 16;
    s32 height = 256;
    s32 i;

    gDPPipeSync(pthis->dList++);
    gDPSetOtherMode(pthis->dList++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_IA16 | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
    gDPSetCombineMode(pthis->dList++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPLoadTextureBlock_4b(pthis->dList++, sGfxPrintFontData, G_IM_FMT_CI, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadTLUT(pthis->dList++, 64, 256, sGfxPrintFontTLUT);

    for (i = 1; i < 4; i++) {
        gDPSetTile(pthis->dList++, G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, i * 2, i, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                   G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
        gDPSetTileSize(pthis->dList++, i * 2, 0, 0, 60, 1020);
    }

    gDPSetColor(pthis->dList++, G_SETPRIMCOLOR, pthis->color);

    gDPLoadMultiTile_4b(pthis->dList++, sGfxPrintRainbowData, 0, 1, G_IM_FMT_CI, 2, 8, 0, 0, 1, 7, 4,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 1, 3, G_TX_NOLOD, G_TX_NOLOD);

    gDPLoadTLUT(pthis->dList++, 16, 320, sGfxPrintRainbowTLUT);

    for (i = 1; i < 4; i++) {
        gDPSetTile(pthis->dList++, G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, i * 2 + 1, 4, G_TX_NOMIRROR | G_TX_WRAP, 3,
                   G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, 1, G_TX_NOLOD);
        gDPSetTileSize(pthis->dList++, i * 2 + 1, 0, 0, 4, 28);
    }
}

void GfxPrint_SetColor(GfxPrint* pthis, u8 r, u8 g, u8 b, u8 a) {
    pthis->color.r = r;
    pthis->color.g = g;
    pthis->color.b = b;
    pthis->color.a = a;
    gDPPipeSync(pthis->dList++);
    gDPSetColor(pthis->dList++, G_SETPRIMCOLOR, pthis->color);
}

void GfxPrint_SetPosPx(GfxPrint* pthis, s32 x, s32 y) {
    pthis->posX = pthis->baseX + (x * 4);
    pthis->posY = pthis->baseY + (y * 4);
}

void GfxPrint_SetPos(GfxPrint* pthis, s32 x, s32 y) {
    GfxPrint_SetPosPx(pthis, x * 8, y * 8);
}

void GfxPrint_SetBasePosPx(GfxPrint* pthis, s32 x, s32 y) {
    pthis->baseX = x * 4;
    pthis->baseY = y * 4;
}

void GfxPrint_PrintCharImpl(GfxPrint* pthis, u8 c) {
    u32 tile = (c & 0xFF) * 2;

    if (pthis->flags & GFXP_FLAG_UPDATE) {
        pthis->flags &= ~GFXP_FLAG_UPDATE;

        gDPPipeSync(pthis->dList++);
        if (pthis->flags & GFXP_FLAG_RAINBOW) {
            gDPSetTextureLUT(pthis->dList++, G_TT_RGBA16);
            gDPSetCycleType(pthis->dList++, G_CYC_2CYCLE);
            gDPSetRenderMode(pthis->dList++, G_RM_OPA_CI, G_RM_XLU_SURF2);
            gDPSetCombineMode(pthis->dList++, G_CC_INTERFERENCE, G_CC_PASS2);
        } else {
            gDPSetTextureLUT(pthis->dList++, G_TT_IA16);
            gDPSetCycleType(pthis->dList++, G_CYC_1CYCLE);
            gDPSetRenderMode(pthis->dList++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetCombineMode(pthis->dList++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
        }
    }

    if (pthis->flags & GFXP_FLAG_SHADOW) {
        gDPSetColor(pthis->dList++, G_SETPRIMCOLOR, 0);

        if (pthis->flags & GFXP_FLAG_ENLARGE) {
            gSPTextureRectangle(pthis->dList++, (pthis->posX + 4) << 1, (pthis->posY + 4) << 1, (pthis->posX + 4 + 32) << 1,
                                (pthis->posY + 4 + 32) << 1, tile, (u16)(c & 4) * 64, (u16)(c >> 3) * 256, 1 << 9,
                                1 << 9);
        } else {
            gSPTextureRectangle(pthis->dList++, pthis->posX + 4, pthis->posY + 4, pthis->posX + 4 + 32, pthis->posY + 4 + 32,
                                tile, (u16)(c & 4) * 64, (u16)(c >> 3) * 256, 1 << 10, 1 << 10);
        }

        gDPSetColor(pthis->dList++, G_SETPRIMCOLOR, pthis->color);
    }

    if (pthis->flags & GFXP_FLAG_ENLARGE) {
        gSPTextureRectangle(pthis->dList++, (pthis->posX) << 1, (pthis->posY) << 1, (pthis->posX + 32) << 1,
                            (pthis->posY + 32) << 1, tile, (u16)(c & 4) * 64, (u16)(c >> 3) * 256, 1 << 9, 1 << 9);
    } else {
        gSPTextureRectangle(pthis->dList++, pthis->posX, pthis->posY, pthis->posX + 32, pthis->posY + 32, tile,
                            (u16)(c & 4) * 64, (u16)(c >> 3) * 256, 1 << 10, 1 << 10);
    }

    pthis->posX += 32;
}

void GfxPrint_PrintChar(GfxPrint* pthis, u8 c) {
    u8 charParam = c;

    if (c == ' ') {
        pthis->posX += 32;
    } else if (c > ' ' && c < 0x7F) {
        GfxPrint_PrintCharImpl(pthis, charParam);
    } else if (c >= 0xA0 && c < 0xE0) {
        if (pthis->flags & GFXP_FLAG_HIRAGANA) {
            if (c < 0xC0) {
                charParam = c - 0x20;
            } else {
                charParam = c + 0x20;
            }
        }
        GfxPrint_PrintCharImpl(pthis, charParam);
    } else {
        switch (c) {
            case '\0':
                break;
            case '\n':
                pthis->posY += 32;
            case '\r':
                pthis->posX = pthis->baseX;
                break;
            case '\t':
                do {
                    GfxPrint_PrintCharImpl(pthis, ' ');
                } while ((pthis->posX - pthis->baseX) % 256);
                break;
            case GFXP_HIRAGANA_CHAR:
                pthis->flags |= GFXP_FLAG_HIRAGANA;
                break;
            case GFXP_KATAKANA_CHAR:
                pthis->flags &= ~GFXP_FLAG_HIRAGANA;
                break;
            case GFXP_RAINBOW_ON_CHAR:
                pthis->flags |= GFXP_FLAG_RAINBOW;
                pthis->flags |= GFXP_FLAG_UPDATE;
                break;
            case GFXP_RAINBOW_OFF_CHAR:
                pthis->flags &= ~GFXP_FLAG_RAINBOW;
                pthis->flags |= GFXP_FLAG_UPDATE;
                break;
            case GFXP_UNUSED_CHAR:
            default:
                break;
        }
    }
}

void GfxPrint_PrintStringWithSize(GfxPrint* pthis, const void* buffer, u32 charSize, u32 charCount) {
    const char* str = (const char*)buffer;
    u32 count = charSize * charCount;

    while (count != 0) {
        GfxPrint_PrintChar(pthis, *(str++));
        count--;
    }
}

void GfxPrint_PrintString(GfxPrint* pthis, const char* str) {
    while (*str != '\0') {
        GfxPrint_PrintChar(pthis, *(str++));
    }
}

void* GfxPrint_Callback(void* arg, const char* str, u32 size) {
    auto pthis = (GfxPrint*)arg;

    GfxPrint_PrintStringWithSize(pthis, str, sizeof(char), size);

    return pthis;
}

void GfxPrint_Init(GfxPrint* pthis) {
    pthis->flags &= ~GFXP_FLAG_OPEN;

    pthis->callback = GfxPrint_Callback;
    pthis->dList = NULL;
    pthis->posX = 0;
    pthis->posY = 0;
    pthis->baseX = 0;
    pthis->baseY = 0;
    pthis->color = Color_RGBA8(0, 0, 0, 0);

    pthis->flags &= ~GFXP_FLAG_HIRAGANA;
    pthis->flags &= ~GFXP_FLAG_RAINBOW;
    pthis->flags |= GFXP_FLAG_SHADOW;
    pthis->flags |= GFXP_FLAG_UPDATE;

    if (sDefaultSpecialFlags & GFXP_FLAG_ENLARGE) {
        pthis->flags |= GFXP_FLAG_ENLARGE;
    } else {
        pthis->flags &= ~GFXP_FLAG_ENLARGE;
    }
}

void GfxPrint_Destroy(GfxPrint* pthis) {
}

void GfxPrint_Open(GfxPrint* pthis, Gfx* dList) {
    if (!(pthis->flags & GFXP_FLAG_OPEN)) {
        pthis->flags |= GFXP_FLAG_OPEN;
        pthis->dList = dList;
        GfxPrint_Setup(pthis);
    } else {
        osSyncPrintf("gfxprint_open:２重オープンです\n");
    }
}

Gfx* GfxPrint_Close(GfxPrint* pthis) {
    Gfx* ret;

    pthis->flags &= ~GFXP_FLAG_OPEN;
    gDPPipeSync(pthis->dList++);
    ret = pthis->dList;
    pthis->dList = NULL;

    return ret;
}

s32 GfxPrint_VPrintf(GfxPrint* pthis, const char* fmt, va_list args) {
    return PrintUtils_VPrintf(&pthis->callback, fmt, args);
}

s32 GfxPrint_Printf(GfxPrint* pthis, const char* fmt, ...) {
    s32 ret;
    va_list args = 0;
    va_start(args, fmt);

    ret = GfxPrint_VPrintf(pthis, fmt, args);

    va_end(args);

    return ret;
}
