#pragma once

#ifndef PCH_H
#define PCH_H

#define NOMINMAX

#define PI 3.14159f
#define RADIAN 6.283185f

#define DEG2RAD(x) (x * PI / 180)
#define RAD2DEG(x) (x * 180 / PI)

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];


#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <random> // for std::mt19937
#include <memory>

#include "olcPixelGameEngine.h"

using olc::vi2d;
using olc::vf2d;
//using olc::Pixel;

#include "typedefs.hpp"
#include "vectors.hpp"
#include "math.hpp"

#include "entry.hpp"
#include "pendulum.hpp"

#endif