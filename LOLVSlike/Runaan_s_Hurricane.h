#pragma once
#include<graphics.h>
#include<iostream>

#include"Player.h"

extern Atlas Runaan_s_Hurricane_left;
extern Atlas Runaan_s_Hurricane_right;

class Runaan_s_Hurricane :public Player
{
public:
	Runaan_s_Hurricane()
	{
		anim_left.set_atlas(&Runaan_s_Hurricane_left);
		anim_right.set_atlas(&Runaan_s_Hurricane_right);

		anim_left.set_interval(75);
		anim_right.set_interval(75);

		type = 1;
	}
	~Runaan_s_Hurricane() = default;

	void Ping()
	{
		switch (flag)
		{
		case 0:
			speed = 5;
			break;
		case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:
			speed = 6;
			break;
		case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 19:
		{
			speed = 7;
			break;
		}
		case 20:case 21:case 22:case 23:case 24:
		{
			speed = 8;
			break;
		}
		case 25:
		{
			speed = 10;
			break;
		}
		}
	}


private:

};