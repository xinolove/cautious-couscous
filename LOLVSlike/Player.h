#pragma once
#include<graphics.h>

#include"animation.h"
#include"util.h"

extern IMAGE img_shadow;

class Player
{
public:
	Player()
	{
		current_animation=&anim_right;
	}
	~Player() = default;

	virtual void on_update(int delta)
	{
		shadow.x = position.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2) - 5;
		shadow.y = position.y + FRAME_HEIGHT - 8;
		
		int direction = is_move_right - is_move_left;

		
		if (direction != 0)
		{
			is_facing_right = direction > 0;
			current_animation = is_facing_right ? &anim_right : &anim_left;
		}
       
		current_animation->on_update(delta);
	}

	virtual void on_draw(const POINT& position)
	{
		putimage_alpha(shadow.x, shadow.y, &img_shadow);
		current_animation->on_draw(position .x,position.y);
	}

	virtual void on_input(const ExMessage& msg)
	{

		switch (msg.message)
		{
		case WM_KEYDOWN:
					switch (msg.vkcode)
					{
					case 87:
						is_move_up = true;
						break;
					case 83:
						is_move_down = true;
						break;
					case 0x41:
						is_move_left = true;
						break;
					case 0x44:
						is_move_right = true;
						break;
					}
					break;
		case WM_KEYUP:
					switch (msg.vkcode)
					{
					case 87:
						is_move_up = false;
						break;
					case 83:
						is_move_down = false;
						break;
					case 0x41:
						is_move_left = false;
						break;
					case 0x44:
						is_move_right = false;
						break;
					}
					break;
					}
	}

	POINT GetPosition()const {
		return position;
	}

	void set_position(int x, int y)
	{
		position.x = x, position.y = y;
	}

protected:
	POINT position = { 0,0 };
	POINT shadow = { 0,0 };
	Animation anim_left;
	Animation anim_right;
	Animation* current_animation;

	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
	bool is_facing_right = true;
	IMAGE img_shadow;
	float speed=0.55f;
public:	
	const int FRAME_WIDTH = 80;
	const int FRAME_HEIGHT = 80;
	const int SHADOW_WIDTH = 32;
	int HP = 600;
	int damage = 100;
	static int flag;
};