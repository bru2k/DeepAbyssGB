#include <gb/gb.h>

//level tilemaps
const unsigned char level01[] =
{
	0x37,0x31,0x2F,0x32,0x32,0x2F,0x30,0x31,0x32,0x2F,
	0x32,0x2F,0x31,0x30,0x2F,0x32,0x32,0x31,0x37,0x37,
	0x3C,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x38,0x37,
	0x3D,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x39,0x37,
	0x3C,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x38,0x37,
	0x3F,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x3A,0x37,
	0x3D,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x39,0x37,
	0x3C,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x36,0x37,
	0x3C,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x48,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x36,0x37,
	0x3D,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2F,0x46,
	0x3F,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x47,
	0x34,0x2E,0x2E,0x2E,0x2E,0x2E,0x48,0x2E,0x2E,0x2E,
	0x2E,0x49,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x47,
	0x34,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x47,
	0x37,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,
	0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x45,
	0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,
	0x44,0x43,0x44,0x43,0x44,0x43,0x44,0x43,0x44,0x43,
	0x44,0x43,0x44,0x43,0x44,0x43,0x44,0x43,0x44,0x43,
	0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,
	0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42
};

const unsigned char level02[] =
{
	0x37,0x37,0x37,0x32,0x30,0x2f,0x32,0x2f,0x30,0x31,
	0x31,0x30,0x32,0x2f,0x30,0x32,0x2f,0x30,0x32,0x2f,
	0x32,0x32,0x2f,0x30,0x30,0x2f,0x32,0x2f,0x31,0x37,
	0x37,0x37,0x37,0x37,0x31,0x30,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x36,0x37,0x37,0x37,0x3c,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x38,0x37,0x37,0x37,0x3e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x3a,0x37,
	0x37,0x37,0x3e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x3a,0x37,0x37,0x37,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x38,0x37,0x37,0x37,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x3a,0x37,0x37,
	0x37,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x48,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x39,0x37,0x37,0x37,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x38,0x37,0x37,0x37,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x48,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x3a,0x37,0x37,0x37,
	0x2e,0x2e,0x2e,0x33,0x33,0x33,0x33,0x33,0x33,0x33,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2f,0x31,0x37,0x2e,0x2e,0x2e,0x36,0x37,0x37,0x37,
	0x37,0x37,0x34,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x33,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x46,0x2e,0x2e,0x2e,0x38,
	0x37,0x37,0x37,0x37,0x37,0x34,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x37,0x2e,0x48,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x47,0x2e,
	0x2e,0x2e,0x3b,0x37,0x37,0x37,0x37,0x37,0x3c,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x37,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x47,0x2e,0x2e,0x2e,0x38,0x37,0x37,0x37,0x37,
	0x37,0x3e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2f,0x2e,
	0x2e,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33,
	0x33,0x33,0x33,0x33,0x45,0x2e,0x2e,0x2e,0x3a,0x37,
	0x37,0x37,0x37,0x37,0x3d,0x2e,0x2e,0x2e,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x38,0x37,0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x2e,0x2e,
	0x2e,0x2e,0x2f,0x31,0x32,0x32,0x30,0x2f,0x2e,0x2e,
	0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x39,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,0x37,
	0x37,0x40,0x41,0x40,0x41,0x40,0x41,0x40,0x41,0x40,
	0x41,0x40,0x41,0x40,0x41,0x40,0x41,0x40,0x41,0x40,
	0x44,0x43,0x44,0x43,0x44,0x43,0x44,0x43,0x44,0x43,
	0x44,0x43,0x44,0x43
};

const unsigned char test_level[] =
{
	0x37,0x31,0x2F,0x32,0x32,0x2F,0x30,0x31,0x32,0x2F,
	0x32,0x2F,0x31,0x30,0x2F,0x32,0x32,0x31,0x37,0x37,
	0x3C,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x38,0x37,
	0x3D,0x2E,0x2E,0x48,0x2E,0x2E,0x2E,0x2E,0x2E,0x48,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x48,0x2E,0x2E,0x39,0x37,
	0x3C,0x2E,0x2E,0x2E,0x2E,0x2E,0x48,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x48,0x2E,0x2E,0x2E,0x2E,0x2E,0x38,0x37,
	0x3F,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x3A,0x37,
	0x3D,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x39,0x37,
	0x3C,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x36,0x37,
	0x3C,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x36,0x37,
	0x3D,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x36,0x37,
	0x3F,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x36,0x37,
	0x34,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x36,0x37,
	0x34,0x2E,0x2E,0x2E,0x49,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x36,0x37,
	0x37,0x33,0x33,0x33,0x33,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x33,0x33,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x37,0x37,0x37,0x37,
	0x37,0x37,0x37,0x37,0x37,0x2E,0x2E,0x2E,0x2E,0x2E,
	0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x37,0x37,0x37,0x37,
	0x44,0x43,0x44,0x43,0x44,0x40,0x41,0x40,0x41,0x40,
	0x41,0x40,0x41,0x40,0x41,0x40,0x44,0x43,0x44,0x43,
	0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,
	0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42
};

//level dimensions as number of tiles
const UINT8 levels_width[] = {20,33,20};
const UINT8 levels_height[] = {18,18,18};

const UINT8 gems_required[] = {1,2,2};

//spawn points in pixels
const UINT8 spawns_x[] = {12, 20, 20};
const UINT8 spawns_y[] = {80, 60, 60};

//references to each tilemap for background loading
const unsigned char *levels[] = {&level01[0], &level02[0], &test_level[0]};