#include <cmath>
#include <iostream>
#include <fstream>
#include "Image2D.hpp"
#include "Image2Dreader.hpp"
#include "Image2Dwriter.hpp"
#include "accessor.hpp"

using namespace std;

int main(int argc, char **argv)
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2DReader<Color> ColorImage2DReader;
    typedef ColorImage2D::Iterator ColorIterator;
    if (argc < 2)
    {
        std::cerr << "Usage: save-channel <input.ppm>" << std::endl;
        return 0;
    }

    ColorImage2D img;
    std::ifstream input(argv[1]); // récupère le 1er argument.
    bool ok = ColorImage2DReader::reader(input, img, false);
    if (!ok)
    {
        std::cerr << "Error reading input file." << std::endl;
        return 1;
    }
    input.close();
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef GrayLevelImage2D::Iterator GrayLevelIterator;

    GrayLevelImage2D img2(img.w(), img.h());

    typedef ColorImage2D::GenericConstIterator<ColorGreenAccessor> ColorGreenConstIterator;
    ColorGreenConstIterator itGreen = img.begin<ColorGreenAccessor>();

    for (GrayLevelIterator it = img2.begin(), itE = img2.end();
         it != itE; ++it)
    {
        *it = *itGreen;
        ++itGreen;
    }

    ofstream output("inputGreen.ppm"); // récupère le 2eme argument.
    bool ok2 = GrayLevelImage2DWriter::write(img2, output, false);
    if (!ok2)
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();

    //---------------------------
    GrayLevelImage2D img3(img.w(), img.h());

    typedef ColorImage2D::GenericConstIterator<ColorBlueAccessor> ColorBlueConstIterator;
    ColorBlueConstIterator itBlue = img.begin<ColorBlueAccessor>();

    for (GrayLevelIterator it = img3.begin(), itE = img3.end();
         it != itE; ++it)
    {
        *it = *itBlue;
        ++itBlue;
    }

    ofstream outputblue("inputBlue.ppm"); // récupère le 2eme argument.
    bool ok3 = GrayLevelImage2DWriter::write(img3, outputblue, false);
    if (!ok3)
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    outputblue.close();

    //---------------------------
    GrayLevelImage2D img4(img.w(), img.h());

    typedef ColorImage2D::GenericConstIterator<ColorRedAccessor> ColorRedConstIterator;
    ColorRedConstIterator itRed = img.begin<ColorRedAccessor>();

    for (GrayLevelIterator it = img4.begin(), itE = img4.end();
         it != itE; ++it)
    {
        *it = *itRed;
        ++itRed;
    }

    ofstream outputred("inputRed.ppm"); // récupère le 2eme argument.
    bool ok4 = GrayLevelImage2DWriter::write(img4, outputred, false);
    if (!ok4)
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    outputred.close();

    return 0;
}
