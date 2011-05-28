#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

// Para simplificar el control de la posición Z de las imágenes
#define ZFONDO 0
#define ZESCENARIO 1
#define ZOBJETOESCENARIO 2
#define ZPERSONAJE 3
#define ZGUI 4