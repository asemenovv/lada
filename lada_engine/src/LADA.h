#pragma once

#include "app/Application.h"
#include "app/Logger.h"
#include "app/Window.h"

#include "app/layer/Layer.h"
#include "imgui/ImGuiLayer.h"

#include "events/EventManager.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"

#include "renderer/material/Texture.h"
#include "render/VertexBufferLayout.h"
#include "renderer/buffers/IndexBuffer.h"
#include "render/Renderer.h"
#include "renderer/material/Shader.h"
#include "renderer/buffers/VertexArray.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "spdlog/spdlog.h"

// ====== Entry Point ======
#include "app/EntryPoint.h"
