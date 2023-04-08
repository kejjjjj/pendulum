#pragma once

#ifndef __pend1
#define __pend1

#include "pch.h"

class Pendulum
{
public:
	Pendulum(const ivec2& pos, const ivec2& mins, const ivec2& maxs);
	~Pendulum() = default;

	struct platform
	{
		ivec2 pos;
		ivec2 mins;
		ivec2 maxs;
		Pixel color;

		void Draw();
	}pf;

	struct stand
	{
		fvec2 pos;
		ivec2 mins;
		ivec2 maxs;
		Pixel color;

		ivec2 delta_pos;

		void Draw();
		void UpdatePos(Pendulum::platform& plat);
	}s;

	void Draw();

};

#endif