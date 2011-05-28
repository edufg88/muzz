#ifndef DATOS_CANCION_H
#define DATOS_CANCION_H
#include <iostream>
using namespace std;

// Géneros musicales
#define BLUES 1
#define ROCK 2
#define DANCE 3
#define DISCO 4
#define FUNK 5
#define RAP 6
#define JAZZ 7
#define POP 8
#define R_AND_B 9
#define REGGAE 10
#define TECHNO 11
#define SKA 12
#define HOUSE 13
#define CLASSICAL 14
#define SOUL 15
#define PUNK 16
#define LATIN 17
#define METAL 18
#define CHILL_OUT 19


class DatosCancion
{
    public:
        DatosCancion();
        ~DatosCancion();

        // Obtiene los datos a partir de la canción cargada por el interfaz
        void obtenerDatos();
        string getTitulo() const;
        string getArtista() const;
        string getAlbum() const;
        int getGenero() const;
        string getFecha() const;
        string getComentarios() const;
        unsigned int getDuracion();
        float getFrecuencia() const;
        float getVolumen();
        float getPan();

        void setVolumen(float pVol);
        void setPan(float pPan);
        void setGenero(int gen);
        string getStringGenero(int gen);

    private:
        string titulo;
        string artista;
        string album;
        int genero;
        string fecha;
        string comentarios;

        unsigned int duracion;
        float frecuencia;
        float volumen;
        float pan;
        int prioridad;

        int clasificarGenero(int gen);
};

#endif