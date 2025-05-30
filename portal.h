/*
La clase Portal implementa puntos de transición entre niveles de Ray y el Reino Perdido, heredando de la clase Coleccionable.
Representa portales mágicos que permiten a Ray viajar entre diferentes áreas del hormiguero. La clase Portal gestiona
dos tipos de portales: de entrada (tipo 0) que marcan el punto de aparición de Ray, y de salida (tipo 1) que transportan
a Ray al siguiente nivel cuando se activan. Incluye sistema de animación con múltiples frames para crear efectos visuales
de portal activo, temporizador de cooldown para evitar teletransporte accidental, y caja de colisión para detectar cuando
Ray entra en contacto.
*/

#ifndef PORTAL_H
#define PORTAL_H

#include "coleccionable.h"
#include "colisionador.h"
#include "configuracion.h"

#include <SFML/Graphics.hpp>
#include <cstdint>

class Portal : public Coleccionable
{
private:
    // Atributos
    sf::RectangleShape cajaColision;
    int tipo;
    short int cuadro;
    sf::Clock relojAnimacion;
    sf::Sprite spritePortal;
    std::vector<sf::Texture> texturasPortal;

public:
    // Atributo público para controlar el tiempo de teletransporte
    sf::Clock relojPortal;
    
    // Métodos
    Portal(sf::Vector2f posicion, int tipo);

    Colisionador getColisionador()
    {
        return Colisionador(cajaColision);
    }

    bool puedeTeletransportar()
    {
        return relojPortal.getElapsedTime() > sf::milliseconds(700);
    }
    
    int getTipo()
    {
        return tipo;
    }

    void animacion(int cuadros, int ms, int inicioX, int inicioY);
    void actualizar();
    void dibujar(sf::RenderWindow& ventana);
};

#endif // PORTAL_H