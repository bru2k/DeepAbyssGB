#include <gb/gb.h>
#include "input.c"
#include "menus.c"
#include "hudmaps.c"
#include "levels.c"
#include "game.c"
#include "scenes.c"
#include "graphics.c"

#include "tiles/hudtiles.c"
#include "tiles/cavetiles.c"
#include "tiles/herotiles.c"
#include "tiles/bubbletiles.c"

void main()
{
	DISPLAY_ON;
	
	//check LCD status every hblank
	STAT_REG = 0x44;
	
	//load HUD tiles to window / background VRAM
	set_win_data(0, 46, hud_tiles);
	
	faded_out = FALSE;
	
	while(1)
	{
		switch(scene)
		{
			case TITLE:
				//LCD interrupt handler at the last H-Blank
				LYC_REG = 143;
				
				disable_interrupts();
				add_LCD(menu_LCD);
				add_VBL(menu_VBL);
				enable_interrupts();
				set_interrupts(VBL_IFLAG | LCD_IFLAG);
				
				//load title screen
				set_win_tiles(0, 0, 20, 3, title_win);
				set_bkg_data(46, 10, title_tiles);
				set_bkg_tiles(0, 0, 20, 32, title_bkg);
				
				move_win(7, 40);
				move_bkg(0, 0);

				SHOW_WIN;
				SHOW_BKG;
				HIDE_SPRITES;
				
				//fade in title screen
				while(faded_out == TRUE)
				{
					menu_update();
					fade_from_white(4);
					vbl_wait(2);
				}
				
				//title screen loop
				while(1)
				{
					menu_update();
					
					//continue to level selection
					if(key_down(J_A) || key_down(J_START))  
					{
						//fade out title screen
						while(faded_out == FALSE)
						{
							menu_update();
							fade_to_black(4);
							vbl_wait(2);
						}
						
						//remove menu-specific interrupt handlers
						disable_interrupts;
						remove_LCD(menu_LCD);
						remove_VBL(menu_VBL);
						enable_interrupts;
						
						//return background to its origin
						move_bkg(0, 0);
						
						scene = SELECTION;
						break;
					}
					previous_keys = joypad();
					vbl_wait(2);
				}
				break;
			
			case SELECTION:
				//level selection only uses the background
				HIDE_WIN;
				
				//change the displayed level number to selected
				selection_bkg[172] = 0x04 + selected / 10;
				selection_bkg[173] = 0x04 + selected % 10;
				
				set_bkg_tiles(0, 0, 20, 18, selection_bkg);
				
				//fade in level selection
				while(faded_out == TRUE)
				{
					fade_from_black(4);
					vbl_wait(2);
				}
				
				while(1)
				{
					selection_update();
					
					//continue to game
					if(key_down(J_A) || key_down(J_START))
					{
						while(faded_out == FALSE)
						{
							fade_to_black(4);
							vbl_wait(2);
						}
						
						//move window and backgroun to their origins, for some reason window has an X offset of 7
						move_win(7, 0);
						move_bkg(0, 0);
						
						set_win_tiles(0, 0, 20, 2, game_win);
						
						//load cave tiles to window / background VRAM
						set_bkg_data(46, 28, cave_tiles);
						
						level_width = levels_width[selected-1];
						level_height = levels_height[selected-1];
						
						//copy selected level's tilemap
						for(int j = 0; j < level_height; j++)
						{
							for(int i = 0; i < level_width; i++)
							{
								level[level_width * j + i] = levels[selected-1][level_width * j + i];
							}
						}
						
						set_bkg_tiles(0, 0, level_width, level_height, level);
						
						set_sprite_data(0, 16, hero_tiles);
						set_sprite_data(16, 8, bubble_tiles);
						setup(spawns_x[selected-1], spawns_y[selected-1]);
						LYC_REG = 9;
						disable_interrupts();
						add_LCD(game_LCD);
						add_VBL(game_VBL);
						enable_interrupts();
						set_interrupts(VBL_IFLAG | LCD_IFLAG);
						SHOW_WIN;
						scene = GAME;
						break;
					}
					previous_keys = joypad();
					vbl_wait(4);
				}
				break;
			
			case GAME:
				//fade in game
				while(faded_out == TRUE)
				{
					fade_from_black(4);
					vbl_wait(2);
				}
				
				while(scene == GAME)
				{
					game_update();
					previous_keys = joypad();
					vbl_wait(1);
				}
				break;
		}
	}
}