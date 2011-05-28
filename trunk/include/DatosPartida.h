#ifndef DATOS_PARTIDA_H
#define DATOS_PARTIDA_H

#include <iostream>
using namespace std;

class DatosPartida
{
public:
    static DatosPartida* getInstancia();
    ~DatosPartida();

    void setVida (int v);
    void setEscudo (int e);
    void setPuntos (int p);
    void setEstadoAnimo (int ea);
    int getVida () const;
    int getEscudo () const;
    int getPuntos () const;
    int getEstadoAnimo() const;

private:
    DatosPartida();
    static DatosPartida* instancia;
    int vidaPersonaje;
    int escudoPersonaje;
    int puntos;
    int estadoAnimo;

};

#endif