#include "semilla.h"
#include "gestorRecursos.h"
#include <cstdint>

// Constructor: inicializar semilla en posición especificada
Semilla::Semilla(sf::Vector2f posicion) {
    cuadro = 0;
    relojAnimacion.restart();

    // Configurar sprite de la semilla
    spriteSemilla.setTexture(GestorRecursos::getInstance()->obtenerTextura("semilla"), true);
    spriteSemilla.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), TAMAÑO_CUADRO_SEMILLA));
    spriteSemilla.setOrigin(80.0f, 80.0f);
    spriteSemilla.scale(0.1f, 0.1f);
    spriteSemilla.setPosition(posicion);

    // Configurar caja de colisión
    cajaColision.setSize(sf::Vector2f(24, 24));
    cajaColision.setFillColor(COLOR_COLECCIONABLE);
    cajaColision.setOrigin(12, 12);
    cajaColision.setPosition(posicion);
}

// Obtener colisionador de la semilla
Colisionador Semilla::getColisionador() {
    return Colisionador(cajaColision);
}

// Método de animación (actualmente comentado/deshabilitado)
void Semilla::animacion(int cuadros, int ms, int inicioX, int inicioY) {
    // Animación deshabilitada para mantener semilla estática
}

// Actualizar semilla (sin animación activa)
void Semilla::actualizar() {
    // Sin lógica de actualización activa
}

// Dibujar semilla en la ventana
void Semilla::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteSemilla);
}