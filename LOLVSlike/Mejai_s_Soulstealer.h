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

	}
	~Mejai_s_Soulstealer() = default;

private:
	
};