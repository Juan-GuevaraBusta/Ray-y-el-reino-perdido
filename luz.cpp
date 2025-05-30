#include "luz.h"
#include "gestorRecursos.h"
#include <cstdint>

// Constructor: Inicializa el objeto luz en la posición especificada
Luz::Luz(sf::Vector2f posicion) {
    cuadro = 0;
    relojAnimacion.restart();

    // Configuración del sprite de luz
    spriteLuz.setTexture(GestorRecursos::getInstance()->obtenerTextura("lumiazul"), true);
    spriteLuz.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), TAMAÑO_CUADRO_LUZ));
    spriteLuz.setOrigin(80.0f, 80.0f);
    spriteLuz.scale(0.1f, 0.1f); // Escalar el sprite para hacerlo más pequeño
    spriteLuz.setPosition(posicion);

    // Configuración de la caja de colisión
    cajaColision.setSize(sf::Vector2f(24, 24));
    cajaColision.setFillColor(COLOR_COLECCIONABLE);
    cajaColision.setOrigin(12.0f, 12.0f);
    cajaColision.setPosition(posicion);
}

// Obtiene el colisionador del objeto luz
Colisionador Luz::getColisionador() {
    return Colisionador(cajaColision);
}

// Método de animación (actualmente deshabilitado)
void Luz::animacion(int cuadros, int ms, int inicioX, int inicioY) {
    // Código de animación comentado - funcionalidad deshabilitada
}

// Actualiza la lógica del objeto luz
void Luz::actualizar() {
    // Llamada a animación comentada - funcionalidad deshabilitada
}

// Dibuja el objeto luz en la ventana
void Luz::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteLuz);
}