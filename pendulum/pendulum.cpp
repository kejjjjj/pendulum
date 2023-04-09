#include "pch.h"

Pendulum::Pendulum(const ivec2& pos, const ivec2& mins, const ivec2& maxs)
{
	pf.pos = pos;
	pf.mins = mins;
	pf.maxs = maxs;
	pf.color = { 0,0,0,255 };

	s.pos = { (float)pos.x, (float)pos.y+5 };
	const int length = (pos.x + maxs.x - (pos.x - mins.x)) / 15;
	s.mins = { length, 15 };
	s.maxs = { length, 15 };
	s.color = Pixel(255,0,0,255);

	b.pos = { pf.pos.x, pf.pos.y - int(b.line_length) };
	b.radius = 7;
	b.color = Pixel(255, 0, 0, 255);
	b.pivot = &s.pos;
	b.angle = 45;

	b.pos.x = b.pos.x + (SIN(b.angle) * 10);
	b.pos.y = b.pos.y - (COS(b.angle) * 10);

}
void Pendulum::platform::Draw()
{
	engine->FillRect(pos - mins, { maxs.x*2, maxs.y }, color);
}
void Pendulum::stand::Draw()
{
	engine->FillRect(pos - mins, { maxs.x*2, maxs.y }, COL::RED);
}
void Pendulum::Ball::Draw()
{
	//pos.x = pos.x + (SIN(angle) * 2);
	//pos.y = pos.y - (COS(angle) * 2);



	engine->FillCircle(real_pos, radius, COL::RED);
}
void Pendulum::Ball::UpdatePos(Pendulum::stand& stand)
{
	const float G = 0.4f;
	const float accel = G * SIN(angle);
	velocity += accel;
	velocity *= damping;
	angle += velocity;
	
	real_pos.x = pivot->x + (SIN(angle) * line_length);
	real_pos.y = pivot->y - (COS(angle) * line_length);

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
	b.UpdatePos(s);

	if (engine->GetKey(olc::Key::DEL).bPressed) {
		b.angle = 0;
	}

	engine->DrawLine({ int(s.pos.x), int(s.pos.y - s.mins.y/2)}, b.real_pos, COL::BLACK);
	pf.Draw();
	s.Draw();
	b.Draw();

	

}