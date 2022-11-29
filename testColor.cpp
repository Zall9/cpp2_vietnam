#include <iostream>
#include <fstream>
#include "Color.hpp"

int main(int argc, char **argv)
{
    typedef Image2D<Color> ColorImage2D;
    ColorImage2D img(8, 8, Color(255, 0, 255));
    for (int y = 0; y < img.h(); ++y)
    {
        for (int x = 0; x < img.w(); ++x)
            std::cout << " " << (int)img.at(x, y).red;
        std::cout << std::endl;
    }
}
