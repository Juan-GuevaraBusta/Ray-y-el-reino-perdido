/*
La clase Luz implementa objetos de energía bioluminiscente de Ray y el Reino Perdido, heredando de la clase Coleccionable.
Representa fuentes de luz mágica que Ray puede recolectar para aumentar su puntuación y cargar su bastón luminoso.
La clase Luz otorga +1 punto al puntaje y +1 unidad de luz cuando Ray las recolecta, permitiendo que acumule energía
para ataques especiales. Incluye caja de colisión para detección de recolección, sprite escalado apropiadamente para
el mundo de juego. Las luces aparecen distribuidas
por los niveles como fuente principal de puntuación y recurso estratégico para el combate.
*/

#ifndef LUZ_H
#define LUZ_H

#include "coleccionable.h"
#include "colisionador.h"
#include "configuracion.h"
#include <cstdint>

#include <SFML/Graphics.hpp>

class Luz : public Coleccionable
{
private:
    // Atributos de colisión y posición
    sf::RectangleShape cajaColision; // Caja de colisión del objeto luz

    // Atributos de animación
    short int cuadro; // Frame actual de animación
    sf::Clock relojAnimacion; // Control de tiempo de animación

    // Atributos gráficos
    sf::Sprite spriteLuz; // Sprite visual del objeto luz
    std::vector<sf::Texture> texturasPortal; // Texturas para animación

public:
    // Constructor
    Luz(sf::Vector2f posicion);

    // Obtiene el colisionador del objeto
    Colisionador getColisionador();

    // Controla la animación del objeto
    void animacion(int cuadros, int ms, int inicioX, int inicioY);

    // Actualiza la lógica del objeto
    void actualizar();

    // Dibuja el objeto en pantalla
    void dibujar(sf::RenderWindow& ventana);
};

#endif // LUZ_H