#include "DatosCancion.h"
#include "InterfazAudio.h"
#include <string.h>
#include <boost/lexical_cast.hpp>

DatosCancion::DatosCancion()
{

}

DatosCancion::~DatosCancion()
{

}

void DatosCancion::obtenerDatos()
{
    InterfazAudio* ia = InterfazAudio::getInstancia();
    
    // Obtenemos informacion de la canción
    ////////////////////////////////////////
    ia->getSound()->getLength(&duracion, FMOD_TIMEUNIT_MS);
    ia->getSound()->getDefaults(&frecuencia, &volumen, &pan, &prioridad);
    ia->getChannel()->getVolume(&volumen);
    ia->getChannel()->getPan(&pan);
   
    // Obtenemos información de los TAGS
    ////////////////////////////////////////
    char name[256];
    int numTags, numTagsUpdated;
    FMOD_TAG tag;

    ia->getSound()->getName(name, 256);
    ia->getSound()->getNumTags(&numTags, &numTagsUpdated);
    
    for (int i = 0; i < numTags; i++)
    {
        ia->getSound()->getTag(NULL, i, &tag);

        if (tag.datatype == FMOD_TAGDATATYPE_STRING)
        {
            if (strcmp(tag.name, "TITLE") == 0)
            {
                titulo = static_cast<char*>(tag.data);
            }
            else if (strcmp(tag.name, "ARTIST") == 0)
            {
                artista = static_cast<char*>(tag.data);
            }
            else if (strcmp(tag.name, "ALBUM") == 0)
            {
                album = static_cast<char*>(tag.data);
            }
            else if (strcmp(tag.name, "YEAR") == 0)
            {
                fecha = static_cast<char*>(tag.data);
            }
            else if (strcmp(tag.name, "COMMENT") == 0)
            {
                comentarios = static_cast<char*>(tag.data);
            }
            else if (strcmp(tag.name, "GENRE") == 0)
            {
                // Clasificamos el género dentro de nuestra lista particular
                string s = static_cast<char*>(tag.data);
                int gen = boost::lexical_cast<int>(s);
                genero = clasificarGenero(gen);
            }
        }
    }

    cout << "Freq: " << this->frecuencia << endl;
}

string DatosCancion::getTitulo() const
{
    return titulo;
}

string DatosCancion::getArtista() const
{
    return artista;
}

string DatosCancion::getAlbum() const
{
    return album;
}

int DatosCancion::getGenero() const
{
    return genero;
}

string DatosCancion::getFecha() const
{
    return fecha;
}

string DatosCancion::getComentarios() const
{
    return comentarios;
}

unsigned int DatosCancion::getDuracion()
{
    if (InterfazAudio::getInstancia()->getSound() != NULL)
    {
        InterfazAudio::getInstancia()->getSound()->getLength(&duracion, FMOD_TIMEUNIT_MS);
    }
    return duracion;
}

float DatosCancion::getFrecuencia() const
{
    return frecuencia;
}

float DatosCancion::getVolumen() 
{
    InterfazAudio::getInstancia()->getChannel()->getVolume(&volumen);
    return volumen;
}

float DatosCancion::getPan() 
{
    InterfazAudio::getInstancia()->getChannel()->getPan(&pan);
    return pan;
}

void DatosCancion::setVolumen(float pVol)
{
    if (pVol >= 0 && pVol <= 1.0)
    {
        InterfazAudio::getInstancia()->getChannel()->setVolume(pVol);
        volumen = pVol;
    }
}

void DatosCancion::setPan(float pPan)
{
    if (pPan >= -1.0 && pPan <= 1.0)
    {
        InterfazAudio::getInstancia()->getChannel()->setPan(pPan);
        pan = pPan;
    }

    cout << "pan: " << pan << endl;
}

void DatosCancion::setGenero(int gen)
{
    genero = gen;
}

string DatosCancion::getStringGenero(int gen)
{
    switch(gen)
    {
        case 1:
            return "blues";
        case 2:
            return "rock";
        case 3:
            return "dance";
        case 4:
            return "disco";
        case 5:
            return "funk";
        case 6:
            return "rap";
        case 7:
            return "jazz";
        case 8:
            return "pop";
        case 9:
            return "r and b";
        case 10:
            return "reggae";
        case 11:
            return "techno";
        case 12:
            return "ska";
        case 13:
            return "house";
        case 14:
            return "classical";
        case 15:
            return "soul";
        case 16:
            return "punk";
        case 17:
            return "latin";
        case 18:
            return "metal";
        case 19:
            return "chill out";
        default:
            return "";
    }
}

int DatosCancion::clasificarGenero(int gen)
{
    switch (gen)
    {
        case 0:
            return 1;
            break;
        case 1:
            return 2;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 3;
            break;
        case 4:
            return 4;
            break;
        case 5:
            return 5;
            break;
        case 6:
            return 16;
            break;
        case 7:
            return 6;
            break;
        case 8:
            return 7;
            break;
        case 9:
            return 18;
            break;
        case 10:
            return 8;
            break;
        case 11:
            return 2;
            break;
        case 12:
            return 8;
            break;
        case 13:
            return 8;
            break;
        case 14:
            return 9;
            break;
        case 15:
            return 6;
            break;
        case 16:
            return 10;
            break;
        case 17:
            return 2;
            break;
        case 18:
            return 11;
            break;
        case 19:
            return 11;
            break;
        case 20:
            return 11;
            break;
        case 21:
            return 12;
            break;
        case 22:
            return 18;
            break;
        case 23:
            return 18;
            break;
        case 24:
            return 8;
            break;
        case 25:
            return 11;
            break;
        case 26:
            return 19;
            break;
        case 27:
            return 13;
            break;
        case 28:
            return 8;
            break;
        case 29:
            return 7;
            break;
        case 30:
            return 7;
            break;
        case 31:
            return 11;
            break;
        case 32:
            return 14;
            break;
        case 33:
            return 14;
            break;
        case 34:
            return 11;
            break;
        case 35:
            return 13;
            break;
        case 36:
            return 8;
            break;
        case 37:
            return 8;
            break;
        case 38:
            return 7;
            break;
        case 39:
            return 11;
            break;
        case 40:
            return 2;
            break;
        case 41:
            return 17;
            break;
        case 42:
            return 15;
            break;
        case 43:
            return 16;
            break;
        case 44:
            return 19;
            break;
        case 45:
            return 19;
            break;
        case 46:
            return 8;
            break;
        case 47:
            return 2;
            break;
        case 48:
            return 2;
            break;
        case 49:
            return 16;
            break;
        case 50:
            return 16;
            break;
        case 51:
            return 11;
            break;
        case 52:
            return 11;
            break;
        case 53:
            return 8;
            break;
        case 54:
            return 3;
            break;
        case 55:
            return 3;
            break;
        case 56:
            return 2;
            break;
        case 57:
            return 8;
            break;
        case 58:
            return 17;
            break;
        case 59:
            return 6;
            break;
        case 60:
            return 8;
            break;
        case 61:
            return 6;
            break;
        case 62:
            return 5;
            break;
        case 63:
            return 8;
            break;
        case 64:
            return 15;
            break;
        case 65:
            return 8;
            break;
        case 66:
            return 8;
            break;
        case 67:
            return 13;
            break;
        case 68:
            return 13;
            break;
        case 69:
            return 8;
            break;
        case 70:
            return 8;
            break;
        case 71:
            return 8;
            break;
        case 72:
            return 7;
            break;
        case 73:
            return 5;
            break;
        case 74:
            return 7;
            break;
        case 75:
            return 2;
            break;
        case 76:
            return 8;
            break;
        case 77:
            return 19;
            break;
        case 78:
            return 2;
            break;
        case 79:
            return 2;
            break;
        case 80:
            return 2;
            break;
        case 81:
            return 2;
            break;
        case 82:
            return 2;
            break;
        case 83:
            return 7;
            break;
        case 84:
            return 7;
            break;
        case 85:
            return 7;
            break;
        case 86:
            return 17;
            break;
        case 87:
            return 13;
            break;
        case 88:
            return 19;
            break;
        case 89:
            return 19;
            break;
        case 90:
            return 19;
            break;
        case 91:
            return 2;
            break;
        case 92:
            return 2;
            break;
        case 93:
            return 2;
            break;
        case 94:
            return 2;
            break;
        case 95:
            return 2;
            break;
        case 96:
            return 2;
            break;
        case 97:
            return 14;
            break;
        case 98:
            return 14;
            break;
        case 99:
            return 19;
            break;
        case 100:
            return 14;
            break;
        case 101:
            return 14;
            break;
        case 102:
            return 14;
            break;
        case 103:
            return 14;
            break;
        case 104:
            return 14;
            break;
        case 105:
            return 14;
            break;
        case 106:
            return 14;
            break;
        case 107:
            return 4;
            break;
        case 108:
            return 14;
            break;
        case 109:
            return 8;
            break;
        case 110:
            return 8;
            break;
        case 111:
            return 8;
            break;
        case 112:
            return 13;
            break;
        case 113:
            return 17;
            break;
        case 114:
            return 17;
            break;
        case 115:
            return 2;
            break;
        case 116:
            return 8;
            break;
        case 117:
            return 8;
            break;
        case 118:
            return 15;
            break;
        case 119:
            return 6;
            break;
        case 120:
            return 8;
            break;
        case 121:
            return 16;
            break;
        case 122:
            return 19;
            break;
        case 123:
            return 19;
            break;
        case 124:
            return 13;
            break;
        case 125:
            return 3;
            break;
        case 126:
            return 13;
            break;
        case 127:
            return 13;
            break;
        case 128:
            return 13;
            break;
        case 129:
            return 11;
            break;
        case 130:
            return 11;
            break;
        case 131:
            return 8;
            break;
        case 132:
            return 8;
            break;
        case 133:
            return 16;
            break;
        case 134:
            return 16;
            break;
        case 135:
            return 6;
            break;
        case 136:
            return 6;
            break;
        case 137:
            return 18;
            break;
        case 138:
            return 18;
            break;
        case 139:
            return 2;
            break;
        case 140:
            return 2;
            break;
        case 141:
            return 2;
            break;
        case 142:
            return 17;
            break;
        case 143:
            return 17;
            break;
        case 144:
            return 18;
            break;
        case 145:
            return 8;
            break;
        case 146:
            return 8;
            break;
        case 147:
            return 8;
            break;
        case 148:
            return 8;
            break;
        default:
            return 8;
            break;
    }

    return 8;
}