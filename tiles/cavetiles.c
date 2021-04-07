const unsigned char cave_tiles[] =
{
	0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
	0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
	0x80,0x95,0x81,0xDF,0xCF,0x7E,0xDF,0x70,
	0xDF,0x70,0xFF,0x20,0xFF,0x20,0xFF,0x00,
	0x01,0x5F,0x13,0xB6,0xFB,0xEE,0xFB,0x0E,
	0xFB,0x0E,0xFF,0x04,0xFF,0x04,0xFF,0x00,
	0x00,0x9A,0x08,0x6A,0x9E,0xDF,0xBE,0xB3,
	0xBE,0xE3,0xBF,0xE1,0xFF,0x60,0xFF,0x40,
	0x11,0xF5,0x20,0x39,0x71,0xD3,0x7B,0x5F,
	0xFF,0x86,0xFF,0x00,0xFF,0x00,0xFF,0x00,
	0xFF,0xFF,0x00,0x00,0x00,0x04,0x00,0xAE,
	0x00,0x14,0x00,0xB2,0x00,0xAD,0x00,0x7B,
	0x01,0xDB,0x01,0xEB,0x01,0x4D,0x01,0xEF,
	0x01,0x15,0x01,0xB3,0x01,0xAD,0x01,0x7B,
	0x00,0xDA,0x00,0xEB,0x00,0x4D,0x00,0xEE,
	0x00,0x14,0x00,0xB2,0x00,0xAD,0xFF,0xFF,
	0x80,0xDA,0x80,0xEB,0x80,0xCD,0x80,0xEE,
	0x80,0x94,0x80,0xB2,0x80,0xAD,0x80,0xFB,
	0x00,0xDA,0x00,0xEB,0x00,0x4D,0x00,0xEE,
	0x00,0x14,0x00,0xB2,0x00,0xAD,0x00,0x7B,
	0xE0,0x3A,0xF8,0x1B,0xFC,0x05,0xFE,0x02,
	0xFE,0x02,0xFC,0x06,0xFC,0x0D,0xF8,0x0B,
	0xF8,0x0A,0xF0,0x1B,0xF0,0x1D,0xF0,0x1E,
	0xF0,0x14,0xF0,0x32,0xE0,0x6D,0x80,0xFB,
	0xF0,0x1A,0xE0,0x2B,0xE0,0x2D,0xE0,0x2E,
	0xE0,0x34,0xF0,0x32,0xFC,0x0D,0xFC,0x07,
	0xE0,0x3A,0xF0,0x1B,0xF8,0x0D,0xF8,0x0E,
	0xF8,0x1C,0xF0,0x32,0xE0,0x6D,0xC0,0xFB,
	0x07,0x5C,0x1F,0xD8,0x3F,0xA0,0x7F,0x40,
	0x7F,0x40,0x3F,0x60,0x3F,0xB0,0x1F,0xD0,
	0x1F,0xD0,0x0F,0xE8,0x0F,0x48,0x0F,0xE8,
	0x0F,0x18,0x0F,0xBC,0x07,0xAE,0x01,0x7B,
	0x0F,0xD8,0x07,0xEC,0x07,0x4C,0x07,0xEC,
	0x07,0x14,0x0F,0xBC,0x3F,0xB0,0x3F,0x60,
	0x07,0xDC,0x0F,0xE8,0x1F,0x50,0x1F,0xF0,
	0x1F,0x18,0x0F,0xBC,0x07,0xAE,0x03,0x7B,
	0xFF,0x00,0x7F,0x00,0x1F,0x80,0x03,0xE0,
	0x00,0xF8,0x00,0xFF,0x00,0xFF,0x00,0xFF,
	0xFF,0x00,0xFE,0x00,0xF8,0x01,0xC0,0x07,
	0x00,0x3B,0x00,0xFF,0x00,0xFF,0x00,0xFF,
	0x00,0xFB,0x00,0xDF,0x00,0xFF,0x00,0xFF,
	0x00,0xFB,0x00,0xFF,0x00,0xFF,0x00,0xFF,
	0x00,0xDA,0x00,0x6B,0x00,0x8D,0x00,0xE2,
	0x00,0xF8,0x00,0xFF,0x00,0xFF,0x00,0xFF,
	0x00,0xDA,0x00,0xEA,0x00,0x49,0x00,0xC7,
	0x00,0x3B,0x00,0xFF,0x00,0xFF,0x00,0xFF,
	0xFF,0x00,0xFF,0x3C,0xEF,0x66,0xDF,0xE2,
	0xDB,0xE7,0xA5,0xBF,0x99,0xBD,0x01,0x7B,
	0x01,0xDB,0x99,0xFB,0xA5,0xFD,0xDB,0xE7,
	0xDF,0xE2,0xEF,0x66,0xFF,0x3C,0xFF,0x00,
	0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
	0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFF,0x00,
	0xFF,0x00,0xFF,0x18,0xEF,0x24,0xCB,0x46,
	0xFB,0x46,0xF7,0x2C,0xFF,0x18,0xFF,0x00,
	0xFF,0x3C,0xFF,0x42,0xCF,0x72,0xE7,0xFF,
	0x99,0xFF,0xBB,0xDD,0x87,0xF9,0xFF,0x7E
};

const unsigned char lava_tiles[] =
{
	0xFF,0x00,0x7F,0x80,0x1F,0x60,0x03,0x1C,
	0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,
	0xFF,0x00,0xFE,0x01,0xF8,0x06,0xC0,0x38,
	0x00,0xC4,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x04,0x00,0x20,0x00,0x00,0x00,0x00,
	0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x25,0x00,0x94,0x00,0x72,0x00,0x1D,
	0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x25,0x00,0x15,0x00,0xB6,0x00,0x38,
	0x00,0xC4,0x00,0x00,0x00,0x00,0x00,0x00,
	
	0xFF,0x00,0xFF,0x00,0x0F,0xF0,0x01,0x0E,
	0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
	0xFF,0x00,0xFF,0x00,0xF0,0x0F,0x80,0x70,
	0x00,0x82,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x22,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x25,0x00,0x14,0x00,0xF2,0x00,0x0F,
	0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x25,0x00,0x14,0x00,0xBF,0x00,0x70,
	0x00,0x82,0x00,0x00,0x00,0x00,0x00,0x00,
	
	0xFF,0x00,0xFF,0x00,0x07,0xF8,0x00,0x27,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,
	0xFF,0x00,0xFF,0x00,0xE0,0x1F,0x00,0xE0,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
	0x00,0x25,0x00,0x14,0x00,0xFA,0x00,0x27,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22,
	0x00,0x25,0x00,0x14,0x00,0xBF,0x00,0xE0,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22,
	
	0xFF,0x00,0xFF,0x00,0x3F,0xC0,0xC7,0x38,
	0xF8,0x07,0xFF,0x00,0xDF,0x20,0xFB,0x04,
	0xFF,0x00,0xFF,0x00,0xFC,0x03,0xE3,0x1C,
	0x1F,0xE0,0xFF,0x00,0xDF,0x20,0xFB,0x04,
	0xFF,0x00,0xFF,0x00,0xFF,0x00,0xFB,0x04,
	0xFF,0x00,0xFF,0x00,0xDF,0x20,0xFB,0x04,
	0x00,0x25,0x00,0x14,0x00,0xF2,0xC0,0x39,
	0xF8,0x07,0xFF,0x00,0xDF,0x20,0xFB,0x04,
	0x00,0x25,0x00,0x14,0x00,0xB3,0x03,0x1C,
	0x1F,0xE0,0xFF,0x00,0xDF,0x20,0xFB,0x04,
	
	0xFF,0x00,0x1F,0xE0,0xE7,0x18,0xF9,0x06,
	0xFE,0x01,0xF7,0x08,0xFE,0x01,0xFF,0x00,
	0xFF,0x00,0xF8,0x07,0xE7,0x18,0x9F,0x60,
	0x7F,0x80,0xF7,0x08,0xFE,0x01,0xFF,0x00,
	0xFF,0x00,0xF7,0x08,0xFE,0x01,0xFF,0x00,
	0xFF,0x00,0xF7,0x08,0xFE,0x01,0xFF,0x00,
	0x00,0x25,0x00,0xF4,0xE0,0x1A,0xF8,0x07,
	0xFE,0x01,0xF7,0x08,0xFE,0x01,0xFF,0x00,
	0x00,0x25,0x00,0x17,0x07,0xB8,0x1F,0x60,
	0x7F,0x80,0xF7,0x08,0xFE,0x01,0xFF,0x00,
	
	0xFF,0x00,0xFF,0x00,0xFF,0x00,0xF8,0x07,
	0x07,0xF8,0xFF,0x00,0xFD,0x02,0xFF,0x00,
	0xFF,0x00,0xFF,0x00,0xFF,0x00,0x1F,0xE0,
	0xE0,0x1F,0xFF,0x00,0xFD,0x02,0xFF,0x00,
	0xFF,0x00,0xFF,0x00,0xFD,0x02,0xFF,0x00,
	0xDF,0x20,0xFF,0x00,0xFD,0x02,0xFF,0x00,
	0x00,0x25,0x00,0x14,0x00,0xB2,0x00,0x17,
	0x07,0xF8,0xFF,0x00,0xFD,0x02,0xFF,0x00,
	0x00,0x25,0x00,0x14,0x00,0xB2,0x00,0xF1,
	0xE0,0x1F,0xFF,0x00,0xFD,0x02,0xFF,0x00,
	
	0xFF,0x00,0xFF,0x00,0x3F,0xC0,0xC7,0x38,
	0xF8,0x07,0xFD,0x02,0xFF,0x00,0xFF,0x00,
	0xFF,0x00,0xFF,0x00,0xFC,0x03,0xE3,0x1C,
	0x1F,0xE0,0xFD,0x02,0xFF,0x00,0xFF,0x00,
	0xFF,0x00,0xFD,0x02,0xFF,0x00,0xDF,0x20,
	0xFF,0x00,0xFD,0x02,0xFF,0x00,0xFF,0x00,
	0x00,0x25,0x00,0x14,0x00,0xF2,0xC0,0x39,
	0xF8,0x07,0xFD,0x02,0xFF,0x00,0xFF,0x00,
	0x00,0x25,0x00,0x14,0x00,0xB3,0x03,0x1C,
	0x1F,0xE0,0xFD,0x02,0xFF,0x00,0xFF,0x00
};

const unsigned char exit_tiles[] =
{
	0xFF,0x00,0xFF,0x3C,0xEF,0x66,0xDF,0xE2,
	0xDB,0xE7,0xA5,0xBF,0x99,0xBD,0x01,0x7B,
	0x01,0xDB,0x99,0xFB,0xA5,0xFD,0xDB,0xE7,
	0xDF,0xE2,0xEF,0x66,0xFF,0x3C,0xFF,0x00,

	0xFF,0x00,0xFF,0x3C,0xE7,0x66,0xE3,0xC2,
	0xE7,0xC3,0xBD,0xA7,0x99,0xBD,0x01,0x7B,
	0x01,0xDB,0x99,0xFB,0xBD,0xE5,0xE7,0xC3,
	0xE3,0xC2,0xE7,0x66,0xFF,0x3C,0xFF,0x00
};