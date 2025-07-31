#include "ldpch.h"
#include "Texture.h"
#include "stb_image.h"
#include "app/Logger.h"
#include "app/GlCall.h"
#include "renderer/Renderer.h"

namespace Lada {
    Texture::Texture(const unsigned char *data, const int width, const int height, const int BPP) {
        GL_CALL(glGenTextures(1, &m_RendererID));
        Bind();

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, data);
        Unbind();
    }

    Texture::~Texture() {
    }

    void Texture::Bind(const unsigned int slot) const {
        GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    }

    void Texture::Unbind() const {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }
}
