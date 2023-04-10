#pragma once

#ifndef __celll
#define __celll

#include "pch.h"

class Cell
{
public:
	Cell() : brain(1000) {}

	Cell(size_t num_instructions) : brain(num_instructions) {}

	Cell copy() { return *this; }

	//void NewBrain(size_t num_instructions) {
	//	delete brain.release();
	//	brain = std::make_unique<Brain>(new Brain(num_instructions));

	//}

	void Reset();
	void NewGeneration();
	void GiveScore(float pendulum_angle);
	void OnDeath();
	Brain brain;
	float score = 0;
	bool dead = false;

	//Cell copy() { return *this; }

};
inline Cell BestCell;
inline size_t total_attempts = 0;
#endif