#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2Dwriter.hpp"
#include "Image2Dreader.hpp"
#include "accessor.hpp"

using namespace std;


int main(int argc, char **argv)
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<Color> ColorImage2DWriter;
    typedef Image2DReader<Color> ColorImage2DReader;

    typedef ColorImage2D::Iterator ColorIterator;
    typedef Image2D<Color>::GenericIterator<ColorValueAccessor> HUEIterator;

    if (argc < 2)
    {
        std::cerr << "Usage: rotationColor <input.ppm>" << std::endl;
        return 0;
    }

    // lecture d'une image en couleur

    ColorImage2D img;
    std::ifstream input(argv[1]); // récupère le 1er argument.
    bool ok = ColorImage2DReader::reader(input, img, false);
    if (!ok)
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();


    for (ColorIterator it = img.begin(), itE = img.end(); it != itE; ++it)
    {
        Color c = *it;
        c.red = (c.red+60)%360;
        c.green = (c.green+60)%360;
        c.blue = (c.blue+60)%360;
        *it = c;
    }


    ofstream output("image_rotated.ppm");
    ColorImage2DWriter::write(img, output, false);
    output.close();
    return 0;
}