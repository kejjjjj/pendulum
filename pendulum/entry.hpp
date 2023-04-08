#pragma once

#include "pch.h"

inline olc::PixelGameEngine* engine;
inline float fElapsed;
class Game : public olc::PixelGameEngine
{

public:
	Game(const std::string_view& name) {
		sAppName = name;
	}

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};