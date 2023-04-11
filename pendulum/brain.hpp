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
			int value = int(random(-2, 2));

			while (value == NULL) {
				value = int(random(-2, 2));
			}
			directions.push_back(value);


		}
	}
	void Mutate()
	{
		 float rate = 0.005f;
		std::for_each(directions.begin(), directions.end(), [&rate](short& dir)
			{
				if (random(1.f) < rate) {
					int value = int(random(-2, 2));

					while (value == NULL) {
						value = int(random(-2, 2));
					}
					dir = value;
				}
			});
		it = directions.begin();
		time_until_update = 0;
		directions.front() = 0;
	}
	size_t steps_taken = 0;
	std::list<short> directions;
	std::list<short>::iterator it;
	int iterator = 0;
	float time_alive = 0;
	float time_until_update = 0;
	int frames = 0;
};


#endif