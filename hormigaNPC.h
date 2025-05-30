/*
La clase HormigaNPC implementa a las hormigas normales de Ray y el Reino Perdido, heredando de la clase Personaje.
Representa la vida normal del hormiguero con hormigas que se mueven de forma errática pero pacífica por los túneles.
La clase HormigaNPC no puede atacar a Ray ni a otros personajes, sirviendo como elementos de ambientación.
Gestiona movimiento aleatorio con cambios de dirección impredecibles, física de movimiento
con gravedad similar a otros personajes, texturas animadas para direcciones izquierda y derecha, y colisiones físicas
que detienen el movimiento pero no causan daño. Los métodos de combate están implementados como vacíos ya que
estas hormigas nunca participan en combate.
*/

#ifndef HORMIGANNPC_H
#define HORMIGANNPC_H

#include "colisionador.h"
#include "personaje.h"
#include "configuracion.h"
#include <cstdint>

#include <SFML/Graphics.hpp>

class HormigaNPC : public Personaje {
private:
    sf::RectangleShape cajaColision; // Caja para detectar colisiones
    int desplazamientoCajaColision; // Offset de la caja de colisión
    Accion accion; // Acción actual de la hormiga

    sf::Vector2f velocidad; // Velocidad actual de movimiento
    sf::Vector2f aceleracion; // Aceleración aplicada (gravedad)

    sf::Clock relojMovimiento; // Control de tiempo para movimiento
    sf::Clock relojCambioDireccion; // Control de tiempo para cambios de dirección
    float velocidadMovimiento; // Velocidad base de movimiento
    int direccionActual; // Dirección actual (-1 izq, 0 quieto, 1 der)
    float tiempoCambioDireccion; // Tiempo hasta próximo cambio de dirección

    short int cuadro; // Frame actual de animación
    sf::Clock relojAnimacion; // Control de tiempo para animación
    sf::Sprite spriteHormigaNPC; // Sprite visual

    std::vector<sf::Texture> texturasIzquierda; // Texturas para caminar izquierda
    std::vector<sf::Texture> texturasDerecha; // Texturas para caminar derecha

public:
    sf::Vector2f direccionColision; // Dirección de última colisión

    // Constructor
    HormigaNPC(int tipo, sf::Vector2f posicion);
    ~HormigaNPC();

    // Manejo de acciones
    void setAccion(Accion accion);
    Accion getAccion();

    // Métodos virtuales heredados (vacíos para NPCs pacíficos)
    void atacar(Personaje* enemigo) override;
    bool puedeAtacar() override;

    // Métodos de salud (inmortales)
    void cambiarSalud(int valor) override;
    int getSalud() override;

    // Sistema de física
    sf::Vector2f getVelocidad();
    void setVelocidadX(float velocidadX);
    void setVelocidadY(float velocidadY);
    void enColision(sf::Vector2f direccionColision);

    // IA de movimiento errático
    void cambiarDireccion();
    void moverErraticamente();

    // Recursos y renderizado
    void cargarTexturas();
    sf::Vector2f getPosicion();
    sf::Vector2f getMitadTamaño();
    Colisionador getColisionador();
    void animacion(int cuadros, int ms, int inicioX, int inicioY);
    void actualizar();
    void dibujar(sf::RenderWindow& ventana);
};

#endif // HORMIGANNPC_H