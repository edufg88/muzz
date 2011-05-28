#include "GeneradorNiveles.h"
// Objetos
#include "Objetos/Suelo.h"
#include "Objetos/Roca.h"
#include "Objetos/Pinchos.h"
#include "Objetos/Plataforma.h"
#include "Objetos/PlataformaMovil.h"
#include "Objetos/Pico.h"
#include "Objetos/BloqueSimetrico.h"
#include "Objetos/Estrella.h"
#include "Objetos/Silencio.h"
#include "Objetos/Meta.h"
// Enemigos
#include "Enemigos/Bola.h"
#include "Enemigos/Cuadrado.h"
#include "Enemigos/Gusano.h"
#include "Enemigos/Rueda.h"
#include "Enemigos/Triangulo.h"
#include "Enemigos/Jefe.h"

GeneradorNiveles* GeneradorNiveles::instancia = NULL;

GeneradorNiveles* GeneradorNiveles::getInstancia()
{
    if (instancia == NULL)
    {
        instancia = new GeneradorNiveles();
    }

    return instancia;
}

GeneradorNiveles::GeneradorNiveles()
{

}

GeneradorNiveles::~GeneradorNiveles()
{

}

Nivel* GeneradorNiveles::generar()
{
    Nivel* nivel = NULL;
    // Primero obtenemos los datos que necesitamos
    int tipo = InterfazIA::getInstancia()->getTipoNivel("modTipoNivel");
    cout << "tipo ES: " << tipo << endl;
    tipo = 1; // TEMPORALLL!!
    // Generamos el nivel
    switch (tipo)
    {
        case RECOGIDA_ESTRELLAS:
            nivel = GenRecogidaEstrellas();
            break;
        case DESTRUIR_ENEMIGOS:
            nivel = GenDestruirEnemigos();
            break;
        case SUPERVIVENCIA:
            nivel = GenSupervivencia();
            break;
        case CONSEGUIR_PUNTOS:
            nivel = GenSupervivencia();
            break;
        default:
            cerr << "ERROR: Generador Niveles Generar: tipo de nivel desconocido " << endl;
    }

    return nivel;
}

void GeneradorNiveles::leerNivel(Nivel* n, int tipo)
{
    // Iteradores para objetos y enemigos;
    int iteradorObjs = 0;
    int iteradorEnems = 0;

    TiXmlDocument document("data/niveles.xml");
    bool ok = document.LoadFile();
    if (ok)
    {
        TiXmlElement* root = document.FirstChildElement( "niveles" );
        if (root)
        {
            TiXmlElement* niveles = root->FirstChildElement( "nivelesTipo" + boost::lexical_cast<string>(tipo) );
            if (niveles)
            {
                int cantidad = atoi(niveles->Attribute( "cantidad" ));
                int numNivel = (Gosu::milliseconds() % cantidad) + 1;

                TiXmlElement* nivel = niveles->FirstChildElement( "nivel" );

                // Así recorremos todos los niveles del tipo hasta elegir uno aleatoriamente
                for (int i = 0; i < numNivel; i++)
                {
                    // Descomentar cuando todo funcione
                    //nivel = niveles->NextSiblingElement( "nivel" );
                }

                if (nivel)
                {
                    // ###########################################################
                    // Obtenemos los datos que necesitemos para crear el nivel
                    // ###########################################################
                    // El tamaño del nivel
                    TiXmlElement* ancho = nivel->FirstChildElement( "ancho" );
                    if (ancho)
                    {
                        int an = atoi(ancho->GetText());
                        n->setAncho(an);
                        cout << "ancho" << an << endl;
                    }

                    TiXmlElement* alto = ancho->NextSiblingElement( "alto" );
                    if (alto)
                    {
                        int al = atoi(alto->GetText());
                        n->setAlto(al);
                        cout << "alto " << al << endl;
                    }

                    // Ahora los objetos primero el suelo
                    TiXmlElement* suelo = alto->NextSiblingElement( "suelo" );
                    if (suelo)
                    {
                        TiXmlElement* bloque = suelo->FirstChildElement( "bloque" );

                        // Tenemos que recorrer todos los bloques
                        while (bloque)
                        {
                            TiXmlElement* atribs = bloque->FirstChildElement( "x" );

                            int x = atoi(atribs->GetText());
                            atribs = atribs->NextSiblingElement( "y" );
                            int y = atoi(atribs->GetText());
                            atribs = atribs->NextSiblingElement( "tam" );
                            int tam = atoi(atribs->GetText());
                            
                            cout << "Bloque ------" << endl;
                            cout << "x: " << x << " y: " << y << " tam: " << tam << endl;
                            cout << "-------------" << endl;

                            // Creamos el objeto y lo añadimos al nivel
                            Suelo* s = new Suelo(tam, "suelo", x, y);
                            n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), s);
                            iteradorObjs++;

                            // Pasamos al siguiente
                            bloque = bloque->NextSiblingElement( "bloque" );
                        }
                    }

                    // Todos los objetos
                    TiXmlElement* objetos = suelo->NextSiblingElement( "objetos" );
                    if (objetos)
                    {
                        TiXmlElement* objeto = objetos->FirstChildElement( "objeto" );
                        // Tenemos que recorrer todos los objetos
                        while (objeto)
                        {
                            // Extraemos el tipo de objeto
                            string tipoObj = objeto->Attribute("tipo");

                            // Extraemos la posición
                            TiXmlElement* atribs = objeto->FirstChildElement( "x" );
                            int x = atoi(atribs->GetText());
                            atribs = atribs->NextSiblingElement( "y" );
                            int y = atoi(atribs->GetText());

                            cout << "Objeto ------" << endl;
                            cout <<"tipo: " << tipoObj << " x: " << x << " y: " << y << endl;
                            cout << "-------------" << endl;

                            // Creamos el objeto y lo añadimos al nivel
                            if (tipoObj == "roca")
                            {
                                Roca* r = new Roca("roca", x, y);
                                n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), r);
                            }
                            else if (tipoObj == "pico")
                            {
                                Pico* p = new Pico("pico", x, y);
                                n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), p);
                            }
                            else if (tipoObj == "pinchos")
                            {
                                // Hay que leer otro atributo para saber el número de pinchos
                                atribs = atribs->NextSiblingElement( "num" );
                                int num = atoi(atribs->GetText());

                                Pinchos* p = new Pinchos(num, "pinchos", x, y);
                                n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), p);
                            }
                            else if (tipoObj == "plataforma")
                            {
                                Plataforma* p = new Plataforma("plataforma", x, y);
                                n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), p);
                            }
                            else if (tipoObj == "plataformamovil")
                            {
                                // Hay que leer la direccion de la plataforma
                                atribs = atribs->NextSiblingElement( "dir" );
                                string sdir = atribs->GetText();
                                int dir = 0;

                                if (sdir == "H")
                                {
                                    dir = IZQUIERDA_DERECHA;
                                }
                                else if (sdir == "V")
                                {
                                    dir = ARRIBA_ABAJO;
                                }

                                PlataformaMovil* pm = new PlataformaMovil(dir, "plataformamovil", x, y);
                                n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), pm);
                            }
                            else if (tipoObj == "bloquessimetricos")
                            {
                                // Hay que leer la direccion de la plataforma
                                atribs = atribs->NextSiblingElement( "dir" );
                                string sdir = atribs->GetText();

                                BloqueSimetrico* aux = new BloqueSimetrico(IZQUIERDA, ".", 0, 0);

                                if (sdir == "H")
                                {
                                    BloqueSimetrico* b1 = new BloqueSimetrico(IZQUIERDA, "bloquesimetrico", x + aux->getAncho()/2, y);
                                    BloqueSimetrico* b2 = new BloqueSimetrico(DERECHA, "bloquesimetrico", x - aux->getAncho()/2, y);
                                    b1->setSimetrico(b2);
                                    b2->setSimetrico(b1);
                                    n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), b1);
                                    iteradorObjs++;
                                    n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), b2);
                                }
                                else if (sdir == "V")
                                {
                                    BloqueSimetrico* b1 = new BloqueSimetrico(ARRIBA, "bloquesimetrico", x, y - aux->getAlto()/2);
                                    BloqueSimetrico* b2 = new BloqueSimetrico(ABAJO, "bloquesimetrico", x, y + aux->getAlto()/2);
                                    b1->setSimetrico(b2);
                                    b2->setSimetrico(b1);
                                    n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), b1);
                                    iteradorObjs++;
                                    n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), b2);
                                }

                                delete aux; aux = NULL;
                            }
                            else if (tipoObj == "estrella")
                            {
                                Estrella* e = new Estrella("estrella", x, y);
                                n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), e);
                            }
                            else if (tipoObj == "meta")
                            {
                                Meta* m = new Meta("meta", x, y);
                                n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), m);
                            }
                            else if (tipoObj == "silencio")
                            {
                                // Hay que leer el tipo de silencio
                                atribs = atribs->NextSiblingElement( "tipo" );
                                int tipo = atoi(atribs->GetText());

                                Silencio* s = new Silencio(tipo, "silencio", x, y);
                                n->setObjeto("objeto" + boost::lexical_cast<string>(iteradorObjs), s);
                            }

                            iteradorObjs++;

                            // Pasamos al siguiente
                            objeto = objeto->NextSiblingElement( "objeto" );
                        }
                    }
                    // Todos los enemigos
                    TiXmlElement* enemigos = objetos->NextSiblingElement( "enemigos" );
                    if (enemigos)
                    {
                        TiXmlElement* enemigo = enemigos->FirstChildElement( "enemigo" );
                        // Tenemos que recorrer todos los enemigos
                        while (enemigo)
                        {
                            // Extraemos el tipo de objeto
                            string tipoEn = enemigo->Attribute("tipo");

                            // Extraemos la posición
                            TiXmlElement* atribs = enemigo->FirstChildElement( "x" );
                            int x = atoi(atribs->GetText());
                            atribs = atribs->NextSiblingElement( "y" );
                            int y = atoi(atribs->GetText());

                            cout << "Enemigo ------" << endl;
                            cout <<"tipo: " << tipoEn << " x: " << x << " y: " << y << endl;
                            cout << "-------------" << endl;

                            if (tipoEn == "bola")
                            {
                                Bola* b = new Bola ("bola", x, y);
                                n->setEnemigo("enemigo" + boost::lexical_cast<string>(iteradorEnems), b);
                            }
                            else if (tipoEn == "cuadrado")
                            {
                                Cuadrado* c = new Cuadrado("cuadrado", x, y);
                                n->setEnemigo("enemigo" + boost::lexical_cast<string>(iteradorEnems), c);
                            }
                            else if (tipoEn == "rueda")
                            {
                                Rueda* r = new Rueda("rueda", x, y);
                                n->setEnemigo("enemigo" + boost::lexical_cast<string>(iteradorEnems), r);
                            }
                            else if (tipoEn == "gusano")
                            {
                                Gusano* g = new Gusano("gusano", x, y);
                                n->setEnemigo("enemigo" + boost::lexical_cast<string>(iteradorEnems), g);
                            }
                            else if (tipoEn == "triangulo")
                            {
                                Triangulo* t = new Triangulo("triangulo", x, y);
                                n->setEnemigo("enemigo" + boost::lexical_cast<string>(iteradorEnems), t);
                            }
                            
                            iteradorEnems++;
                            // Pasamos al siguiente
                            enemigo = enemigo->NextSiblingElement( "enemigo" );
                        }
                    }
                    else
                        cerr << "ERROR: leerNivel: problema al leer ENEMIGOS" << endl;
                }
                else
                    cerr << "ERROR: leerNivel: problema al leer NIVEL" << endl;
            }
            else
                cerr << "ERROR: leerNivel: problema al leer NIVELESTIPOx" << endl;
        }
        else
            cerr << "ERROR: leerNivel: problema al leer NIVELES" << endl;
    }
    else
    {
        cerr << "ERROR: leerNivel: no se pudo abrir el fichero" << endl;
    }

    n->nObjs = iteradorObjs;
}

Nivel* GeneradorNiveles::GenRecogidaEstrellas()
{
    Nivel* nivel = new Nivel(RECOGIDA_ESTRELLAS);

    leerNivel(nivel, RECOGIDA_ESTRELLAS);
    
    return nivel;
}

Nivel* GeneradorNiveles::GenDestruirEnemigos()
{
    Nivel* nivel = new Nivel(DESTRUIR_ENEMIGOS);

    leerNivel(nivel, DESTRUIR_ENEMIGOS);

    return nivel;
}

Nivel* GeneradorNiveles::GenSupervivencia()
{
    Nivel* nivel = new Nivel(SUPERVIVENCIA);

    leerNivel(nivel, SUPERVIVENCIA);

    return nivel;
}

Nivel* GeneradorNiveles::GenConseguirPuntos()
{
    Nivel* nivel = new Nivel(CONSEGUIR_PUNTOS);

    leerNivel(nivel, CONSEGUIR_PUNTOS);

    return nivel;
}