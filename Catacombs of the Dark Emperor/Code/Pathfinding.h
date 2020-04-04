#pragma once

#include "Utils.h"
#include "Room.h"

class Level;

struct Path
{
	std::vector<Vector2f> points;

	int Count()
	{
		return (int)points.size();
	}

	Vector2f Next()
	{
		Vector2f next = points.back();
		points.pop_back();

		return next;
	}

	bool Valid()
	{
		return points.size() > 0;
	}
};

struct PathNode
{
	Vector2i pos;
	int cost;
	int g, f, h;
	PathNode* parent;

	bool operator<(PathNode other) const
	{
		return f < other.f;
	}

	bool operator>(PathNode other) const
	{
		return f > other.f;
	}

	bool operator==(PathNode other)
	{
		return pos == other.pos;
	}
};

#define IVEC2_MAP(type) std::unordered_map<Vector2i, type, Vector2iHash, Vector2iCompare>

struct SortedNodeList
{
	IVEC2_MAP(PathNode*) table;
	std::vector<PathNode*> nodes;

	int Count()
	{
		return (int)nodes.size();
	}

	int BinarySearch(PathNode* item)
	{
		int first = 0;
		int last = (int)nodes.size() - 1;

		while (first <= last)
		{
			int mid = (first + last) / 2;

			if (*item > * nodes[mid])
				first = mid + 1;
			else if (*item < *nodes[mid])
				last = mid - 1;
			else return mid;
		}

		return -(first + 1);
	}

	void Add(PathNode* node)
	{
		int index = BinarySearch(node);
		if (index < 0) index = ~index;

		nodes.insert(nodes.begin() + index, node);
	}

	void Add(Vector2i pos, PathNode* node)
	{
		auto it = table.find(pos);

		if (it != table.end())
			return;

		table.insert(std::make_pair(pos, node));
		Add(node);
	}

	bool TryGetValue(Vector2i pos, PathNode** value)
	{
		auto it = table.find(pos);

		if (it == table.end())
			return false;

		*value = it->second;
		return true;
	}

	void Remove(PathNode* node)
	{
		nodes.erase(std::find(nodes.begin(), nodes.end(), node));
	}

	void RemoveFirst(Vector2i pos)
	{
		auto it = table.find(pos);
		table.erase(it);

		nodes.erase(nodes.begin());
	}

	PathNode* First()
	{
		return nodes[0];
	}

	void Clear()
	{
		table.clear();
		nodes.clear();
	}

	PathNode* GetNode(int i)
	{
		return nodes[i];
	}
};

struct PathNodeHash
{
	int operator()(PathNode* v) const
	{
		return v->pos.y * 31 + v->pos.x;
	}
};

struct PathNodeCompare
{
	bool operator()(PathNode* a, PathNode* b) const
	{
		return a->pos == b->pos;
	}
};

#define PATHNODE_SET std::unordered_set<PathNode*, PathNodeHash, PathNodeCompare>

struct Pathfinder
{
	SortedNodeList openList;
	PATHNODE_SET closedList;

	constexpr static int MaxNodes = Room::Width * Room::Height;
	int nodeCount;
	PathNode nodeList[MaxNodes];

	int successorCount = 0;
	PathNode* successors[8];
};

void FindPath(Level* level, Vector2i start, Vector2i end, Path* path);
