#pragma once

#include <bitset>

// Initial implementation is taken from https://austinmorlan.coms/posts/entity_component_system/#what-is-an-ecs
namespace Lada {
    using Entity = std::uint32_t;
    constexpr Entity MAX_ENTITIES = 1000;

    using ComponentType = std::uint8_t;
    constexpr ComponentType MAX_COMPONENTS = 32;

    using Signature = std::bitset<MAX_COMPONENTS>;
}
