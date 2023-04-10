#pragma once

#ifndef qmath
#define qmath

#include "pch.h"

float random(const float range); //0 -> HI
float random(const float min, const float range); //LO -> HI
inline auto GetTime() { return std::chrono::system_clock::now(); }
template<typename t>
t TimeDifference(const std::chrono::time_point<std::chrono::system_clock>& old, const std::chrono::time_point<std::chrono::system_clock>& current)
{
	std::chrono::duration<t> difference = current - old;
	return difference.count();
}
#endif