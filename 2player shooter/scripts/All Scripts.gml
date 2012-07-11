#define scr_obj_guyHandleKeys
if (keyboard_check_pressed(leftKey) or keyboard_check_pressed(rightKey))
{
    if (runCheckTimer = 0) {
        runCheckTimer = runCheckTimerStart
        }
    else {
        runSpeed = 2
        }
}
if (runCheckTimer > 0)
{
runCheckTimer = runCheckTimer - 1
}

if (keyboard_check(leftKey))
{
    x -= moveSpeed * runSpeed;
    sprite_index = leftSprite
}
else if (keyboard_check(rightKey))
{
    x += moveSpeed * runSpeed;
    sprite_index = rightSprite
}

if (runSpeed = 2 ){
    runDustTimer -= 1
    if (runDustTimer <= 0 and landed = 1){
        instance_create(x,y + 64 - 16, dustObject)
        runDustTimer = runDustTimerStart
    }
}

if (keyboard_check(upKey))
{
    if (collision_rectangle(x,y + 64,x + sprite_width,y + 66,platform,false,true))
    {
        vspeed = -16
    }
}

if (!keyboard_check(leftKey) and !keyboard_check(rightKey))
    {
        runSpeed = 1
        runDustTimer = 0
    }

#define scr_obj_guyLeftGuySettings
leftKey = ord("A")
rightKey = ord("D")
upKey = ord("W")
fireKey = vk_space
rightSprite = spr_black_guy_right
leftSprite = spr_black_guy_left
dustObject = obj_green_dust
rightLitUpSprite = spr_green_guy_right
rightLitUpSprite = spr_green_guy_left


#define scr_obj_guyRightGuySettings
leftKey = vk_left
rightKey = vk_right
upKey = vk_up
fireKey = vk_enter
rightSprite = spr_black_guy_right
leftSprite = spr_black_guy_left
dustObject = obj_red_dust
rightLitUpSprite = spr_red_guy_right
rightLitUpSprite = spr_red_guy_left


#define scr_obj_guyHandleGravity
if (collision_rectangle(x,y + 64,x + sprite_width,y + 66,platform,false,true)){
    gravity = 0
    vspeed = 0
    if (landed = 0)
    {
        landed = 1
        instance_create(x,y + 64 - 16, dustObject)
        effect_create_above(ef_flare, x, y + 64, 2, c_white)
        runDustTimer = runDustTimerStart
    }
    }
else {
    landed = 0
    gravity = 1
    gravity_direction = 270
    if (vspeed > 8)
    {
        vspeed = 8
    }
}


#define scr_obj_dustDustTimer
timer -= 1
if (timer <= 0){
    instance_destroy()
}

#define scr_obj_guyCreateVariables
facing = 0
moveSpeed = 3
landed = 0
runSpeed = 1
runCheckTimer = 0
runCheckTimerStart = 10
runDustTimer = 0
runDustTimerStart = 8

