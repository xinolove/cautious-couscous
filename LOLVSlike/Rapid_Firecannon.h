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
		case 0:case 1:case 2:case 3:case 4:
			break;
		case 5:case 6:case 7:case 8:case 9:case 10:case 11:case 12:case 13:case 14:
		{
			damage = 120;
			break;
		}
		case 15:case 16:case 17:case 18:case 19:case 20:case 21:case 22:case 23:case 24:
		{
			damage = 160;
			break;
		}
		case 25:
		{
			damage = 350;
			break;
		}
		}
	}

private:

};