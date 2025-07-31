#pragma once

#include "app/GlCall.h"
#include "assets/IAsset.h"
#include "yaml-cpp/node/iterator.h"

namespace Lada {
    class Texture : public IAsset {
        unsigned int m_RendererID;
        std::string m_Name;
    public:
        Texture(const unsigned char* data, int width, int height, int BPP);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        void SetName(const std::string& name) { m_Name = name; }
        std::string GetName() { return m_Name; }
    };
}
