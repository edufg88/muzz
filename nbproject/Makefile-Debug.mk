#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lib/EstadoJuego.o \
	${OBJECTDIR}/lib/Enemigos/Gusano.o \
	${OBJECTDIR}/lib/Objetos/Plataforma.o \
	${OBJECTDIR}/lib/LD/FuzzySet_Trapezium.o \
	${OBJECTDIR}/lib/Objetos/Pico.o \
	${OBJECTDIR}/lib/Enemigos/Cuadrado.o \
	${OBJECTDIR}/lib/ProcesadorAudio.o \
	${OBJECTDIR}/lib/Objeto.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/lib/LD/FuzzySet.o \
	${OBJECTDIR}/lib/InterfazIA.o \
	${OBJECTDIR}/lib/Enemigos/Triangulo.o \
	${OBJECTDIR}/lib/Objetos/PlataformaMovil.o \
	${OBJECTDIR}/lib/Objetos/BloquesSimetricos.o \
	${OBJECTDIR}/lib/Estados/EstadoGameOver.o \
	${OBJECTDIR}/lib/GUI/CampoTexto.o \
	${OBJECTDIR}/lib/Objetos/Meta.o \
	${OBJECTDIR}/lib/GeneradorNiveles.o \
	${OBJECTDIR}/lib/LD/FuzzySet_RightShoulder.o \
	${OBJECTDIR}/lib/ObjetoFijo.o \
	${OBJECTDIR}/lib/IAEnemigos/IACuadrado.o \
	${OBJECTDIR}/lib/Objetos/Bala.o \
	${OBJECTDIR}/lib/Camara.o \
	${OBJECTDIR}/lib/Animacion.o \
	${OBJECTDIR}/lib/ConversorFisico.o \
	${OBJECTDIR}/lib/DatosPartida.o \
	${OBJECTDIR}/lib/IAEnemigos/IAGusano.o \
	${OBJECTDIR}/lib/ElementoGUI.o \
	${OBJECTDIR}/lib/Objetos/Suelo.o \
	${OBJECTDIR}/lib/LD/FuzzySet_Triangle.o \
	${OBJECTDIR}/lib/Enemigo.o \
	${OBJECTDIR}/lib/InterfazAudio.o \
	${OBJECTDIR}/lib/Objetos/Roca.o \
	${OBJECTDIR}/lib/DatosCancion.o \
	${OBJECTDIR}/lib/Protagonista.o \
	${OBJECTDIR}/lib/LD/FzFairly.o \
	${OBJECTDIR}/lib/LD/FuzzyModule.o \
	${OBJECTDIR}/lib/LD/FzAnd.o \
	${OBJECTDIR}/lib/ObjetoMovil.o \
	${OBJECTDIR}/lib/LD/FuzzySet_LeftShoulder.o \
	${OBJECTDIR}/lib/IAEnemigos/IATriangulo.o \
	${OBJECTDIR}/lib/LD/FzSet.o \
	${OBJECTDIR}/lib/LD/FzVery.o \
	${OBJECTDIR}/lib/Juego.o \
	${OBJECTDIR}/lib/IAEnemigos/IABola.o \
	${OBJECTDIR}/lib/Estados/EstadoPartida.o \
	${OBJECTDIR}/lib/Enemigos/Rueda.o \
	${OBJECTDIR}/lib/GUI/Texto.o \
	${OBJECTDIR}/lib/GUI/Panel.o \
	${OBJECTDIR}/lib/IAEnemigos/IARueda.o \
	${OBJECTDIR}/lib/LD/FzOr.o \
	${OBJECTDIR}/lib/Objetos/BloqueSimetrico.o \
	${OBJECTDIR}/lib/Nivel.o \
	${OBJECTDIR}/lib/LD/FuzzyVariable.o \
	${OBJECTDIR}/lib/IAEnemigo.o \
	${OBJECTDIR}/lib/Estados/EstadoFin.o \
	${OBJECTDIR}/lib/Enemigos/Bola.o \
	${OBJECTDIR}/lib/Objetos/Pinchos.o \
	${OBJECTDIR}/lib/GUI/Boton.o \
	${OBJECTDIR}/lib/Enemigos/Jefe.o \
	${OBJECTDIR}/lib/Objetos/Silencio.o \
	${OBJECTDIR}/lib/InterfazFisica.o \
	${OBJECTDIR}/lib/Objetos/Estrella.o \
	${OBJECTDIR}/lib/DetectorColisiones.o \
	${OBJECTDIR}/lib/Estados/EstadoMenu.o \
	${OBJECTDIR}/lib/Estados/EstadoTutorial.o \
	${OBJECTDIR}/lib/Estados/EstadoCancion.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`gosu-config --cxxflags`  
CXXFLAGS=`gosu-config --cxxflags`  

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lBox2D -lmusicbrainz3 -ltinyxml

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/proyecto

dist/Debug/GNU-Linux-x86/proyecto: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -lfftw3 -lm -lgosu `gosu-config --libs` fmod/api/lib/libfmodex.so -pthread -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/proyecto  ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/lib/EstadoJuego.o: lib/EstadoJuego.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/EstadoJuego.o lib/EstadoJuego.cpp

${OBJECTDIR}/lib/Enemigos/Gusano.o: lib/Enemigos/Gusano.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Enemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Enemigos/Gusano.o lib/Enemigos/Gusano.cpp

${OBJECTDIR}/lib/Objetos/Plataforma.o: lib/Objetos/Plataforma.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/Plataforma.o lib/Objetos/Plataforma.cpp

${OBJECTDIR}/lib/LD/FuzzySet_Trapezium.o: lib/LD/FuzzySet_Trapezium.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FuzzySet_Trapezium.o lib/LD/FuzzySet_Trapezium.cpp

${OBJECTDIR}/lib/Objetos/Pico.o: lib/Objetos/Pico.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/Pico.o lib/Objetos/Pico.cpp

${OBJECTDIR}/lib/Enemigos/Cuadrado.o: lib/Enemigos/Cuadrado.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Enemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Enemigos/Cuadrado.o lib/Enemigos/Cuadrado.cpp

${OBJECTDIR}/lib/ProcesadorAudio.o: lib/ProcesadorAudio.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/ProcesadorAudio.o lib/ProcesadorAudio.cpp

${OBJECTDIR}/lib/Objeto.o: lib/Objeto.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objeto.o lib/Objeto.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/lib/LD/FuzzySet.o: lib/LD/FuzzySet.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FuzzySet.o lib/LD/FuzzySet.cpp

${OBJECTDIR}/lib/InterfazIA.o: lib/InterfazIA.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/InterfazIA.o lib/InterfazIA.cpp

${OBJECTDIR}/lib/Enemigos/Triangulo.o: lib/Enemigos/Triangulo.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Enemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Enemigos/Triangulo.o lib/Enemigos/Triangulo.cpp

${OBJECTDIR}/lib/Objetos/PlataformaMovil.o: lib/Objetos/PlataformaMovil.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/PlataformaMovil.o lib/Objetos/PlataformaMovil.cpp

${OBJECTDIR}/lib/Objetos/BloquesSimetricos.o: lib/Objetos/BloquesSimetricos.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/BloquesSimetricos.o lib/Objetos/BloquesSimetricos.cpp

${OBJECTDIR}/lib/Estados/EstadoGameOver.o: lib/Estados/EstadoGameOver.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Estados
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Estados/EstadoGameOver.o lib/Estados/EstadoGameOver.cpp

${OBJECTDIR}/lib/GUI/CampoTexto.o: lib/GUI/CampoTexto.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/GUI
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/GUI/CampoTexto.o lib/GUI/CampoTexto.cpp

${OBJECTDIR}/lib/Objetos/Meta.o: lib/Objetos/Meta.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/Meta.o lib/Objetos/Meta.cpp

${OBJECTDIR}/lib/GeneradorNiveles.o: lib/GeneradorNiveles.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/GeneradorNiveles.o lib/GeneradorNiveles.cpp

${OBJECTDIR}/lib/LD/FuzzySet_RightShoulder.o: lib/LD/FuzzySet_RightShoulder.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FuzzySet_RightShoulder.o lib/LD/FuzzySet_RightShoulder.cpp

${OBJECTDIR}/lib/ObjetoFijo.o: lib/ObjetoFijo.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/ObjetoFijo.o lib/ObjetoFijo.cpp

${OBJECTDIR}/lib/IAEnemigos/IACuadrado.o: lib/IAEnemigos/IACuadrado.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/IAEnemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/IAEnemigos/IACuadrado.o lib/IAEnemigos/IACuadrado.cpp

${OBJECTDIR}/lib/Objetos/Bala.o: lib/Objetos/Bala.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/Bala.o lib/Objetos/Bala.cpp

${OBJECTDIR}/lib/Camara.o: lib/Camara.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Camara.o lib/Camara.cpp

${OBJECTDIR}/lib/Animacion.o: lib/Animacion.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Animacion.o lib/Animacion.cpp

${OBJECTDIR}/lib/ConversorFisico.o: lib/ConversorFisico.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/ConversorFisico.o lib/ConversorFisico.cpp

${OBJECTDIR}/lib/DatosPartida.o: lib/DatosPartida.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/DatosPartida.o lib/DatosPartida.cpp

${OBJECTDIR}/lib/IAEnemigos/IAGusano.o: lib/IAEnemigos/IAGusano.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/IAEnemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/IAEnemigos/IAGusano.o lib/IAEnemigos/IAGusano.cpp

${OBJECTDIR}/lib/ElementoGUI.o: lib/ElementoGUI.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/ElementoGUI.o lib/ElementoGUI.cpp

${OBJECTDIR}/lib/Objetos/Suelo.o: lib/Objetos/Suelo.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/Suelo.o lib/Objetos/Suelo.cpp

${OBJECTDIR}/lib/LD/FuzzySet_Triangle.o: lib/LD/FuzzySet_Triangle.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FuzzySet_Triangle.o lib/LD/FuzzySet_Triangle.cpp

${OBJECTDIR}/lib/Enemigo.o: lib/Enemigo.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Enemigo.o lib/Enemigo.cpp

${OBJECTDIR}/lib/InterfazAudio.o: lib/InterfazAudio.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/InterfazAudio.o lib/InterfazAudio.cpp

${OBJECTDIR}/lib/Objetos/Roca.o: lib/Objetos/Roca.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/Roca.o lib/Objetos/Roca.cpp

${OBJECTDIR}/lib/DatosCancion.o: lib/DatosCancion.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/DatosCancion.o lib/DatosCancion.cpp

${OBJECTDIR}/lib/Protagonista.o: lib/Protagonista.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Protagonista.o lib/Protagonista.cpp

${OBJECTDIR}/lib/LD/FzFairly.o: lib/LD/FzFairly.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FzFairly.o lib/LD/FzFairly.cpp

${OBJECTDIR}/lib/LD/FuzzyModule.o: lib/LD/FuzzyModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FuzzyModule.o lib/LD/FuzzyModule.cpp

${OBJECTDIR}/lib/LD/FzAnd.o: lib/LD/FzAnd.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FzAnd.o lib/LD/FzAnd.cpp

${OBJECTDIR}/lib/ObjetoMovil.o: lib/ObjetoMovil.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/ObjetoMovil.o lib/ObjetoMovil.cpp

${OBJECTDIR}/lib/LD/FuzzySet_LeftShoulder.o: lib/LD/FuzzySet_LeftShoulder.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FuzzySet_LeftShoulder.o lib/LD/FuzzySet_LeftShoulder.cpp

${OBJECTDIR}/lib/IAEnemigos/IATriangulo.o: lib/IAEnemigos/IATriangulo.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/IAEnemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/IAEnemigos/IATriangulo.o lib/IAEnemigos/IATriangulo.cpp

${OBJECTDIR}/lib/LD/FzSet.o: lib/LD/FzSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FzSet.o lib/LD/FzSet.cpp

${OBJECTDIR}/lib/LD/FzVery.o: lib/LD/FzVery.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FzVery.o lib/LD/FzVery.cpp

${OBJECTDIR}/lib/Juego.o: lib/Juego.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Juego.o lib/Juego.cpp

${OBJECTDIR}/lib/IAEnemigos/IABola.o: lib/IAEnemigos/IABola.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/IAEnemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/IAEnemigos/IABola.o lib/IAEnemigos/IABola.cpp

${OBJECTDIR}/lib/Estados/EstadoPartida.o: lib/Estados/EstadoPartida.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Estados
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Estados/EstadoPartida.o lib/Estados/EstadoPartida.cpp

${OBJECTDIR}/lib/Enemigos/Rueda.o: lib/Enemigos/Rueda.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Enemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Enemigos/Rueda.o lib/Enemigos/Rueda.cpp

${OBJECTDIR}/lib/GUI/Texto.o: lib/GUI/Texto.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/GUI
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/GUI/Texto.o lib/GUI/Texto.cpp

${OBJECTDIR}/lib/GUI/Panel.o: lib/GUI/Panel.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/GUI
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/GUI/Panel.o lib/GUI/Panel.cpp

${OBJECTDIR}/lib/IAEnemigos/IARueda.o: lib/IAEnemigos/IARueda.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/IAEnemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/IAEnemigos/IARueda.o lib/IAEnemigos/IARueda.cpp

${OBJECTDIR}/lib/LD/FzOr.o: lib/LD/FzOr.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FzOr.o lib/LD/FzOr.cpp

${OBJECTDIR}/lib/Objetos/BloqueSimetrico.o: lib/Objetos/BloqueSimetrico.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/BloqueSimetrico.o lib/Objetos/BloqueSimetrico.cpp

${OBJECTDIR}/lib/Nivel.o: lib/Nivel.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Nivel.o lib/Nivel.cpp

${OBJECTDIR}/lib/LD/FuzzyVariable.o: lib/LD/FuzzyVariable.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/LD
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/LD/FuzzyVariable.o lib/LD/FuzzyVariable.cpp

${OBJECTDIR}/lib/IAEnemigo.o: lib/IAEnemigo.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/IAEnemigo.o lib/IAEnemigo.cpp

${OBJECTDIR}/lib/Estados/EstadoFin.o: lib/Estados/EstadoFin.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Estados
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Estados/EstadoFin.o lib/Estados/EstadoFin.cpp

${OBJECTDIR}/lib/Enemigos/Bola.o: lib/Enemigos/Bola.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Enemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Enemigos/Bola.o lib/Enemigos/Bola.cpp

${OBJECTDIR}/lib/Objetos/Pinchos.o: lib/Objetos/Pinchos.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/Pinchos.o lib/Objetos/Pinchos.cpp

${OBJECTDIR}/lib/GUI/Boton.o: lib/GUI/Boton.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/GUI
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/GUI/Boton.o lib/GUI/Boton.cpp

${OBJECTDIR}/lib/Enemigos/Jefe.o: lib/Enemigos/Jefe.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Enemigos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Enemigos/Jefe.o lib/Enemigos/Jefe.cpp

${OBJECTDIR}/lib/Objetos/Silencio.o: lib/Objetos/Silencio.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/Silencio.o lib/Objetos/Silencio.cpp

${OBJECTDIR}/lib/InterfazFisica.o: lib/InterfazFisica.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/InterfazFisica.o lib/InterfazFisica.cpp

${OBJECTDIR}/lib/Objetos/Estrella.o: lib/Objetos/Estrella.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Objetos
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Objetos/Estrella.o lib/Objetos/Estrella.cpp

${OBJECTDIR}/lib/DetectorColisiones.o: lib/DetectorColisiones.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/DetectorColisiones.o lib/DetectorColisiones.cpp

${OBJECTDIR}/lib/Estados/EstadoMenu.o: lib/Estados/EstadoMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Estados
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Estados/EstadoMenu.o lib/Estados/EstadoMenu.cpp

${OBJECTDIR}/lib/Estados/EstadoTutorial.o: lib/Estados/EstadoTutorial.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Estados
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Estados/EstadoTutorial.o lib/Estados/EstadoTutorial.cpp

${OBJECTDIR}/lib/Estados/EstadoCancion.o: lib/Estados/EstadoCancion.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/Estados
	${RM} $@.d
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/Estados/EstadoCancion.o lib/Estados/EstadoCancion.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/proyecto

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
