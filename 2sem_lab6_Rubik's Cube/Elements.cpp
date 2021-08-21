#pragma once
#include <glut.h>
#include "Elements.hpp"
#include <cmath>

//Цвета составных кубов
colours Element::BoxColours(Сolour It_is_colour)
{
    colours colour;

    switch (It_is_colour)
    {
        case White:
        {
            colour.red = 1;
            colour.green = 1;
            colour.blue = 1;
            return colour;
        }
        case Yellow:
        {
            colour.red = 1;
            colour.green = 0.9;
            colour.blue = 0;
            return colour;
        }
        case Green:
        {
            colour.red = 0.2;
            colour.green = 0.7;
            colour.blue = 0;
            return colour;
        }
        case Red:
        {
            colour.red = 0.9;
            colour.green = 0.1;
            colour.blue = 0.1;
            return colour;
        }
        case Blue:
        {
            colour.red = 0.2;
            colour.green = 0;
            colour.blue = 0.7;
            return colour;
        }
        case Orange:
        {
            colour.red = 1;
            colour.green = 0.6;
            colour.blue = 0;
            return colour;
        }
        default:
        {
            colour.red = 0.0;
            colour.green = 0.0;
            colour.blue = 0.0;
            return colour;
        }
    }
}

//Размеры и структура составных кубов
Element::Element(float position_x, float position_y, float position_z, Orientation orientation, Сolour colour1, Сolour colour2, Сolour colour3, Сolour colour4, Сolour colour5, Сolour colour6)
{
    _orientation = orientation;
    Points position(position_x, position_y, position_z);
    _position = position;
    _surface.resize(6);

    Points miniCube(0.5, -0.5, -0.5);
    _surface[0].push_back(miniCube);
    miniCube.set(0.5, 0.5, -0.5);
    _surface[0].push_back(miniCube);
    miniCube.set(-0.5, 0.5, -0.5);
    _surface[0].push_back(miniCube);
    miniCube.set(-0.5, -0.5, -0.5);
    _surface[0].push_back(miniCube);

    miniCube.set(0.5, 0.5, 0.5);
    _surface[1].push_back(miniCube);
    miniCube.set(0.5, 0.5, -0.5);
    _surface[1].push_back(miniCube);
    miniCube.set(-0.5, 0.5, -0.5);
    _surface[1].push_back(miniCube);
    miniCube.set(-0.5, 0.5, 0.5);
    _surface[1].push_back(miniCube);

    miniCube.set(-0.5, -0.5, 0.5);
    _surface[2].push_back(miniCube);
    miniCube.set(-0.5, 0.5, 0.5);
    _surface[2].push_back(miniCube);
    miniCube.set(-0.5, 0.5, -0.5);
    _surface[2].push_back(miniCube);
    miniCube.set(-0.5, -0.5, -0.5);
    _surface[2].push_back(miniCube);

    miniCube.set(0.5, -0.5, -0.5);
    _surface[3].push_back(miniCube);
    miniCube.set(0.5, 0.5, -0.5);
    _surface[3].push_back(miniCube);
    miniCube.set(0.5, 0.5, 0.5);
    _surface[3].push_back(miniCube);
    miniCube.set(0.5, -0.5, 0.5);
    _surface[3].push_back(miniCube);

    miniCube.set(0.5, -0.5, -0.5);
    _surface[4].push_back(miniCube);
    miniCube.set(0.5, -0.5, 0.5);
    _surface[4].push_back(miniCube);
    miniCube.set(-0.5, -0.5, 0.5);
    _surface[4].push_back(miniCube);
    miniCube.set(-0.5, -0.5, -0.5);
    _surface[4].push_back(miniCube);

    miniCube.set(0.5, -0.5, 0.5);
    _surface[5].push_back(miniCube);
    miniCube.set(0.5, 0.5, 0.5);
    _surface[5].push_back(miniCube);
    miniCube.set(-0.5, 0.5, 0.5);
    _surface[5].push_back(miniCube);
    miniCube.set(-0.5, -0.5, 0.5);
    _surface[5].push_back(miniCube);

    FieldColour.push_back(colour1);
    FieldColour.push_back(colour2);
    FieldColour.push_back(colour3);
    FieldColour.push_back(colour4);
    FieldColour.push_back(colour5);
    FieldColour.push_back(colour6);
}

//Прорисовка и анимация проворотов
void Element::draw()
{

    colours colour;
    double x = 0, y = 0, z = 0;

    for (int i = 0; i < _surface.size(); i++)
    {

        colour = BoxColours(FieldColour[i]);
        glBegin(GL_POLYGON);

        for (auto& j : _surface[i])
        {

            glColor3f(colour.red, colour.green, colour.blue);
            switch (_rotation)
            {

                case Nothing:
                {

                    x = j.x;
                    y = j.y;
                    z = j.z;
                    break;

                }
                case CenterUpAndDownRotation:
                {

                    x = j.x;
                    y = (j.y) * cos(_angle) - (j.z) * sin(_angle);
                    z = (j.z) * cos(_angle) + (j.y) * sin(_angle);
                    break;

                }
                case CenterLeftAndRightRotation:
                {

                    x = (j.x) * cos(_angle) - (j.z) * sin(_angle);
                    y = j.y;
                    z = (j.z) * cos(_angle) + (j.x) * sin(_angle);
                    break;

                }
                case ClockwiseRotation:
                {

                    x = (j.x) * cos(_angle) - (j.y) * sin(_angle);
                    y = (j.y) * cos(_angle) + (j.x) * sin(_angle);
                    z = j.z;
                    break;

                }
                default:
                {

                    x = j.x;
                    y = j.y;
                    z = j.z;
                    break;

                }

            }

            glVertex3f(x + _position.x, y + _position.y, z + _position.z);

            j.x = x;
            j.y = y;
            j.z = z;
        }

        glEnd();

    }

}
