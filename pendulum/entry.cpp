
#include "pch.h"

Pendulum* pendulum;

bool Game::OnUserCreate()
{
	pendulum = 
		new Pendulum(
			{ScreenWidth()/2, ScreenHeight()/2}, 
			{100, 5}, 
			{100, 5});

	engine = this;

	return true;
}
bool Game::OnUserUpdate(float fElapsedTime)
{
	fElapsed = fElapsedTime;
	Clear(COL::WHITE);
	
	pendulum->Draw();

	return true;
}

int main()
{
	Game demo("EPICNESS");
#pragma warning(suppress : 26812)
	if (demo.Construct(640, 480, 2, 2, false, true))
		demo.Start();
	return 0;
}