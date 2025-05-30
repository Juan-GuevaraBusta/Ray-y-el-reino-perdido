#include "hormigaNPC.h"
#include "gestorRecursos.h"
#include <cstdint>
#include <cstdlib>
#include <ctime>

/**
 * Constructor de la clase HormigaNPC
 * Inicializa una hormiga NPC con movimiento errático y física básica
 */
HormigaNPC::HormigaNPC(int tipo, sf::Vector2f posicion) {
    // Inicializar estado base
    accion = Accion::NINGUNA;
    cuadro = 0;
    relojAnimacion.restart();

    // Configurar física (igual que el jugador)
    aceleracion.x = 1;
    aceleracion.y = 1;
    velocidad.x = 0;
    velocidad.y = 0;

    // Configurar movimiento errático
    srand(static_cast<unsigned int>(time(nullptr)) + reinterpret_cast<uintptr_t>(this));
    velocidadMovimiento = 0.5f;
    direccionActual = 0;
    tiempoCambioDireccion = 0.0f;
    relojMovimiento.restart();
    relojCambioDireccion.restart();

    // Configurar caja de colisión
    cajaColision.setSize(sf::Vector2f(20, 18));
    cajaColision.setOrigin(sf::Vector2f(10, 9));
    cajaColision.setFillColor(sf::Color(0, 255, 0, 100));
    cajaColision.setPosition(posicion);

    // Cargar texturas y configurar sprite
    cargarTexturas();
    spriteHormigaNPC.setTexture(texturasIzquierda[0], true);
    spriteHormigaNPC.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), TAMAÑO_CUADRO_HORMIGA_INFECTADA));
    spriteHormigaNPC.setOrigin(ORIGEN_HORMIGA_INFECTADA);
    spriteHormigaNPC.setPosition(cajaColision.getPosition().x, cajaColision.getPosition().y - 4);
}

HormigaNPC::~HormigaNPC() {
}

/**
 * Establece la acción actual de la hormiga NPC
 */
void HormigaNPC::setAccion(Accion accion) {
    this->accion = accion;
}

/**
 * Obtiene la acción actual de la hormiga NPC
 */
Accion HormigaNPC::getAccion() {
    return accion;
}

/**
 * Método de ataque vacío (las NPCs no atacan)
 */
void HormigaNPC::atacar(Personaje* enemigo) {
    // Las hormigas NPC no atacan
}

/**
 * Las NPCs nunca pueden atacar
 */
bool HormigaNPC::puedeAtacar() {
    return false;
}

/**
 * Las NPCs son inmortales - no reciben daño
 */
void HormigaNPC::cambiarSalud(int valor) {
    // No hace nada - inmortales
}

/**
 * Retorna salud alta para indicar inmortalidad
 */
int HormigaNPC::getSalud() {
    return 999;
}

/**
 * Obtiene la velocidad actual de movimiento
 */
sf::Vector2f HormigaNPC::getVelocidad() {
    return velocidad;
}

/**
 * Establece la velocidad horizontal
 */
void HormigaNPC::setVelocidadX(float velocidadX) {
    velocidad.x = velocidadX;
}

/**
 * Establece la velocidad vertical
 */
void HormigaNPC::setVelocidadY(float velocidadY) {
    velocidad.y = velocidadY;
}

/**
 * Maneja la respuesta a colisiones, cambiando dirección al chocar con paredes
 */
void HormigaNPC::enColision(sf::Vector2f direccionColision) {
    if (direccionColision.x < 0.0f) {
        velocidad.x = 0.0f;
        if (direccionActual == -1) {
            direccionActual = 1;
            relojCambioDireccion.restart();
        }
    } else if (direccionColision.x > 0.0f) {
        velocidad.x = 0.0f;
        if (direccionActual == 1) {
            direccionActual = -1;
            relojCambioDireccion.restart();
        }
    }

    if (direccionColision.y > 0.0f) {
        velocidad.y = 0.0f;
    } else if (direccionColision.y < 0.0f) {
        velocidad.y = 0.0f;
    }
}

/**
 * Cambia aleatoriamente la dirección de movimiento
 */
void HormigaNPC::cambiarDireccion() {
    int nuevaDireccion = rand() % 3 - 1; // -1, 0, o 1
    direccionActual = nuevaDireccion;
    tiempoCambioDireccion = 1.0f + (rand() % 3000) / 1000.0f;
    relojCambioDireccion.restart();
}

/**
 * Implementa movimiento errático aleatorio
 */
void HormigaNPC::moverErraticamente() {
    // Cambiar dirección periódicamente
    if (relojCambioDireccion.getElapsedTime().asSeconds() >= tiempoCambioDireccion) {
        cambiarDireccion();
    }

    // Aplicar movimiento según dirección
    switch(direccionActual) {
        case -1: // Izquierda
            velocidad.x = -velocidadMovimiento;
            setAccion(Accion::CAMINANDO);
            break;
        case 1: // Derecha
            velocidad.x = velocidadMovimiento;
            setAccion(Accion::CAMINANDO);
            break;
        case 0: // Quieto
        default:
            velocidad.x = 0;
            setAccion(Accion::NINGUNA);
            break;
    }
}

/**
 * Carga todas las texturas necesarias para la hormiga NPC
 */
void HormigaNPC::cargarTexturas() {
    // Preparar vectores de texturas
    texturasIzquierda.resize(2);
    texturasDerecha.resize(2);

    // Cargar texturas de movimiento
    texturasIzquierda[0] = GestorRecursos::getInstance()->obtenerTextura("hN_izq1");
    texturasIzquierda[1] = GestorRecursos::getInstance()->obtenerTextura("hN_izq2");
    texturasDerecha[0] = GestorRecursos::getInstance()->obtenerTextura("hN_der1");
    texturasDerecha[1] = GestorRecursos::getInstance()->obtenerTextura("hN_der2");
}

/**
 * Obtiene la posición actual de la hormiga NPC
 */
sf::Vector2f HormigaNPC::getPosicion() {
    return cajaColision.getPosition();
}

/**
 * Obtiene la mitad del tamaño para cálculos de colisión
 */
sf::Vector2f HormigaNPC::getMitadTamaño() {
    return sf::Vector2f(10, 9);
}

/**
 * Obtiene el colisionador para detectar choques
 */
Colisionador HormigaNPC::getColisionador() {
    return Colisionador(cajaColision);
}

/**
 * Sistema de animación (actualmente deshabilitado)
 */
void HormigaNPC::animacion(int cuadros, int ms, int inicioX, int inicioY) {
    // Animación comentada para optimización
}

/**
 * Actualiza la física, movimiento y animación de la hormiga NPC cada frame
 */
void HormigaNPC::actualizar() {
    // Aplicar movimiento errático
    moverErraticamente();

    // Sistema de animación
    static int frameActual = 0;
    static bool ultimaDireccionDerecha = false;
    static sf::Clock relojFrame;

    // Cambiar frame cada 200ms
    if (relojFrame.getElapsedTime().asSeconds() >= 0.2f) {
        frameActual = (frameActual + 1) % 2;
        relojFrame.restart();
    }

    // Recordar dirección para texturas
    if (velocidad.x > 0) {
        ultimaDireccionDerecha = true;
    } else if (velocidad.x < 0) {
        ultimaDireccionDerecha = false;
    }

    // Aplicar texturas según movimiento
    if (velocidad.x > 0) {
        spriteHormigaNPC.setTexture(texturasDerecha[frameActual]);
    } else if (velocidad.x < 0) {
        spriteHormigaNPC.setTexture(texturasIzquierda[frameActual]);
    } else {
        if (ultimaDireccionDerecha) {
            spriteHormigaNPC.setTexture(texturasDerecha[frameActual]);
        } else {
            spriteHormigaNPC.setTexture(texturasIzquierda[frameActual]);
        }
    }

    // Aplicar gravedad y movimiento
    velocidad.y += aceleracion.y;
    cajaColision.move(velocidad);

    // Sincronizar sprite con caja de colisión
    spriteHormigaNPC.setPosition(cajaColision.getPosition().x, cajaColision.getPosition().y - 4);
}

/**
 * Dibuja la hormiga NPC en la ventana de juego
 */
void HormigaNPC::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteHormigaNPC);
}