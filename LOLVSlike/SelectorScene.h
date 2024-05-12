#ifndef _SELECTOR_SCENE_H_
#define _SELECTOR_SCENE_H_

#include"scene.h"
#include"scene_manager.h"
#include"button.h"
#include"Player.h"
#include"enemy.h"
#include"bullet.h"
#include"Divine_Sunderer.h"
#include"Infinity_Edge.h"
#include"Mejai_s_Soulstealer.h"
#include"Morellonomicon.h"
#include"Rapid_Firecannon.h"
#include"Runaan_s_Hurricane.h"
#include"util.h"

#include<iostream>

extern IMAGE img_select;

extern Player* player;

extern SceneManager scene_manager;

class SelectorScene :public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void on_enter()
	{
		
	}
	void on_update(int delta)
	{
		
	}
	void on_draw()
	{
		putimage(0, 0, &img_select);

		setlinecolor(RGB(0, 255, 255));
		setfillcolor(RGB(0, 128, 255));
		clearrectangle(position.x, position.y, position.x + SELECT_WIDTH, position.y + SELECT_HEIGHT);

		switch (role)
		{
		case PlayerType::Divine_Sunderer:
			loadimage(&img_selection, _T("img/role/selected/Divine_Sunderer.jpg"));
			
			break;
		case PlayerType::Infinity_Edge:
			loadimage(&img_selection, _T("img/role/selected/Infinity_Edge.jpg"));
			
			break;
		case PlayerType::Mejai_s_Soulstealer:
			loadimage(&img_selection, _T("img/role/selected/Mejai_s_Soulstealer.jpg"));
			
			break;
		case PlayerType::Morellonomicon:
			loadimage(&img_selection, _T("img/role/selected/Morellonomicon.jpg"));
			
			break;
		case PlayerType::Rapid_Firecannon:
			loadimage(&img_selection, _T("img/role/selected/Rapid_Firecannon.jpg"));
			
			break;
		case PlayerType::Runaan_s_Hurricane:
			loadimage(&img_selection, _T("img/role/selected/Runaan_s_Hurricane.jpg"));
			
			break;
		default:
			loadimage(&img_selection, _T("img/role/selected/Divine_Sunderer.jpg"));
			
			break;
		}
		putimage(position.x, position.y, &img_selection);
	}
	void on_input(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
			case 87:
			{
				is_w_down = true;
				break;
			}
			case 83:
			{
				is_s_down = true;
				break;
			}
			}break;
		case WM_KEYUP:
			switch (msg.vkcode)
			{
			case 87:
			{
				is_w_down = false;
				role = (PlayerType)(((int)PlayerType::InValid + (int)role + 1) % (int)PlayerType::InValid);
				break;
			}
			case 83:
			{
				is_s_down = false;
				role = (PlayerType)(((int)PlayerType::InValid + (int)role - 1) % (int)PlayerType::InValid);
				break;
			}
			case VK_RETURN:
			{
				
				scene_manager.switch_to(SceneManager::SceneType::Game);
				break;
			}
			}
			break;
		default:
			break;
		}
	}
	void on_exit()
	{
		switch (role)
		{
		case PlayerType::Divine_Sunderer:
			player = new Divine_Sunderer();
			mciSendString(_T("play div from 0"), NULL, 0, NULL);
			break;
		case PlayerType::Infinity_Edge:
			player = new Infinity_Edge();
			mciSendString(_T("play inf from 0"), NULL, 0, NULL);
			break;
		case PlayerType::Mejai_s_Soulstealer:
			player = new Mejai_s_Soulstealer;
			mciSendString(_T("play mej from 0"), NULL, 0, NULL);
			break;
		case PlayerType::Morellonomicon:
			player = new Morellonomicon();
			mciSendString(_T("play mor from 0"), NULL, 0, NULL);
			break;
		case PlayerType::Rapid_Firecannon:
			player = new Rapid_Firecannon();
			mciSendString(_T("play rap from 0"), NULL, 0, NULL);
			break;
		case PlayerType::Runaan_s_Hurricane:
			player = new Runaan_s_Hurricane();
			mciSendString(_T("play run from 0"), NULL, 0, NULL);
			break;
		}
	}
private:
	Vector2 position = { (WINDOW_WIDTH/2 -SELECT_WIDTH)/2,(WINDOW_HEIGHT/2 - SELECT_WIDTH)/2 };
	bool is_w_down = false;
	bool is_s_down = false;
	const int SELECT_WIDTH = 512;
	const int SELECT_HEIGHT = 512;
	IMAGE img_selection = NULL;

	enum class PlayerType
	{
		Divine_Sunderer = 0,
		Infinity_Edge,
		Mejai_s_Soulstealer,
		Morellonomicon,
		Rapid_Firecannon,
		Runaan_s_Hurricane,
		InValid
	};
	PlayerType role = PlayerType::Divine_Sunderer;
};

#endif// !_SELECTOR_SCENE_H_
