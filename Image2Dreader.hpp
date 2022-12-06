#ifndef _IMAGE2DREADER_HPP_
#define _IMAGE2DREADER_HPP_

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include "Color.hpp"
#include "Image2D.hpp"
using namespace std;
template <typename TValue>
class Image2DReader
{
public:
    typedef TValue Value;
    typedef Image2D<Value> Image;

    static bool reader(Image &img, std::ostream &output, bool ascii)
    {
        std::cerr << "[Image2DReader<TValue>::write] NOT IMPLEMENTED." << std::endl;
        return false;
    }
};

/// Specialization for gray-level images.
template <>
class Image2DReader<unsigned char>
{
public:
    typedef unsigned char Value;
    typedef Image2D<Value> Image;

    static string readline(std::istream &input)
    {
        string str;
        do
        {
            getline(input, str);
        } while (str != "" && str[0] == '#');
        return str;
    }
    static bool reader(std::istream &input, Image &img, bool ascii)
    {
        // read header from PGM file
        if (!input.good())
            return false;
        std::string format = readline(input);

        std::string line = readline(input);
        std::string delim = " ";
        int m_width;
        int m_height;
        m_width = std::stoi(line.substr(0, line.find(delim)));
        line.erase(0, line.find(delim) + delim.length());
        m_height = std::stoi(line);
        std::cout << m_width << " " << m_height << " " << format << std::endl;
        // read the line and put it in cout
        std::cout << readline(input) << std::endl;
        //  new image
        img = Image(m_width, m_height, 0);
        // img.fill(0);
        if (format == "P5")
        {
            input >> std::noskipws;
            unsigned char v;
            for (Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it)
            {
                input >> v;
                *it = v;
            }
        }
        else
        {
            input >> std::skipws;
            int v;
            for (Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it)
            {
                input >> v;
                *it = v;
            }
        }
        return true;
    }
};
/// Specialization for color images.

template <>
class Image2DReader<Color>
{
public:
    typedef Color Value;
    typedef Image2D<Value> Image;

    static string readline(std::istream &input)
    {
        string str;
        do
        {
            getline(input, str);
        } while (str != "" && str[0] == '#');
        return str;
    }
    static bool reader(std::istream &input, Image &img, bool ascii)
    {
        // import image
        if (!input.good())
            return false;
        std::string format = readline(input);

        std::string line = readline(input);
        std::string delim = " ";
        int m_width;
        int m_height;
        m_width = std::stoi(line.substr(0, line.find(delim)));
        line.erase(0, line.find(delim) + delim.length());
        m_height = std::stoi(line);
        std::cout << m_width << " " << m_height << " " << format << std::endl;
        // read the line and put it in cout
        std::cout << readline(input) << std::endl;

        // new image
        //img = Image(m_width, m_height, Color(0, 0, 0));
        img = Image(m_width, m_height, Color());

        // img.fill(0);
        if (format == "P6")
        {
            input >> std::noskipws;
            Color v;
            for (Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it)
            {
                input >> v.red >> v.green >> v.blue;
                *it = v;
            }
        }
        else
        {   
            input >> std::skipws;
            int r, g, b;
            for (Image::Iterator it = img.begin(), itE = img.end(); it != itE; ++it)
            {

                input >> r >> g >> b;
                *it = Color(r, g, b);
            }
        }
        return true;
    }
};

#endif // _IMAGE2DREADER_HPP_