#include "Engine/Core/Color.hpp"
#include <sstream>

Color::Color()
{
    this->color.r = 0;
    this->color.g = 0;
    this->color.b = 0;
    this->color.a = 255;
}

Color::Color(const int r, const int g, const int b, const int a)
{
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->color.a = a;
}

Color::Color(const char* hexString, const Uint8 alpha)
{
    std::stringstream stream;

    stream << std::hex << hexString;
    std::string colorString = stream.str();

    // We remove the # character if present
    if (colorString[0] == '#')
    {
        colorString.erase(0,1);
    }

    // We check the size is correct
    if (colorString.size() == 6)
    {
        std::stringstream redString;
        redString << std::hex << (colorString.substr(0,2));

        std::stringstream greenString;
        greenString << std::hex << (colorString.substr(2,2));

        std::stringstream blueString;
        blueString << std::hex << (colorString.substr(4,2));

        unsigned int red;
        unsigned int green;
        unsigned int blue;

        redString >> red;
        blueString >> blue;
        greenString >> green;

        this->color.r = red;
        this->color.g = green;
        this->color.b = blue;
        this->color.a = alpha;
    }
}

Color::Color(const Color & other)
{
    this->color = other.color;
}

void Color::SetRed(int value)
{
    if (value > 255)
    {
        value = 255;
    }

    if (value < 0)
    {
      value = 0;
    }

    this->color.r = value;
}

void Color::SetGreen(int value)
{
    if (value > 255)
    {
        value = 255;
    }

    if (value < 0)
    {
        value = 0;
    }

    this->color.g = value;
}

void Color::SetBlue(int value)
{
    if (value > 255)
    {
        value = 255;
    }

    if (value < 0)
    {
        value = 0;
    }

    this->color.b = value;
}

void Color::SetAlpha(int value)
{
    if (value > 255)
    {
        value = 255;
    }

    if (value < 0)
    {
        value = 0;
    }
    this->color.a = value;
}

Uint8 Color::GetRed()
{
    return this->color.r;
}

Uint8 Color::GetGreen()
{
    return this->color.g;
}

Uint8 Color::GetBlue()
{
    return this->color.b;
}

Uint8 Color::GetAlpha()
{
    return this->color.a;
}

bool Color::operator !=(const Color& other)
{
    if (this->color.r != other.color.r)
    {
        return true;
    }
    else if (this->color.g != other.color.g)
    {
        return true;
    }
    else if (this->color.b != other.color.b)
    {
        return true;
    }
    else if (this->color.a != other.color.a)
    {
        return true;
    }
    return false;
}

bool Color::operator ==(const Color& other)
{
    if (this->color.r != other.color.r)
    {
        return false;
    }
    else if (this->color.g != other.color.g)
    {
        return false;
    }
    else if (this->color.b != other.color.b)
    {
        return false;
    }
    else if (this->color.a != other.color.a)
    {
        return false;
    }
    return true;
}

SDL_Color Color::ToSDLColor()
{
    return this->color;
}

Uint32 Color::ToPixelValue(SDL_PixelFormat* format)
{
    return SDL_MapRGBA(format, this->color.r, this->color.g, this->color.b, this->color.a);
}

const std::string Color::ToString()
{
    std::stringstream stream;

    stream << "red: " << this->color.r
            << " green: " << this->color.g
            << " blue: " << this->color.b
            << " alpha: " << this->color.a;

    return stream.str();
}
