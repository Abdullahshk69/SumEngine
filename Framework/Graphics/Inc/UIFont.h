#pragma once

#include "Color.h"

namespace SumEngine::Graphics
{
    class UIFont final
    {
    public:
        enum class FontType
        {
            Arial,
            CourierNew,
            Consolas,
            TimesNewRoman,
            Verdana
        };

        static void StaticInitialize(FontType font);
        static void StaticTerminate();
        static UIFont* Get();

        UIFont() = default;
        ~UIFont();

        void Initialize(FontType font);
        void Terminate();

        void DrawString(const wchar_t* str, const Math::Vector2& position, const Color& color, float size = 10.0f);
        float GetStringWidth(const wchar_t* str, float size) const;

    private:
        FontType mFontType = FontType::Arial;
        IFW1Factory* mFontFactory = nullptr;
        IFW1FontWrapper* mFontWrapper = nullptr;        // You need a wrapper for each font type to be used (As in how many fonts to be used at a time)
    };
}