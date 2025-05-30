#include "bloque.h"
#include "gestorRecursos.h"
#include <cstdint>

/**
 * Constructor de la clase Bloque
 * Inicializa un bloque en una posición específica con un tipo de textura determinado
 * @param posicion - Vector2f que indica la posición del bloque en el mundo
 * @param tipoBloque - String que especifica qué tipo de textura usar para el bloque
 */
Bloque::Bloque(sf::Vector2f posicion, const std::string& tipoBloque) {
    // Asigna la textura del bloque usando el gestor de recursos
    // La textura se obtiene según el tipo de bloque especificado
    spriteBloque.setTexture(GestorRecursos::getInstance()->obtenerTextura(tipoBloque), true);

    // Configura el origen del sprite en el centro para facilitar rotaciones y posicionamiento
    spriteBloque.setOrigin(TAMAÑO_BLOQUE / 2, TAMAÑO_BLOQUE / 2);
    spriteBloque.setPosition(posicion);

    // Si necesitas escalar la imagen para que coincida con TAMAÑO_BLOQUE
    // spriteBloque.setScale(escalaX, escalaY);

    // Configura la caja de colisión como un rectángulo del tamaño del bloque
    cajaColision.setSize(sf::Vector2f(TAMAÑO_BLOQUE, TAMAÑO_BLOQUE));
    cajaColision.setOrigin(sf::Vector2f(TAMAÑO_BLOQUE / 2, TAMAÑO_BLOQUE / 2));
    cajaColision.setPosition(posicion);
    cajaColision.setFillColor(sf::Color::Transparent); // Invisible, solo para colisión
}

/**
 * Función que dibuja el bloque en la ventana de renderizado
 * Renderiza el sprite del bloque en la ventana proporcionada
 * @param ventana - Referencia a la ventana donde se dibujará el bloque
 */
void Bloque::dibujar(sf::RenderWindow& ventana) {
    // Dibuja el sprite del bloque en la ventana
    ventana.draw(spriteBloque);
}

/**
 * Función que retorna el colisionador asociado a este bloque
 * Crea y retorna un objeto Colisionador basado en la caja de colisión del bloque
 * @return Colisionador - Objeto que maneja las colisiones de este bloque
 */
Colisionador Bloque::getColisionador() {
    return Colisionador(cajaColision);
}