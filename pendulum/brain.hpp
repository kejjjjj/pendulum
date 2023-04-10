#pragma once

#ifndef __Brain
#define __Brain

#include "pch.h"

class Brain
{
public:
	Brain(size_t num_instructions) {
		Create(num_instructions);
		it = directions.begin();
	}
	void Create(size_t num_instructions) {
		for (int i = 0; i < num_instructions; i++) {
			directions.push_back(int(random(-2, 2)));


		}
	}
	void Mutate()
	{
		constexpr float rate = 0.01f;
		std::for_each(directions.begin(), directions.end(), [&rate](short& dir)
			{
				if (random(1.f) < rate) {
					dir = int(random(-2, 2));
				}
			});
		it = directions.begin();
		time_until_update = 0.5f;
	}
	size_t steps_taken = 0;
	std::list<short> directions;
	std::list<short>::iterator it;
	float time_alive = 0;
	float time_until_update = 0.5f;
	decltype(GetTime()) last_it_update;
};


#endif