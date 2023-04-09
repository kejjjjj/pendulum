#pragma once

#ifndef __pend1
#define __pend1

#include "pch.h"

class Pendulum
{
public:
	Pendulum(const ivec2& pos, const ivec2& mins, const ivec2& maxs);
	~Pendulum() = default;

	const float GRAVITY = 9.80665f;

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

	struct Ball
	{
		ivec2 pos;
		ivec2 real_pos;
		fvec2* pivot;
		float radius = 0;
		Pixel color;
		float line_length = 100;
		float angle = 0;
		float velocity;
		float damping = 0.995f;
		void Draw();
		void UpdatePos(Pendulum::stand& stand);
	}b;

	void Draw();

};

#endif