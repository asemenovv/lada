#pragma once

#include <vector>

namespace Svch {
    template<typename T>
    std::vector<std::vector<T> > prefixes(const std::vector<T> &v) {
        std::vector<std::vector<T> > res;
        res.reserve(v.size());
        for (size_t i = 1; i <= v.size(); ++i) {
            res.emplace_back(v.begin(), v.begin() + i);
        }
        return res;
    }
}
