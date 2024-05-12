#pragma once
#include<graphics.h>
#include<iostream>

#include"Player.h"


extern Atlas Mejai_s_Soulstealer_left;
extern Atlas Mejai_s_Soulstealer_right;


class Mejai_s_Soulstealer :public Player
{
public:
	Mejai_s_Soulstealer()
	{
		anim_left.set_atlas(&Mejai_s_Soulstealer_left);
		anim_right.set_atlas(&Mejai_s_Soulstealer_right);

		anim_left.set_interval(75);
		anim_right.set_interval(75);

		type = 3;
	}
	~Mejai_s_Soulstealer() = default;

	void Ping()
	{
		switch (flag)
		{
		case 0:case 1:case 2:case 3:case 4:
			damage = 100;
			speed = 5;
			break;
		case 5:case 6:case 7:case 8:case 9:
		{
			speed = 5;
			damage = 120;
			break;
		}
		case 10:case 11:case 12:case 13:case 14:
		{
			damage = 140;
			speed = 6;
			break;
		}
		case 15:case 16:case 17:case 18:case 19:
		{
			damage = 160;
			speed = 6;
			break;
		}
		case 20:case 21:case 22:case 23:case 24:
		{
			damage = 180;
			speed = 6;
			break;
		}
		case 25:
		{
			damage = 250;
			speed = 7;
			break;
		}
		}
	}

private:

};