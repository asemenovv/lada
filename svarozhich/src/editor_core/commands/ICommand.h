#pragma once
#include <QString>

namespace Svch {
    class ICommand {
    public:
        virtual ~ICommand() = default;

        virtual void Redo() = 0;
        virtual void Undo() = 0;
        virtual QString Text() = 0;
    };
}
