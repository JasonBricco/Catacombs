#include "Stdafx.h"
#include "Pathfinding.h"
#include "Room.h"
#include "Level.h"

static Pathfinder pathfinder;

static PathNode* GetNode(Vector2i pos, int cost)
{
	if (pathfinder.nodeCount >= Pathfinder::MaxNodes)
		return nullptr;

	pathfinder.nodeList[pathfinder.nodeCount] = { pos, cost };
	return &pathfinder.nodeList[pathfinder.nodeCount++];
}

static int GetPathCost(int* grid, int x, int y)
{
	return grid[y * Room::Width + x];
}

static void GetSuccessors(int* grid, Vector2i pos)
{
	pathfinder.successorCount = 0;

	for (int i = 0; i < 4; ++i)
	{
		Vector2i next = pos + directions[i];

		if (Room::InBounds(next.x, next.y))
		{
			int cost = grid[next.y * Room::Width + next.x];

			if (cost != INT_MAX)
				pathfinder.successors[pathfinder.successorCount++] = GetNode(next, cost);
		}
	}

	for (int i = 4; i < 8; i++)
	{
		Vector2i dir = directions[i];
		Vector2i next = pos + dir;

		if (Room::InBounds(next.x, next.y))
		{
			int cost = GetPathCost(grid, next.x, next.y);

			if (cost != INT_MAX)
			{
				int adjX = GetPathCost(grid, pos.x + dir.x, pos.y);
				int adjY = GetPathCost(grid, pos.x, pos.y + dir.y);

				if (adjX != INT_MAX && adjY != INT_MAX)
					pathfinder.successors[pathfinder.successorCount++] = GetNode(next, cost);
			}
		}
	}
}

static void TracePath(PathNode* node, Vector2i start, Path* path)
{
	PathNode* current = node;
	assert(current != nullptr);

	while (current->pos != start)
	{
		path->points.push_back(Vector2f(current->pos.x + 0.5f, current->pos.y + 0.5f));
		current = current->parent;
		assert(current != nullptr);
	}
}

// Compute the estimated number of cells to reach the destination 
// using Manhattan distance.
static int ComputeHeuristic(Vector2i start, Vector2i end)
{
	return abs(end.x - start.x) + abs(end.y - start.y);
}

void FindPath(Level* level, Vector2i start, Vector2i end, Path* path)
{
	Room* room = level->GetCurrentRoom();

	path->points.clear();
	int* grid = room->PathGrid();

	// Return if the ending position is out of bounds or not reachable.
	if (!Room::InBounds(start.x, start.y) || !Room::InBounds(end.x, end.y))
		return;

	if (grid[end.y * Room::Width + end.x] == INT_MAX)
		return;

	auto& open = pathfinder.openList;
	auto& closed = pathfinder.closedList;

	open.Add(start, GetNode(start, 0));

	while (open.Count() > 0)
	{
		PathNode* current = open.First();
		open.RemoveFirst(current->pos);

		closed.insert(current);

		if (current->pos == end)
		{
			TracePath(current, start, path);
			break;
		}

		GetSuccessors(grid, current->pos);
		bool failed = false;

		for (int i = 0; i < pathfinder.successorCount; ++i)
		{
			PathNode* next = pathfinder.successors[i];

			if (next == nullptr)
			{
				failed = true;
				break;
			}

			auto it = closed.find(next);

			if (it != closed.end())
				continue;

			Vector2i nP = next->pos;
			int newG = current->g + next->cost;

			PathNode* node;
			if (!open.TryGetValue(next->pos, &node))
			{
				next->g = newG;
				next->h = ComputeHeuristic(nP, end);
				next->f = next->g + next->h;
				next->parent = current;
				open.Add(next->pos, next);
			}
			else
			{
				if (newG < node->g)
				{
					open.Remove(node);
					node->g = newG;
					node->f = node->g + node->h;
					node->parent = current;
					open.Add(node);
				}
			}
		}

		if (failed)
		{
			Print("Failed to find the path.\n");
			break;
		}
	}

	closed.clear();
	open.Clear();
	pathfinder.nodeCount = 0;
}
