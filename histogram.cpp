#include <iostream>
#include <fstream>
#include <algorithm>
#include "Image2D.hpp"
#include "Image2Dreader.hpp"
#include "Image2Dwriter.hpp"
#include "accessor.hpp"

using namespace std;

int main(int argc, char **argv)
{
    typedef Image2D<Color> ColorImage2D;
    typedef Image2D<unsigned char> GrayLevelImage2D;
    typedef Image2DWriter<Color> ColorImage2DWriter;
    typedef Image2DWriter<unsigned char> GrayLevelImage2DWriter;
    typedef ColorImage2D::Iterator ColorIterator;
    if (argc < 2)
    {
        std::cerr << "Usage: save-barre <input.ppm>" << std::endl;
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

    Histogram h;
    h.init(img.begin<ColorValueAccessor>(), img.end<ColorValueAccessor>());
    auto copy = std::vector<double>(h._histo);
    std::sort(copy.begin(), copy.end());
    double max = *(copy.end() - 1);
    GrayLevelImage2D shownHisto(512, 256, 255);
    for (int j = 0; j < 256; ++j)
    {
        for (int i = 0; i < 256; ++i)
        {
            if (h._histo[i] * 256 / max >= 256 - j)
            {
                shownHisto.at(i, j) = 0;
            }
        }
    }
    max = *(h._cumhisto.end() - 1);
    for (int j = 0; j < 256; ++j)
    {
        for (int i = 0; i < 256; ++i)
        {
            if (h._cumhisto[i] * 256 / max >= 256 - j)
            {
                shownHisto.at(i + 256, j) = 0;
            }
        }
    }
    ofstream output("image_histogram.pgm");
    bool ok2 = ColorImage2DWriter::write(img, output, false);
    if (!ok2)
    {
        std::cerr << "Error writing output file." << std::endl;
        return 1;
    }
    output.close();
    return 0;
}