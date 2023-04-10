#include "pch.h"

Pendulum::Pendulum(const MainPendulum& pend) : cell(10000)
{
	pos = pend.pf.pos;
	mins = pend.pf.mins;
	maxs = pend.pf.maxs;

	s.pos = { (float)pos.x, (float)pos.y+5 };
	const int length = (pos.x + maxs.x - (pos.x - mins.x)) / 15;
	s.mins = { length, 15 };
	s.maxs = { length, 15 };
	s.color = Pixel(rand()%255, rand() % 255, rand() % 255, 255);

	b.pos = { pos.x, pos.y - int(b.line_length) };
	b.radius = 7;
	b.color = Pixel(255, 0, 0, 255);
	b.pivot = &s.pos;
	b.angle = 359;

	b.pos.x = b.pos.x + (SIN(b.angle) * 10);
	b.pos.y = b.pos.y - (COS(b.angle) * 10);

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

void Pendulum::UpdateStand(int direction)
{
	auto s = &this->s;
	static float t{};
	static float ref_vel = 0;
	if (direction == 1) {
		if (!rightmove)
			t = 0;
		s->velocity = std::lerp(s->velocity, 1.f, t);
		t = std::clamp((t += 0.01f), 0.f, 1.f);
		ref_vel = s->velocity;
		rightmove = true;

	}
	else if (direction == -1) {
		if (rightmove)
			t = 0;
		s->velocity = std::lerp(s->velocity, -1.f, t);
		t = std::clamp((t += 0.01f), 0.f, 1.f);
		ref_vel = s->velocity;

		rightmove = false;
	}
	else if (s->velocity) {
		s->velocity = std::lerp(0, ref_vel, t);
		t = std::clamp((t -= 0.01f), 0.f, 1.f);
	}

	//engine->DrawString({ 0,0 }, std::format("v: {}", s->velocity), COL::BLACK);



	s->pos.x += fElapsed * (s->velocity * 255);

	if (s->pos.x < pos.x - mins.x) {
		s->pos.x = pos.x - mins.x;
		s->velocity = NULL;
	}

	if (s->pos.x > pos.x + maxs.x) {
		s->pos.x = pos.x + maxs.x;
		s->velocity = NULL;
	}
}
void Pendulum::UpdateBall()
{
	auto ball = &this->b;

	const float G = 0.1f;
	const float accel = G * SIN(ball->angle);
	ball->velocity += accel + (this->s.velocity / 50);
	ball->velocity *= ball->damping;
	ball->angle += ball->velocity;
	ball->n_angle = fabs(fmodf(ball->angle, 360));


	ball->real_pos.x = ball->pivot->x + (SIN(ball->angle) * ball->line_length);
	ball->real_pos.y = ball->pivot->y - (COS(ball->angle) * ball->line_length);
}
void Pendulum::Update()
{
	if (!cell.dead) {
		//short dir = 0;

		//if (engine->GetKey(olc::Key::A).bHeld) {
		//	dir = -1;
		//}else if (engine->GetKey(olc::Key::D).bHeld) {
		//	dir = 1;
		//}

		UpdateStand(*cell.brain.it);
		UpdateBall();

		if (cell.brain.time_until_update <= 0) {
			++cell.brain.it;
			cell.brain.time_until_update = 0.25f;
			cell.brain.last_it_update = global_time;
		}

		

		if (b.n_angle >= 90 && b.n_angle <= 270) {
			cell.dead = true;
		}
		else {
			cell.GiveScore(b.n_angle);

		}
		cell.brain.time_until_update -= TimeDifference<float>(cell.brain.last_it_update, GetTime());
		//engine->DrawString({ 0,100 }, std::format("iteration: {}\nangle: {}", distance(cell.brain.directions.begin(), cell.brain.it), b.n_angle), COL::BLACK);

	}
	else {
		cell.OnDeath();
	}
	//engine->DrawString({ 0,100 }, std::format("score: {}\nbest score: {}\ngeneration: {}", cell.score, BestCell.score, total_attempts), COL::BLACK);

	//if (engine->GetKey(olc::Key::DEL).bPressed) {
	//	b.angle = 1.f;
	//	b.velocity = 0;
	//	
	//}

	engine->DrawLine({ int(s.pos.x), int(s.pos.y - s.mins.y/2)}, b.real_pos, COL::BLACK);

	s.Draw();
	b.Draw();

	if (cell.brain.it == cell.brain.directions.end())
		cell.dead = true;

}
void Pendulum::Reset()
{
	s.pos = { (float)pos.x, (float)pos.y + 5 };
	const int length = (pos.x + maxs.x - (pos.x - mins.x)) / 15;
	s.mins = { length, 15 };
	s.maxs = { length, 15 };
	//s.color = Pixel(255, 0, 0, 255);

	b.pos = { pos.x, pos.y - int(b.line_length) };
	b.radius = 7;
	b.color = Pixel(255, 0, 0, 255);
	b.pivot = &s.pos;
	b.angle = 359;
	b.velocity = 0;

	b.pos.x = b.pos.x + (SIN(b.angle) * 10);
	b.pos.y = b.pos.y - (COS(b.angle) * 10);

	cell.dead = false;
	cell.score = NULL;
	cell.brain.time_until_update = 0.5;
}