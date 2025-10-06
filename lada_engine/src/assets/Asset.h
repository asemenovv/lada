#pragma once

#include "core/UUID.h"

namespace Lada {
    using AssetID = UUID;

    enum class AssetType {
        Scene,
        Mesh,
        Material,
        Texture,
    };

    class Asset {
    public:
        Asset(const AssetID& id, AssetType type);

        virtual ~Asset() = default;

        AssetID& ID() { return m_ID; }

        AssetType Type() const { return m_Type; }
    private:
        AssetID m_ID;
        AssetType m_Type;
    };
}
