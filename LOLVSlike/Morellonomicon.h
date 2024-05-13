#pragma once
#include<graphics.h>
#include<iostream>

#include"Player.h"

extern Atlas Morellonomicon_left;
extern Atlas Morellonomicon_right;

class Morellonomicon :public Player
{
public:
	Morellonomicon()
	{
		anim_left.set_atlas(&Morellonomicon_left);
		anim_right.set_atlas(&Morellonomicon_right);

		anim_left.set_interval(75);
		anim_right.set_interval(75);

		type = 1;
	}
	~Morellonomicon() = default;
	
	void Ping()
	{

		switch (flag)
		{
		case 0:
			break;
		case 1:
			damage = 110;
			break;
		case 2:
			damage = 120;
			break;
		case 3:
			damage = 130;
			break;
		case 4:
			damage = 140;
			break;
		case 5:
			damage = 150;
			break;
		case 6:
			damage = 160;
			break;
		case 7:
			damage = 170;
			break;
		case 8:
			damage = 180;
			break;
		case 9:
			damage = 190;
			break;
		case 10:
			damage = 200;
			break;
		default:
			int n = rand() % 2;
			if (n)
				HP+=125;
			else
				HP-=100;
			break;
		}
	}

private:

};