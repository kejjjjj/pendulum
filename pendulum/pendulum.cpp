#include "pch.h"

Pendulum::Pendulum(const MainPendulum& pend) : cell(10000)
{

	pos = pend.pf.pos;
	mins = pend.pf.mins;
	maxs = pend.pf.maxs;

	s.original_pos = { (float)pos.x, (float)pos.y + 5 };
	s.pos = { (float)s.original_pos.x, (float)s.original_pos.y+5 };
	const int length = (pos.x + maxs.x - (pos.x - mins.x)) / 15;
	s.mins = { length, 15 };
	s.maxs = { length, 15 };
	s.color = olc::Pixel(rand()%255, rand() % 255, rand() % 255, 255);

	b.pos = { pos.x, pos.y - int(b.line_length) };
	b.radius = 7;
	b.color = olc::Pixel(255, 0, 0, 255);
	b.pivot = &s.pos;
	b.angle = 1;



}
void Pendulum::DrawStand()
{

	auto col = olc::BLACK;

	if (!cell.best) {
		col.a = 55;
	}
	else {
		col.g = 255;
	}

	engine->FillRect(s.pos - s.mins, { s.maxs.x*2, s.maxs.y }, col);


}
void Pendulum::DrawBall()
{
	//pos.x = pos.x + (SIN(angle) * 2);
	//pos.y = pos.y - (COS(angle) * 2);
	auto col = b.color;

	if (!cell.best)
		col.a = 55;
	else {
		col.r = 0;
		col.g = 255;
	}
	engine->FillCircle(b.real_pos, b.radius, col);

}

void Pendulum::UpdateStand(int direction)
{
	auto s = &this->s;

	if (direction == 1) {
		if (!rightmove)
			s->t = 0;
		s->velocity = std::lerp(s->velocity, 1.f, s->t);
		s->t = std::clamp((s->t += 0.01f), 0.f, 1.f);
		s->ref_velocity = s->velocity;
		rightmove = true;

	}
	else if (direction == -1) {
		if (rightmove)
			s->t = 0;
		s->velocity = std::lerp(s->velocity, -1.f, s->t);
		s->t = std::clamp((s->t += 0.01f), 0.f, 1.f);
		s->ref_velocity = s->velocity;

		rightmove = false;
	}
	else if (s->velocity) {
		s->velocity = std::lerp(0, s->ref_velocity, s->t);
		s->t = std::clamp((s->t -= 0.01f), 0.f, 1.f);
	}

	//engine->DrawString({ 0,0 }, std::format("v: {}", s->velocity), COL::BLACK);



	s->pos.x += fElapsed * (s->velocity * 175);

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


		if (cell.brain.frames > 0) {
			cell.brain.frames = 0;
			++cell.brain.it;
			++cell.brain.iterator;
		}
		

		if (b.n_angle >= 90 && b.n_angle <= 270) {
			cell.dead = true;
		}
		else {
			cell.GiveScore(b.n_angle);

		}
		//engine->DrawString({ 0,100 }, std::format("iteration: {}\nangle: {}", distance(cell.brain.directions.begin(), cell.brain.it), b.n_angle), COL::BLACK);
		cell.brain.time_alive = TimeDifference<float>(pendulum->start_time, global_time);
	}
	else {
		cell.OnDeath();
	}

	UpdateStand(*cell.brain.it);
	UpdateBall();

	
	engine->SetPixelMode(olc::Pixel::ALPHA);

	DrawStand();
	DrawBall();

	auto col = olc::Pixel(olc::BLACK);

	if (!cell.best)
		col.a = 55;

	engine->DrawLine({ int(s.pos.x), int(s.pos.y - s.mins.y / 2) }, b.real_pos, col);

	engine->SetPixelMode(olc::Pixel::NORMAL);


	if (cell.brain.it == cell.brain.directions.end())
		cell.dead = true;

	cell.brain.frames++;

}
void Pendulum::Reset()
{
	s.pos = { (float)s.original_pos.x, (float)s.original_pos.y + 5 };
	const int length = (s.original_pos.x + maxs.x - (s.original_pos.x - mins.x)) / 15;
	s.mins = { length, 15 };
	s.maxs = { length, 15 };
	s.t = 0;
	s.ref_velocity = 0;
	s.velocity = 0;
	//s.color = Pixel(255, 0, 0, 255);

	b.pos = { (int)s.original_pos.x, (int)s.original_pos.y - int(b.line_length) };
	b.radius = 7;
	//b.color = Pixel(255, 0, 0, 255);
	b.pivot = &s.pos;
	b.angle = 1;
	b.n_angle = 0;
	b.velocity = 0;

	cell.dead = false;
	cell.score = NULL;
	cell.brain.time_until_update = 0;
	cell.brain.iterator = 0;
	//cell.brain.last_it_update = GetTime();
	cell.brain.steps_taken = 0;
	fElapsed = 0;
	rightmove = false;

	//std::cout << "spawnpos: { " << b.pivot->x << " , " << b.pivot->y << " }\n";
}