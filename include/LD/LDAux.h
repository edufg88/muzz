#ifndef LD_AUX_H
#define	LD_AUX_H

#include <math.h>
#include <iostream>
#include <limits>
using namespace std;

// Definimos algunas constantes de interés
const int MaxInt = (std::numeric_limits<int>::max)();
const double  MaxDouble = (std::numeric_limits<double>::max)();
const double  MinDouble = (std::numeric_limits<double>::min)();
const float   MaxFloat  = (std::numeric_limits<float>::max)();
const float   MinFloat  = (std::numeric_limits<float>::min)();

// Devuelve el menor de 2 valores
template <class T>
inline T minimum(const T& a, const T& b)
{
	if (a < b)
		return a;
	else
		return b;
}

// Devuelve el mayor de 2 valores
template <class T>
inline T maximum(const T& a, const T& b)
{
	if (a > b)
		return a;
	else
		return b;
}

// Compara 2 números reales y devuelve si son iguales
inline bool isEqual(float a, float b)
{
	if (fabs(a-b) < 1E-12)
	{
		return true;
	}
	else
		return false;
}

inline bool isEqual(double a, double b)
{
	if (fabs(a-b) < 1E-12)
	{
		return true;
	}
	else
		return false;
}

#endif
