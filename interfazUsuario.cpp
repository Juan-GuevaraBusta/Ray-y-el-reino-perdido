#include "interfazUsuario.h"
#include "gestorRecursos.h"
#include <cstdint>
#include <algorithm>

// Constructor: inicializa la interfaz de usuario con referencias al jugador
InterfazUsuario::InterfazUsuario(Jugador* jugador) : jugador(jugador) {
    gestorNombres = nullptr; // Inicializar gestor como nullptr

    // Configurar posición para los indicadores de salud
    posicionSalud.x = 40;
    posicionSalud.y = 686;

    // Configurar fondo de la barra de estado
    fondoEstado.setSize(sf::Vector2f(ANCHO_VENTANA, 60));
    fondoEstado.setPosition(0, ALTO_VENTANA - 40);
    fondoEstado.setFillColor(sf::Color(20, 20, 20, 200));

    // Configurar texto de puntuación
    textoPuntuacion.setFont(GestorRecursos::getInstance()->obtenerFuente("interfaz"));
    textoPuntuacion.setCharacterSize(24);
    textoPuntuacion.setFillColor(sf::Color(255, 255, 255));
    textoPuntuacion.setPosition(640, 686);

    // Configurar texto de récord
    textoPuntuacionRecord.setFont(GestorRecursos::getInstance()->obtenerFuente("interfaz"));
    textoPuntuacionRecord.setCharacterSize(24);
    textoPuntuacionRecord.setFillColor(sf::Color(255, 255, 255));
    textoPuntuacionRecord.setPosition(960, 686);

    // Configurar texto de luz
    textoLuz.setFont(GestorRecursos::getInstance()->obtenerFuente("interfaz"));
    textoLuz.setCharacterSize(24);
    textoLuz.setFillColor(sf::Color(255, 255, 0));
    textoLuz.setPosition(460, 686);

    // Configurar texto para vidas extra
    textoVidasExtra.setFont(GestorRecursos::getInstance()->obtenerFuente("interfaz"));
    textoVidasExtra.setCharacterSize(20);
    textoVidasExtra.setFillColor(sf::Color(255, 100, 100));
    textoVidasExtra.setPosition(240, 690);
}

// Obtiene el máximo puntaje almacenado en el archivo JSON
int InterfazUsuario::obtenerMaximoPuntaje() {
    if (gestorNombres == nullptr) {
        return 0;
    }

    try {
        // Obtener el top 10 de puntajes
        std::vector<DatosJugador> top10 = gestorNombres->obtenerTop10();

        if (top10.empty()) {
            return 0;
        }

        // Retornar el puntaje más alto (primer elemento)
        return top10[0].puntaje;

    } catch (const std::exception& e) {
        return 0;
    }
}

// Actualiza todos los elementos de la interfaz con la información actual del jugador
void InterfazUsuario::actualizar() {
    // Actualizar texto de puntuación actual
    textoPuntuacion.setString("Puntuacion: " + std::to_string(jugador->getPuntuacion()));

    // Actualizar texto de récord usando el máximo puntaje del JSON
    int recordActual = obtenerMaximoPuntaje();
    textoPuntuacionRecord.setString("Record: " + std::to_string(recordActual));

    // Actualizar texto de luz
    textoLuz.setString("Luz: " + std::to_string(jugador->getLuz()));

    // Ajustar barras de vida visibles según la salud actual
    // Quitar sprites si la salud bajó
    while (salud.size() > std::min(jugador->getSalud(), 5)) {
        salud.pop_back();
    }

    // Agregar sprites si faltan
    while (salud.size() < std::min(jugador->getSalud(), 5)) {
        salud.push_back(BarraVida(sf::Vector2f(posicionSalud.x + salud.size() * 40, posicionSalud.y), TipoBarra::VIDA));
    }

    // Mostrar contador de vidas extra si tiene más de 5
    if (jugador->getSalud() > 5) {
        textoVidasExtra.setString("+" + std::to_string(jugador->getSalud() - 5));
    } else {
        textoVidasExtra.setString("");
    }
}

// Dibuja todos los elementos de la interfaz en la ventana
void InterfazUsuario::dibujar(sf::RenderWindow& ventana) {
    // Dibujar fondo de la barra de estado
    ventana.draw(fondoEstado);

    // Dibujar todos los textos informativos
    ventana.draw(textoPuntuacion);
    ventana.draw(textoPuntuacionRecord);
    ventana.draw(textoLuz);
    ventana.draw(textoVidasExtra);

    // Dibujar todas las barras de vida visibles (máximo 5)
    for (BarraVida& barra : salud)
        barra.dibujar(ventana);
}