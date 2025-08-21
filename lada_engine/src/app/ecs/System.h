#pragma once

#include <set>

#include "ECSUtils.h"

class System {
public:
    std::set<Lada::Entity> m_Entities;
};
