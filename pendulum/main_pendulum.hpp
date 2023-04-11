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

	decltype(GetTime()) last_population_update;
	decltype(GetTime()) last_it_update;
	decltype(GetTime()) start_time;
	float time_until_update;

	void Draw();

};

void _main();


#endif