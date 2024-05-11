#pragma once
#include<graphics.h>
#include<string>
#include<vector>
#include<iostream>
#include<functional>

#include"altas.h"
#include"animation.h"
#include"Player.h"
#include"enemy.h"

class Bullet
{
public:
	POINT position = { 0,0 };

	Bullet() = default;
	~Bullet() = default;

	void Draw()const
	{
		setlinecolor(RGB(255, 255, 0));
		setfillcolor(RGB(255, 128, 0));
		fillcircle(position.x, position.y, RADIUS);
	}


private:
	const int RADIUS = 10;
};

void UpdateBullets(std::vector<Bullet>& bullet_list, const Player& player)
{
	const double RADIAL_SPEED = 0.001;
	const double TANGENT_SPEED = 0.002;
	double radian_interval = 2 * 3.14159 / bullet_list.size();
	POINT player_position = player.GetPosition();
	double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;
		bullet_list[i].position.x = player_position.x + player.FRAME_WIDTH / 2 + (int)(radius * sin(radian));
		bullet_list[i].position.y = player_position.y + player.FRAME_HEIGHT / 2 + (int)(radius * cos(radian));
	}
}
