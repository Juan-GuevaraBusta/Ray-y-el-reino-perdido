#include "portal.h"
#include "gestorRecursos.h"
#include <cstdint>

Portal::Portal(sf::Vector2f posicion, int tipo)
{
    cuadro = 0;
    relojAnimacion.restart();
    this->tipo = tipo;

    spritePortal.setTexture(GestorRecursos::getInstance()->obtenerTextura("portal1"), true);
    spritePortal.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(120, 200)));
    spritePortal.setOrigin(60.0f, 100.0f);
    spritePortal.scale(0.4f, 0.4f);
    spritePortal.setPosition(posicion);

    cajaColision.setSize(sf::Vector2f(44, 68));
    cajaColision.setFillColor(COLOR_COLECCIONABLE);
    cajaColision.setOrigin(22.95f, 34.0f);
    cajaColision.setPosition(posicion);
}

void Portal::animacion(int cuadros, int ms, int inicioX, int inicioY)
{
    // Cambiar frame cada 'ms' millisegundos
    if (relojAnimacion.getElapsedTime().asMilliseconds() >= ms)
    {
        relojAnimacion.restart();

        // Avanzar al siguiente cuadro
        cuadro++;
        if (cuadro >= cuadros)
            cuadro = 0;

        // Cambiar la textura directamente desde GestorRecursos
        std::string nombreTextura = "portal" + std::to_string(cuadro + 1);
        spritePortal.setTexture(GestorRecursos::getInstance()->obtenerTextura(nombreTextura), true);
    }
}

void Portal::actualizar()
{
    animacion(6, 110, 120, 0);

    cajaColision.setPosition(spritePortal.getPosition().x, spritePortal.getPosition().y);
}

void Portal::dibujar(sf::RenderWindow& ventana)
{
    // ventana.draw(cajaColision);  // Descomentando esto se muestra la caja de colisión
    ventana.draw(spritePortal);
}