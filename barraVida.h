/*
La clase BarraVida representa los indicadores visuales de salud de Ray en la interfaz de usuario
de Ray y el Reino Perdido. Se encarga de mostrar la luz y la vida en la parte inferior de la pantalla, proporcionando
feedback visual inmediato del estado de salud del personaje. La clase BarraVida utiliza la misma textura de las
semillas coleccionables pero escalada a menor tamaño para el HUD, creando consistencia visual entre los
elementos del juego y la interfaz de usuario.
*/

#pragma once
#include <cstdint>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

// Enumeración para el tipo de barra
enum class TipoBarra {
    VIDA,
    LUZ
};

class BarraVida {
private:
    sf::Sprite spriteVida; // Sprite que representa visualmente la barra de vida

public:
    // Constructor que inicializa la barra de vida
    BarraVida(const sf::Vector2f& posicion, TipoBarra tipo = TipoBarra::VIDA);
    // Dibuja la barra de vida en la ventana
    void dibujar(sf::RenderWindow& ventana);
};