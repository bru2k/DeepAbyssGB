# (ABANDONED)
Due to the technical limitations of the platform I must abandon this project :(
The Game Boy's VRAM contains 2 32x32 tiled background maps. In Deep Abyss includes maps which are double the width and double the height.
This means that lines of tiles need to be replaced as the background scrolls. While I could get the map to extend in horizontal and vertical
scrolling, I found implementing smooth and free diagonal scrolling impossible. In Deep Abyss the player's character can be controlled while
jumping or falling, so it is crucial that the viewpoint tracks them. There could be some workarounds to this but I wanted the project to stay
true to the original, which is why I am no longer working on it.

# DeepAbyssGB
Game Boy port of Deep Abyss, a 2D platformer originally found on Mophun-powered Sony Ericsson phones  

Original game by L. Majewski & Synergix

Reference PC port:
https://www.youtube.com/watch?v=Qy6QZZvkZ1Q

Tools used:  
GBDK-2020 https://github.com/gbdk-2020/gbdk-2020  
Gameboy Tile Designer http://www.devrs.com/gb/hmgd/gbtd.html  
Gameboy Map Builder http://www.devrs.com/gb/hmgd/gbmb.html  

Controls:  
Left/Right - walk  
A - jump  
B - hold/release to open/close parachute
