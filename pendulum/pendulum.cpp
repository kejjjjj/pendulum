#include "pch.h"

Pendulum::Pendulum(const ivec2& pos, const ivec2& mins, const ivec2& maxs)
{
	pf.pos = pos;
	pf.mins = mins;
	pf.maxs = maxs;
	pf.color = { 0,0,0,255 };

	s.pos = { (float)pos.x, (float)pos.y+5 };
	const int length = (pos.x + maxs.x - (pos.x - mins.x)) / 20;
	s.mins = { length, 15 };
	s.maxs = { length, 15 };
	s.color = Pixel(255,0,0,255);

}
void Pendulum::platform::Draw()
{
	engine->FillRect(pos - mins, { maxs.x*2, maxs.y }, color);
}
void Pendulum::stand::Draw()
{
	engine->FillRect(pos - mins, { maxs.x*2, maxs.y }, COL::RED);
}
void Pendulum::stand::UpdatePos(Pendulum::platform& plat)
{
	float rightmove = 0;
	rightmove += engine->GetKey(olc::Key::D).bHeld ? 255 : 0;
	rightmove += engine->GetKey(olc::Key::A).bHeld ? -255 : 0;

	engine->DrawString({ 0,0 }, std::format("rightmove: {}", rightmove), COL::BLACK);

	pos.x += fElapsed * rightmove;

	if (pos.x < plat.pos.x - plat.mins.x)
		pos.x = plat.pos.x - plat.mins.x;

	if (pos.x > plat.pos.x + plat.maxs.x)
		pos.x = plat.pos.x + plat.maxs.x;

}
void Pendulum::Draw()
{

	s.UpdatePos(pf);

	pf.Draw();
	s.Draw();
}