#include "UUID.h"

#include <random>

namespace Lada{
    static std::random_device s_RandomDevice;
    static std::mt19937_64 eng(s_RandomDevice());
    static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

    UUID::UUID(): UUID(s_UniformDistribution(eng)) {
    }

    UUID::UUID(const uint64_t uuid): m_UUID(uuid) {
    }

    UUID::UUID(const UUID& other): m_UUID(other.m_UUID) {
    }

    UUID::operator uint64_t() const
    {
        return m_UUID;
    }

    bool UUID::operator==(const UUID &other) const {
        return m_UUID == other.m_UUID;
    }
}
