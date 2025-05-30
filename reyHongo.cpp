#include "reyHongo.h"
#include "gestorRecursos.h"
#include <cstdint>
#include <iostream>

// Constructor: inicializar rey hongo con posición, daño y salud
ReyHongo::ReyHongo(sf::Vector2f posicion, int daño, int salud) {
    accion = Accion::NINGUNA;
    cuadro = 0;
    this->daño = daño;
    this->salud = salud;
    estaMuerto = false;
    relojAnimacion.restart();
    relojAtaque.restart();

    // Inicializar física
    aceleracion.x = 1;
    aceleracion.y = 1; // gravedad
    velocidad.x = 0;
    velocidad.y = 0;

    // Configurar la caja de colisión - doble del tamaño de las hormigas infectadas
    cajaColision.setSize(sf::Vector2f(40, 36));
    cajaColision.setOrigin(sf::Vector2f(20, 18));
    cajaColision.setFillColor(sf::Color(255, 255, 0, 100));
    cajaColision.setPosition(posicion);

    // Cargar texturas al inicializar
    cargarTexturas();

    // Configurar sprite inicial
    spriteReyHongo.setTexture(*texturasFrontal[0], true);
    desplazamientoCajaColision = 0;

    // Configurar el sprite - doble de tamaño que las hormigas infectadas
    spriteReyHongo.setOrigin(ORIGEN_REY_HONGO);
    spriteReyHongo.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), TAMAÑO_CUADRO_REY_HONGO));
    spriteReyHongo.setScale(3.0f, 3.0f);

    // Posicionar el sprite en relación a la caja de colisión
    spriteReyHongo.setPosition(
        cajaColision.getPosition().x,
        cajaColision.getPosition().y - 22
    );
}

ReyHongo::~ReyHongo() {
}

// Establecer acción actual del rey hongo
void ReyHongo::setAccion(Accion accion) {
    this->accion = accion;
}

// Obtener acción actual del rey hongo
Accion ReyHongo::getAccion() {
    return accion;
}

// Obtener salud actual del rey hongo
int ReyHongo::getSalud() {
    return salud;
}

// Cambiar salud del rey hongo
void ReyHongo::cambiarSalud(int valor) {
    salud += valor;

    // Verificar si murió
    if (salud <= 0 && !estaMuerto) {
        morir();
    }
}

// Verificar si el rey hongo está vivo
bool ReyHongo::estaVivo() {
    return !estaMuerto && salud > 0;
}

// Ejecutar muerte del rey hongo
void ReyHongo::morir() {
    estaMuerto = true;
    velocidad.x = 0;
    velocidad.y = 0;
    setAccion(Accion::MURIENDO);
}

// Atacar a un enemigo
void ReyHongo::atacar(Personaje* enemigo) {
    enemigo->cambiarSalud(-daño);
    relojAtaque.restart();
}

// Verificar si puede atacar
bool ReyHongo::puedeAtacar() {
    return relojAtaque.getElapsedTime() > sf::milliseconds(250);
}

// Obtener velocidad actual
sf::Vector2f ReyHongo::getVelocidad() {
    return velocidad;
}

// Establecer velocidad horizontal
void ReyHongo::setVelocidadX(float velocidadX) {
    velocidad.x = velocidadX;
}

// Establecer velocidad vertical
void ReyHongo::setVelocidadY(float velocidadY) {
    velocidad.y = velocidadY;
}

// Manejar colisiones
void ReyHongo::enColision(sf::Vector2f direccionColision) {
    if (direccionColision.x < 0.0f) { // colisión a la izquierda
        velocidad.x = 0.0f;
    } else if (direccionColision.x > 0.0f) { // colisión a la derecha
        velocidad.x = 0.0f;
    }

    if (direccionColision.y > 0.0f) { // colisión abajo
        velocidad.y = 0.0f;
    } else if (direccionColision.y < 0.0f) { // colisión arriba
        velocidad.y = 0.0f;
    }
}

// Obtener posición actual
sf::Vector2f ReyHongo::getPosicion() {
    return cajaColision.getPosition();
}

// Obtener mitad del tamaño para cálculos de colisión
sf::Vector2f ReyHongo::getMitadTamaño() {
    return sf::Vector2f(20, 18);
}

// Obtener colisionador
Colisionador ReyHongo::getColisionador() {
    return Colisionador(cajaColision);
}

// Cargar todas las texturas del rey hongo
void ReyHongo::cargarTexturas() {
    // Reservar espacio en los vectores
    texturasFrontal.resize(2);
    texturasIzquierda.resize(2);
    texturasAtaque.resize(2);
    texturasMuerteFrontal.resize(2);
    texturasMuerteIzquierda.resize(2);

    // Cargar texturas del Rey Hongo vivo
    texturasFrontal[0] = &GestorRecursos::getInstance()->obtenerTextura("hV_front1");
    texturasFrontal[1] = &GestorRecursos::getInstance()->obtenerTextura("hV_front2");
    texturasIzquierda[0] = &GestorRecursos::getInstance()->obtenerTextura("hV_izq1");
    texturasIzquierda[1] = &GestorRecursos::getInstance()->obtenerTextura("hV_izq2");

    // Cargar texturas de ataque
    texturasAtaque[0] = &GestorRecursos::getInstance()->obtenerTextura("hVA_1");
    texturasAtaque[1] = &GestorRecursos::getInstance()->obtenerTextura("hVA_2");

    // Cargar texturas del Rey Hongo muerto
    texturasMuerteFrontal[0] = &GestorRecursos::getInstance()->obtenerTextura("hM_front1");
    texturasMuerteFrontal[1] = &GestorRecursos::getInstance()->obtenerTextura("hM_front2");
    texturasMuerteIzquierda[0] = &GestorRecursos::getInstance()->obtenerTextura("hM_izq1");
    texturasMuerteIzquierda[1] = &GestorRecursos::getInstance()->obtenerTextura("hM_izq2");
}

// Actualizar textura según estado y animación
void ReyHongo::actualizarTextura() {
    // Variables estáticas para mantener estado entre llamadas
    static int frameActual = 0;
    static bool ultimaDireccionFrontal = true;
    static sf::Clock relojFrame;

    // Cambiar frame cada 300ms
    if (relojFrame.getElapsedTime().asSeconds() >= 0.3f) {
        frameActual = (frameActual + 1) % 2;
        relojFrame.restart();
    }

    // Lógica de texturas para rey hongo muerto
    if (estaMuerto) {
        static bool ultimaDireccionDerecha = false;

        // Mantener la última dirección conocida para la textura de muerte
        if (ultimaDireccionDerecha) {
            spriteReyHongo.setTexture(*texturasMuerteIzquierda[frameActual]);
        } else {
            spriteReyHongo.setTexture(*texturasMuerteFrontal[frameActual]);
        }
        return;
    }

    // Recordar la última dirección para reyes vivos
    if (velocidad.x > 0) {
        ultimaDireccionFrontal = false;
    } else if (velocidad.x < 0) {
        ultimaDireccionFrontal = false;
    } else {
        ultimaDireccionFrontal = true;
    }

    // Seleccionar texturas según el estado actual
    if (accion == Accion::ATACANDO) {
        spriteReyHongo.setTexture(*texturasAtaque[frameActual]);
    } else if (accion == Accion::CAMINANDO || velocidad.x != 0) {
        spriteReyHongo.setTexture(*texturasIzquierda[frameActual]);
    } else {
        spriteReyHongo.setTexture(*texturasFrontal[frameActual]);
    }
}

// Método legacy de animación
void ReyHongo::animacion(int cuadros, int ms, int inicioX, int inicioY) {
    // Ya no se usa, la animación se maneja en actualizarTextura()
}

// Actualizar rey hongo
void ReyHongo::actualizar() {
    // Los reyes muertos no se mueven pero sí muestran animación
    if (estaMuerto) {
        actualizarTextura();
        spriteReyHongo.setPosition(
            cajaColision.getPosition().x,
            cajaColision.getPosition().y - 22
        );
        return;
    }

    // Lógica solo para reyes vivos
    actualizarTextura();

    // Aplicar gravedad
    velocidad.y += aceleracion.y;

    // Mover la caja de colisión
    cajaColision.move(velocidad);

    // Sincronizar sprite con caja de colisión
    spriteReyHongo.setPosition(
        cajaColision.getPosition().x,
        cajaColision.getPosition().y - 22
    );
}

// Dibujar rey hongo en la ventana
void ReyHongo::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteReyHongo);
}