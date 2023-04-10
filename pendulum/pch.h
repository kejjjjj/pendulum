#pragma once

#ifndef PCH_H
#define PCH_H

#define NOMINMAX

#define PI 3.14159f
#define RADIAN 6.283185f

#define DEG2RAD(x) (x * PI / 180)
#define RAD2DEG(x) (x * 180 / PI)

#define SIN(x) (sin(DEG2RAD((x))))
#define COS(x) (cos(DEG2RAD((x))))
#define TAN(x) (tan(DEG2RAD(x)))

#define ASIN(x) (asin(DEG2RAD((x))))
#define ACOS(x) (acos(DEG2RAD((x))))
#define ATAN(x) (atan(DEG2RAD(x)))

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
#include <list>
#include <chrono>

#include "olcPixelGameEngine.h"

using olc::vi2d;
using olc::vf2d;
//using olc::Pixel;

#include "typedefs.hpp"
#include "vectors.hpp"
#include "math.hpp"

#include "brain.hpp"
#include "cell.hpp"


#include "main_pendulum.hpp"
#include "pendulum.hpp"
#include "entry.hpp"

#include "population.hpp"

#endif