#pragma once

namespace Lada {
    class MetalTest {
    public:
        MetalTest() = default;

        void Hello();
    private:
        class Impl;
        Impl* m_Impl;
    };
}
