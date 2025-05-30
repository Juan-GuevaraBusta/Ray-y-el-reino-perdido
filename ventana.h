/*
La clase Ventana maneja la funcionalidad de la ventana del juego usando
la librería SFML. Se encarga de crear y configurar la ventana, procesar eventos del sistema operativo como el
cierre de ventana y teclas especiales, y controlar estados como pantalla completa, pausa y enfoque. Proporciona
métodos para inicializar el dibujado, mostrar objetos en pantalla y finalizar cada frame. Incluye
funcionalidades para alternar entre modo ventana y pantalla completa, así como pausar el juego cuando sea necesario.
*/

#ifndef VENTANA_H
#define VENTANA_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <cstdint>

class Ventana {
private:
    bool terminada;                      // Estado de finalización del juego
    bool pantallaCompleta;               // Estado de pantalla completa
    bool sincVertical;                   // Sincronización vertical
    bool pausada;                        // Estado de pausa
    bool enfocada;                       // Estado de enfoque de la ventana
    std::string tituloVentana;           // Título de la ventana
    sf::Vector2u tamañoVentana;          // Tamaño de la ventana
    sf::RenderWindow ventanaSFML;        // Ventana de SFML

    // Configurar parámetros de la ventana
    void configurar(const std::string& titulo, const sf::Vector2u& tamaño);
    // Crear la ventana SFML
    void crear();
    // Destruir la ventana SFML
    void destruir();

public:
    // Constructores
    Ventana();
    Ventana(const std::string& titulo, const sf::Vector2u& tamaño);
    ~Ventana();

    // Gestión de dibujado
    void iniciarDibujo();
    void finalizarDibujo();
    void actualizar();

    // Getters de estado
    bool terminado() { return terminada; }
    bool pausado() { return pausada; }
    bool enfocado() { return enfocada; }
    bool esPantallaCompleta() { return pantallaCompleta; }
    sf::Vector2u getTamañoVentana() { return tamañoVentana; }
    sf::RenderWindow* getVentanaRender() { return &ventanaSFML; }

    // Controles de estado
    void togglePantallaCompleta();
    void togglePausado();
    void dibujar(sf::Drawable& dibujable);
};

#endif // VENTANA_H