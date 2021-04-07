#include <gb/gb.h>

UINT8 effects_refresh; // For timing fades

BOOLEAN faded_out = FALSE;

void vbl_wait(UINT8 frames)
{
	for(int i = 0; i < frames; i++)
	{
		wait_vbl_done();
	}
}

void fade_to_black(UINT8 interval)
{
	if(effects_refresh + 1 == interval)
	{
		switch(BGP_REG)
		{
			case 0b11100100:
				BGP_REG = 0b11111001;
				OBP0_REG = 0b11110001;
				effects_refresh = 0;
				break;
			
			case 0b11111001:
				BGP_REG = 0b11111110;
				OBP0_REG = 0b11111101;
				effects_refresh = 0;
				break;
				
			case 0b11111110:
				BGP_REG = 0b11111111;
				OBP0_REG = 0b11111101;				
				effects_refresh = 0;
				faded_out = TRUE;
				break;	
		}
	}
	effects_refresh++;
}

void fade_from_black(UINT8 interval)
{
	if(effects_refresh + 1 == interval)
	{
		switch(BGP_REG)
		{
			case 0b11111111:
				BGP_REG = 0b11111110;
				OBP0_REG = 0b11111101;
				effects_refresh = 0;
				break;
			
			case 0b11111110:
				BGP_REG = 0b11111001;
				OBP0_REG = 0b11111001;
				effects_refresh = 0;
				break;
				
			case 0b11111001:
				BGP_REG = 0b11100100;
				OBP0_REG = 0b11100001;
				effects_refresh = 0;
				faded_out = FALSE;
				break;	
		}
	}
	effects_refresh++;
}

void fade_to_white(UINT8 interval)
{
	if(effects_refresh + 1 == interval)
	{
		switch(BGP_REG)
		{
			case 0b11100100:
				BGP_REG = 0b10010000;
				OBP0_REG = 0b10000001;
				effects_refresh = 0;
				break;
			
			case 0b10010000:
				BGP_REG = 0b01000000;
				OBP0_REG = 0b00000001;
				effects_refresh = 0;
				break;
				
			case 0b01000000:
				BGP_REG = 0b00000000;				
				effects_refresh = 0;
				faded_out = TRUE;
				break;	
		}
	}
	effects_refresh++;
}

void fade_from_white(UINT8 interval)
{
	if(effects_refresh + 1 == interval)
	{
		switch(BGP_REG)
		{
			case 0b00000000:
				BGP_REG = 0b01000000;
				OBP0_REG = 0b00000001;
				effects_refresh = 0;
				break;
			
			case 0b01000000:
				BGP_REG = 0b10010000;
				OBP0_REG = 0b10000001;
				effects_refresh = 0;
				break;
				
			case 0b10010000:
				BGP_REG = 0b11100100;
				OBP0_REG = 0b11100001;				
				effects_refresh = 0;
				faded_out = FALSE;
				break;	
		}
	}
	effects_refresh++;
}