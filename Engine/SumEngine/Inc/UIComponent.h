#pragma once

#include "Component.h"

namespace SumEngine
{
    class UIComponent : public Component
    {
    public:
        virtual void Render() = 0;
    };
}