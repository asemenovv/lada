#pragma once

namespace lada::event {
    template<typename T>
    class IEventListener {
    public:
        virtual ~IEventListener() = default;
        virtual bool OnEvent(const T& e) = 0;
    };
}
