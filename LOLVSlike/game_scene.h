#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include"scene.h"
#include"scene_manager.h"
#include"button.h"
#include"Player.h"
#include"enemy.h"
#include"bullet.h"
#include"util.h"

#include<iostream>

extern Player *player;

extern IMAGE img_background;

class GameScene :public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter()
	{
		player->set_position(300, 300);
	}
	void on_update(int delta)
	{
	
		player->on_update(delta);
	}
	void on_draw()
	{	
		srand(time(0));
		static int n = rand() % 8;
		switch (n)
		{
		case 0:
			loadimage(&img_background, _T("img/��ΰ�㳡.jpg"));
			break;
		case 1:
			loadimage(&img_background, _T("img/Ӣ��֮��.jpg"));
			break;
		case 2:
			loadimage(&img_background, _T("img/ˡ����ķ���.jpg"));
			break;
		case 3:
			loadimage(&img_background, _T("img/̫��֮��.jpg"));
			break;
		case 4:
			loadimage(&img_background, _T("img/����ؿ�.jpg"));
			break;
		case 5:
			loadimage(&img_background, _T("img/��ή֮��.jpg"));
			break;
		case 6:
			loadimage(&img_background, _T("img/��������.jpg"));
			break;
		case 7:
			loadimage(&img_background, _T("img/�����¿�.jpg"));
			break;
		}
		putimage(0,0,&img_background);
		player->on_draw(player->GetPosition());
        
	}
	 void on_input(const ExMessage& msg)
	 {
		 player->on_input(msg);
	 }
	 void on_exit()
	 {
		
	 }
private:

};


#endif// !_GAME_SCENE_H_