#pragma once
#include "Renderer.h"
#include "assets/AssetManager.h"
#include "scene/Scene.h"

namespace Lada {
    class SceneRenderer {
    public:
        explicit SceneRenderer(Scene* scene, Render::Renderer* renderer, AssetManager* assetManager);

        void DrawScene();
    private:
        Scene* m_Scene;
        Render::Renderer* m_Renderer;
        AssetManager* m_AssetManager;
    };
}
