#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include"scene.h"
#include"scene_manager.h"
#include"button.h"
#include"Player.h"
#include"enemy.h"
#include"bullet.h"
#include"util.h"
#include"Vector2.h"

#include<iostream>
#include<vector>

void DrawPlayerScore(int score)
{
	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家得分：%d"), score);
	settextstyle(25, 0, _T("img/QingNiaoHuaGuangJianMeiHei-2.ttf"));
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	outtextxy(10, 30, text);
}
void DrawPlayerHP(int HP)
{
	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家HP：%d"), HP);
	settextstyle(25, 0, _T("img/QingNiaoHuaGuangJianMeiHei-2.ttf"));
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	outtextxy(300, 30, text);
}

void DrawPlayerFlag(int flag)
{
	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家被动层数：%d"), flag);
	settextstyle(25, 0, _T("img/QingNiaoHuaGuangJianMeiHei-2.ttf"));
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	outtextxy(600, 30, text);
}

extern std::vector<Enemy*> enemy_list;
extern std::vector<Bullet> bullet_list;

extern Player *player;

extern int score;

int limit = 0;

extern bool running;

extern bool collision;
extern int timer;

extern IMAGE img_background;
extern IMAGE img_injury;

class GameScene :public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter()
	{
		mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);
		player->set_position(300, 300);
	}
	void on_update(int delta)
	{
		collision = false;
		player->on_update(delta);
		TryGenerateEnemy(enemy_list);
		for (Enemy* enemy : enemy_list)
		{
			enemy->Increase(score);
			enemy->Move(player->GetPosition(),delta);
		}
		for (Enemy* enemy : enemy_list)
		{
			if (enemy->CheckPlayerCollision(player->GetPosition()))
			{
				collision = true;
				if (player->flag >= 5)
					player->flag -= 5;
				else
					player->flag = 0;
				mciSendString(_T("play hurt from 0"), NULL, 0, NULL);
				player->HP -= enemy->GetDamage();
				enemy->InjuryProtection(player->GetPosition());
			}
		}

		const double RADIAL_SPEED = 0.001;
		const double TANGENT_SPEED = 0.002;
		double radian_interval = 2 * 3.14159 / bullet_list.size();
		Vector2 player_position = player->GetPosition();
		double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
		for (size_t i = 0; i < bullet_list.size(); i++)
		{
			double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;
			bullet_list[i].position.x = player_position.x + player->GetSize().x / 2 + (int)(radius * sin(radian));
			bullet_list[i].position.y = player_position.y + player->GetSize().y / 2 + (int)(radius * cos(radian));
		}

		for (Enemy* enemy : enemy_list)
		{
			for (const Bullet& bullet : bullet_list)
			{
				if (enemy->CheckBulletCollision(bullet))
				{
					mciSendString(_T("play hit from 0"), NULL, 0, NULL);
					player->Ping();
					
					enemy->Hurt(player->GetPosition(),player->damage);
					
				}
			}
		}
		if (player->HP <= 0)
					{
						static TCHAR text[128];
						_stprintf_s(text, _T("最终得分：%d！"), score);
						MessageBox(GetHWnd(), text, _T("游戏结束"), MB_OK);
						running = false;
					}

		for (size_t i = 0; i < enemy_list.size(); i++)
		{
			Enemy* enemy = enemy_list[i];
			if (enemy->CheckAlive() <= 0)
			{
				if (player->flag < 25)
					player->flag++;
				score++;
				std::swap(enemy_list[i], enemy_list.back());
				enemy_list.pop_back();
				delete enemy;
			}
		}
	}
	void on_draw()
	{
		srand(time(0));
		static int n = rand() % 9;
		switch (n)
		{
		case 0:
			loadimage(&img_background, _T("img/宏伟广场.jpg"));
			break;
		case 1:
			loadimage(&img_background, _T("img/英勇之厅.jpg"));
			break;
		case 2:
			loadimage(&img_background, _T("img/恕瑞玛的废墟.jpg"));
			break;
		case 3:
			loadimage(&img_background, _T("img/太阳之城.jpg"));
			break;
		case 4:
			loadimage(&img_background, _T("img/天界秘库.jpg"));
			break;
		case 5:
			loadimage(&img_background, _T("img/枯萎之地.jpg"));
			break;
		case 6:
			loadimage(&img_background, _T("img/普雷西典.jpg"));
			break;
		case 7:
			loadimage(&img_background, _T("img/以绪奥肯.jpg"));
			break;
		case 8:
			loadimage(&img_background, _T("img/MSI.jpg"));
		}
		putimage(0, 0, &img_background);
		if (collision)
		{
			timer = 10;
			putimage_alpha(player->GetPosition().x, player->GetPosition().y, &img_injury);
			timer--;
		}
		else if (timer > 0)
		{
			putimage_alpha(player->GetPosition().x, player->GetPosition().y, &img_injury);
			timer--;
		}
		else
		{
			player->on_draw(player->GetPosition());
		}	
		for (Enemy* enemy : enemy_list)
		{
			enemy->Draw(75);
		}
		for (const Bullet& bullet : bullet_list)
			bullet.Draw();
		DrawPlayerScore(score);
		DrawPlayerHP(player->HP);
		DrawPlayerFlag(player->flag);
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