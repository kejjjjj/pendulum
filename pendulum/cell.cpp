#include "pch.h"


void Cell::Reset()
{
	score = NULL;
	brain.time_alive = 0;
	dead = false;


}
void Cell::NewGeneration()
{



	//Reset();
	//NewBrain(10000);


}
void Cell::GiveScore(float pendulum_angle)
{
	if (pendulum_angle > 90) {
		pendulum_angle = fmodf(pendulum_angle, 90);
		score += (pendulum_angle);
	}
	else score += 90.f - pendulum_angle;
}
void Cell::OnDeath()
{
	//if (BestCell.score > this->score) {
	//	*this = BestCell;
	//}
	//else {
	//	BestCell = *this;
	//	std::cout << "best score: " << this->score << '\n';
	//}

	//this->Reset();
	//this->brain.Mutate();

	//total_attempts++;

}