#include "InterfazIA.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "DatosPartida.h"
#include "LD/FzAnd.h"
#include "LD/FzOr.h"
#include "InterfazAudio.h"

InterfazIA* InterfazIA::instancia = NULL;

InterfazIA* InterfazIA::getInstancia()
{
    if (instancia == NULL)
    {
        instancia = new InterfazIA();
    }

    return instancia;
}

InterfazIA::InterfazIA()
{

}

InterfazIA::~InterfazIA()
{
    FuzzyModule* fm = modulosLD["modTipoNivel"];
    if (fm != NULL)
        delete fm;
    fm = NULL;
    modulosLD.clear();
    // Borramos todos los módulos
    /*
    map<string, FuzzyModule*>::iterator it;
    for (it = modulosLD.begin(); it != modulosLD.end(); it++)
    {
        FuzzyModule* fm = it->second;
        if (fm != NULL)
            delete fm;
        fm = NULL;
    }
    modulosLD.clear();
    */
}

void InterfazIA::initTN(string nombreModulo)
{
    // Creamos un nuevo módulo difuso
    FuzzyModule* fuzzyMod = new FuzzyModule();
    modulosLD[nombreModulo] = fuzzyMod;

    //----
    // Variables difusas que necesitaremos
    //----
    FuzzyVariable* duracion = fuzzyMod->CreateFLV("duracion");
    FuzzyVariable* genero = fuzzyMod->CreateFLV("genero");
    FuzzyVariable* estadoAnimo = fuzzyMod->CreateFLV("estadoAnimo");

    FuzzyVariable* desTipoNivel1 = fuzzyMod->CreateFLV("desTipoNivel1");
    FuzzyVariable* desTipoNivel2 = fuzzyMod->CreateFLV("desTipoNivel2");
    FuzzyVariable* desTipoNivel3 = fuzzyMod->CreateFLV("desTipoNivel3");
    FuzzyVariable* desTipoNivel4 = fuzzyMod->CreateFLV("desTipoNivel4");
    
    //----
    // Conjuntos para las distintas variables
    //----

    double a,m,n,b;

    // Duración
    a = 0, m = 90, b = 150;
    FzSet duracion_baja = duracion->AddLeftShoulderSet("baja", a, m, b);
    a = 100, m = 150, n = 210, b = 260;
    FzSet duracion_media = duracion->AddTrapeziumSet("media", a, m, n, b);
    a = 210, m = 270, b = 360;
    FzSet duracion_alta = duracion->AddRightShoulderSet("alta", a, m, b);

    // Género
    a = 0, m = 10, b = 25;
    FzSet genero_relax = genero->AddLeftShoulderSet("relax", a, m, b);
    a = 10, m = 25, b = 50;
    FzSet genero_suave = genero->AddTriangularSet("suave", a, m, b);
    a = 30, m = 40, n = 60, b = 70;
    FzSet genero_medio = genero->AddTrapeziumSet("medio", a, m, n, b);
    a = 50, m = 75, n = 90;
    FzSet genero_intenso = genero->AddTriangularSet("intenso", a, m, b);
    a = 75, m = 90, b = 100;
    FzSet genero_duro = genero->AddRightShoulderSet("duro", a, m, b);

    // Estado de ánimo
    a = 0, m = 10, b = 25;
    FzSet estado_triste = estadoAnimo->AddLeftShoulderSet("triste", a, m, b);
    a = 10, m = 25, b = 50;
    FzSet estado_tranquilo = estadoAnimo->AddTriangularSet("tranquilo", a, m, b);
    a = 30, m = 40, n = 60, b = 70;
    FzSet estado_indiferente = estadoAnimo->AddTrapeziumSet("indiferente", a, m, n, b);
    a = 50, m = 75, n = 90;
    FzSet estado_alegre = estadoAnimo->AddTriangularSet("alegre", a, m, b);
    a = 75, m = 90, b = 100;
    FzSet estado_euforico = estadoAnimo->AddRightShoulderSet("euforico", a, m, b);

    // Variable de salida (Deseabilidad del tipo de nivel)

    a = 0; m = 10; b = 20;
    FzSet tipo1_indeseable = desTipoNivel1->AddLeftShoulderSet("indeseable", a, m, b);
    FzSet tipo2_indeseable = desTipoNivel2->AddLeftShoulderSet("indeseable", a, m, b);
    FzSet tipo3_indeseable = desTipoNivel3->AddLeftShoulderSet("indeseable", a, m, b);
    FzSet tipo4_indeseable = desTipoNivel4->AddLeftShoulderSet("indeseable", a, m, b);

    a = 15; m = 25; n = 35; b = 45;
    FzSet tipo1_poco_deseable = desTipoNivel1->AddTrapeziumSet("poco deseable", a, m, n, b);
    FzSet tipo2_poco_deseable = desTipoNivel2->AddTrapeziumSet("poco deseable", a, m, n, b);
    FzSet tipo3_poco_deseable = desTipoNivel3->AddTrapeziumSet("poco deseable", a, m, n, b);
    FzSet tipo4_poco_deseable = desTipoNivel4->AddTrapeziumSet("poco deseable", a, m, n, b);

    a = 35; m = 40; n = 60; b = 65;
    FzSet tipo1_indiferente = desTipoNivel1->AddTrapeziumSet("indiferente", a, m, n, b);
    FzSet tipo2_indiferente = desTipoNivel2->AddTrapeziumSet("indiferente", a, m, n, b);
    FzSet tipo3_indiferente = desTipoNivel3->AddTrapeziumSet("indiferente", a, m, n, b);
    FzSet tipo4_indiferente = desTipoNivel4->AddTrapeziumSet("indiferente", a, m, n, b);

    a = 55; m = 65; n = 75; b = 85;
    FzSet tipo1_deseable = desTipoNivel1->AddTrapeziumSet("deseable", a, m, n, b);
    FzSet tipo2_deseable = desTipoNivel2->AddTrapeziumSet("deseable", a, m, n, b);
    FzSet tipo3_deseable = desTipoNivel3->AddTrapeziumSet("deseable", a, m, n, b);
    FzSet tipo4_deseable = desTipoNivel4->AddTrapeziumSet("deseable", a, m, n, b);

    a = 80; m = 90; n = 100;
    FzSet tipo1_muy_deseable = desTipoNivel1->AddRightShoulderSet("muy deseable", a, m, b);
    FzSet tipo2_muy_deseable = desTipoNivel2->AddRightShoulderSet("muy deseable", a, m, b);
    FzSet tipo3_muy_deseable = desTipoNivel3->AddRightShoulderSet("muy deseable", a, m, b);
    FzSet tipo4_muy_deseable = desTipoNivel4->AddRightShoulderSet("muy deseable", a, m, b);

    //----
    // Generamos las reglas
    //----    
    // Reglas para el Tipo 1 de nivel (Recogida de estrellas)
    fuzzyMod->AddRule(*new FzAnd(duracion_baja, *new FzOr(estado_tranquilo, estado_indiferente)), tipo1_deseable);
    fuzzyMod->AddRule(*new FzAnd(duracion_baja, estado_indiferente, *new FzOr(genero_relax, genero_suave, genero_medio)), tipo1_deseable);
    fuzzyMod->AddRule(*new FzAnd(*new FzOr(duracion_media, duracion_alta), *new FzOr(*new FzOr(estado_tranquilo, estado_indiferente), *new FzOr(genero_relax, genero_suave))), tipo1_muy_deseable);
    fuzzyMod->AddRule(*new FzOr(estado_euforico, genero_duro), tipo1_indeseable);
    fuzzyMod->AddRule(*new FzOr(estado_alegre, genero_intenso), tipo1_poco_deseable);
    
    // Reglas para el Tipo 2 de nivel (Destruir enemigos)
    fuzzyMod->AddRule(*new FzOr(estado_euforico, estado_alegre), tipo2_muy_deseable);
    fuzzyMod->AddRule(*new FzAnd(estado_indiferente, *new FzOr(genero_duro, genero_intenso)), tipo2_deseable);
    // Reglas para el Tipo 3 de nivel (Supervivencia)
    fuzzyMod->AddRule(*new FzAnd(duracion_baja, *new FzOr(estado_alegre, estado_euforico)), tipo3_muy_deseable);
    fuzzyMod->AddRule(*new FzAnd(duracion_baja, estado_indiferente, *new FzOr(genero_duro, genero_intenso)), tipo3_muy_deseable);
    fuzzyMod->AddRule(*new FzAnd(duracion_media, *new FzOr(estado_euforico, genero_duro)), tipo3_deseable);
    fuzzyMod->AddRule(duracion_alta, tipo3_poco_deseable);
    // Reglas para el Tipo 4 de nivel (Conseguir puntos)
    fuzzyMod->AddRule(*new FzAnd(*new FzOr(estado_triste, estado_tranquilo), *new FzOr(genero_suave, genero_relax)), tipo4_muy_deseable);
    fuzzyMod->AddRule(*new FzAnd(*new FzOr(estado_triste, estado_tranquilo), genero_medio), tipo4_deseable);
    
}

int InterfazIA::getDeseabilidadTN1(string nombreModulo, int duracion, int genero, int estadoAnimo)
{
    FuzzyModule* fm = modulosLD[nombreModulo];
    int res_centroide;
    int res_max_av;

    if (fm == NULL)
    {
        cerr << "Error: getDeseabilidadTN1, no se encuentra el módulo" << endl;
    }
    else
    {
        fm->Fuzzify("duracion", duracion);
        fm->Fuzzify("genero", getIntensidadGenero(genero));
        fm->Fuzzify("estadoAnimo", estadoAnimo);

        res_max_av = fm->DeFuzzify("desTipoNivel1", FuzzyModule::max_av);
        res_centroide = fm->DeFuzzify("desTipoNivel1", FuzzyModule::centroid);
    }

    cout << "DESEABILIDAD TIPO 1 ---- " << endl;
    cout << "Duracion: " << duracion << endl;
    cout << "Genero: " << genero << " Intensidad: " << getIntensidadGenero(genero) << endl;
    cout << "Estado: " << estadoAnimo << endl;
    cout << "RES_max_av: " << res_max_av << endl;
    cout << "RES_centroide: " << res_centroide << endl;

    return res_centroide;
}

int InterfazIA::getDeseabilidadTN2(string nombreModulo, int duracion, int genero, int estadoAnimo)
{
    FuzzyModule* fm = modulosLD[nombreModulo];
    int res_centroide;
    int res_max_av;

    if (fm == NULL)
    {
        cerr << "Error: getDeseabilidadTN2, no se encuentra el módulo" << endl;
    }
    else
    {
        fm->Fuzzify("duracion", duracion);
        fm->Fuzzify("genero", getIntensidadGenero(genero));
        fm->Fuzzify("estadoAnimo", estadoAnimo);

        res_max_av = fm->DeFuzzify("desTipoNivel2", FuzzyModule::max_av);
        res_centroide = fm->DeFuzzify("desTipoNivel2", FuzzyModule::centroid);
    }

    cout << "DESEABILIDAD TIPO 2 ---- " << endl;
    cout << "Duracion: " << duracion << endl;
    cout << "Genero: " << genero << " Intensidad: " << getIntensidadGenero(genero) << endl;
    cout << "Estado: " << estadoAnimo << endl;
    cout << "RES_max_av: " << res_max_av << endl;
    cout << "RES_centroide: " << res_centroide << endl;

    return res_centroide;
}

int InterfazIA::getDeseabilidadTN3(string nombreModulo, int duracion, int genero, int estadoAnimo)
{
    FuzzyModule* fm = modulosLD[nombreModulo];
    int res_centroide;
    int res_max_av;

    if (fm == NULL)
    {
        cerr << "Error: getDeseabilidadTN3, no se encuentra el módulo" << endl;
    }
    else
    {
        fm->Fuzzify("duracion", duracion);
        fm->Fuzzify("genero", getIntensidadGenero(genero));
        fm->Fuzzify("estadoAnimo", estadoAnimo);

        res_max_av = fm->DeFuzzify("desTipoNivel3", FuzzyModule::max_av);
        res_centroide = fm->DeFuzzify("desTipoNivel3", FuzzyModule::centroid);
    }

    cout << "DESEABILIDAD TIPO 3 ---- " << endl;
    cout << "Duracion: " << duracion << endl;
    cout << "Genero: " << genero << " Intensidad: " << getIntensidadGenero(genero) << endl;
    cout << "Estado: " << estadoAnimo << endl;
    cout << "RES_max_av: " << res_max_av << endl;
    cout << "RES_centroide: " << res_centroide << endl;

    return res_centroide;
}

int InterfazIA::getDeseabilidadTN4(string nombreModulo, int duracion, int genero, int estadoAnimo)
{
    FuzzyModule* fm = modulosLD[nombreModulo];
    int res_centroide;
    int res_max_av;

    if (fm == NULL)
    {
        cerr << "Error: getDeseabilidadTN4, no se encuentra el módulo" << endl;
    }
    else
    {
        fm->Fuzzify("duracion", duracion);
        fm->Fuzzify("genero", getIntensidadGenero(genero));
        fm->Fuzzify("estadoAnimo", estadoAnimo);

        res_max_av = fm->DeFuzzify("desTipoNivel4", FuzzyModule::max_av);
        res_centroide = fm->DeFuzzify("desTipoNivel4", FuzzyModule::centroid);
    }

    cout << "DESEABILIDAD TIPO 4 ---- " << endl;
    cout << "Duracion: " << duracion << endl;
    cout << "Genero: " << genero << " Intensidad: " << getIntensidadGenero(genero) << endl;
    cout << "Estado: " << estadoAnimo << endl;
    cout << "RES_max_av: " << res_max_av << endl;
    cout << "RES_centroide: " << res_centroide << endl;

    return res_centroide;
}

int InterfazIA::getTipoNivel(string nombreModulo)
{
    int* des = new int[4];
    int resultado = -1;
    // Inicializamos el módulo con el que trabajaremos
    initTN(nombreModulo);
    // Obtenemos los datos que necesitamos para el módulo
    int duracion = InterfazAudio::getInstancia()->getDatosCancion()->getDuracion();
    int genero = InterfazAudio::getInstancia()->getDatosCancion()->getGenero();
    int estadoAnimo = DatosPartida::getInstancia()->getEstadoAnimo();

    // Obtenemos cada una de las deseabilidades
    des[0] = getDeseabilidadTN1(nombreModulo, duracion, genero, estadoAnimo);
    des[1] = getDeseabilidadTN2(nombreModulo, duracion, genero, estadoAnimo);
    des[2] = getDeseabilidadTN3(nombreModulo, duracion, genero, estadoAnimo);
    des[3] = getDeseabilidadTN4(nombreModulo, duracion, genero, estadoAnimo);

    resultado = maximo(des, 4);

    if (resultado == des[0])
        return 1;
    else if (resultado == des[1])
        return 2;
    else if (resultado == des[2])
        return 3;
    else if (resultado == des[3])
        return 4;
    else
        return 1;
}

int InterfazIA::getIntensidadGenero(int genero)
{
    switch (genero)
    {
        case CLASSICAL:
        case CHILL_OUT:
            return aleatorio(10, 30);

        case POP:
        case LATIN:
            return aleatorio(40, 60);

        case BLUES:
        case JAZZ:
        case R_AND_B:
            return aleatorio(40, 70);

        case RAP:
        case REGGAE:
        case SOUL:
            return aleatorio(50,70);

        case DANCE:
        case DISCO:
        case FUNK:
            return aleatorio(60, 80);

        case ROCK:
        case METAL:
        case PUNK:
        case SKA:
            return aleatorio(70, 90);

        case TECHNO:
        case HOUSE:
            return aleatorio(70, 100);

        default:
            cerr << "ERROR: género desconocido analizando intensidad" << endl;
            return 50;
    }
}

int InterfazIA::aleatorio(int min, int max)
{
    srand(time(0));
    int rango = max-min+1;
    int entero = min + fabs(int((rand()*max)%rango + 1));

    return entero;
}

int InterfazIA::maximo(int* v, int tam)
{
    int max = -1;

    for (int i = 0; i < tam; i++)
    {
        if (v[i] > max)
            max = v[i];
    }

    return max;
}