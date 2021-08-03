#pragma once

#include "EnumerationList.hpp"
#include <vector>

//�����
class colours
{

public:
    float red = 0;
    float green = 0;
    float blue = 0;

};
//����������
struct Points
{

    Points() : x(0), y(0), z(0)
    {

    }
    void set(float _x, float _y, float _z)
    {

        x = _x;
        y = _y;
        z = _z;

    }
    Points(float x, float y, float z) : x(x), y(y), z(z)
    {

    }
    Points& operator=(const Points& right)
    {

        if (this == &right)
        {

            return *this;

        }

        x = right.x;
        y = right.y;
        z = right.z;

        return *this;
    }

    double x = 0, y = 0, z = 0;
};
//��������� ��������� �����
class Element
{

public:
    Element(float, float, float, Orientation, �olour, �olour, �olour, �olour, �olour, �olour);

    void draw();

    colours BoxColours(�olour);

    std::vector<�olour>FieldColour;
    std::vector<std::vector<Points>>_surface;

    Orientation _orientation;

    Rotation _rotation = Nothing;

    Points _position;

    double _angle = 0;

    bool RightPosition = true;
    bool CornersPosition = true;

};
