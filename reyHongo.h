/*
La clase ReyHongo implementa al jefe final de Ray y el Reino Perdido, heredando de la clase Personaje.
Representa la amenaza principal que Ray debe derrotar para completar el juego. La clase ReyHongo gestiona
un sistema de salud de 10 puntos, detectar y persegue a Ray, movimiento errático cuando Ray no está cerca, sistema de
combate que inflige 1 punto de daño, y texturas animadas que cambian entre estados vivo, atacando y muerto.
Incluye física de movimiento con gravedad y colisiones similar a otros personajes pero con mayor resistencia y
comportamiento más agresivo.
*/

#ifndef REYHONGO_H
#define REYHONGO_H

#include "colisionador.h"
#include "personaje.h"
#include "configuracion.h"
#include <cstdint>

#include <SFML/Graphics.hpp>

class ReyHongo : public Personaje {
private:
    sf::RectangleShape cajaColision;           // Caja de colisión del rey hongo
    int desplazamientoCajaColision;            // Desplazamiento de la caja de colisión
    Accion accion;                             // Acción actual del rey hongo
    int salud;                                 // Puntos de vida del rey hongo
    int daño;                                  // Daño que inflige al atacar
    bool estaMuerto;                           // Estado de muerte del rey hongo

    sf::Vector2f velocidad;                    // Velocidad de movimiento
    sf::Vector2f aceleracion;                  // Aceleración (gravedad)

    short int cuadro;                          // Cuadro actual de animación
    sf::Clock relojAnimacion;                  // Reloj para animaciones
    sf::Sprite spriteReyHongo;                 // Sprite del rey hongo

    // Vectores de texturas para diferentes estados
    std::vector<sf::Texture*> texturasFrontal;         // Texturas frontales
    std::vector<sf::Texture*> texturasIzquierda;       // Texturas laterales
    std::vector<sf::Texture*> texturasAtaque;          // Texturas de ataque
    std::vector<sf::Texture*> texturasMuerteFrontal;   // Texturas de muerte frontal
    std::vector<sf::Texture*> texturasMuerteIzquierda; // Texturas de muerte lateral

public:
    sf::Clock relojAtaque;                     // Reloj para controlar ataques
    sf::Vector2f direccionColision;            // Dirección de colisión

    // Constructor con posición, daño y salud
    ReyHongo(sf::Vector2f posicion, int daño, int salud);
    ~ReyHongo();

    // Gestión de acciones
    void setAccion(Accion accion);
    Accion getAccion();

    // Gestión de salud
    int getSalud();
    void cambiarSalud(int valor);

    // Sistema de ataque
    void atacar(Personaje* enemigo);
    bool puedeAtacar();

    // Sistema de física
    sf::Vector2f getVelocidad();
    void setVelocidadX(float velocidadX);
    void setVelocidadY(float velocidadY);
    void enColision(sf::Vector2f direccionColision);

    // Sistema de muerte
    bool estaVivo();
    void morir();

    // Getters de posición y colisión
    sf::Vector2f getPosicion();
    sf::Vector2f getMitadTamaño();
    Colisionador getColisionador();

    // Sistema de texturas
    void cargarTexturas();
    void actualizarTextura();

    // Sistema de animación (legacy)
    void animacion(int cuadros, int ms, int inicioX, int inicioY);

    // Actualizar rey hongo
    void actualizar();
    // Dibujar rey hongo
    void dibujar(sf::RenderWindow& ventana);
};

#endif // REYHONGO_H