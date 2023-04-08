#include "pch.h"

float random(const float range) { //0 -> HI
	static std::mt19937 mt;
	std::uniform_real_distribution num{ 0.f, range };
	return num(mt);

}
float random(const float min, const float range) { //LO -> HI
	static std::mt19937 mt;
	std::uniform_real_distribution num{ min, range };
	return num(mt);
}