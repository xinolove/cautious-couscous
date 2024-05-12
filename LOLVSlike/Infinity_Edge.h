#pragma once
#include<graphics.h>
#include<iostream>

#include"Player.h"

extern Atlas Infinity_Edge_left;
extern Atlas Infinity_Edge_right;

class Infinity_Edge :public Player
{
public:
	Infinity_Edge()
	{
		anim_left.set_atlas(&Infinity_Edge_left);
		anim_right.set_atlas(&Infinity_Edge_right);

		anim_left.set_interval(75);
		anim_right.set_interval(75);

		type = 2;
	}
	~Infinity_Edge() = default;

	void Ping()
	{
		switch (flag)
		{
		case 25:
		{
			damage = 500;
			break;
		}
		default:
			break;
		}
	}
private:

};