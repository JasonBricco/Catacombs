#pragma once

struct DrawTarget
{
	Drawable* drawable;
	int layer;
};

// Handles drawing of sprites. All sprite drawing should
// go through this class rather than directly to the RenderWindow.
// That way, all required processing can occur (such as sorting).
class Renderer
{
	RenderWindow* window;
	std::vector<DrawTarget> targets;

public:
	Renderer(RenderWindow* win)
	{
		window = win;
		targets.reserve(576);
	}

	inline void Draw(Drawable* drawable, int layer)
	{
		DrawTarget target = { drawable, layer };
		targets.push_back(target);
	}

	inline void Draw(Drawable* drawable)
	{
		DrawTarget target = { drawable, 0 };
		targets.push_back(target);
	}

	void WriteToWindow();

	inline RenderWindow* getWindow()
	{
		return window;
	}
};
