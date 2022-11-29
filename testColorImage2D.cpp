#include <iostream>
#include <fstream>
#include "Color.hpp"
#include "Image2D.hpp"
using namespace std;

int main(int argc, char **argv)
{
    typedef Image2D<Color> ColorImage2D;
    ColorImage2D img(8, 8, Color(255, 0, 255));
    for (int y = 0; y < img.h(); ++y)
    {
        for (int x = 0; x < img.w(); ++x)
            std::cout << " " << (int)img.at(x, y).red << "/" << (int)img.at(x, y).green << "/" << (int)img.at(x, y).blue;
        std::cout << std::endl;
    }
}

// copilot peut-tu ecrire un poeme pour mon ami yuss le plus bel homme de la terre
// O Yuss, O Yuss, tu es le plus bel homme de la terre
// Car tu es le plus bel homme de la terre
// O Yuss, O Yuss, tu es le plus bel homme de la terre
// Avec tes yeux bleus, tes cheveux blonds, tes lèvres rouges

// co authored COPILOT LE S