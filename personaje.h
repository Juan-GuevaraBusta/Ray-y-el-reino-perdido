/*
La clase Personaje define la interfaz base abstracta para todas las entidades vivientes en Ray y el Reino Perdido.
Establece el contrato común que deben cumplir Ray, las Hormigas Infectadas, las Hormigas Normales NPC y el Rey Hongo.
Define métodos virtuales puros para el manejo de acciones, posición, salud, combate y renderizado que cada personaje
debe implementar según sus características específicas. La clase Personaje utiliza el enum Accion para estandarizar
los estados de comportamiento de todas las entidades del juego.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

enum class Accion
{
    NINGUNA,
    CAMINANDO,
    ATACANDO,
    MURIENDO,
    CURANDO,
    SUPERGOLPE
};

class Personaje
{
public:
    virtual void setAccion(Accion accion) = 0;
    virtual Accion getAccion() = 0;
    virtual sf::Vector2f getPosicion() = 0;
    virtual int getSalud() = 0;
    virtual void cambiarSalud(int valor) = 0;

    virtual void atacar(Personaje* enemigo) = 0;
    virtual bool puedeAtacar() = 0;

    virtual void actualizar() = 0;
    virtual void dibujar(sf::RenderWindow& ventana) = 0;
};