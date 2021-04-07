#include "hudmaps.h"

UINT8 menu_refresh;
UINT8 win_top = 55;
UINT8 selected = 1;
UINT8 unlocked = 1;

void menu_LCD()
{
    if(LYC_REG == 143)
    {
        SHOW_WIN;
        LYC_REG = win_top + 23;
    }
    else
    {
        HIDE_WIN;
        LYC_REG = 143;
    }
}

void menu_VBL()
{
    SHOW_WIN;
}

void menu_update()
{
	menu_refresh++;
	scroll_bkg(0, 1);
	if(menu_refresh + 1 & 2)
	{
		if(menu_refresh + 1 < 2 * 8)
		{
			win_top++;
		}
		else if(menu_refresh + 1 < 2 * 16)
		{
			win_top--;
		}
		else
		{
			menu_refresh = 0;
		}
		move_win(7, win_top);
	}
}

void selection_update()
{
	if(key_down(J_LEFT))    
	{
		if(selected > 1)
		{
			selected--;
			selection_bkg[165] = 0x2B;
			selection_bkg[172] = 0x04 + selected / 10;
			selection_bkg[173] = 0x04 + selected % 10;
		}
	}
	else if(key_down(J_RIGHT))    
	{
		if(selected < unlocked)
		{
			selected++;
			selection_bkg[174] = 0x2D;
			selection_bkg[172] = 0x04 + selected / 10;
			selection_bkg[173] = 0x04 + selected % 10;
		}
	}
	else
	{
		selection_bkg[165] = 0x2A;
		selection_bkg[174] = 0x2C;
	}
	set_bkg_tiles(0, 0, 20, 18, selection_bkg);
}