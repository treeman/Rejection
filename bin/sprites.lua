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
    {   name = "dude_head",
        path = "gfx/objects.png",
        x = 0, y = 1 * box, w = box, h = box, },  
        
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
        
    -- time machine
    {   name = "timemachine",
        path = "gfx/objects.png",
        x = 4 * box, y = 2 * box, w = box, h = box, },
}
