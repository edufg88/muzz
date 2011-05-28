#ifndef INTERFAZ_FISICA_H
#define INTERFAZ_FISICA_H
#include "Objeto.h"
#include "DetectorColisiones.h"

// Definición para tipos de objeto
#define ESTATICO 1
#define CINEMATICO 2
#define DINAMICO 3

class InterfazFisica
{
    public:
        static InterfazFisica* getInstancia();
        ~InterfazFisica();
        void actualizar();

        void crearMundo();
        b2Body* crearBox(int tipo, Objeto* obj, float32 ancho, float32 alto, float32 densidad, float32 friccion = 0.0f, bool puedeDormir = false, bool rotacionFija = false);
        b2Body* crearCirculo(int tipo, Objeto* obj, float32 radio, float32 densidad, float32 friccion = 0.0f, bool puedeDormir = false);

        b2World* getMundo() const;

        void setStep(float32 s);
        void setIterVel(int32 iter);
        void setIterPos(int32 iter);

    private:
        static InterfazFisica* instancia;
        InterfazFisica();
        
        b2World* mundo;
        DetectorColisiones* detectorColisiones;
        float32 step;
        int32 iterVel;
        int32 iterPos;

};


#endif