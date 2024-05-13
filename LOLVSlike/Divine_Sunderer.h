#pragma once
#include<graphics.h>
#include<iostream>

#include"Player.h"

extern Atlas Divine_Sunderer_left;
extern Atlas Divine_Sunderer_right;

class Divine_Sunderer:public Player
{
public:
	Divine_Sunderer()
	{
		anim_left.set_atlas(&Divine_Sunderer_left);
		anim_right.set_atlas(&Divine_Sunderer_right);

		anim_left.set_interval(75);
		anim_right.set_interval(75);

		type = 1;
	}
	~Divine_Sunderer() = default;

	void Ping()
	{
		srand(time(0));
		int n = rand() % 5;
		if (n == 0)
			HP+=50;
	}


private:

};