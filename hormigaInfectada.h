/*
La clase HormigaInfectada implementa a enemigos de Ray y el Reino Perdido, heredando de la clase Personaje.
Representa hormigas cubiertas de esporas del hongo que detectan y persiguen a Ray cuando está cerca. La clase HormigaInfectada
detecta a Ray en un rango de 3 cuadros, persecución activa con mayor velocidad, movimiento errático cuando Ray no está cerca,
sistema de combate que inflige 1 punto de daño, y dos variantes de salud (débiles con 2 puntos, fuertes con 4 puntos).
Incluye texturas animadas que cambian entre estados vivo y muerto, física de movimiento con gravedad y sistema de
colisiones para interactuar con el entorno del hormiguero.
*/

#ifndef HORMIGAINFECTADA_H
#define HORMIGAINFECTADA_H

#include "colisionador.h"
#include "personaje.h"
#include "configuracion.h"
#include <cstdint>
#include <vector>

#include <SFML/Graphics.hpp>

class HormigaInfectada : public Personaje {
private:
    sf::RectangleShape cajaColision; // Caja para detectar colisiones
    int desplazamientoCajaColision; // Offset de la caja de colisión
    Accion accion; // Acción actual de la hormiga
    int salud; // Puntos de vida
    int daño; // Daño que inflige

    sf::Vector2f velocidad; // Velocidad actual de movimiento
    sf::Vector2f aceleracion; // Aceleración aplicada (gravedad)

    sf::Clock relojMovimiento; // Control de tiempo para movimiento
    sf::Clock relojCambioDireccion; // Control de tiempo para cambios de dirección
    float velocidadMovimiento; // Velocidad base de movimiento
    int direccionActual; // Dirección actual (-1 izq, 0 quieto, 1 der)
    float tiempoCambioDireccion; // Tiempo hasta próximo cambio de dirección

    bool persiguiendoJugador; // Estado de persecución
    float distanciaDeteccion; // Distancia para detectar jugador
    float velocidadPersecucion; // Velocidad al perseguir
    bool estaMuerta; // Estado de vida
    bool puntosOtorgados; // Control para evitar dar puntos múltiples veces

    short int cuadro; // Frame actual de animación
    sf::Clock relojAnimacion; // Control de tiempo para animación
    sf::Sprite spriteHormigaInfectada; // Sprite visual

    std::vector<sf::Texture*> texturasIzquierda; // Texturas para caminar izquierda
    std::vector<sf::Texture*> texturasDerecha; // Texturas para caminar derecha
    sf::Texture* texturaMuertaIzq; // Textura muerte mirando izquierda
    sf::Texture* texturaMuertaDer; // Textura muerte mirando derecha

public:
    sf::Clock relojAtaque; // Control de tiempo entre ataques
    sf::Vector2f direccionColision; // Dirección de última colisión

    // Constructor
    HormigaInfectada(int tipo, sf::Vector2f posicion, int daño, int salud);
    ~HormigaInfectada();

    // Manejo de acciones y estado
    void setAccion(Accion accion);
    Accion getAccion();
    int getSalud();
    void cambiarSalud(int valor);

    // Sistema de combate
    void atacar(Personaje* enemigo);
    bool puedeAtacar();

    // Sistema de física
    sf::Vector2f getVelocidad();
    void setVelocidadX(float velocidadX);
    void setVelocidadY(float velocidadY);
    void enColision(sf::Vector2f direccionColision);

    // IA y movimiento
    void cambiarDireccion();
    void moverErraticamente();
    void detectarYPerseguirJugador(sf::Vector2f posicionJugador);
    float calcularDistancia(sf::Vector2f pos1, sf::Vector2f pos2);

    // Sistema de muerte
    bool estaViva();
    void morir();
    bool acabaDeMorir();

    // Recursos y renderizado
    void cargarTexturas();
    sf::Vector2f getPosicion();
    sf::Vector2f getMitadTamaño();
    Colisionador getColisionador();
    void animacion(int cuadros, int ms, int inicioX, int inicioY);
    void actualizar();
    void dibujar(sf::RenderWindow& ventana);
};

#endif