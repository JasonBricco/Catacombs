#include "Stdafx.h"
#include "Renderer.h"

void Renderer::WriteToWindow()
{
    // Sort in increasing order according to layer.
    std::sort(targets.begin(), targets.end(), [](auto a, auto b)
    {
        return a.layer < b.layer;
    });

    for (DrawTarget target : targets)
        window->draw(target.sprite);

    targets.clear();
}
