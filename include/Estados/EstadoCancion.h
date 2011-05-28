#ifndef ESTADO_CANCION_H
#define ESTADO_CANCION_H

#include "EstadoJuego.h"
#include "GUIAux.h"

class EstadoCancion : public EstadoJuego
{
    public:
        EstadoCancion();
        ~EstadoCancion();

        void entrar();
        void actualizar();
        void pintar();
        void salir();

        void buttonDown(Gosu::Button btn);
        void buttonUp(Gosu::Button btn);

        void leerInput();

        void ejecutarBeat(int tipo);

    private:
        int cargando;
        // Fondo del menú
        boost::scoped_ptr<Gosu::Image> fondo;
        /**
         * Elementos GUI
         */
        Texto* tRuta, *tDatos, *tTitulo, *tArtista, *tAlbum, *tAnyo, *tGenero, *tEstadoAnimo;
        CampoTexto* ctRuta, *ctTitulo, *ctArtista, *ctAlbum, *ctAnyo, *ctGenero, *ctEstadoAnimo;
        Boton* bFijarRuta,*bGenero, *bJugar, *bMas, *bMenos;
        Panel* pGrad, *pPivote;
        Panel* pCargando;

        Texto* tPorcentaje;

        // Abre el dialogo de examinar ficheros y devuelve la ruta absoluta de la canción elegida
        void leerCancion();
        void cargarGeneros();
        void inicializarGUI();
        void pintarGUI();

        int estadoDeAnimo;
        bool hayCancion;
};

#endif