#pragma once
#include<graphics.h>
#include<iostream>

#include"Player.h"

extern Atlas Rapid_Firecannon_left;
extern Atlas Rapid_Firecannon_right;

class Rapid_Firecannon :public Player
{
public:
	Rapid_Firecannon()
	{
		anim_left.set_atlas(&Rapid_Firecannon_left);
		anim_right.set_atlas(&Rapid_Firecannon_right);

		anim_left.set_interval(75);
		anim_right.set_interval(75);

		type = 6;
	}
	~Rapid_Firecannon() = default;

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
			damage = 100;
			break;
		}
	}

private:

};