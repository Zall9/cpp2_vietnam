#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include "Color.hpp"
#include "Image2D.hpp"
#include "Image2Dwriter.hpp"
#include "Image2Dreader.hpp"
using namespace std;

int testRedToBlue()
{
    typedef Image2D<Color> ColorImage2D;
    typedef ColorImage2D::Iterator Iterator;

    ColorImage2D img(256, 256, Color(255, 255, 0));
    Iterator it = img.begin();
    for (int y = 0; y < 256; ++y)
        for (int x = 0; x < 256; ++x)
        {
            *it++ = Color(y, x, (5 * x + 2 * y) % 256);
        }

    ifstream input("kowloon.ppm");
    bool ok2 = Image2DReader<Color>::reader(input, img, false);
    if (!ok2)
    {
        std::cerr << "Error writing reader file." << std::endl;
        return 1;
    }
    for (auto &c : img)
    {
        c = Color(c.blue,c.green,c.red);
    }

    ofstream output("kowloonInverted.ppm");
    bool ok3 = Image2DWriter<Color>::write(img, output, false);
    output.close();
    return 0;
}

int main()
{
    return testRedToBlue();
}