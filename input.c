#include <gb/gb.h>

UINT8 previous_keys;

BOOLEAN key_down(UINT8 key)
{
    if(!(previous_keys & key) && (joypad() & key))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

BOOLEAN key_up(UINT8 key)
{
    if((previous_keys & key) && !(joypad() & key))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}