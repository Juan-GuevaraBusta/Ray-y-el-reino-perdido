#include "jugador.h"
#include "gestorRecursos.h"
#include "gestorAudio.h"
#include <fstream>
#include <cstdint>
#include <iostream>

// Constructor: Inicializa el jugador y carga su posición desde el archivo de nivel
Jugador::Jugador(std::string nombreArchivo) {
    // Inicialización de variables de estado
    accion = Accion::NINGUNA;
    aceleracion.x = 1;
    aceleracion.y = 1; // gravedad
    velocidad.x = 0;
    velocidad.y = 0;
    velocidadMaxima = 3.2;
    velocidadSalto = 18.4;
    velocidadCaida = 15.0;
    daño = 1;
    salud = 3;
    puntuacion = 0;
    luz = 0;
    puedeSaltar = true;
    potenciador = true;
    perdio = false;
    animacionMuerteMostrada = false;

    relojAtaque.restart();
    relojAnimacion.restart();

    // Configuración de la caja de colisión
    cajaColision.setSize(sf::Vector2f(20, 26));
    cajaColision.setOrigin(sf::Vector2f(10, 13));
    cajaColision.setFillColor(sf::Color(255, 0, 0, 100));

    cuadro = 0;

    // Configuración inicial del sprite
    sf::Texture& texturaJugador = GestorRecursos::getInstance()->obtenerTextura("rS_front1");
    spriteJugador.setTexture(texturaJugador, true);
    spriteJugador.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), TAMAÑO_CUADRO_JUGADOR));
    spriteJugador.setOrigin(ORIGEN_JUGADOR);

    // Lectura del archivo de nivel para encontrar la posición inicial del jugador
    std::ifstream nivel;
    nivel.open(nombreArchivo.c_str());

    if (!nivel.is_open()) {
        // Si no se puede abrir el archivo, usar posición por defecto
        posicionInicial = sf::Vector2f(55, 680);
        cajaColision.setPosition(posicionInicial);
        spriteJugador.setPosition(posicionInicial.x, posicionInicial.y);
        nivel.close();
        return;
    }

    bool jugadorEncontrado = false;

    // Búsqueda del jugador en el grid del nivel
    for (int bloqueY = 0; bloqueY < 18; bloqueY++) {
        for (int bloqueX = 0; bloqueX < 32; bloqueX++) {
            int buscarJugador;
            nivel >> buscarJugador;
            if (buscarJugador == 2) { // Case 2 es donde aparece el jugador
                // Calcular la posición basada en las coordenadas del grid
                float posX = 23 + bloqueX * TAMAÑO_BLOQUE;
                float posY = 20 + bloqueY * TAMAÑO_BLOQUE;

                posicionInicial = sf::Vector2f(posX, posY);
                cajaColision.setPosition(posicionInicial);
                spriteJugador.setPosition(posicionInicial.x, posicionInicial.y - 4);

                jugadorEncontrado = true;
                break;
            }
        }
        if (jugadorEncontrado) break;
    }

    // Si no se encontró el jugador en el archivo, usar posición por defecto
    if (!jugadorEncontrado) {
        posicionInicial = sf::Vector2f(55, 680);
        cajaColision.setPosition(posicionInicial);
        spriteJugador.setPosition(posicionInicial.x, posicionInicial.y - 4);
    }

    nivel.close();
}

// Ejecuta el ataque del jugador contra un enemigo
void Jugador::atacar(Personaje* enemigo_personaje) {
    enemigo_personaje->cambiarSalud(-daño);
    relojAtaque.restart();
    GestorAudio::getInstance()->reproducirSonido("rayAtaque");
}

// Maneja las colisiones del jugador ajustando la velocidad según la dirección
void Jugador::enColision(sf::Vector2f direccionColision) {
    if (direccionColision.x < 0.0f) { // colisión a la izquierda
        velocidad.x = 0.0f;
    } else if (direccionColision.x > 0.0f) { // colisión a la derecha
        velocidad.x = 0.0f;
    }

    if (direccionColision.y > 0.0f) { // colisión abajo
        velocidad.y = 0.0f;
        puedeSaltar = true;
    } else if (direccionColision.y < 0.0f) { // colisión arriba
        velocidad.y = 0.0f;
    }
}

// Termina el juego estableciendo el estado de muerte del jugador
void Jugador::finJuego() {
    // Detener completamente el movimiento
    velocidad.x = 0;
    velocidad.y = 0;

    // Asegurar que la salud sea 0
    salud = 0;

    // Cambiar a estado de muerte
    accion = Accion::MURIENDO;

    // Marcar que se mostró la animación de muerte
    animacionMuerteMostrada = true;

    // Cambiar inmediatamente a la textura de muerte para evitar bugs visuales
    spriteJugador.setTexture(texturaMuerto);

    // Reproducir sonido de muerte
    GestorAudio::getInstance()->reproducirSonido("rayMuerte");
}

// Reinicia el estado del jugador para comenzar una nueva partida
void Jugador::reiniciarJuego() {
    puntuacion = 0;
    salud = 3;
    luz = 0;
    perdio = false;
    animacionMuerteMostrada = false;
    accion = Accion::NINGUNA;

    // Volver a la posición inicial guardada
    cajaColision.setPosition(posicionInicial);
    spriteJugador.setPosition(posicionInicial.x, posicionInicial.y - 4);
}

// Carga todas las texturas del jugador según su estado de salud
void Jugador::cargarTexturas() {
    // Reservar espacio en los vectores (2 frames cada uno)
    texturasSanoFrontal.resize(2);
    texturasSanoDerecha.resize(2);
    texturasSanoIzquierda.resize(2);
    texturasHeridoFrontal.resize(2);
    texturasHeridoDerecha.resize(2);
    texturasHeridoIzquierda.resize(2);
    texturasSinCascoFrontal.resize(2);
    texturasSinCascoDerecha.resize(2);
    texturasSinCascoIzquierda.resize(2);
    texturasAtaqueHerido.resize(2);
    texturasAtaqueSinCasco.resize(2);
    texturasAtaqueSano.resize(2);

    // Cargar texturas para Ray Sano (salud = 3 o mas)
    texturasSanoFrontal[0] = GestorRecursos::getInstance()->obtenerTextura("rS_front1");
    texturasSanoFrontal[1] = GestorRecursos::getInstance()->obtenerTextura("rS_front2");
    texturasSanoDerecha[0] = GestorRecursos::getInstance()->obtenerTextura("rS_der1");
    texturasSanoDerecha[1] = GestorRecursos::getInstance()->obtenerTextura("rS_der2");
    texturasSanoIzquierda[0] = GestorRecursos::getInstance()->obtenerTextura("rS_izq1");
    texturasSanoIzquierda[1] = GestorRecursos::getInstance()->obtenerTextura("rS_izq2");
    texturasAtaqueSano[0] = GestorRecursos::getInstance()->obtenerTextura("rSA_izq");
    texturasAtaqueSano[1] = GestorRecursos::getInstance()->obtenerTextura("rSA_der");

    // Cargar texturas para Ray Herido (salud = 2)
    texturasHeridoFrontal[0] = GestorRecursos::getInstance()->obtenerTextura("rH_front1");
    texturasHeridoFrontal[1] = GestorRecursos::getInstance()->obtenerTextura("rH_front2");
    texturasHeridoDerecha[0] = GestorRecursos::getInstance()->obtenerTextura("rH_der1");
    texturasHeridoDerecha[1] = GestorRecursos::getInstance()->obtenerTextura("rH_der2");
    texturasHeridoIzquierda[0] = GestorRecursos::getInstance()->obtenerTextura("rH_izq1");
    texturasHeridoIzquierda[1] = GestorRecursos::getInstance()->obtenerTextura("rH_izq2");
    texturasAtaqueHerido[0] = GestorRecursos::getInstance()->obtenerTextura("rHA_izq");
    texturasAtaqueHerido[1] = GestorRecursos::getInstance()->obtenerTextura("rHA_der");

    // Cargar texturas para Ray Sin Casco (salud = 1)
    texturasSinCascoFrontal[0] = GestorRecursos::getInstance()->obtenerTextura("r_front1");
    texturasSinCascoFrontal[1] = GestorRecursos::getInstance()->obtenerTextura("r_front2");
    texturasSinCascoDerecha[0] = GestorRecursos::getInstance()->obtenerTextura("r_right1");
    texturasSinCascoDerecha[1] = GestorRecursos::getInstance()->obtenerTextura("r_right2");
    texturasSinCascoIzquierda[0] = GestorRecursos::getInstance()->obtenerTextura("r_izq1");
    texturasSinCascoIzquierda[1] = GestorRecursos::getInstance()->obtenerTextura("r_izq2");
    texturasAtaqueSinCasco[0] = GestorRecursos::getInstance()->obtenerTextura("rA_izq");
    texturasAtaqueSinCasco[1] = GestorRecursos::getInstance()->obtenerTextura("rA_der");

    // Cargar textura para Ray Muerto (salud = 0)
    texturaMuerto = GestorRecursos::getInstance()->obtenerTextura("rM_izq");
}

// Método de animación (actualmente vacío, la animación se maneja en actualizar())
void Jugador::animacion(int cuadros, int ms, int inicioX, int inicioY) {
    // Método vacío - la animación se maneja directamente en actualizar()
}

// Actualiza la lógica del jugador: entrada, física, animación y texturas
void Jugador::actualizar() {
    // Cargar texturas si no se han cargado aún
    static bool texturasIniciadas = false;
    if (!texturasIniciadas) {
        cargarTexturas();
        texturasIniciadas = true;
    }

    // Si el jugador está muerto, solo mostrar textura de muerte y no procesar input
    if (salud <= 0) {
        // Mostrar textura de muerte de forma estable
        spriteJugador.setTexture(texturaMuerto);

        // Detener todo movimiento
        velocidad.x = 0;
        velocidad.y = 0;
        accion = Accion::MURIENDO;

        // Mantener la posición del sprite sincronizada (sin física)
        spriteJugador.setPosition(cajaColision.getPosition().x, cajaColision.getPosition().y - 4);

        // No procesar más lógica
        return;
    }

    // Procesamiento de entrada del teclado
    velocidad.x = 0;
    bool atacando = false;

    // Movimiento izquierda
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocidad.x = -velocidadMaxima;
        setAccion(Accion::CAMINANDO);
        GestorAudio::getInstance()->reproducirSonido("rayCaminando");
    }

    // Movimiento derecha
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocidad.x = velocidadMaxima;
        setAccion(Accion::CAMINANDO);
        GestorAudio::getInstance()->reproducirSonido("rayCaminando");
    }

    // Salto
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && puedeSaltar) {
        puedeSaltar = false;
        velocidad.y = -velocidadSalto;
        GestorAudio::getInstance()->reproducirSonido("raySalto");
    }

    // Curación con luz
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) &&
       luz >= 10 &&
       salud < 10 &&
       !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
       !sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        cambiarLuz(-10);
        cambiarSalud(1);
        setAccion(Accion::CURANDO);
    }

    // Super golpe con puntuación
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) &&
        puntuacion >= 10 &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        cambiarPuntuacion(-10);
        setAccion(Accion::SUPERGOLPE);
    }

    // Ataque básico
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        velocidad.x /= 4;
        setAccion(Accion::ATACANDO);
        atacando = true;
    }

    // Aplicar gravedad
    velocidad.y += aceleracion.y;

    // Control de animación (cambio de frame cada 100ms)
    static int frameActual = 0;
    static bool ultimaDireccionDerecha = false;
    if (relojAnimacion.getElapsedTime().asSeconds() >= 0.1f) {
        frameActual = (frameActual + 1) % 2;
        relojAnimacion.restart();
    }

    // Recordar la última dirección de movimiento
    if (velocidad.x > 0) {
        ultimaDireccionDerecha = true;
    } else if (velocidad.x < 0) {
        ultimaDireccionDerecha = false;
    }

    // Limitar velocidad de caída para evitar problemas con las colisiones
    if (velocidad.y > velocidadCaida) {
        velocidad.y = velocidadCaida;
    }

    // Sistema de texturas basado en salud y movimiento
    switch(salud) {
        case 2: // Ray Herido
            if (atacando) {
                if (velocidad.x > 0) {
                    spriteJugador.setTexture(texturasAtaqueHerido[1]);
                } else if (velocidad.x < 0) {
                    spriteJugador.setTexture(texturasAtaqueHerido[0]);
                } else {
                    spriteJugador.setTexture(texturasAtaqueHerido[ultimaDireccionDerecha ? 1 : 0]);
                }
            } else if (velocidad.x > 0) {
                spriteJugador.setTexture(texturasHeridoDerecha[frameActual]);
            } else if (velocidad.x < 0) {
                spriteJugador.setTexture(texturasHeridoIzquierda[frameActual]);
            } else {
                spriteJugador.setTexture(texturasHeridoFrontal[frameActual]);
            }
            break;

        case 1: // Ray Sin Casco
            if (atacando) {
                if (velocidad.x > 0) {
                    spriteJugador.setTexture(texturasAtaqueSinCasco[1]);
                } else if (velocidad.x < 0) {
                    spriteJugador.setTexture(texturasAtaqueSinCasco[0]);
                } else {
                    spriteJugador.setTexture(texturasAtaqueSinCasco[ultimaDireccionDerecha ? 1 : 0]);
                }
            } else if (velocidad.x > 0) {
                spriteJugador.setTexture(texturasSinCascoDerecha[frameActual]);
            } else if (velocidad.x < 0) {
                spriteJugador.setTexture(texturasSinCascoIzquierda[frameActual]);
            } else {
                spriteJugador.setTexture(texturasSinCascoFrontal[frameActual]);
            }
            break;

        case 0: // Ray Muerto (este caso no debería ejecutarse debido al return anterior)
            spriteJugador.setTexture(texturaMuerto);
            break;

        default: // Ray Sano (salud >= 3)
            if (atacando) {
                if (velocidad.x > 0) {
                    spriteJugador.setTexture(texturasAtaqueSano[1]);
                } else if (velocidad.x < 0) {
                    spriteJugador.setTexture(texturasAtaqueSano[0]);
                } else {
                    spriteJugador.setTexture(texturasAtaqueSano[ultimaDireccionDerecha ? 1 : 0]);
                }
            } else if (velocidad.x > 0) {
                spriteJugador.setTexture(texturasSanoDerecha[frameActual]);
            } else if (velocidad.x < 0) {
                spriteJugador.setTexture(texturasSanoIzquierda[frameActual]);
            } else {
                spriteJugador.setTexture(texturasSanoFrontal[frameActual]);
            }
            break;
    }

    // Actualizar posiciones
    cajaColision.move(velocidad);
    spriteJugador.setPosition(cajaColision.getPosition().x, cajaColision.getPosition().y - 4);
}

// Dibuja el sprite del jugador en la ventana
void Jugador::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteJugador);
}

// Establece la acción actual del jugador
void Jugador::setAccion(Accion accion) {
    this->accion = accion;
}

// Obtiene la acción actual del jugador
Accion Jugador::getAccion() {
    return accion;
}

// Establece la posición del jugador
void Jugador::setPosicion(sf::Vector2f posicion) {
    cajaColision.setPosition(posicion);
    spriteJugador.setPosition(posicion.x, posicion.y - 4);
}

// Establece la velocidad horizontal del jugador
void Jugador::setVelocidadX(float velocidadX) {
    velocidad.x = velocidadX;
}

// Establece la velocidad vertical del jugador
void Jugador::setVelocidadY(float velocidadY) {
    velocidad.y = velocidadY;
}

// Establece el valor de luz del jugador
void Jugador::setLuz(int luz) {
    this->luz = luz;
}

// Modifica la salud del jugador y reproduce sonido si recibe daño
void Jugador::cambiarSalud(int valor) {
    int saludAnterior = salud;
    salud += valor;

    // Reproducir sonido cuando recibe daño
    if (valor < 0 && salud > 0) {
        GestorAudio::getInstance()->reproducirSonido("rayHerido");
    }
}

// Modifica la puntuación del jugador
void Jugador::cambiarPuntuacion(int valor) {
    puntuacion += valor;
}

// Modifica la cantidad de luz del jugador
void Jugador::cambiarLuz(int valor) {
    luz += valor;
}

// Obtiene la velocidad actual del jugador
sf::Vector2f Jugador::getVelocidad() {
    return velocidad;
}

// Obtiene la salud actual del jugador
int Jugador::getSalud() {
    return salud;
}

// Obtiene la puntuación actual del jugador
int Jugador::getPuntuacion() {
    return puntuacion;
}

// Obtiene la cantidad de luz actual del jugador
int Jugador::getLuz() {
    return luz;
}

// Verifica si el jugador puede atacar (cooldown de ataque)
bool Jugador::puedeAtacar() {
    return relojAtaque.getElapsedTime() > sf::milliseconds(300);
}

// Obtiene la posición actual del jugador
sf::Vector2f Jugador::getPosicion() {
    return cajaColision.getPosition();
}

// Obtiene la mitad del tamaño del jugador para cálculos de colisión
sf::Vector2f Jugador::getMitadTamaño() {
    return sf::Vector2f(20, 28);
}

// Obtiene el colisionador del jugador
Colisionador Jugador::getColisionador() {
    return Colisionador(cajaColision);
}

// Verifica si el jugador ha perdido
bool Jugador::haPerdido() {
    return perdio;
}

// Marca al jugador como perdedor
void Jugador::perder() {
    perdio = true;
}