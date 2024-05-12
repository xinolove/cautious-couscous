#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include"scene.h"
#include"scene_manager.h"
#include"button.h"
#include"Player.h"
#include"enemy.h"
#include"bullet.h"
#include"util.h"
#include"altas.h"
#include"animation.h"

#include<graphics.h>
#include<iostream>

extern SceneManager scene_manager;

extern StartGameButton btn_start_game;
extern QuitGameButton btn_quit_game;



extern IMAGE img_menu;


class MenuScene:public Scene
{
public:
	MenuScene() = default;
	~MenuScene()=default;

	void on_enter()
	{

	}
	void on_draw()
	{
	
		putimage(0, 0, &img_menu);
		btn_start_game.Draw();
		btn_quit_game.Draw();
	}
	 void on_input(const ExMessage& msg) 
	 {
		 btn_start_game.ProcessEvent(msg);
		 btn_quit_game.ProcessEvent(msg);
	 }
private:

};


#endif// !_MENU_SCENE_H_