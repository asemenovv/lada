#pragma once

#define BIT(x) (1 << x)
#define BIND_HANDLER(e, fn) RegisterHandler<e>(std::bind(&fn, this, std::placeholders::_1))
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Lada {
    std::string workingDir();
}
