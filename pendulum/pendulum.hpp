#pragma once

#ifndef __pend1
#define __pend1

#include "pch.h"

class Pendulum
{
public:
	Pendulum(const MainPendulum& pend);
	~Pendulum() = default;

	const float GRAVITY = 9.80665f;

	struct stand
	{
		fvec2 original_pos;
		fvec2 pos;
		ivec2 mins;
		ivec2 maxs;
		olc::Pixel color;
		float velocity;
		float t = 0;
		float ref_velocity = 0;

		
	}s;

	struct Ball
	{
		ivec2 pos;
		ivec2 real_pos;
		fvec2* pivot;
		float radius = 0;
		olc::Pixel color;
		float line_length = 100;
		float angle = 0;
		float n_angle = 0;
		float velocity;
		float damping = 0.995f;
	}b;

	void UpdateStand(int direction);
	void UpdateBall();

	void DrawStand();
	void DrawBall();

	void Reset();

	ivec2 pos;
	ivec2 mins;
	ivec2 maxs;
	bool rightmove = false;

	friend class Cell;

	Cell cell;

	void Update();
};

#endif