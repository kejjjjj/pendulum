#include "pch.h"

void Population::Update()
{
	std::for_each(population.begin(), population.end(), [](Pendulum* p)
		{
			p->Update();
		});
}
bool Population::GenerationActive()
{
	bool all_are_dead = true;

	std::for_each(population.begin(), population.end(), [&all_are_dead](const Pendulum* p)
		{
			if (!p->cell.dead) {
				all_are_dead = false;

			}
		});

	return !all_are_dead;
}
void Population::Reset()
{
	std::for_each(population.begin(), population.end(), [](Pendulum* p)
		{
			p->Reset();
		});
}
float Population::fitnessSum()
{
	float sum = 0;
	std::for_each(population.begin(), population.end(), [&sum](const Pendulum* p) {sum += p->cell.score; });

	return sum;
}
Cell Population::SetBestCell()
{
	Cell* best = 0;
	float highest_fitness = 0;

	for (auto i : population) {

		if (i->cell.score >= highest_fitness) {
			highest_fitness = i->cell.score;
			best = &i->cell;
		}

	}
	if (!best) {
		throw std::exception("!best");
	}

	return *best;
}
void Population::NewGeneration()
{
	static std::vector<Cell> newCells;
	if (newCells.empty()) {
		for (auto i : population)
			newCells.push_back(i->cell);
	}

	const auto GetRandomParent = [this]() -> Cell* {

		float rand = random(fitnessSum());
		float runningSum = 0;

		for (auto i : population) {
			runningSum += i->cell.score;

			if (runningSum > rand)
				return &i->cell;
		}

		return nullptr;
	};

	Cell best = SetBestCell();

	if (BestCell.score >= best.score) {
		best = BestCell;
	}
	else
		BestCell = best;

	newCells[0] = best;

	for (int i = 1; i < population.size(); i++) {

		Cell* parent = GetRandomParent();

		newCells[i] = *parent;

	}

	int j = 0;
	for (auto& i : population) {
		i->cell = best;
		i->cell.brain.Mutate();

		j++;
	}
	total_attempts++;
}