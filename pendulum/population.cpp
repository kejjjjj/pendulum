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
		for (auto i : population) {
			newCells.push_back(i->cell);
		}
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
	BestCell.best = false;
	best.best = false;

	if (BestCell.score >= best.score) {
		best.score = BestCell.score;
		best.brain.directions = BestCell.brain.directions;
		best.brain.time_alive = BestCell.brain.time_alive;

	}
	else {
		BestCell.score = best.score;
		BestCell.brain.directions = best.brain.directions;

		if (BestCell.brain.time_alive <= best.brain.time_alive) {
			BestCell.brain.time_alive = best.brain.time_alive;
			std::time_t now = std::time(0);
#pragma warning(suppress : 4996)
			char* dt = std::ctime(&now);
			std::cout << "new record: " << std::format("{:.3f}s", BestCell.brain.time_alive) << " : " << dt;

		}


		std::cout << "new score: " << std::format("{} points\n", BestCell.score);
		//auto dist = std::distance(best.brain.directions.begin(), best.brain.it);
		std::cout << "instructions used: " << best.brain.iterator << '/' << best.brain.directions.size() << '\n';
	}

	newCells[0] = best;
	newCells[0].best = true;
	
	for (auto& i : population)
		i->cell.best = false;

	population.front()->cell.best = false;
	population.front()->cell.brain.directions = best.brain.directions;
	population.front()->cell.brain.time_alive = best.brain.time_alive;
	population.front()->cell.score = best.score;

	//for (int i = 1; i < population.size(); i++) {

	//	Cell* parent = GetRandomParent();
	//	newCells[i] = *parent;

	//}

	int j = 0;
	for (auto& i : population) {
		if (!i->cell.best) {
			i->cell.brain.directions = best.brain.directions;
			i->cell.brain.time_alive = best.brain.time_alive;
			i->cell.brain.Mutate();
		}
		j++;
	}
	total_attempts++;
}