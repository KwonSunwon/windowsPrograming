#pragma once

#include "stdafx.h"

class Object
{
protected:
    POINT position;
    RECT shape;
    BOOL isLive;
    int speed;
    BOOL deadEffect;
    int deadEffectCount;
    int type;

public:
    void move_left();
    void move_right();
    void move_up();
    void move_down();

    void dead();
    void dead_effect(HDC);

    RECT get_pos_rect();
    int get_speed();

    POINT get_position();
    POINT get_point();

    BOOL get_is_live();
};