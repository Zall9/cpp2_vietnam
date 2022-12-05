#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2Dwriter.hpp"
#include "Image2Dreader.hpp"
#include "accessor.hpp"

int main(int argc, char **argv)
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef Image2DWriter<Color> ColorImage2DWriter;
    typedef ColorImage2D::Iterator ColorIterator;
    if (argc < 2)
    {
        std::cerr << "Usage: save-channels <input.ppm>" << std::endl;
        return 0;
    }
  
    std::ifstream input(argv[1]);

    ColorImage2D img;
    bool ok = ColorImage2DReader::reader(input, img, false);
    if (!ok)
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    typedef ColorImage2D::GenericIterator<ColorRedAccessor> ColorRedIterator;
    typedef ColorImage2D::GenericIterator<ColorGreenAccessor> ColorGreenIterator;
    typedef ColorImage2D::GenericIterator<ColorBlueAccessor> ColorBlueIterator;
    ColorRedIterator itRed = img.begin<ColorRedAccessor>();
    ColorGreenIterator itGreen = img.begin<ColorGreenAccessor>();
    ColorBlueIterator itBlue = img.begin<ColorBlueAccessor>();
    // On écrit la composante verte dans l'image en niveaux de gris.
    int x = 0;
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    for (ColorIterator it = img.begin(), itE = img.end();it != itE; ++it)
    {
        switch (x % 3)
        {
        case 0:
            *itGreen = *itBlue = 0;
            break;
        case 1:
            *itRed = *itBlue = 0;
            break;
        case 2:
            *itRed = *itGreen = 0;
            break;
        }
        ++itRed;
        ++itGreen;
        ++itBlue;
        x = (x + 1) % img.w();
    }
    std::ofstream output("image_barre.ppm");
    bool ok2 = ColorImage2DWriter::write(img, output, false);
     if (!ok2)
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}