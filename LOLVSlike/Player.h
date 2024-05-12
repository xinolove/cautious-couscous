#pragma once
#include<graphics.h>

#include"animation.h"
#include"util.h"
#include"Vector2.h"

extern IMAGE img_shadow;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;


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
		shadow.x = position.x + (size.x / 2 - SHADOW_WIDTH / 2)-10 ;
		shadow.y = position.y + size.y-12;
		
		int direction = is_move_right - is_move_left;

		
		if (direction != 0)
		{
			is_facing_right = direction > 0;
			current_animation = is_facing_right ? &anim_right : &anim_left;
		}
       
		int dir_x = is_move_right - is_move_left;
		int dir_y = is_move_down - is_move_up;
		double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
		if (len_dir != 0)
		{
			double normalized_x = dir_x / len_dir;
			double normalized_y = dir_y / len_dir;
			position.x += (int)(speed * normalized_x);
			position.y += (int)(speed * normalized_y);
		}

		if (position.x < 0)position.x = 0;
		if (position.y < 0)position.y = 0;
		if (position.x + size.x > WINDOW_WIDTH)position.x = WINDOW_WIDTH - size.x;
		if (position.y + size.y > WINDOW_HEIGHT)position.y = WINDOW_HEIGHT - size.y;


		current_animation->on_update(delta);
	}

	virtual void on_draw(const Vector2& position1)
	{
		putimage_alpha(shadow.x, shadow.y, &img_shadow);
		current_animation->on_draw(position1 .x,position1.y);
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

	Vector2 GetPosition()const {
		return position;
	}

	Vector2 GetSize()const {
		return size;
	}

	int GetType() {
		return type;
	}

	void set_position(int x, int y)
	{
		position.x = x, position.y = y;
	}

	virtual void Ping()
	{

	}

protected:
	Vector2 position = { 0,0 };
	Vector2 shadow = { 0,0 };
	Vector2 size = {80,80};
	Animation anim_left;
	Animation anim_right;
	Animation* current_animation;

	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
	bool is_facing_right = true;
	int speed=5;
public:	
	const int SHADOW_WIDTH = 32;
	int HP = 600;
	int damage = 100;
	static int flag;
	int type=0;
};
int Player::flag = 0;