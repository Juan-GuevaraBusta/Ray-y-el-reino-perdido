/*
La clase Colisionador maneja toda la detección y resolución de colisiones de Ray y el Reino Perdido.
Se encarga de detectar intersecciones entre cajas rectangulares, calcular la profundidad de penetración entre objetos,
 y aplicar fuerzas de empuje configurables según el tipo de objeto. La clase Colisionador proporciona un sistema
de física simple pero efectivo que permite interacciones realistas entre Ray, enemigos, objetos coleccionables
y elementos del terreno, manteniendo un rendimiento óptimo para el gameplay fluido.
*/

#ifndef COLISIONADOR_H
#define COLISIONADOR_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstdint>

class Colisionador {
private:
    sf::RectangleShape& cuerpo; // Referencia al cuerpo rectangular del objeto

public:
    // Constructor que inicializa el colisionador
    Colisionador(sf::RectangleShape& cuerpo);

    // Mueve el colisionador en las coordenadas especificadas
    void mover(float x, float y);

    // Obtiene la posición actual del colisionador
    sf::Vector2f getPosicion();

    // Obtiene la mitad del tamaño del colisionador
    sf::Vector2f getMitadTamaño();

    // Comprueba colisión con otro colisionador y aplica física
    // fuerzaEmpuje indica qué tan difícil es mover el objeto (0 - fácilmente, 1 - imposible)
    bool comprobarColision(Colisionador otroColisionador, sf::Vector2f& direccion, float fuerzaEmpuje);
};

#endif // COLISIONADOR_H