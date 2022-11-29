#include <vector>
#include "Image2D.hpp"

// Public Member Functions

typedef unsigned char GrayLevel; // le type pour les niveaux de gris.

// declare method of class GrayLevelImage2d.hpp

Image2D::Image2D(int w, int h, Value g)
{
    m_width = w;
    m_height = h;
    // resize rempoli automatiquement de 0
    m_data.resize(w * h, g);
};

void Image2D::fill(Value g)
{
    m_data.assign(m_width * m_height, g);
};

int Image2D::w() const
{
    return m_width;
};

int Image2D::h() const
{
    return m_height;
};

TValue Image2D::at(int i, int j) const
{
    return m_data[i + j * m_width];
};

TValue &Image2D::at(int i, int j)
{
    return m_data[i + j * m_width];
};
