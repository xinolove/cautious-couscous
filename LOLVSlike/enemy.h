#pragma once
#include<graphics.h>
#include<string>
#include<vector>
#include<iostream>
#include<functional>

#include"altas.h"
#include"animation.h"
#include"Player.h"
#include"bullet.h"

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern Atlas shadow_entities_left;
extern Atlas shadow_entities_right;

extern IMAGE img_shadow;

class Enemy
{
public:
	Enemy()
	{
		current_animation = &anim_right;

		anim_left.set_atlas(&shadow_entities_left);
		anim_right.set_atlas(&shadow_entities_right);

		anim_left.set_interval(75);
		anim_right.set_interval(75);

		enum class SpawnEdge
		{
			Up = 0,
			Down,
			Left,
			Right
		};

		SpawnEdge edge = (SpawnEdge)(rand() % 4);
		switch (edge)
		{
		case SpawnEdge::Up:
			position.x = rand() % WINDOW_WIDTH;
			position.y = -size.y;
			break;
		case SpawnEdge::Down:
			position.x = rand() % WINDOW_WIDTH;
			position.y = -WINDOW_HEIGHT;
			break;
		case SpawnEdge::Left:
			position.x = -size.x;
			position.y = rand() % WINDOW_HEIGHT;
			break;
		case SpawnEdge::Right:
			position.x = -WINDOW_WIDTH;
			position.y = rand() % WINDOW_HEIGHT;
			break;
		default:
			break;
		}
	}
	~Enemy()
	{}


	bool CheckPlayerCollision(Vector2 player_position)
	{
		float w1 = size.x / 1.8;
		float h1 = size.y / 1.8;
		float w2 = w1;
		float h2 = h1;
		float w = abs(position.x - player_position.x);
		float h = abs(position.y - player_position.y);

		if (w < (w1 + w2) / 2 && h < (h1 + h2) / 2)
			return true;
		else
			return false;
	}

	void Move(Vector2 player_position ,int delta)
	{
		int dir_x = player_position.x - position.x;
		int dir_y = player_position.y - position.y;
		double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
		if (len_dir != 0)
		{
			double normalized_x = dir_x / len_dir;
			double normalized_y = dir_y / len_dir;
			position.x += (int)(SPEED * normalized_x);
			position.y += (int)(SPEED * normalized_y);
		}
		if (dir_x < 0)
			facing_left = true;
		else if (dir_x > 0)
			facing_left = false;

		current_animation = facing_left ? &anim_left : &anim_right;
		current_animation->on_update(delta);
	}

	void InjuryProtection(Vector2 player_position)
	{
		int dir_x = player_position.x - position.x;
		int dir_y = player_position.y - position.y;
		double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);

		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		position.x -= (int)(50 * SPEED * normalized_x);
		position.y -= (int)(50 * SPEED * normalized_y);

	}

	bool CheckBulletCollision(const Bullet& bullet)
	{
		bool is_overlap_x = bullet.position.x >= position.x && bullet.position.x <= position.x + size.x;
		bool is_overlap_y = bullet.position.y >= position.y && bullet.position.y <= position.y + size.y;
		return is_overlap_x && is_overlap_y;
	}

	void Draw(int delta)
	{
		int pos_shadow_x = position.x + (size.x / 2 - size.y / 2)+20;
		int pos_shadow_y = position.y + size.y - 15;
		putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);
		current_animation->on_draw(GetPosition().x, GetPosition().y);

	}

	void Hurt(Vector2 player_position,int player_damage)
	{
		HP -= player_damage;
		if (HP > 0)
		{
			int dir_x = player_position.x - position.x;
			int dir_y = player_position.y - position.y;
			double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);

			double normalized_x = dir_x / len_dir;
			double normalized_y = dir_y / len_dir;
			position.x -= (int)(25 * SPEED * normalized_x);
			position.y -= (int)(25 * SPEED * normalized_y);
		}
	}



	void Increase(int score)
	{
		if (!is_increased)
		{
			if (score >= 125)
				SPEED = 5,HP = 1000, is_increased = true;
			else if (score >= 100)
				SPEED = 4, HP = 750, is_increased = true;
			else if (score >= 75)
				HP = 500, is_increased = true;
			else if (score >= 50)
				HP = 450, is_increased = true;
			else if (score >= 25)
				HP = 400, is_increased = true;
		}
	}

	int GetDamage()
	{
		return damage;
	}

	int CheckAlive()
	{
		return HP;
	}
	Vector2 GetPosition()const {
		return position;
	}
	Vector2 GetSize()const {
		return size;
	}


public:
	
private:
	int SPEED = 3;
	int damage = 100;
	int HP = 360;
	const int SHADOW_WIDTH = 48;
	bool is_increased=false;

	Animation anim_left;
	Animation anim_right;
	Animation* current_animation;
	Vector2 position = { 0,0 };
	Vector2 size = {80,100};
	bool facing_left = false;
};

void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTERVAL = 60;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}