#include "colisionador.h"
#include <cmath>
#include <cstdint>

Colisionador::Colisionador(sf::RectangleShape& cuerpo) : cuerpo(cuerpo)
{
}

void Colisionador::mover(float x, float y)
{
    cuerpo.move(x, y);
}


bool Colisionador::comprobarColision(Colisionador otroColisionador, sf::Vector2f& direccion, float fuerzaEmpuje)
{
    sf::Vector2f otraPosicion = otroColisionador.getPosicion();
    sf::Vector2f otroMitadTamaño = otroColisionador.getMitadTamaño();
    sf::Vector2f estaPosicion = getPosicion();
    sf::Vector2f esteMitadTamaño = getMitadTamaño();

    float deltaX = otraPosicion.x - estaPosicion.x;
    float deltaY = otraPosicion.y - estaPosicion.y;
    float interseccionX = fabs(deltaX) - (otroMitadTamaño.x + esteMitadTamaño.x);
    float interseccionY = fabs(deltaY) - (otroMitadTamaño.y + esteMitadTamaño.y);

    if (interseccionX < 0.0f && interseccionY < 0.0f)
    {
        fuerzaEmpuje = std::min(std::max(fuerzaEmpuje, 0.0f), 1.0f);

        if (interseccionX > interseccionY)
        {
            if (deltaX > 0.0f)
            {
                mover(interseccionX * (1.0f - fuerzaEmpuje), 0.0f);
                otroColisionador.mover(-interseccionX * fuerzaEmpuje, 0.0f);
                direccion.x = 1.0f;
                direccion.y = 0.0f;
            }
            else
            {
                mover(-interseccionX * (1.0f - fuerzaEmpuje), 0.0f);
                otroColisionador.mover(interseccionX * fuerzaEmpuje, 0.0f);
                direccion.x = -1.0f;
                direccion.y = 0.0f;
            }
        }
        else
        {
            if (deltaY > 0.0f)
            {
                mover(0.0f, interseccionY * (1.0f - fuerzaEmpuje));
                otroColisionador.mover(0.0f, -interseccionY * fuerzaEmpuje);
                direccion.x = 0.0f;
                direccion.y = -1.0f;
            }
            else
            {
                mover(0.0f, -interseccionY * (1.0f - fuerzaEmpuje));
                otroColisionador.mover(0.0f, interseccionY * fuerzaEmpuje);
                direccion.x = 0.0f;
                direccion.y = 1.0f;
            }
        }
        return true;
    }
    return false;
}

sf::Vector2f Colisionador::getPosicion()
{
    return cuerpo.getPosition();
}

sf::Vector2f Colisionador::getMitadTamaño()
{
    return cuerpo.getSize() / 2.0f;
}