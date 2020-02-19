#pragma once

#include "Level.h"

// Base class for a level generator.
class Generator
{
	virtual void Build(Level*) {}
};

// Builds a single room, places the player in it,
// and sets it as the current room.
struct BasicGenerator : public Generator
{
	void Build(Level*) override;
};
