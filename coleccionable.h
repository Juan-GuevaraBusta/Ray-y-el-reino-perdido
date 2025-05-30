/*
La clase Coleccionable define la interfaz base para todos los objetos que Ray puede recolectar
en Ray y el Reino Perdido. Establece el contrato común que deben cumplir las luces bioluminiscentes,
las semillas restauradoras y los portales de transición entre niveles. La clase Coleccionable define
métodos virtuales para animación, actualización de estado y renderizado que cada objeto coleccionable.
*/

#ifndef COLECCIONABLE_H
#define COLECCIONABLE_H

#include <SFML/Graphics.hpp>
#include <cstdint>

class Coleccionable
{
public:
    virtual void animacion(int cuadros, int ms, int inicioX, int inicioY) = 0;
    virtual void actualizar() = 0;
    virtual void dibujar(sf::RenderWindow& ventana) = 0;
};

#endif // COLECCIONABLE_H