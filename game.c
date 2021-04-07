#include <gb/gb.h>
#include "input.h"
#include "graphics.h"
#include "scenes.h"
#include "tiles/cavetiles.h"

#define SPRITE_SIZE				8
#define MOVING_VERTICALLY       0x08
#define MOVING_HORIZONTALLY     0x04
#define JUMPING                 0x02
#define FACING_RIGHT            0x01

//4x4 sprite
typedef struct metasprite
{
    UBYTE tile_ids[16]; //subsprites
	
	//coordinates
    UINT8 world_x;
    UINT8 world_y;
	
	//screen position
    UINT8 x;
    UINT8 y;
} metasprite;

//current level
unsigned char level[40*40];
UINT8 level_width;
UINT8 level_height;

//4x the pixel difference per frame of falling
UINT8 gravity;

/*
bits 7-4: previous movement state
bits 3-0: current movement state
single movement state starting at MSB: moving vertically, moving horizontally, jumping, facing right
*/
UINT8 movement = MOVING_VERTICALLY | FACING_RIGHT;

//animation / movement refreshes
UINT8 game_refresh = 0;
UINT8 walking_refresh = 6;
UINT8 jumping_refresh = 0;
UINT8 falling_refresh = 0;

BOOLEAN h_swapped = FALSE; //have the tiles in the level's tilemap been swapped vertically
BOOLEAN standing = FALSE;
BOOLEAN blocked_left = FALSE;
BOOLEAN blocked_right = FALSE;
BOOLEAN requirement_met = FALSE;

//stats and items
UINT8 lives = 3;
UINT8 gems = 0;
UINT8 score = 0;
UINT8 chutes = 0; //number of parachutes in the inventory

metasprite hero;
metasprite bubble;

//drawing the game HUD - interrupt handlers
void game_LCD()
{
    if(LYC_REG == 143)
    {
        SHOW_WIN;
        LYC_REG = 9;
    }
    else
    {
        HIDE_WIN;
		SHOW_SPRITES;
        LYC_REG = 143; //show window on the last H-Blank, if it's only done in the V-Blank some artifacts appear on screen
    }
}

void game_VBL()
{
	HIDE_SPRITES; //hiding sprites to not overlap the HUD
}

//drawing the results / gameover window - interrupt handlers
void window_LCD()
{
	if(LYC_REG == 143)
    {
        SHOW_WIN;
        LYC_REG = 99;
    }
    else
    {
        HIDE_WIN;
		SHOW_SPRITES;
        LYC_REG = 143; //show window on the last H-Blank, if it's only done in the V-Blank some artifacts appear on screen
    }
}

void window_VBL()
{
	HIDE_SPRITES; //hiding sprites to not overlap the window
}

//updating HUD
void update_gems()
{
	game_win[1] = 0x04 + (gems / 10) % 10;
    game_win[2] = 0x04 + gems % 10;
	set_win_tiles(1, 0, 2, 1, game_win + 1);
}

void update_chutes()
{
	game_win[5] = 0x04 + chutes;
	set_win_tiles(5, 0, 2, 1, game_win + 5);
}

void update_score()
{
	game_win[8] = 0x04 + (score / 1000) % 10;
    game_win[9] = 0x04 + (score / 100) % 10;
    game_win[10] = 0x04 + (score / 10) % 10;
    game_win[11] = 0x04 + score % 10;
	set_win_tiles(8, 0, 4, 1, game_win + 8);
}

void update_lives()
{
	game_win[19] = 0x04 + lives;
	set_win_tiles(19, 0, 1, 1, game_win + 19);
}

char getTileAt(int x, int y)
{
	return(*(level + (x / 8) + (y / 8) * level_width));
}

//returns a tile at world coordinates (x,y)
char get_tile_at(int x, int y)
{
	if(x < 256)
	{
		return(*(level + (x / 8) + (y / 8) * level_width));
	}
	else
	{
		return(*(level + ((x - 255) / 8) + (y / 8) * level_width));
	}
}

//replaces a tile in the level tilemap
void set_tile_at(int x, int y, int tile_id)
{
    *(level + (x / 8) + (y / 8) * level_width) = tile_id;
}

//moving all 4 subsprites
void move_metasprite(metasprite *ms, UINT8 x, UINT8 y)
{
    move_sprite(ms->tile_ids[0], x + 6, y);
    move_sprite(ms->tile_ids[1], x + SPRITE_SIZE + 6, y);
    move_sprite(ms->tile_ids[2], x + 6, y + SPRITE_SIZE);
    move_sprite(ms->tile_ids[3], x + SPRITE_SIZE + 6, y + SPRITE_SIZE);
}

//setting up the level to its initial state
void setup(UINT8 spawn_x, UINT8 spawn_y)
{
	//handling spawns at both ends of a level (wip)
	if(spawn_x > 176)
	{
		h_swapped = TRUE;
		movement = MOVING_VERTICALLY;
	}
	else
	{
		h_swapped = FALSE;
		movement = MOVING_VERTICALLY | FACING_RIGHT;
	}
	
	gravity = 4;
	walking_refresh = 6;
	jumping_refresh = 0;
	falling_refresh = 0;
	requirement_met = FALSE;
	
	//hero setup
    hero.world_x = spawn_x;
    hero.world_y = spawn_y;
    hero.x = spawn_x;
    hero.y = spawn_y;
	//set sprites to base tiles
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
	//assign sprites to metasprite
	hero.tile_ids[0] = 0;
    hero.tile_ids[1] = 1;
    hero.tile_ids[2] = 2;
    hero.tile_ids[3] = 3;
    move_metasprite(&hero, hero.x, hero.y);
	
	//bubbles setup - wip
	bubble.world_x = 12;
    bubble.world_y = 60;
    bubble.x = 12;
    bubble.y = 60;
    set_sprite_tile(4, 16);
    set_sprite_tile(5, 17);
    set_sprite_tile(6, 18);
    set_sprite_tile(7, 19);
	bubble.tile_ids[0] = 4;
    bubble.tile_ids[1] = 5;
    bubble.tile_ids[2] = 6;
    bubble.tile_ids[3] = 7;
    move_metasprite(&bubble, bubble.x, bubble.y);
	
	update_gems();
	update_chutes();
	update_score();
	update_lives();
}

//wip
void move_bubbles()
{
	bubble.world_y--;
	bubble.y--;
	move_metasprite(&bubble, bubble.x, bubble.y);
}

void walk_left()
{
	//loop walking animation
    if(walking_refresh > 29)
    {
        walking_refresh = 6;
    }
    
    if(!(movement & MOVING_VERTICALLY))
    {
        set_sprite_tile(0, 1);
        set_sprite_tile(1, 0);
		
		//change legs frames
        set_sprite_tile(2, 3 + walking_refresh / 6 * 2);
        set_sprite_tile(3, 2 + walking_refresh / 6 * 2);
    }
    if((movement & FACING_RIGHT))
    {
		//flip the sprites if hero's direction has changed
        set_sprite_prop(0, S_FLIPX);
        set_sprite_prop(1, S_FLIPX);
        set_sprite_prop(2, S_FLIPX);
        set_sprite_prop(3, S_FLIPX);
		
        movement = movement & ~FACING_RIGHT;
    }

    movement = movement | MOVING_HORIZONTALLY;

    if(!blocked_left)
    {
        hero.world_x--;
		
		//keep hero in the center of the screen when he's more than 80 pixels away from the levels edges
        if(hero.world_x < 80)
        {
            hero.x = hero.world_x;
            move_metasprite(&hero, hero.x, hero.y);
        }
        else if(hero.world_x > level_width * 8 - 81)
        {
            hero.x = 160 - (level_width * 8 - hero.world_x);
            move_metasprite(&hero, hero.x, hero.y);
        }
        else
        {
			//move the background and bubbles relatively
            scroll_bkg(-1, 0);
			bubble.x++;
        }
		
		//swap the tiles back to their original location when the player is one tile away from seeing the left edge of the level
		if(h_swapped && hero.world_x < 89)
		{
			for(int y = 0; y < 18; y++)
			{
				unsigned char tile = getTileAt(0, y * 8);
				set_tile_at(0, y * 8, getTileAt(32 * 8, y * 8));
				set_tile_at(32 * 8, y * 8, tile);
			}
			set_bkg_tiles(0, 0, level_width, level_height, level);
			h_swapped = FALSE;
		}
    }
    walking_refresh++;
}

void walk_right() {
	//loop walking animation
    if(walking_refresh > 29)
    {
        walking_refresh = 6;
    }

    if(!(movement & MOVING_VERTICALLY))
    {
        set_sprite_tile(0, 0);
        set_sprite_tile(1, 1);
		
		//change legs frames
        set_sprite_tile(2, 2 + walking_refresh / 6 * 2);
        set_sprite_tile(3, 3 + walking_refresh / 6 * 2);
    }
    if(!(movement & FACING_RIGHT))
    {
        set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
        set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(2, get_sprite_prop(2) & ~S_FLIPX);
        set_sprite_prop(3, get_sprite_prop(3) & ~S_FLIPX);
        movement = movement | FACING_RIGHT;
    }

    movement = movement | MOVING_HORIZONTALLY;

    if(!blocked_right)
    {
        hero.world_x++;
		
		//keep hero in the center of the screen when he's more than 80 pixels away from the levels edges
        if(hero.world_x < 81)
        {
            hero.x = hero.world_x;
            move_metasprite(&hero, hero.x, hero.y);
        }
        else if(hero.world_x > level_width * 8 - 80)
        {
            hero.x = 160 - (level_width * 8 - hero.world_x);
            move_metasprite(&hero, hero.x, hero.y);
        }
        else
        {
            scroll_bkg(1, 0);
			bubble.x--;
        }
		
		//swap the edges tiles when the player is one tile away from seeing the right edge of the level
		if(!h_swapped && hero.world_x > 176)
		{
			for(int y = 0; y < 18; y++)
			{
				unsigned char tile = getTileAt(0, y * 8);
				set_tile_at(0, y * 8, getTileAt(32 * 8, y * 8));
				set_tile_at(32 * 8, y * 8, tile);
			}
			set_bkg_tiles(0, 0, level_width, level_height, level);
			h_swapped = TRUE;
		}
    }
    walking_refresh++;
}

void jump()
{
	//differences found by frame-by-frame analysis of the original game
    switch(jumping_refresh)
    {
        case 1:
            hero.world_y = hero.world_y - 7;
            hero.y = hero.y - 7;
            break;
        case 4:
            hero.world_y = hero.world_y - 6;
            hero.y = hero.y - 6;
            break;
        case 7:
            hero.world_y = hero.world_y - 2;
            hero.y = hero.y - 2;
            break;
        case 9:
            hero.world_y = hero.world_y - 4;
            hero.y = hero.y - 4;
            break;
        case 12:
            hero.world_y = hero.world_y - 2;
            hero.y = hero.y - 2;
            break;
        case 15:
            hero.world_y = hero.world_y - 1;
            hero.y = hero.y - 1;
            break;
        case 18:
            hero.world_y = hero.world_y - 1;
            hero.y = hero.y - 1;
            break;
        
        case 21:
            hero.world_y = hero.world_y - 2;
            hero.y = hero.y - 2;
            break;

        case 26:
            jumping_refresh = 0;
            movement = movement & ~JUMPING;
            break;
    }
	
	//jumping animation frame
    if(movement & FACING_RIGHT)
    {
        set_sprite_tile(0, 12);
        set_sprite_tile(1, 13);
        set_sprite_tile(2, 14);
        set_sprite_tile(3, 15);
    }
    else
    {
        set_sprite_tile(0, 13);
        set_sprite_tile(1, 12);
        set_sprite_tile(2, 15);
        set_sprite_tile(3, 14);
    }
	
    move_metasprite(&hero, hero.x, hero.y);
    jumping_refresh++;
}

void fall()
{
	//cancel parachute
	if(key_up(J_B))
	{
		gravity = 4;
	}
	
	if((falling_refresh * gravity) % 4 == 0)
	{
		hero.world_y = hero.world_y + 1;
		hero.y = hero.y + 1;
	}

	//show the falling animation frame (wip, it's the same as jumping so far)
    if(movement & FACING_RIGHT)
    {
        set_sprite_tile(0, 12);
        set_sprite_tile(1, 13);
        set_sprite_tile(2, 14);
        set_sprite_tile(3, 15);
    }
    else
    {
        set_sprite_tile(0, 13);
        set_sprite_tile(1, 12);
        set_sprite_tile(2, 15);
        set_sprite_tile(3, 14);
    }
    move_metasprite(&hero, hero.x, hero.y);
	
	falling_refresh++;
}

void stop()
{
	//setting up the standing animation frame
    if(!(movement & MOVING_HORIZONTALLY))
    {
		if(movement & FACING_RIGHT)
		{
			set_sprite_tile(0, 0);
			set_sprite_tile(1, 1);
			set_sprite_tile(2, 2);
			set_sprite_tile(3, 3);
		}
		else
		{
			set_sprite_tile(0, 1);
			set_sprite_tile(1, 0);
			set_sprite_tile(2, 3);
			set_sprite_tile(3, 2);
		}
    }
	
	//turning direction
    if(((movement >> 4) & FACING_RIGHT) && !(movement & FACING_RIGHT))
    {
        set_sprite_prop(0, S_FLIPX);
        set_sprite_prop(1, S_FLIPX);
        set_sprite_prop(2, S_FLIPX);
        set_sprite_prop(3, S_FLIPX);
    }

    if(!((movement >> 4) & FACING_RIGHT) && (movement & FACING_RIGHT))
    {
        set_sprite_prop(0, get_sprite_prop(0) & ~S_FLIPX);
        set_sprite_prop(1, get_sprite_prop(0) & ~S_FLIPX);
        set_sprite_prop(2, get_sprite_prop(0) & ~S_FLIPX);
        set_sprite_prop(3, get_sprite_prop(0) & ~S_FLIPX);
    }
}

void die()
{
	lives--;
	if(lives < 1) //gameover
	{
		//reset progress
		gems = 0;
		score = 0;
		chutes = 0;
		lives = 3;
		selected = 1;
		unlocked = 1;
		
		while(!faded_out)
		{
			fade_to_white(4);
			vbl_wait(2);
		}
		
		//set up the gameover window
		set_win_tiles(0, 0, 20, 7, gameover_win);
		move_win(7, 44);
		disable_interrupts();
		LYC_REG = 99;
		remove_LCD(game_LCD);
		remove_VBL(game_VBL);
		add_LCD(window_LCD);
		add_VBL(window_VBL);
		enable_interrupts();
		
		while(faded_out)
		{
			fade_from_white(4);
			vbl_wait(2);
		}
			
		while(1)
		{
			if(key_down(J_A) || key_down(J_START)) //return to the title screen
			{
				disable_interrupts();
				remove_LCD(window_LCD);
				remove_VBL(window_VBL);
				enable_interrupts();
		
				while(!faded_out)
				{
					fade_to_white(4);
					vbl_wait(2);
				}
				
				scene = TITLE;
				break;
			}
			vbl_wait(2);
		}
	}
	else //continue the game
	{
		while(!faded_out)
		{
			fade_to_black(4);
			vbl_wait(2);
		}
		
		//reset level background's location and tilemap
		move_bkg(0, 0);
		for(int j = 0; j < level_height; j++)
		{
			for(int i = 0; i < level_width; i++)
			{
				level[level_width * j + i] = levels[selected-1][level_width * j + i];
			}
		}
		set_bkg_tiles(0, 0, level_width, level_height, level);
		setup(spawns_x[selected-1], spawns_y[selected-1]);
		
		while(faded_out)
		{
			fade_from_black(4);
			vbl_wait(2);
		}
	}
}

void check_collisions()
{
    standing = 0;
	blocked_left = 0;
	blocked_right = 0;
	
	//left foot standing
    if(get_tile_at((unsigned int) (hero.world_x + 2 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x + 2 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y) < 64)
		{	
			standing = 1;
			gravity = 4;
			movement = movement & ~MOVING_VERTICALLY;
		}
	}
	//or right foot standing
	else if(get_tile_at((unsigned int) (hero.world_x + 10 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x + 10 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y) < 64)
		{
			standing = 1;
			gravity = 4;
			movement = movement & ~MOVING_VERTICALLY;
		}
    }
	
	//left foot touching lava
    if(get_tile_at((unsigned int) (hero.world_x + 2 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 6) > 63
	&& get_tile_at((unsigned int) (hero.world_x + 2 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 6) < 69)
    {
		die();
    }
	//or right foot touching lava
	else if(get_tile_at((unsigned int) (hero.world_x + 10 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 6) > 63
	&& get_tile_at((unsigned int) (hero.world_x + 10 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 6) < 69)
    {
		die();
    }

    //left foot hit a wall
    if(get_tile_at((unsigned int) (hero.world_x - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 1) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 1) < 64)
        {
			blocked_left = 1;
		}
		else if(requirement_met && get_tile_at((unsigned int) (hero.world_x - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 1) == 71)  //complete level
		{
			
		}
    }
	
	if(get_tile_at((unsigned int) (hero.world_x + 1 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 9) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x + 1 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 9) < 64)
        {
			blocked_left = 1;
		}
    }
	
	//left side head hit the ceiling
    if(get_tile_at((unsigned int) (hero.world_x + 1 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 7) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x + 1 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 7) < 64)
        {
			blocked_left = 1;
			movement = movement & ~JUMPING;
			jumping_refresh = 0;
		}
    }
	
	if(get_tile_at((unsigned int) (hero.world_x + 2 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 13) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x + 2 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 13) < 64)
        {
			blocked_left = 1;
			movement = movement & ~JUMPING;
			jumping_refresh = 0;
		}
    }

    //right foot hit a wall
	if(get_tile_at((unsigned int) (hero.world_x + 12 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 1) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x + 12 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 1) < 64)
        {
			blocked_right = 1;
		}
		else if(requirement_met && get_tile_at((unsigned int) (hero.world_x + 12 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 1) == 71)  //complete level
		{
			while(!faded_out)
			{
				fade_to_white(4);
				vbl_wait(1);
			}
			
			//set up the complete window
			//display stats
			complete_win[94] = 0x04 + gems_required[0] / 10;
			complete_win[95] = 0x04 + gems_required[0] % 10;
			complete_win[113] = 0x04 + gems / 10;
			complete_win[114] = 0x04 + gems % 10;
			set_win_tiles(0, 0, 20, 7, complete_win);
			move_win(7, 44);
			LYC_REG = 99;
			disable_interrupts();
			remove_LCD(game_LCD);
			remove_VBL(game_VBL);
			add_LCD(window_LCD);
			add_VBL(window_VBL);
			enable_interrupts();
			
			//if a level has not been finished before unlock the next level
			if(selected == unlocked)
			{
				selected++;
				unlocked++;
			}
			
			while(faded_out)
			{
				fade_from_white(4);
				vbl_wait(2);
			}
			
			while(1)
			{
				if(key_down(J_A) || key_down(J_START)) //return to level selection
				{
					while(!faded_out)
					{
						fade_to_black(4);
						vbl_wait(2);
					}
					
					disable_interrupts;
					remove_LCD(window_LCD);
					remove_VBL(window_VBL);
					enable_interrupts;
					move_bkg(0, 0);
					set_bkg_tiles(0, 0, 20, 18, selection_bkg);
					scene = SELECTION;
					break;
				}
				vbl_wait(2);
			}
		}
    }
	
	if(get_tile_at((unsigned int) (hero.world_x + 11 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 9) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x + 11 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 9) < 64)
        {
			blocked_right = 1;
		}
    }
	
	//right side head hit the ceiling
    if(get_tile_at((unsigned int) (hero.world_x + 11 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 7) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x + 11 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 7) < 64)
        {
			blocked_right = 1;
			movement = movement & ~JUMPING;
			jumping_refresh = 0;
		}
    }
	
	if(get_tile_at((unsigned int) (hero.world_x + 10 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 13) > 46)
    {
		if(get_tile_at((unsigned int) (hero.world_x + 10 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 13) < 64)
        {
			blocked_right = 1;
			movement = movement & ~JUMPING;
			jumping_refresh = 0;
		}
    }

    //pickup gems
    if(get_tile_at((unsigned int) (hero.world_x + 8 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 10) == 72)
    {
        set_tile_at((unsigned int) (hero.world_x + 8 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 10, 46); // replace with empty tile
    
        set_bkg_tiles(0, 0, level_width, level_height, level);
        
        score += 10;
		gems++;
		update_gems();
		update_score();
        if(gems >= gems_required[selected-1])
		{
			requirement_met = TRUE;
		}
    }
    else if(get_tile_at((unsigned int) (hero.world_x + 4 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 10) == 72)
    {
        set_tile_at((unsigned int) (hero.world_x + 4 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 10, 46); // replace with empty tile
    
        set_bkg_tiles(0, 0, level_width, level_height, level);
        
		score += 10;
		gems++;
		update_gems();
		update_score();
        if(gems >= gems_required[selected-1])
		{
			requirement_met = TRUE;
		}
    }
    else if(get_tile_at((unsigned int) (hero.world_x + 8 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 2) == 72)
    {
        set_tile_at((unsigned int) (hero.world_x + 8 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 2, 46); // replace with empty tile
    
        set_bkg_tiles(0, 0, level_width, level_height, level);
        
        score += 10;
		gems++;
		update_gems();
		update_score();
        if(gems >= gems_required[selected-1])
		{
			requirement_met = TRUE;
		}
    }
    else if(get_tile_at((unsigned int) (hero.world_x + 4 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 2) == 72)
    {
        set_tile_at((unsigned int) (hero.world_x + 4 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 2, 46); // replace with empty tile
    
        set_bkg_tiles(0, 0, level_width, level_height, level);
        
        score += 10;
		gems++;
		update_gems();
		update_score();
        if(gems >= gems_required[selected-1])
		{
			requirement_met = TRUE;
		}
    }
	
	//pickup parachute
    if(get_tile_at((unsigned int) (hero.world_x + 8 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 10) == 73)
    {
        set_tile_at((unsigned int) (hero.world_x + 8 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 10, 46); // replace with empty tile
    
        set_bkg_tiles(0, 0, level_width, level_height, level);
        
		score += 5;
        chutes++;
		update_chutes();
		update_score();
    }
    else if(get_tile_at((unsigned int) (hero.world_x + 4 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 10) == 73)
    {
        set_tile_at((unsigned int) (hero.world_x + 4 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 10, 46); // replace with empty tile
    
        set_bkg_tiles(0, 0, level_width, level_height, level);
        
		score += 5;
		chutes++;
		update_chutes();
		update_score();
    }
    else if(get_tile_at((unsigned int) (hero.world_x + 8 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 2) == 73)
    {
        set_tile_at((unsigned int) (hero.world_x + 8 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 2, 46); // replace with empty tile
    
        set_bkg_tiles(0, 0, level_width, level_height, level);
        
		score += 5;
        chutes++;
		update_chutes();
		update_score();
    }
    else if(get_tile_at((unsigned int) (hero.world_x + 4 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 2) == 73)
    {
        set_tile_at((unsigned int) (hero.world_x + 4 - (movement & FACING_RIGHT)), (unsigned int) hero.world_y - 2, 46); // replace with empty tile
    
        set_bkg_tiles(0, 0, level_width, level_height, level);
        
		score += 5;
        chutes++;
		update_chutes();
		update_score();
    }

    if(standing)
    {
        movement = movement & ~MOVING_VERTICALLY;
        stop();
    }
    else
    {
        movement = movement | MOVING_VERTICALLY;
    }
}

void animate_level()
{	
	if((game_refresh + 1) & 10)
	{
		//animate lava and exit
		switch(game_refresh + 1)
		{
			case 10:
				set_bkg_data(64, 5, lava_tiles+80);
				break;

			case 20:
				set_bkg_data(64, 5, lava_tiles+160);
				break;

			case 30:
				set_bkg_data(64, 5, lava_tiles+240);
				break;

			case 40:
				set_bkg_data(64, 5, lava_tiles+320);
				if(requirement_met) //the exit is flashing when the requirement has been met
				{
					set_bkg_data(69, 2, exit_tiles+32);
				}
				break;

			case 50:
				set_bkg_data(64, 5, lava_tiles+400);
				break;
				
			case 60:
				set_bkg_data(64, 5, lava_tiles+480);
				break;

			case 70:
				set_bkg_data(64, 5, lava_tiles);
				if(requirement_met) //the exit is flashing when the requirement has been met
				{
					set_bkg_data(69, 2, exit_tiles);
				}
				game_refresh = 0;
				break;
		}
    }
}

void movement_update()
{
	if(joypad() & J_LEFT)    
	{
		walk_left();
	}
	
	if(joypad() & J_RIGHT)  
    {
		walk_right();
	}
	
	if(movement & MOVING_VERTICALLY)
	{
		//open parachute in air
		if(chutes > 0 && key_down(J_B))
		{
			chutes--;
			update_chutes();
			movement = movement & ~JUMPING;
			gravity = 1;
		}
			
		if(movement & JUMPING)
		{		
			jump();
		}
		else
		{
			fall();
		}
	}
	else if(key_down(J_A))
	{
		movement = movement | MOVING_VERTICALLY | JUMPING;
		jump();
	}
        
    //check if the movement state has been changed   
	if((movement >> 4) != (movement & (MOVING_VERTICALLY | MOVING_HORIZONTALLY | JUMPING | FACING_RIGHT)))
	{
		//reset walking animation
		walking_refresh = 3;
		stop();
	}
	
	//shift movement states, copying the current movement state (skipping the horizontal bit)
	movement = (movement << 4) + (movement & (MOVING_VERTICALLY | JUMPING | FACING_RIGHT));
}

void game_update()
{
	check_collisions();
	movement_update();
	if((game_refresh + 1) % 2 == 0)
	{
		move_bubbles();
	}
	animate_level();
	game_refresh++;
}