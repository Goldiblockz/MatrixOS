#pragma once

#include "Color.h"
#include <math.h>

namespace MatrixOS::SYS
{
    uint32_t Millis();
}

namespace ColorEffects
{
    inline Color Rainbow(uint16_t period = 1000, int32_t offset = 0)
    {
        float hue = ((MatrixOS::SYS::Millis() - offset) % period) / (float)period;
        return Color::HsvToRgb(hue, 1.0, 1.0);
    }

    inline uint8_t Breath(uint16_t period = 1000, int32_t offset = 0)
    {
       float brightness = (1 + sin(2 * M_PI * (MatrixOS::SYS::Millis() - offset) / period)) / 2 * 255;
       return (uint8_t)brightness;
    }

    inline Color ColorBreath(Color color, uint16_t period = 1000, int32_t offset = 0)
    {
        return color.Scale(Breath(period, offset)).Gamma();
    }

    inline uint8_t Strobe(uint16_t period = 1000, int32_t offset = 0)
    {
        return (MatrixOS::SYS::Millis() - offset) % period < (period / 2) ? 255 : 0;
    }

    inline Color ColorStrobe(Color color, uint16_t period = 1000, int32_t offset = 0)
    {
        return color.Scale(Strobe(period, offset));
    }

    inline uint8_t Saw(uint16_t period = 1000, int32_t offset = 0)
    {
        return (MatrixOS::SYS::Millis() - offset) % period * 255 / period;
    }

    inline Color ColorSaw(Color color, uint16_t period = 1000, int32_t offset = 0)
    {
        return color.Scale(Saw(period, offset)).Gamma();
    }
}