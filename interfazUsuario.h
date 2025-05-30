/*
La clase InterfazUsuario gestiona el HUD (Head-Up Display) de Ray y el Reino Perdido mostrando información
crítica del gameplay en tiempo real. Se encarga de mostrar la salud actual de Ray mediante semillas visuales
que aparecen y desaparecen según el daño recibido, el puntaje actual del jugador que aumenta al recolectar
luz y eliminar enemigos, el récord personal del jugador almacenado localmente, y el contador de luz recolectada
que Ray puede usar para ataques especiales. La clase InterfazUsuario mantiene una referencia al jugador para
acceder a sus estadísticas, actualiza automáticamente las barras de vida agregando o quitando semillas según
cambios de salud, y proporciona un fondo semi-transparente en la parte inferior de la pantalla para mejorar
la legibilidad de la información mostrada.
*/

#ifndef INTERFAZ_USUARIO_H
#define INTERFAZ_USUARIO_H

#include "barraVida.h"
#include "jugador.h"
#include "configuracion.h"
#include "gestorNombres.h"
#include <cstdint>

#include <SFML/Graphics.hpp>
#include <list>

class InterfazUsuario
{
private:
    // Atributos
    Jugador* jugador; // Referencia al jugador actual
    GestorNombres* gestorNombres; // Gestor para manejar puntajes y nombres

    sf::Vector2f posicionSalud; // Posición base para las barras de vida
    sf::Text textoPuntuacion; // Texto que muestra la puntuación actual
    sf::Text textoPuntuacionRecord; // Texto que muestra el récord
    sf::Text textoLuz; // Texto que muestra la cantidad de luz
    sf::Text textoVidasExtra; // Texto para vidas adicionales (+5)

    sf::RectangleShape fondoEstado; // Fondo de la barra de estado

public:
    // Atributos públicos
    std::list<BarraVida> salud; // Lista de barras de vida visibles

    // Constructor
    InterfazUsuario(Jugador* jugador);

    // Actualiza la información de la interfaz
    void actualizar();

    // Dibuja todos los elementos de la interfaz
    void dibujar(sf::RenderWindow& ventana);

    // Establece el gestor de nombres para obtener récords
    void setGestorNombres(GestorNombres* gestor) {
        gestorNombres = gestor;
    }

    // Obtiene el máximo puntaje del archivo JSON
    int obtenerMaximoPuntaje();

    // Agrega una barra de vida visual (máximo 5), si tiene mas de 5 vidas se agregará el símbolo +
    void agregarVidaSprite() {
        if (salud.size() < 5) {
            salud.push_back(BarraVida(sf::Vector2f(posicionSalud.x + salud.size() * 40, posicionSalud.y), TipoBarra::VIDA));
        }
    }
};

#endif