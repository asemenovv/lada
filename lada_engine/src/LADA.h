#pragma once

#include "app/Application.h"
#include "app/Logger.h"
#include "platform/glfw/GlfwWindow.h"

#include "app/layer/Layer.h"
#include "imgui/ImGuiLayer.h"

#include "events/EventManager.h"
#include "events/Event.h"
#include "events/ApplicationEvent.h"
#include "events/KeyEvent.h"

#include "renderer/material/Texture.h"
#include "renderer/material/Material.h"
#include "renderer/material/Shader.h"
#include "renderer/buffers//VertexBufferLayout.h"
#include "renderer/buffers/IndexBuffer.h"
#include "renderer/Mesh.h"
#include "app/GlCall.h"
#include "renderer/buffers/VertexArray.h"
#include "renderer/Renderer.h"
#include "renderer/model/Model.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "spdlog/spdlog.h"

// ====== Entry Point ======
#include "app/EntryPoint.h"
