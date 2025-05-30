/*
La clase Bloque representa los elementos sólidos del terreno en Ray y el Reino Perdido que forman
la estructura física del laberinto del hormiguero. Se encarga de crear bloques con diferentes texturas
según el nivel actual para proporcionar variedad visual, establecer colisiones sólidas que detienen
el movimiento de personajes y objetos, y renderizar las texturas de bloques con el tamaño estándar
del juego. La clase Bloque utiliza tanto un sprite visual como una caja de colisión invisible para
separar la representación gráfica de la física del juego, permitiendo texturas de diferentes tamaños
manteniendo colisiones consistentes.
*/

#ifndef BLOQUE_H
#define BLOQUE_H

#include "colisionador.h"
#include "configuracion.h"
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>

class Bloque {
private:
    sf::RectangleShape cajaColision; // Forma rectangular para detectar colisiones
    sf::Sprite spriteBloque; // Sprite que contiene la textura visual del bloque

public:
    // Constructor que inicializa un bloque
    Bloque(sf::Vector2f posicion, const std::string& tipoBloque);

    // Dibuja el bloque en la ventana
    void dibujar(sf::RenderWindow& ventana);

    // Obtiene el colisionador del bloque
    Colisionador getColisionador();
};

#endif // BLOQUE_H