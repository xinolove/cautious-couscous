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
#include"Vector2.h"

extern IMAGE img_energy;

class Bullet
{
public:
	POINT position = { 0,0 };

	Bullet() = default;
	~Bullet() = default;

	void Draw()const
	{
		
		putimage_alpha(position.x-12, position.y-12, &img_energy);
	}

private:
	const int RADIUS = 10;
};