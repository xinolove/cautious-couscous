#include<graphics.h>
#include<string>
#include<vector>
#include<iostream>
#include<functional>

#include"scene.h"
#include"altas.h"
#include"animation.h"
#include"menu_scene.h"
#include"game_scene.h"
#include"SelectorScene.h"
#include"scene_manager.h"
#include"button.h"
#include"Player.h"
#include"enemy.h"
#include"bullet.h"
#include"util.h"


const int WINDOW_WIDTH = 1760;
const int WINDOW_HEIGHT = 990;

const int BUTTON_WIDTH = 192;
const int BUTTON_HEIGHT = 75;

bool running = true;

IMAGE img_menu;
IMAGE img_select;
IMAGE img_background;
IMAGE img_injury;
IMAGE img_shadow;

Atlas Divine_Sunderer_left;
Atlas Divine_Sunderer_right;
Atlas Infinity_Edge_left;
Atlas Infinity_Edge_right;
Atlas Mejai_s_Soulstealer_left;
Atlas Mejai_s_Soulstealer_right;
Atlas Morellonomicon_left;
Atlas Morellonomicon_right;
Atlas Rapid_Firecannon_left;
Atlas Rapid_Firecannon_right;
Atlas Runaan_s_Hurricane_left;
Atlas Runaan_s_Hurricane_right;

Atlas shadow_entities_left;
Atlas shadow_entities_right;


SceneManager scene_manager;

Scene* menu_scene = NULL;
Scene* game_scene = NULL;
Scene* selector_scene = NULL;

void flip_atlas(Atlas& src, Atlas& dst)
{
	dst.clear();
	for (int i = 0; i < src.get_size(); i++)
	{
		IMAGE img_flpipped;
		flip_image(src.get_image(i), &img_flpipped);
		dst.add_image(img_flpipped);
	}
}

void load_game_resources()
{
	AddFontResourceEx(_T("img/QingNiaoHuaGuangJianMeiHei-2.ttf"), FR_PRIVATE, NULL);
	
	loadimage(&img_select, _T("img/select.jpg"));
	loadimage(&img_menu, _T("img/menu.png"));
	loadimage(&img_injury, _T("img/R-C.png"));
	loadimage(&img_shadow, _T("img/shadow_player.png"));

	shadow_entities_left.load_from_file(_T("img/shadow_entities/shadow_entities_left_%d.png"), 6);
	shadow_entities_right.load_from_file(_T("img/shadow_entities/shadow_entities_right_%d.png"), 6);
	Divine_Sunderer_left.load_from_file(_T("img/Divine_Sunderer/Divine_Sunderer_left_%d.png"), 6);
	Divine_Sunderer_right.load_from_file(_T("img/Divine_Sunderer/Divine_Sunderer_right_%d.png"), 6);
	Infinity_Edge_left.load_from_file(_T("img/Infinity_Edge/Infinity_Edge_left_%d.png"), 6);
	Infinity_Edge_right.load_from_file(_T("img/Infinity_Edge/Infinity_Edge_right_%d.png"), 6);
	Mejai_s_Soulstealer_left.load_from_file(_T("img/Mejai_s_Soulstealer/Mejai_s_Soulstealer_left_ %d.png"), 6);
	Mejai_s_Soulstealer_right.load_from_file(_T("img/Mejai_s_Soulstealer/Mejai_s_Soulstealer_right_ %d.png"), 6);
	Morellonomicon_left.load_from_file(_T("img/Morellonomicon/Morellonomicon_left_%d.png"), 6);
	Morellonomicon_right.load_from_file(_T("img/Morellonomicon/Morellonomicon_right_%d.png"), 6);
	Rapid_Firecannon_left.load_from_file(_T("img/Rapid_Firecannon/Rapid_Firecannon_left_%d.png"), 6);
	Rapid_Firecannon_right.load_from_file(_T("img/Rapid_Firecannon/Rapid_Firecannon_right_%d.png"), 6);
	Runaan_s_Hurricane_left.load_from_file(_T("img/Runaan_s_Hurricane/Runaan_s_Hurricane_left_%d.png"), 6);
	Runaan_s_Hurricane_right.load_from_file(_T("img/Runaan_s_Hurricane/Runaan_s_Hurricane_right_%d.png"), 6);

	mciSendString(_T("open mus/tftset10_trailer.mp3 alias bgm "), NULL, 0, NULL);
	mciSendString(_T("open mus/URF_champion_select.mp3 alias select "), NULL, 0, NULL);
	mciSendString(_T("open mus/sci-fi_weapon_blaster_laser_boom_zap_01.wav alias hit "), NULL, 0, NULL);
	mciSendString(_T("open mus/voice_female_a_hurt_pain_01.wav alias hurt "), NULL, 0, NULL);
}

StartGameButton btn_start_game;
QuitGameButton btn_quit_game;

Player* player=NULL;


int main()
{
	initgraph(1760, 990);

	load_game_resources();
	

	RECT region_btn_start_game, region_btn_quit_game;

	region_btn_start_game.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_start_game.right = region_btn_start_game.left + BUTTON_WIDTH;
	region_btn_start_game.top = 430;
	region_btn_start_game.bottom = region_btn_start_game.top + BUTTON_HEIGHT;

	region_btn_quit_game.left = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
	region_btn_quit_game.right = region_btn_quit_game.left + BUTTON_WIDTH;
	region_btn_quit_game.top = 550;
	region_btn_quit_game.bottom = region_btn_quit_game.top + BUTTON_HEIGHT;


	btn_start_game = StartGameButton(region_btn_start_game,
		_T("img/ui_start_idle.png"), _T("img/ui_start_hovered.png"), _T("img/ui_start_pushed.png"));
	btn_quit_game = QuitGameButton(region_btn_quit_game,
		_T("img/ui_quit_idle.png"), _T("img/ui_quit_hovered.png"), _T("img/ui_quit_pushed.png"));

	int score = 0;
	int timer = 0;
	bool is_esc = false;
	ExMessage msg;
	const int FPS = 60;
	
	std::vector<Enemy*> enemy_list;
	std::vector<Bullet> bullet_list(3);

	BeginBatchDraw();

	menu_scene = new MenuScene();
	game_scene = new GameScene();
	selector_scene = new SelectorScene();

	scene_manager.set_current_scene(menu_scene);


	while (true)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
			
		}
		
		/*bool collision = false;

			player.Soulstealer();
			TryGenerateEnemy(enemy_list);
			player.Move();
			UpdateBullets(bullet_list, player);

			for (Enemy* enemy : enemy_list)
			{
				enemy->Move(player);
			}


			for (Enemy* enemy : enemy_list)
			{
				for (const Bullet& bullet : bullet_list)
				{
					if (enemy->CheckBulletCollision(bullet))
					{
						mciSendString(_T("play hit from 0"), NULL, 0, NULL);
						enemy->Hurt(player);
					}
				}
			}

			for (size_t i = 0; i < enemy_list.size(); i++)
			{
				Enemy* enemy = enemy_list[i];
				if (enemy->CheckAlive() <= 0)
				{
					if (player.flag < 25)
						player.flag++;
					score++;
					std::swap(enemy_list[i], enemy_list.back());
					enemy_list.pop_back();
					delete enemy;
				}
			}
			for (Enemy* enemy : enemy_list)
			{
				if (enemy->CheckPlayerCollision(player))
				{
					collision = true;
					if (player.flag >= 5)
						player.flag -= 5;
					else
						player.flag = 0;
					mciSendString(_T("play hurt from 0"), NULL, 0, NULL);
					player.HP -= enemy->damage;
					enemy->InjuryProtection(player);
					if (player.HP <= 0)
					{
						static TCHAR text[128];
						_stprintf_s(text, _T("最终得分：%d！"), score);
						MessageBox(GetHWnd(), text, _T("游戏结束"), MB_OK);
						running = false;
						break;
					}
				}
			}*/
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		scene_manager.on_update(delta_tick);
		last_tick_time = current_tick_time;

		cleardevice();
		scene_manager.on_draw();
			/*putimage(0, 0, &img_background);
			if (collision)
			{
				timer = 10;
				putimage_alpha(player.GetPosition().x, player.GetPosition().y, &img_injury);
				timer--;
			}
			else if (timer > 0)
			{
				putimage_alpha(player.GetPosition().x, player.GetPosition().y, &img_injury);
				timer--;
			}
			else
			{
				player.Draw(1000 / 144);
			}
			for (Enemy* enemy : enemy_list)
				enemy->Draw(1000 / 144);
			for (const Bullet& bullet : bullet_list)
				bullet.Draw();
			DrawPlayerScore(score);
			DrawPlayerHP(player.HP);*/

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / FPS)
		{
			Sleep(1000 / FPS - delta_time);
		}
	}


	EndBatchDraw();

	return 0;
}