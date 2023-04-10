#pragma once

#ifndef _p_opulation
#define _p_opulation

#include "pch.h"

class Population
{
public:
	Population(const int32_t cells) {
		std::cout << "Population(constructor): allocating " << cells * sizeof(Pendulum) << " bytes of memory\n";

		for (int i = 0; i < cells; i++) {
			Pendulum* pend = new Pendulum(*pendulum); // a new brain with 1000 instructions

			population.push_back(pend);
		}
	}
	~Population() {
		std::cout << "clear memory\n";
		for (auto i : population) {
			delete i;
		}
		population.clear();
		population.resize(0);
	}

	void Update();
	bool GenerationActive();
	void Reset();
	float fitnessSum();
	void NewGeneration();
	std::list<Pendulum*> population;
	Cell SetBestCell();

	bool active = false;

};

#endif