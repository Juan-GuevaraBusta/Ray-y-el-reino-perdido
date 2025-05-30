#include "hormigaInfectada.h"
#include "gestorRecursos.h"
#include <cstdint>
#include <cmath>

/**
 * Constructor de la clase HormigaInfectada
 * Inicializa una hormiga enemiga con IA básica, física y sistema de combate
 */
HormigaInfectada::HormigaInfectada(int tipo, sf::Vector2f posicion, int daño, int salud) {
    // Inicializar estado base
    accion = Accion::NINGUNA;
    cuadro = 0;
    this->daño = daño;
    this->salud = salud;
    relojAnimacion.restart();
    relojAtaque.restart();

    // Configurar física (gravedad y velocidad)
    aceleracion.x = 1;
    aceleracion.y = 1;
    velocidad.x = 0;
    velocidad.y = 0;

    // Configurar IA y movimiento
    srand(static_cast<unsigned int>(time(nullptr)) + reinterpret_cast<uintptr_t>(this));
    velocidadMovimiento = 0.8f;
    velocidadPersecucion = 1.5f;
    direccionActual = 0;
    tiempoCambioDireccion = 0.0f;
    persiguiendoJugador = false;
    distanciaDeteccion = 120.0f;
    estaMuerta = false;
    puntosOtorgados = false;
    relojMovimiento.restart();
    relojCambioDireccion.restart();

    // Configurar caja de colisión
    cajaColision.setSize(sf::Vector2f(20, 18));
    cajaColision.setOrigin(sf::Vector2f(10, 9));
    cajaColision.setFillColor(sf::Color(255, 0, 255, 100));
    cajaColision.setPosition(posicion);

    // Cargar todas las texturas
    cargarTexturas();

    // Configurar sprite inicial según tipo de hormiga
    switch (tipo) {
        case 8:
            spriteHormigaInfectada.setTexture(*texturasIzquierda[0], true);
            desplazamientoCajaColision = -12;
            break;
        case 9:
            spriteHormigaInfectada.setTexture(*texturasDerecha[0], true);
            desplazamientoCajaColision = 12;
            break;
        default:
            spriteHormigaInfectada.setTexture(*texturasIzquierda[0], true);
            desplazamientoCajaColision = 0;
            break;
    }

    // Configurar propiedades del sprite
    spriteHormigaInfectada.setOrigin(ORIGEN_HORMIGA_INFECTADA);
    spriteHormigaInfectada.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), TAMAÑO_CUADRO_HORMIGA_INFECTADA));
    spriteHormigaInfectada.setPosition(cajaColision.getPosition().x, cajaColision.getPosition().y);
}

HormigaInfectada::~HormigaInfectada() {
}

/**
 * Establece la acción actual de la hormiga
 */
void HormigaInfectada::setAccion(Accion accion) {
    this->accion = accion;
}

/**
 * Obtiene la acción actual de la hormiga
 */
Accion HormigaInfectada::getAccion() {
    return accion;
}

/**
 * Obtiene los puntos de salud actuales
 */
int HormigaInfectada::getSalud() {
    return salud;
}

/**
 * Modifica la salud de la hormiga y verifica si debe morir
 */
void HormigaInfectada::cambiarSalud(int valor) {
    salud += valor;

    // Verificar muerte
    if (salud <= 0 && !estaMuerta) {
        morir();
    }
}

/**
 * Realiza un ataque contra un enemigo
 */
void HormigaInfectada::atacar(Personaje* enemigo) {
    enemigo->cambiarSalud(-daño);
    relojAtaque.restart();
}

/**
 * Verifica si la hormiga puede atacar (cooldown completado)
 */
bool HormigaInfectada::puedeAtacar() {
    return relojAtaque.getElapsedTime() > sf::milliseconds(250);
}

/**
 * Obtiene la velocidad actual de movimiento
 */
sf::Vector2f HormigaInfectada::getVelocidad() {
    return velocidad;
}

/**
 * Establece la velocidad horizontal
 */
void HormigaInfectada::setVelocidadX(float velocidadX) {
    velocidad.x = velocidadX;
}

/**
 * Establece la velocidad vertical
 */
void HormigaInfectada::setVelocidadY(float velocidadY) {
    velocidad.y = velocidadY;
}

/**
 * Maneja la respuesta a colisiones, ajustando velocidad y dirección
 */
void HormigaInfectada::enColision(sf::Vector2f direccionColision) {
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
void HormigaInfectada::cambiarDireccion() {
    int nuevaDireccion = rand() % 3 - 1; // -1, 0, o 1
    direccionActual = nuevaDireccion;
    tiempoCambioDireccion = 1.0f + (rand() % 2000) / 1000.0f;
    relojCambioDireccion.restart();
}

/**
 * Implementa movimiento errático cuando no persigue al jugador
 */
void HormigaInfectada::moverErraticamente() {
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
 * Calcula la distancia euclidiana entre dos puntos
 */
float HormigaInfectada::calcularDistancia(sf::Vector2f pos1, sf::Vector2f pos2) {
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    return std::sqrt(dx * dx + dy * dy);
}

/**
 * Sistema de IA para detectar y perseguir al jugador
 */
void HormigaInfectada::detectarYPerseguirJugador(sf::Vector2f posicionJugador) {
    // Las hormigas muertas no persiguen
    if (estaMuerta) {
        velocidad.x = 0;
        setAccion(Accion::NINGUNA);
        return;
    }

    sf::Vector2f miPosicion = getPosicion();
    float distancia = calcularDistancia(miPosicion, posicionJugador);

    if (distancia <= distanciaDeteccion) {
        // Jugador detectado - iniciar persecución
        persiguiendoJugador = true;

        // Determinar dirección hacia el jugador
        if (posicionJugador.x > miPosicion.x) {
            velocidad.x = velocidadPersecucion;
            direccionActual = 1;
        } else if (posicionJugador.x < miPosicion.x) {
            velocidad.x = -velocidadPersecucion;
            direccionActual = -1;
        } else {
            velocidad.x = 0;
            direccionActual = 0;
        }

        setAccion(Accion::ATACANDO);
    } else {
        // Jugador fuera de rango - comportamiento normal
        persiguiendoJugador = false;
        moverErraticamente();
    }
}

/**
 * Carga todas las texturas necesarias para la hormiga
 */
void HormigaInfectada::cargarTexturas() {
    // Preparar vectores de texturas
    texturasIzquierda.resize(2);
    texturasDerecha.resize(2);

    // Cargar texturas de movimiento
    texturasIzquierda[0] = &GestorRecursos::getInstance()->obtenerTextura("hI_vivaizq1");
    texturasIzquierda[1] = &GestorRecursos::getInstance()->obtenerTextura("hI_vivaizq2");
    texturasDerecha[0] = &GestorRecursos::getInstance()->obtenerTextura("hI_vivader1");
    texturasDerecha[1] = &GestorRecursos::getInstance()->obtenerTextura("hI_vivader2");

    // Cargar texturas de muerte
    texturaMuertaIzq = &GestorRecursos::getInstance()->obtenerTextura("hI_muertaizq");
    texturaMuertaDer = &GestorRecursos::getInstance()->obtenerTextura("hI_muertader");
}

/**
 * Verifica si la hormiga está viva
 */
bool HormigaInfectada::estaViva() {
    return !estaMuerta && salud > 0;
}

/**
 * Ejecuta la muerte de la hormiga, deteniendo movimiento y persecución
 */
void HormigaInfectada::morir() {
    estaMuerta = true;
    velocidad.x = 0;
    velocidad.y = 0;
    persiguiendoJugador = false;
    setAccion(Accion::NINGUNA);
}

/**
 * Obtiene la posición actual de la hormiga
 */
sf::Vector2f HormigaInfectada::getPosicion() {
    return cajaColision.getPosition();
}

/**
 * Obtiene la mitad del tamaño para cálculos de colisión
 */
sf::Vector2f HormigaInfectada::getMitadTamaño() {
    return sf::Vector2f(10, 9);
}

/**
 * Obtiene el colisionador para detectar choques
 */
Colisionador HormigaInfectada::getColisionador() {
    return Colisionador(cajaColision);
}

/**
 * Sistema de animación (actualmente deshabilitado)
 */
void HormigaInfectada::animacion(int cuadros, int ms, int inicioX, int inicioY) {
    // Animación comentada para optimización
}

/**
 * Actualiza la física, animación y estado de la hormiga cada frame
 */
void HormigaInfectada::actualizar() {
    // Las hormigas muertas solo muestran textura de muerte
    if (estaMuerta) {
        static bool ultimaDireccionDerecha = false;

        if (ultimaDireccionDerecha) {
            spriteHormigaInfectada.setTexture(*texturaMuertaDer);
        } else {
            spriteHormigaInfectada.setTexture(*texturaMuertaIzq);
        }

        spriteHormigaInfectada.setPosition(cajaColision.getPosition().x, cajaColision.getPosition().y);
        return;
    }

    // Sistema de animación para hormigas vivas
    static int frameActual = 0;
    static bool ultimaDireccionDerecha = false;
    static sf::Clock relojFrame;

    // Cambiar frame cada 150ms
    if (relojFrame.getElapsedTime().asSeconds() >= 0.15f) {
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
        spriteHormigaInfectada.setTexture(*texturasDerecha[frameActual]);
    } else if (velocidad.x < 0) {
        spriteHormigaInfectada.setTexture(*texturasIzquierda[frameActual]);
    } else {
        if (ultimaDireccionDerecha) {
            spriteHormigaInfectada.setTexture(*texturasDerecha[frameActual]);
        } else {
            spriteHormigaInfectada.setTexture(*texturasIzquierda[frameActual]);
        }
    }

    // Aplicar gravedad y movimiento
    velocidad.y += aceleracion.y;
    cajaColision.move(velocidad);

    // Sincronizar sprite con caja de colisión
    spriteHormigaInfectada.setPosition(cajaColision.getPosition().x, cajaColision.getPosition().y);
}

/**
 * Verifica si la hormiga acaba de morir para otorgar puntos
 */
bool HormigaInfectada::acabaDeMorir() {
    if (salud <= 0 && estaMuerta && !puntosOtorgados) {
        puntosOtorgados = true;
        return true;
    }
    return false;
}

/**
 * Dibuja la hormiga en la ventana de juego
 */
void HormigaInfectada::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteHormigaInfectada);
}