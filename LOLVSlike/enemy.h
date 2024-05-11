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

extern Atlas shadow_entities_left;
extern Atlas shadow_entities_right;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern const int BUTTON_WIDTH;
extern const int BUTTON_HEIGHT;


class Enemy
{
public:
	Enemy()
	{
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
			position.y = -FRAME_HEIGHT;
			break;
		case SpawnEdge::Down:
			position.x = rand() % WINDOW_WIDTH;
			position.y = -WINDOW_HEIGHT;
			break;
		case SpawnEdge::Left:
			position.x = -FRAME_WIDTH;
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

	bool CheckBulletCollision(const Bullet& bullet)
	{
		bool is_overlap_x = bullet.position.x >= position.x && bullet.position.x <= position.x + FRAME_WIDTH;
		bool is_overlap_y = bullet.position.y >= position.y && bullet.position.y <= position.y + FRAME_WIDTH;
		return is_overlap_x && is_overlap_y;
	}


	bool CheckPlayerCollision(const Player& player)
	{
		float w1 = FRAME_WIDTH / 1.8;
		float h1 = FRAME_HEIGHT / 1.8;
		float w2 = w1;
		float h2 = h1;
		float w = abs(position.x - player.GetPosition().x);
		float h = abs(position.y - player.GetPosition().y);

		if (w < (w1 + w2) / 2 && h < (h1 + h2) / 2)
			return true;
		else
			return false;
	}

	void Move(const Player& player)
	{
		const POINT& player_position = player.GetPosition();
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
	}

	void InjuryProtection(const Player& player)
	{
		const POINT& player_position = player.GetPosition();
		int dir_x = player_position.x - position.x;
		int dir_y = player_position.y - position.y;
		double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);

		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		position.x -= (int)(50 * SPEED * normalized_x);
		position.y -= (int)(50 * SPEED * normalized_y);
	}

	void Draw(int delta)
	{
		int pos_shadow_x = position.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2);
		int pos_shadow_y = position.y + FRAME_HEIGHT - 10;
		putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

		if (facing_left)
			anim_left.on_update(delta);
		else
			anim_right.on_update(delta);

	}

	void Hurt(const Player& player)
	{
		HP -= player.damage;
		if (HP > 0)
		{
			const POINT& player_position = player.GetPosition();
			int dir_x = player_position.x - position.x;
			int dir_y = player_position.y - position.y;
			double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);

			double normalized_x = dir_x / len_dir;
			double normalized_y = dir_y / len_dir;
			position.x -= (int)(25 * SPEED * normalized_x);
			position.y -= (int)(25 * SPEED * normalized_y);
		}
	}

	int CheckAlive()
	{
		return HP;
	}

	

public:
	int damage = 100;
	int HP = 300;
private:
	const int SPEED = 2;
	const int FRAME_WIDTH = 80;
	const int FRAME_HEIGHT = 100;
	const int SHADOW_WIDTH = 48;

	IMAGE img_shadow;
	Animation anim_left;
	Animation anim_right;
	POINT position = { 0,0 };
	bool facing_left = false;
};

void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTERVAL = 240;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}