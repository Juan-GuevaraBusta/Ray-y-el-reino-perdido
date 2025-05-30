/*
La clase Juego representa el motor principal de Ray y el Reino Perdido que coordina toda la lógica
del gameplay. Se encarga de ejecutar el bucle principal del juego, gestionar la carga y transición entre
niveles del hormiguero, coordinar las interacciones entre Ray y todos los personajes del mundo,
manejar el sistema de colisiones entre personajes y objetos, procesar la recolección de objetos y el sistema
de puntuación, controlar el flujo de audio con música específica por nivel, y determinar las condiciones de
victoria y derrota del jugador. La clase Juego integra todos los subsistemas del juego incluyendo física,
audio, gráficos y persistencia de datos para crear la experiencia completa de gameplay.
*/


#ifndef JUEGO_H
#define JUEGO_H

#include "interfazUsuario.h"
#include "jugador.h"
#include "ventana.h"
#include "mundo.h"
#include "gestorNombres.h"
#include <cstdint>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Juego
{
private:
    Ventana ventana; // Ventana principal del juego
    sf::Clock reloj; // Reloj para controlar FPS
    float tiempoTranscurrido; // Tiempo acumulado
    bool pausado; // Estado de pausa
    bool reiniciado; // Control de reinicio
    bool juegoGanado; // Estado de victoria

    unsigned int mundoActual; // Índice del mundo actual
    std::vector<Mundo> mundos; // Todos los mundos del juego
    Jugador jugador; // Jugador principal
    InterfazUsuario interfaz; // Interfaz de usuario

    GestorNombres* gestorNombres; // Gestor de puntajes y nombres

    // Cambia la música según el nivel actual
    void cambiarMusicaNivel(int nivel);

public:
    // Constructor y destructor
    Juego();
    ~Juego();

    // Ejecuta el bucle principal del juego
    void ejecutar();

    // Carga todos los niveles desde archivos
    void cargarNiveles();

    // Actualiza la lógica del juego
    void actualizar();

    // Dibuja todos los elementos en pantalla
    void dibujar();

    // Verifica si el jugador perdió
    bool jugadorPerdio();

    // Verifica si el jugador ganó
    bool jugadorGano();

    // Obtiene referencia a la ventana
    Ventana* getVentana();

    // Establece el gestor de nombres y lo conecta a la interfaz
    void setGestorNombres(GestorNombres* gestor) {
        gestorNombres = gestor;
        interfaz.setGestorNombres(gestor);
    }

    // Reinicia completamente el juego
    void reiniciarCompleto() {
        // Limpiar mundos
        mundos.clear();

        // Resetear variables
        juegoGanado = false;
        mundoActual = 0;
        reiniciado = false;

        // Recargar niveles
        cargarNiveles();

        // Reiniciar jugador
        jugador.reiniciarJuego();

        // Establecer posición inicial
        jugador.setPosicion(mundos[mundoActual].posicionInicialJugador);

        // Reiniciar música
        cambiarMusicaNivel(mundoActual);
    }
};

#endif