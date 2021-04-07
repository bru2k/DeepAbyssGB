#include <gb/gb.h>

/*
*	Wait for the screen to fully refresh (V-Sync)
*	frames - the number of V-Blank cycles to wait
*/
void vbl_wait(UINT8 frames);

BOOLEAN faded_out;	//	True if the screen is faded out to a solid color

/*
*	Fade functions
*	interval - the number of times a function has to be called per fade step
*/
void fade_to_black(UINT8 interval);
void fade_from_black(UINT8 interval);
void fade_to_white(UINT8 interval);
void fade_from_white(UINT8 interval);
