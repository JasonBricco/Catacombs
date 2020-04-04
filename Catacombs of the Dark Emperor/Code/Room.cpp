
#include "Stdafx.h"
#include "Room.h"

bool Room::TrySetObstacle(int x, int y)
{
	Vector2i p = Vector2i(x, y);

	auto it = obstacles.find(p);

	if (it == obstacles.end())
	{
		obstacles.insert(p);
		return true;
	}

	return false;
}

void Room::RemoveEntity(Entity* entity)
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		if (*it == entity)
		{
			entities.erase(it);
			return;
		}
	}

}

void Room::BuildPathGrid()
{
	for (Entity* entity : entities)
	{
		AABB bb = entity->BoundingBox();
		bb.Shrink(Vector2f(entity->GetSize() * 0.05f));

		if (!entity->IsPassable())
		{
			Vector2i tMin = TilePos(bb.BottomLeft());
			Vector2i tMax = TilePos(bb.TopRight());

			for (int y = tMin.y; y <= tMax.y; ++y)
			{
				for (int x = tMin.x; x <= tMax.x; ++x)
				{
					if (InBounds(x, y))
						pathGrid[y * Room::Width + x] = INT_MAX;
				}
			}
		}
	}
}

void Room::Update(Level* level, float elapsed)
{
	for (Entity* entity : entities)
		entity->Update(level, elapsed);
}

void Room::Draw(Renderer& rend)
{
	for (Entity* entity : entities)
	{
		if (entity->Visible())
			entity->Draw(rend);
	}

	GameState& state = getGameState();

	// Perform this in a separate loop for performance
	// reasons when showOutlines is false.
	if (state.showOutlines)
	{
		for (Entity* entity : entities)
			entity->DrawOutline(rend);
	}

	if (state.showPathGrid)
	{
		debugPathRects.clear();

		if (debugPathRects.capacity() < TileCount)
			debugPathRects.reserve(TileCount);

		for (int y = 0; y < Room::Height; ++y)
		{
			for (int x = 0; x < Room::Width; ++x)
			{
				int cost = pathGrid[y * Room::Width + x];

				if (cost > 0)
				{
					debugPathRects.emplace_back(Vector2f(32.0f, 32.0f));
					RectangleShape* rect = &debugPathRects.back();
					rect->setPosition(Vector2f((float)x, (float)y) * 32.0f);
					rect->setFillColor(Color::Magenta);
					rend.Draw(rect, INT_MAX);
				}
			}
		}
	}
}
