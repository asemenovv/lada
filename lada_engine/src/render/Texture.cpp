#include "Texture.h"

#include <iostream>
#include <ostream>

#include "../vendor/stb_image/stb_image.h"

namespace lada::render {
    Texture::Texture(const std::string& path)
        : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0) {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

        std::cout << "Loading texture: '" << path << "' (" << m_Width << "x" << m_Height << ")" << std::endl;

        GL_CALL(glGenTextures(1, &m_RendererID));
        Bind();

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
        Unbind();

        if (m_LocalBuffer) {
            stbi_image_free(m_LocalBuffer);
        }
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
