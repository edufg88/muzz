#ifndef NIVEL_H
#define NIVEL_H

#include <map>
#include <vector>
#include "Enemigo.h"
using namespace std;

// Tipos de nivel
#define RECOGIDA_ESTRELLAS 1
#define DESTRUIR_ENEMIGOS 2
#define SUPERVIVENCIA 3
#define CONSEGUIR_PUNTOS 4

class Nivel
{
    public:
        Nivel(int tipo);
        Nivel(int tipo, wstring rutaFondo);
        ~Nivel();
        void pintar();
        void actualizar();
        void ejecutarBeat(int tipo);
        Objeto* getObjeto(string key);
        void setObjeto(string key, Objeto* objeto);
        Enemigo* getEnemigo(string key);
        void setEnemigo(string key, Enemigo* enemigo);
        void setFondo();
        void setFondo(wstring rutaFondo);
        int getAncho() const;
        int getAlto() const;
        void setAncho (int a);
        void setAlto (int a);
        int getTipo() const;
        void setFinalizado();
        // Funciones de creación de objetos de nivel
        Objeto* crearBloque(string nombre, float32 posX, float32 posY);
        Objeto* crearBloqueAux(string nombre, float32 posX, float32 posY); // Temporal
        Objeto* crearRoca(string nombre, float32 posX, float32 posY);
        void crearSuelo();

        int nObjs;

    private:
        bool finalizado;
        int tipo;
        int xFondo, yFondo;
        boost::scoped_ptr<Gosu::Image> fondo;
        b2Body* suelo;
        map<string, Objeto*> objetos;
        map<string, Enemigo*> enemigos;
        int ancho;
        int alto;

        vector<Animacion*> pums;
        void initPums();

        void actualizarObjetos();
        void actualizarEnemigos();
        void actualizarEstado();
        void actualizarLanzamientos();

        void generarPico();
        void generarRoca();
        long timerPico;
        long timerRoca;
};

#endif