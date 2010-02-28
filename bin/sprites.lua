-- here are the spriteloading facility
-- be gentle with it

box = 32

sprites = {
    -- dude
    {   name = "dude_left",
        path = "gfx/objects.png",
        x = 0, y = 3 * box, w = box, h = box, },
    {   name = "dude_right",
        path = "gfx/objects.png",
        x = 0, y = 4 * box, w = box, h = box, },
    {   name = "dude_front",
        path = "gfx/objects.png",
        x = box, y = 3 * box, w = box, h = box, },
    {   name = "dude_back",
        path = "gfx/objects.png",
        x = box, y = 4 * box, w = box, h = box, },
        
    -- girl
    {   name = "girl_front",
        path = "gfx/objects.png",
        x = 2 * box, y = 3 * box, w = box, h = box, },
    
    -- dark grass
    {   name = "darkgrass_lvl1",
        path = "gfx/objects.png",
        color = 0xffb1ee49,
        x = 0, y = 0, w = box, h = box, },
    {   name = "darkgrass_lvl2",
        path = "gfx/objects.png",
        color = 0xff5c8920,
        x = 0, y = 0, w = box, h = box, },
    {   name = "darkgrass_lvl3",
        path = "gfx/objects.png",
        color = 0xff416613,
        x = 0, y = 0, w = box, h = box, },
    
    -- light grass
    {   name = "lightgrass_lvl1",
        path = "gfx/objects.png",
        color = 0xffb8f74d,
        x = 0, y = 0, w = box, h = box, },
    {   name = "lightgrass_lvl2",
        path = "gfx/objects.png",
        color = 0xff6e9d29,
        x = 0, y = 0, w = box, h = box, },
    {   name = "lightgrass_lvl3",
        path = "gfx/objects.png",
        color = 0xff476f16,
        x = 0, y = 0, w = box, h = box, },
       
    -- geek dark grass
    {   name = "geekdarkgrass_lvl1",
        path = "gfx/objects.png",
        color = 0xff9fde34,
        x = 0, y = 0, w = box, h = box, },
    {   name = "geekdarkgrass_lvl2",
        path = "gfx/objects.png",
        color = 0xff4e7618,
        x = 0, y = 0, w = box, h = box, },
    {   name = "geekdarkgrass_lvl3",
        path = "gfx/objects.png",
        color = 0xff253e05,
        x = 0, y = 0, w = box, h = box, },
    
    -- geek light grass
    {   name = "geeklightgrass_lvl1",
        path = "gfx/objects.png",
        color = 0xffaae743,
        x = 0, y = 0, w = box, h = box, },
    {   name = "geeklightgrass_lvl2",
        path = "gfx/objects.png",
        color = 0xff6a9926,
        x = 0, y = 0, w = box, h = box, },
    {   name = "geeklightgrass_lvl3",
        path = "gfx/objects.png",
        color = 0xff2f4f09,
        x = 0, y = 0, w = box, h = box, },
    
    -- life
    {   name = "dude_life",
        path = "gfx/life.png",
        x = 0, y = 0, w = 30, h = 29, },  
    -- background
    {   name = "brick",
        path = "gfx/brick.png",
        -- will expand to cover everything
        x = 0, y = 0, w = 800, h = 30, },  
        
    -- time machine
    {   name = "time_machine",
        path = "gfx/objects.png",
        x = 4 * box, y = 2 * box, w = box, h = box, },
    {   name = "hm",
        path = "gfx/objects.png",
        x = 1 * box, y = 1 * box, w = box, h = box, },
        
    -- menu 
    {   name = "menu_pointer",
        path = "gfx/objects.png",
        x = 0 * box, y = 1 * box, w = box, h = box, },
        
    -- build menu
    {   name = "build_background",
        path = "gfx/build_overlay.png",
        x = 0, y = 0, w = 168, h = 51, },
    {   name = "trap_highlight",
        path = "gfx/objects.png",
        x = 5 * box, y = 2 * box, w = box, h = box, },
    {   name = "trap_cancel",
        path = "gfx/objects.png",
        x = 3 * box, y = 3 * box, w = box, h = box, },
    
    -- traps
    {   name = "magnet_trap",
        path = "gfx/objects.png",
        x = 1 * box, y = 2 * box, w = box, h = box, },
    {   name = "blower_trap",
        path = "gfx/objects.png",
        x = 2 * box, y = 2 * box, w = box, h = box, },
    {   name = "pressure_pad",
        path = "gfx/objects.png",
        x = 3 * box, y = 2 * box, w = box, h = box, },
        
    -- flow
    {   name = "flow",
        path = "gfx/objects.png",
        color = 0xffa7d278,
        x = 1 * box, y = 0 * box, w = box, h = box, },
}
