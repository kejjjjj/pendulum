#include "pch.h"

MainPendulum::MainPendulum(const ivec2& pos, const ivec2& mins, const ivec2& maxs)
{
	pf.pos = pos;
	pf.mins = mins;
	pf.maxs = maxs;
	pf.color = { 0,0,0,255 };

}

void MainPendulum::Draw()
{
	auto p = &this->pf;
	engine->FillRect(p->pos - p->mins, { p->maxs.x * 2, p->maxs.y }, p->color);
}

void _main()
{
	static Population population(1000);
	
	if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
		population.active = true;
		population.Reset();
	}

	if(population.active) {


		population.Update();

		population.active = population.GenerationActive();


		if (!population.active) {
			std::cout << "new generation\n";
			population.NewGeneration();
			population.active = true;
			population.Reset();
			Sleep(500);
		}
	}

	engine->DrawString({ 0,100 }, std::format("best score: {}\ngeneration: {}", BestCell.score, total_attempts), COL::BLACK);


}