#pragma once
#include "Renderer.h"
#include "scene/Scene.h"

namespace Lada {
    class SceneRenderer {
    public:
        explicit SceneRenderer(Scene* scene, Render::Renderer* renderer);

        void DrawScene();
    private:
        Scene* m_Scene;
        Render::Renderer* m_Renderer;
    };
}
