#pragma once
#include<graphics.h>
#include<string>
#include<vector>
#include<iostream>
#include<functional>

class Atlas
{
public:
	Atlas() = default;
	~Atlas() = default;

	void load_from_file(LPCTSTR path_template,int num)
	{
		img_list.clear();
		img_list.resize(num);

		TCHAR path_file[256];
		for (size_t i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path_template, i);
			loadimage(&img_list[i], path_file);
		}
	}
	void clear()
	{
		img_list.clear();
	}

	int get_size()
	{
		return (int)img_list.size();
	}

	IMAGE* get_image(int idx)
	{
		if (idx < 0 || idx >= img_list.size())
			return NULL;
		return &img_list[idx];
	}

	void add_image(const IMAGE& img)
	{
		img_list.push_back(img);
	}

public:
	std::vector<IMAGE>img_list;
};