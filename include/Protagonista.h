#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include "ObjetoMovil.h"
#include "Animacion.h"
#include "Objetos/Bala.h"
#include <vector>

// Estados del protagonista
#define PARADO 0
#define MOVIMIENTO 1
#define SALTANDO 2
#define DISPARANDO_PARADO 3
#define DISPARANDO_MOVIMIENTO 4
#define DISPARANDO_SALTANDO 5
#define HERIDO 6
// Direcciones
#define IZQUIERDA 1
#define DERECHA 2

class Protagonista : public ObjetoMovil
{
    public:
        Protagonista(string nombre, float32 x, float32 y);
        ~Protagonista();

        void pintar() const;
        virtual void actualizar();

        // Movimientos del protagonista
        void moverIzquierda();
        void moverDerecha();
        void saltar();
        void disparar(bool especial);
        void parar();
        void pararDisparar();
        void chocar(int dir);
        void recuperar();

        Animacion* getAnimacionMI() const;
        Animacion* getAnimacionMD() const;
        Animacion* getAnimacionParado() const;

        bool getPuedeSaltar() const;
        void setPuedeSaltar(bool puede);
        int getDireccion() const;
        void sufrirDanyo(int danyo);

        void setContraParedDer(bool flag) {contraParedDer = flag;}
        void setContraParedIzq(bool flag) {contraParedIzq = flag;}
        void setContraParedAbajo(bool flag) {contraParedAbajo = flag;}
        void setContraParedArriba(bool flag) {contraParedArriba = flag;}
        bool esContraParedDer() {return contraParedDer;}
        bool esContraParedIzq() {return contraParedIzq;}
        bool esContraParedAbajo() {return contraParedAbajo;}
        bool esContraParedArriba() {return contraParedArriba;}
        void reiniciarContactos();
        
    private:
        vector<Bala*> disparos;
        Animacion* animacionMI;
        Animacion* animacionMD;
        Animacion* animacionSaltarI;
        Animacion* animacionSaltarD;
        Animacion* animacionDispararI;
        Animacion* animacionDispararD;
        Animacion* animacionDispSaltI;
        Animacion* animacionDispSaltD;
        Animacion* animacionParado;
        Animacion* animacionChoqueD;
        Animacion* animacionChoqueI;

        void inicializarAnimaciones();
        void actualizarEstado();
        void actualizarDisparos();
        void actualizarVida();
        void pintarDisparos() const;

        int estado;
        int direccion;
        bool puedeSaltar; // Controla si el personaje se encuentra en el suelo y puede saltar
        // Para evitar que se quede bloqueado en los saltos
        int timerSalto;

        // Flags que controla las colisiones del protagonista
        bool contraParedDer;
        bool contraParedIzq;
        bool contraParedAbajo;
        bool contraParedArriba;

        static long potenciaSalto;
        static int potenciaChoque;
};

#endif