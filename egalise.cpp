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
        std::cerr << "Usage: egalise <input.ppm>" << std::endl;
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

    Histogram h;
    h.init(img.begin<ColorValueAccessor>(), img.end<ColorValueAccessor>());

    for (HUEIterator it = img.begin<ColorValueAccessor>(), itE = img.end<ColorValueAccessor>(); it != itE; it++)
    {
        *it = h.egalisation(*it);
    }

    ofstream output("image_egalised.ppm");
    ColorImage2DWriter::write(img, output, false);
    output.close();
    return 0;
}