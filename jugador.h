/*
La clase Jugador implementa a Ray, el protagonista de Ray y el Reino Perdido, heredando de la clase Personaje.
Gestiona el sistema de salud visual con tres estados (Ray Sano, Ray Herido, Ray Sin Casco), los controles de
movimiento y salto, el sistema de combate con bastón luminoso, la recolección de luz y el manejo de puntuación.
La clase Jugador integra la física de movimiento con gravedad, el sistema de colisiones, la carga y actualización
de texturas según el estado de salud, y la reproducción de efectos de sonido para las acciones de Ray.
*/


#ifndef JUGADOR_H
#define JUGADOR_H

#include "colisionador.h"
#include "personaje.h"
#include "configuracion.h"
#include "mundo.h"
#include <cstdint>

#include <SFML/Graphics.hpp>
#include <string>

class Jugador : public Personaje
{
private:
    // Atributos
    Accion accion; // Acción actual del jugador
    sf::RectangleShape cajaColision; // Caja de colisión del jugador

    sf::Vector2f posicionInicial; // Posición inicial al cargar el nivel
    sf::Vector2f velocidad; // Velocidad actual de movimiento
    sf::Vector2f aceleracion; // Aceleración (gravedad)
    float velocidadSalto; // Velocidad inicial del salto
    int velocidadMaxima; // Velocidad máxima de movimiento horizontal
    bool puedeSaltar; // Control para evitar saltos múltiples
    float velocidadCaida; // Velocidad máxima de caída

    bool potenciador; // Estado de potenciador activo
    bool perdio; // Indicador de derrota
    int daño; // Daño que causa al atacar
    int salud; // Puntos de vida actuales
    int puntuacion; // Puntuación del jugador
    int luz; // Contador de luz recolectada
    sf::Clock relojAtaque; // Control de tiempo entre ataques

    short int cuadro; // Frame actual de animación
    sf::Clock relojAnimacion; // Control de tiempo de animación
    bool animacionMuerteMostrada; // Control para mostrar animación de muerte
    sf::Sprite spriteJugador; // Sprite visual del jugador

    // Texturas para diferentes estados de salud y direcciones
    std::vector<sf::Texture> texturasSanoFrontal; // Texturas frontales con salud completa
    std::vector<sf::Texture> texturasSanoDerecha; // Texturas derecha con salud completa
    std::vector<sf::Texture> texturasSanoIzquierda; // Texturas izquierda con salud completa
    std::vector<sf::Texture> texturasHeridoFrontal; // Texturas frontales herido
    std::vector<sf::Texture> texturasHeridoDerecha; // Texturas derecha herido
    std::vector<sf::Texture> texturasHeridoIzquierda; // Texturas izquierda herido
    std::vector<sf::Texture> texturasSinCascoFrontal; // Texturas frontales sin casco
    std::vector<sf::Texture> texturasSinCascoDerecha; // Texturas derecha sin casco
    std::vector<sf::Texture> texturasSinCascoIzquierda; // Texturas izquierda sin casco
    std::vector<sf::Texture> texturasAtaqueSano; // Texturas de ataque sano
    std::vector<sf::Texture> texturasAtaqueHerido; // Texturas de ataque herido
    std::vector<sf::Texture> texturasAtaqueSinCasco; // Texturas de ataque sin casco
    sf::Texture texturaMuerto; // Textura cuando está muerto

public:
    // Atributos públicos (accesibles para manejo de colisiones)
    sf::Vector2f direccionColision; // Dirección de la colisión detectada

    // Constructor
    Jugador(std::string nombreArchivo);

    // Setters
    void setPosicion(sf::Vector2f posicion);
    void setAccion(Accion accion);
    void setVelocidadX(float velocidadX);
    void setVelocidadY(float velocidadY);
    void setLuz(int luz);

    // Modificadores de estado
    void cambiarSalud(int valor);
    void cambiarPuntuacion(int valor);
    void cambiarLuz(int valor);

    // Getters
    sf::Vector2f getVelocidad();
    Accion getAccion();
    int getSalud();
    int getPuntuacion();
    int getLuz();

    // Sistema de combate
    void atacar(Personaje* enemigo);
    bool puedeAtacar();

    // Sistema de posición y colisiones
    sf::Vector2f getPosicion();
    sf::Vector2f getMitadTamaño();
    Colisionador getColisionador();
    void enColision(sf::Vector2f direccionColision);

    // Control de estado del juego
    bool haPerdido();
    void perder();

    // Control de vida del juego
    void finJuego();
    void reiniciarJuego();

    // Sistema de gráficos y animación
    void cargarTexturas();
    void actualizarTextura();
    void animacion(int cuadros, int ms, int inicioX, int inicioY);
    void actualizar();
    void dibujar(sf::RenderWindow& ventana);
};

#endif // JUGADOR_H