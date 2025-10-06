#pragma once

#include <cstddef>
#include <memory>

namespace Lada {
    class UUID {
    public:
        UUID();

        explicit UUID(uint64_t uuid);

        UUID(const UUID &other);

        ~UUID() = default;

        explicit operator uint64_t() const;

        bool operator==(const UUID &other) const;

    private:
        std::uint64_t m_UUID;
    };
}

template<>
struct std::hash<Lada::UUID> {
    std::size_t operator()(const Lada::UUID &uuid) const noexcept {
        return static_cast<uint64_t>(uuid);
    }
};
