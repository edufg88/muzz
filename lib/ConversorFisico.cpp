#include "ConversorFisico.h"
#include <iostream>
#include <math.h>
using namespace std;

ConversorFisico::ConversorFisico()
{

}

ConversorFisico::~ConversorFisico()
{

}

float ConversorFisico::getPixelsFromMeters(float meters)
{
    return meters*20;
}

float ConversorFisico::getMetersFromPixels(float pixels)
{
    return (pixels*5)/100;
}

b2Vec2 ConversorFisico::getNormalfromDegrees(float angDegrees)
{
    return getNormalfromRadians(getRadiansFromDegrees(angDegrees));
}

b2Vec2 ConversorFisico::getNormalfromRadians(float angRads)
{
    b2Vec2 v;
    float x = cos(angRads);
    float y = sin(angRads);
    v.Set(x, y);

    return v;
}

float ConversorFisico::getRadiansFromDegrees(float degrees)
{
    return degrees*0.0174532;
}

float ConversorFisico::getDegreesFromRadians(float radians)
{
    return radians*57.295791;
}