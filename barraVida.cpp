#include "barraVida.h"
#include <cstdint>
#include "gestorRecursos.h"
#include "configuracion.h"

/**
 * Constructor de la clase BarraVida
 * Inicializa una barra de vida en una posición específica usando una textura de semilla
 * NOTA: Implementación simplificada que solo usa textura de semilla para representar vida
 * @param posicion - Referencia constante al Vector2f que indica dónde posicionar la barra
 * @param tipo - Tipo de barra (parámetro mantenido por compatibilidad, solo se usa VIDA)
 */
BarraVida::BarraVida(const sf::Vector2f& posicion, TipoBarra tipo) {
    // Asigna la textura de semilla al sprite de vida usando el gestor de recursos
    spriteVida.setTexture(GestorRecursos::getInstance()->obtenerTextura("semilla"), true);

    // Configura el rectángulo de textura usando el tamaño definido para semillas
    spriteVida.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), TAMAÑO_CUADRO_SEMILLA));

    // Escala el sprite a un tamaño más pequeño (12.5% del tamaño original)
    spriteVida.scale(0.125f, 0.125f);

    // Posiciona el sprite en las coordenadas especificadas
    spriteVida.setPosition(posicion);
}

/**
 * Función que dibuja la barra de vida en la ventana de renderizado
 * Renderiza el sprite de vida en la ventana proporcionada
 * @param ventana - Referencia a la ventana donde se dibujará la barra de vida
 */
void BarraVida::dibujar(sf::RenderWindow& ventana) {
    // Dibuja el sprite de vida en la ventana
    ventana.draw(spriteVida);
}