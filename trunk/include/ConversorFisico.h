#ifndef CONVERSOR_FISICO_H
#define CONVERSOR_FISICO_H
#include <Box2D/Box2D.h>

class ConversorFisico
{
    public:
        ConversorFisico();
        ~ConversorFisico();
        static float getPixelsFromMeters(float meters);
        static float getMetersFromPixels(float pixels);
        
        static b2Vec2 getNormalfromDegrees(float angDegrees);
        static b2Vec2 getNormalfromRadians(float angRads);
        static float getRadiansFromDegrees(float degrees);
        static float getDegreesFromRadians(float radians);
        
};

#endif