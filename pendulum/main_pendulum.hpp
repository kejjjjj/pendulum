#pragma once

#ifndef mainpeund
#define mainpeund

#include "pch.h"


class MainPendulum
{
public:
	MainPendulum(const ivec2& pos, const ivec2& mins, const ivec2& maxs);
	~MainPendulum() = default;
	struct platform
	{
		ivec2 pos;
		ivec2 mins;
		ivec2 maxs;
		Pixel color;

		void Draw();
	}pf;

	void Draw();

};

void _main();


#endif