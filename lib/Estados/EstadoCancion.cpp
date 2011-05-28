#include "Estados/EstadoCancion.h"
#include "Juego.h"
#include "DatosCancion.h"
#include "Estados/EstadoPartida.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <fstream>


EstadoCancion::EstadoCancion()
{
    cout << "CONSTRUCTOR Estado CANCION" << endl;
    hayCancion = false;
    cargando = 0;
    estadoDeAnimo = 50;
    cargando = false;
    wstring filename = Gosu::sharedResourcePrefix() + L"media/imagenes/cancion/fondocancion.bmp";
    fondo.reset(new Gosu::Image(Juego::getInstancia()->graphics(), filename, false));

    tRuta = tDatos = tTitulo = tArtista = tAlbum = tAnyo = tGenero = tEstadoAnimo = NULL;
    ctRuta = ctTitulo = ctArtista = ctAlbum = ctAnyo = ctGenero = ctEstadoAnimo = NULL;
    bFijarRuta = bJugar = bMas = bMenos = NULL;
    pGrad = pPivote = NULL;
}

EstadoCancion::~EstadoCancion()
{
    cout << "DESTRUCTOR ESTADO CANCION" << endl;
    if (tRuta != NULL) delete tRuta; tRuta = NULL;
    if (tDatos != NULL) delete tDatos; tDatos = NULL;
    if (tTitulo != NULL) delete tTitulo; tTitulo = NULL;
    if (tArtista != NULL) delete tArtista; tArtista = NULL;
    if (tAlbum != NULL) delete tAlbum; tAlbum = NULL;
    if (tGenero != NULL) delete tGenero; tGenero = NULL;
    if (tAnyo != NULL) delete tAnyo; tAnyo = NULL;
    if (tEstadoAnimo != NULL) delete tEstadoAnimo; tEstadoAnimo = NULL;
    if (ctRuta != NULL) delete ctRuta; ctRuta = NULL;
    if (ctTitulo != NULL) delete ctTitulo; ctTitulo = NULL;
    if (ctArtista != NULL) delete ctArtista; ctArtista = NULL;
    if (ctGenero != NULL) delete ctGenero; ctGenero = NULL;
    if (ctAnyo != NULL) delete ctAnyo; ctAnyo = NULL;
    if (ctEstadoAnimo != NULL) delete ctEstadoAnimo; ctEstadoAnimo = NULL;
    if (bFijarRuta != NULL) delete bFijarRuta; bFijarRuta = NULL;
    if (bJugar != NULL) delete bJugar; bJugar = NULL;
    if (bMas != NULL) delete bMas; bMas = NULL;
    if (bMenos != NULL) delete bMenos; bMenos = NULL;
    if (pGrad != NULL) delete pGrad; pGrad = NULL;
    if (pPivote != NULL) delete pPivote; pPivote = NULL;
}

void EstadoCancion::entrar()
{
    cout << "Entro en Estado Cancion" << endl;
    // Indicamos al juego que NO estamos jugando
    Juego::getInstancia()->setJugando(false);
    inicializarGUI();
    InterfazAudio::getInstancia()->cargarCancion("canciones/house.mp3"); // TEMPORAL
    InterfazAudio::getInstancia()->getDatosCancion()->setGenero(6); // TEMPORAL
}

void EstadoCancion::leerCancion()
{
    string ruta;

    // Cargamos el cuadro de selección de canción haciendo una llamada a Zenity
    system("zenity --file-selection --title=\"Selecciona la canción\" --filename=\"canciones\" >> media/historico.txt");
    
    ifstream f("media/historico.txt", ifstream::in);
    f >> ruta;
    while (!f.eof())
    {
        f >> ruta;
    }

    f.close();

    // Comprobamos si se ha cargado cancion o no
    if (ruta.substr(ruta.length()-4, ruta.length()-1) == ".mp3")
    {
        hayCancion = true;
    }

    if (hayCancion)
    {
        // Escribimos la ruta en el campo correspondiente
        wstring wruta;
        wruta.assign(ruta.begin(), ruta.end());
        ctRuta->setTexto(wruta);

        // Pasamos la ruta de la canción al interfaz de audio
        InterfazAudio* ia = InterfazAudio::getInstancia();
        ia->cargarCancion(ruta.c_str());
        ia->obtenerDatos();

        // Mostramos los datos de la canción
        wstring cadena;
        string c;
        c = ia->getDatosCancion()->getTitulo();
        cadena.assign(c.begin(), c.end());
        ctTitulo->setTexto(cadena);
        c = ia->getDatosCancion()->getArtista();
        cadena.assign(c.begin(), c.end());
        ctArtista->setTexto(cadena);
        c = ia->getDatosCancion()->getAlbum();
        cadena.assign(c.begin(), c.end());
        ctAlbum->setTexto(cadena);
        c = ia->getDatosCancion()->getFecha();
        cadena.assign(c.begin(), c.end());
        ctAnyo->setTexto(cadena);
        c = ia->getDatosCancion()->getComentarios();
        cadena.assign(c.begin(), c.end());
        int gen = ia->getDatosCancion()->getGenero();
        c = ia->getDatosCancion()->getStringGenero(gen);
        cadena.assign(c.begin(), c.end());
        ctGenero->setTexto(cadena);
    }
}

void EstadoCancion::actualizar()
{
    if (cargando == 0)
    {
        // Actualizamos algunas posiciones
        bFijarRuta->setPos(ctRuta->ancho()+ctRuta->getX()+20, bFijarRuta->getY());
        bGenero->setPos(ctGenero->ancho()+ctGenero->getX()+20, bGenero->getY());
        pPivote->setPos(pGrad->getX()-5 + (pGrad->ancho()*(float(estadoDeAnimo/100.0))), pPivote->getY());
        // Actualizamos el texto de estado de ánimo
        if (estadoDeAnimo >= 0 && estadoDeAnimo <= 20)
        {
            ctEstadoAnimo->setTexto(L"Triste");
        }
        else if (estadoDeAnimo >= 20 && estadoDeAnimo <= 40)
        {
            ctEstadoAnimo->setTexto(L"Tranquilo");
        }
        else if (estadoDeAnimo >= 40 && estadoDeAnimo <= 60)
        {
            ctEstadoAnimo->setTexto(L"Indiferente");
        }
        else if (estadoDeAnimo >= 60 && estadoDeAnimo <= 80)
        {
            ctEstadoAnimo->setTexto(L"Alegre");
        }
        else if (estadoDeAnimo >= 80 && estadoDeAnimo <= 100)
        {
            ctEstadoAnimo->setTexto(L"Euforico");
        }

        leerInput();
    }
    else if (cargando == 2)
    {
        cargando = 0;
        // Introducimos el estado de ánimo
        DatosPartida::getInstancia()->setEstadoAnimo(estadoDeAnimo);
        // Analizamos los datos de la canción
        Juego::getInstancia()->analizarCancion();
        // Pasamos a jugar el nivel
        Juego::getInstancia()->cambiarEstado(ESTADO_PARTIDA);
    }
}

void EstadoCancion::pintar()
{
    if (cargando == 0)
    {
        fondo->draw(0, 0, ZFONDO);
        pintarGUI();
    }
    else if (cargando == 1)
    {
        pCargando->pintar();
        cargando = 2;
    }
}

void EstadoCancion::salir()
{
    cout << "Salgo de Estado Cancion" << endl;
   
}

void EstadoCancion::buttonDown(Gosu::Button btn)
{
    Juego* j = Juego::getInstancia();

    if (btn == Gosu::msLeft)
    {
//        j->input().setTextInput(0);
//        if (ctRuta->mouseOver())
//        {
//            j->input().setTextInput(ctRuta);
//        }

        if (bFijarRuta->mouseOver())
        {
            leerCancion();
        }
        else if (bJugar->mouseOver())
        {
            if (hayCancion)
                cargando = 1;
        }
        else if (bGenero->mouseOver())
        {
            cargarGeneros();
        }
        else if (bMenos->mouseOver())
        {
            estadoDeAnimo -= 10;
            if (estadoDeAnimo < 0) estadoDeAnimo = 0;
        }
        else if (bMas->mouseOver())
        {
            estadoDeAnimo += 10;
            if (estadoDeAnimo > 100) estadoDeAnimo = 100;
        }
    }
}

void EstadoCancion::buttonUp(Gosu::Button btn)
{

}

void EstadoCancion::leerInput()
{

}

void EstadoCancion::inicializarGUI()
{
    wstring fDejaVuSans = Gosu::sharedResourcePrefix() + L"media/fuentes/dejavusans.ttf";
    wstring fCrayon = Gosu::sharedResourcePrefix() + L"media/fuentes/crayon.ttf";
    Animacion* aEx = new Animacion();
    Animacion* aCom = new Animacion();
    Animacion* aGen =  new Animacion();

    aEx->anyadirImagen(L"media/imagenes/cancion/botonexaminar.png");
    aCom->anyadirImagen(L"media/imagenes/cancion/botoncomenzar.png");
    aGen->anyadirImagen(L"media/imagenes/cancion/botonexaminar.png");
    bFijarRuta = new Boton(aEx, 350, 15);
    bJugar = new Boton(aCom, 580, 540);
    bGenero = new Boton(aGen, 580, 110);

    tRuta = new Texto(fCrayon, L"Ruta: ", 25, 20, 20);
    ctRuta = new CampoTexto(fCrayon, L"Selecciona la cancion...         ", 15, 100, 25);
    tDatos = new Texto(fCrayon, L"Datos: ", 25, 20, 75);
    tTitulo = new Texto(fCrayon, L"Titulo: ", 20, 20, 120);
    ctTitulo = new CampoTexto(fCrayon, L"Titulo", 15, 100, 120);
    tArtista = new Texto(fCrayon, L"Arista: ", 20, 20, 155);
    ctArtista = new CampoTexto(fCrayon, L"Artista", 15, 100, 155);
    tAlbum = new Texto(fCrayon, L"Album: ", 20, 20, 190);
    ctAlbum = new CampoTexto(fCrayon, L"Album", 15, 100, 190);
    tAnyo = new Texto(fCrayon, L"Fecha: ", 20, 20, 225);
    ctAnyo = new CampoTexto(fCrayon, L"Fecha", 15, 100, 225);
    tGenero = new Texto(fCrayon, L"Genero: ", 20, 400, 120);
    ctGenero = new CampoTexto(fCrayon, L"Genero", 15, 500, 120);
    tEstadoAnimo = new Texto(fCrayon, L"Tu estado de animo? ", 20, 400, 170);
    ctEstadoAnimo = new CampoTexto(fCrayon, L"Indiferente", 15, 480, 260);

    Animacion* aGrad = new Animacion();
    Animacion* aPivote = new Animacion();
    aGrad->anyadirImagen(L"media/imagenes/cancion/barragradiente.png");
    aPivote->anyadirImagen(L"media/imagenes/cancion/pivote.png");
    pGrad = new Panel(aGrad, 400, 210);
    pPivote = new Panel(aPivote, 500, 200);
    Animacion* aMas = new Animacion();
    Animacion* aMenos = new Animacion();
    aMas->anyadirImagen(L"media/imagenes/cancion/botonmas.png");
    aMenos->anyadirImagen(L"media/imagenes/cancion/botonmenos.png");
    bMas = new Boton(aMas, 670, 200);
    bMenos = new Boton(aMenos, 340, 200);

    Animacion* aCarg = new Animacion();
    aCarg->anyadirImagen(L"media/imagenes/cancion/cargando.png");
    pCargando = new Panel(aCarg, 0, 0);
}

void EstadoCancion::pintarGUI()
{
    tRuta->pintar();
    ctRuta->pintar();
    bFijarRuta->pintar();
    tDatos->pintar();
    tTitulo->pintar();
    ctTitulo->pintar();
    tArtista->pintar();
    ctArtista->pintar();
    tAlbum->pintar();
    ctAlbum->pintar();
    tAnyo->pintar();
    ctAnyo->pintar();
    tGenero->pintar();
    ctGenero->pintar();
    bGenero->pintar();
    tEstadoAnimo->pintar();
    ctEstadoAnimo->pintar();
    bJugar->pintar();
    pGrad->pintar();
    pPivote->pintar();
    bMas->pintar();
    bMenos->pintar();
}

void EstadoCancion::ejecutarBeat(int tipo)
{

}

void EstadoCancion::cargarGeneros()
{
    string genero;

    // Cargamos el cuadro de selección de canción haciendo una llamada a Zenity

    string zenity = "zenity --list ";
    zenity += "--title=\"Selecciona un género\" ";
    zenity += "--column=\"Número\" --column=\"Género\" \\";
    // A continuación mostramos todos los géneros
    zenity += "1 Blues \\";
    zenity += "2 Rock \\";
    zenity += "3 Dance \\";
    zenity += "4 Disco \\";
    zenity += "5 Funk \\";
    zenity += "6 Rap \\";
    zenity += "7 Jazz \\";
    zenity += "8 Pop \\";
    zenity += "9 R_and_B \\";
    zenity += "10 Reggae \\";
    zenity += "11 Techno \\";
    zenity += "12 Ska \\";
    zenity += "13 House \\";
    zenity += "14 Classical \\";
    zenity += "15 Soul \\";
    zenity += "16 Punk \\";
    zenity += "17 Latin \\";
    zenity += "18 Metal";
    zenity += " >> media/historico.txt";
    system(zenity.c_str());

    ifstream f("media/historico.txt", ifstream::in);
    f >> genero;
    while (!f.eof())
    {
        f >> genero;
    }

    f.close();

    // Guardamos el género
    InterfazAudio::getInstancia()->getDatosCancion()->setGenero(atoi(genero.c_str()));

    // Lo mostramos en el campo de texto
    string c = InterfazAudio::getInstancia()->getDatosCancion()->getStringGenero(atoi(genero.c_str()));
    wstring wc;
    wc.assign(c.begin(), c.end());
    ctGenero->setTexto(wc);
}