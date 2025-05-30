/*
La clase Semilla implementa objetos restauradores de Ray y el Reino Perdido, heredando de la clase Coleccionable.
Representa semillas mágicas que Ray puede recolectar para recuperar salud o ganar puntos según su estado actual.
La clase Semilla implementa un sistema inteligente donde si Ray está sano (salud = 3) la semilla otorga +1 punto,
pero si Ray está herido (salud < 3) la semilla restaura +1 de salud. Incluye animación de sprites para crear
movimiento visual atractivo, caja de colisión para detección de recolección, y textura escalada apropiada para
el tamaño del mundo de juego. Las semillas aparecen distribuidas por los niveles como elementos de supervivencia
y estrategia para el jugador.
*/

#ifndef SEMILLA_H
#define SEMILLA_H

#include "coleccionable.h"
#include "colisionador.h"
#include "configuracion.h"
#include <cstdint>

#include <SFML/Graphics.hpp>

class Semilla : public Coleccionable {
private:
    sf::RectangleShape cajaColision;     // Caja de colisión de la semilla
    short int cuadro;                    // Cuadro actual de animación
    sf::Clock relojAnimacion;            // Reloj para animación
    sf::Sprite spriteSemilla;            // Sprite de la semilla

public:
    // Constructor con posición
    Semilla(sf::Vector2f posicion);

    // Obtener colisionador de la semilla
    Colisionador getColisionador();
    // Animar la semilla (actualmente deshabilitado)
    void animacion(int cuadros, int ms, int inicioX, int inicioY);
    // Actualizar semilla
    void actualizar();
    // Dibujar semilla
    void dibujar(sf::RenderWindow& ventana);
};

#endif // SEMILLA_H