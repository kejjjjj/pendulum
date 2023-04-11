
#include "pch.h"

Pendulum* pend;
bool Game::OnUserCreate()
{
	pendulum = 
		new MainPendulum(
			{ScreenWidth()/2, ScreenHeight()/2}, 
			{200, 5}, 
			{200, 5});

	pend = new Pendulum(*pendulum);

	engine = this;

	std::cout << "fmodf(359, 90) = " << fmodf(359, 90) << '\n';
	std::cout << "fmodf(1, 90) = " << fmodf(1, 90) << '\n';
	std::cout << "fmodf(70, 90) = " << fmodf(70, 90) << '\n';
	std::cout << "fmodf(271, 90) = " << fmodf(271, 90) << '\n';

	return true;
}
bool Game::OnUserUpdate(float fElapsedTime)
{
	global_time = GetTime();
	fElapsed = fElapsedTime;
	Clear(COL::WHITE);
	
	pendulum->Draw();
	
	_main();

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