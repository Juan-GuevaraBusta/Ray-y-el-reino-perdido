#include "ventana.h"
#include "configuracion.h"
#include <cstdint>

// Constructor por defecto: crear ventana con valores predeterminados
Ventana::Ventana() {
    configurar("Ventana", sf::Vector2u(ANCHO_VENTANA, ALTO_VENTANA));
}

// Constructor con parámetros: crear ventana con título y tamaño específicos
Ventana::Ventana(const std::string& titulo, const sf::Vector2u& tamaño) {
    configurar(titulo, tamaño);
}

// Destructor: limpiar recursos
Ventana::~Ventana() {
    destruir();
}

// Configurar parámetros iniciales de la ventana
void Ventana::configurar(const std::string& titulo, const sf::Vector2u& tamaño) {
    terminada = false;
    pantallaCompleta = false;
    enfocada = true;
    pausada = false;
    tituloVentana = titulo;
    tamañoVentana = tamaño;
    sincVertical = true;
    crear();
}

// Crear la ventana SFML con la configuración actual
void Ventana::crear() {
    auto estilo = (pantallaCompleta ? sf::Style::Fullscreen : sf::Style::Default);
    ventanaSFML.create({tamañoVentana.x, tamañoVentana.y, 32}, tituloVentana, estilo);
    ventanaSFML.setVerticalSyncEnabled(false);
}

// Destruir la ventana SFML
void Ventana::destruir() {
    ventanaSFML.close();
}

// Actualizar ventana y procesar eventos
void Ventana::actualizar() {
    sf::Event evento;
    while (ventanaSFML.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            terminada = true;
        } else if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
            terminada = true;
        } else if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::F) {
            togglePantallaCompleta();
        } else if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::P) {
            togglePausado();
        } else if (evento.type == sf::Event::LostFocus) {
            enfocada = false;
        } else if (evento.type == sf::Event::GainedFocus) {
            enfocada = true;
        }
    }
}

// Alternar entre pantalla completa y ventana
void Ventana::togglePantallaCompleta() {
    pantallaCompleta = !pantallaCompleta;
    destruir();
    crear();
}

// Alternar estado de pausa
void Ventana::togglePausado() {
    pausada = !pausada;
}

// Iniciar el proceso de dibujado limpiando la ventana
void Ventana::iniciarDibujo() {
    ventanaSFML.clear(sf::Color::Black);
}

// Finalizar el proceso de dibujado mostrando los cambios
void Ventana::finalizarDibujo() {
    ventanaSFML.display();
}

// Dibujar un objeto en la ventana
void Ventana::dibujar(sf::Drawable& dibujable) {
    ventanaSFML.draw(dibujable);
}