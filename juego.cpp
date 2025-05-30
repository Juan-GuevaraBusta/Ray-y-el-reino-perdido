#include "juego.h"
#include "gestorRecursos.h"
#include "gestorAudio.h"
#include "MenuManager.h"
#include "mundo.h"
#include "gestorNombres.h"
#include <cstdint>
#include <iostream>
#include <map>
#include <cmath>

// Constructor: inicializa el juego con la ventana, jugador e interfaz
Juego::Juego()
    : ventana("Aventura de Hormigas", sf::Vector2u(ANCHO_VENTANA, ALTO_VENTANA)),
      jugador("niveles/nivel1.txt"),
      interfaz(&jugador) {
    cargarNiveles();
    reiniciado = false;
    mundoActual = 0;
    reloj.restart();
    tiempoTranscurrido = 0.0f;
    gestorNombres = nullptr;
    juegoGanado = false;

    // Iniciar música del primer nivel
    GestorAudio::getInstance()->reproducirMusica("musicaNivel1");
}

// Destructor: limpia los recursos
Juego::~Juego() {
    GestorRecursos::getInstance()->limpiar();
}

// Bucle principal del juego
void Juego::ejecutar() {
    while (!ventana.terminado()) {
        if (reloj.getElapsedTime().asSeconds() >= 1.0f / VELOCIDAD_CUADROS) {
            ventana.actualizar(); // permite pausar el juego
            if (ventana.enfocado() && !ventana.pausado()) {
                actualizar();
            }

            dibujar();
            reloj.restart();
        }
    }
}

// Carga todos los niveles del juego desde archivos
void Juego::cargarNiveles() {
    mundos.push_back(Mundo("niveles/level1.txt"));
    mundos.push_back(Mundo("niveles/level2.txt"));
    mundos.push_back(Mundo("niveles/level3.txt"));
    mundos.push_back(Mundo("niveles/goodjob.txt"));
}

// Cambia la música según el nivel actual
void Juego::cambiarMusicaNivel(int nivel) {
    switch(nivel) {
        case 0:
            GestorAudio::getInstance()->reproducirMusica("musicaNivel1");
            break;
        case 1:
            GestorAudio::getInstance()->reproducirMusica("musicaNivel2");
            break;
        case 2:
            GestorAudio::getInstance()->reproducirMusica("musicaNivel3");
            break;
        default:
            GestorAudio::getInstance()->reproducirMusica("musicaNivel1");
            break;
    }
}

// Actualiza toda la lógica del juego
void Juego::actualizar() {
    reiniciado = false;

    // Si el juego está ganado, solo actualizar interfaz
    if (juegoGanado) {
        interfaz.actualizar();
        return;
    }

    // Manejar reinicio del juego con tecla R
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !reiniciado) {
        mundos.clear();
        cargarNiveles();
        jugador.reiniciarJuego();
        reiniciado = true;
        int mundoAnterior = mundoActual;
        mundoActual = 0;
        juegoGanado = false;

        jugador.setPosicion(mundos[mundoActual].posicionInicialJugador);

        if (mundoActual != mundoAnterior) {
            cambiarMusicaNivel(mundoActual);
        }
    }

    // Si el jugador está muerto, manejar la muerte
    if (jugador.getSalud() <= 0) {
        // Actualizar puntaje al momento de morir
        if (!jugador.haPerdido()) {
            if (gestorNombres != nullptr) {
                gestorNombres->actualizarPuntajeUltimoJugador(jugador.getPuntuacion());
            }

            interfaz.salud.clear();
            jugador.finJuego();
            jugador.perder();
        }

        // Actualizar jugador para mostrar textura de muerte
        jugador.actualizar();

        // Seguir actualizando hormigas NPC para que sigan moviéndose
        for (HormigaNPC* hormiga : mundos[mundoActual].hormigasNPC) {
            for (Bloque& bloque : mundos[mundoActual].bloques) {
                if (bloque.getColisionador().comprobarColision(hormiga->getColisionador(), hormiga->direccionColision, 1.0f)) {
                    hormiga->enColision(hormiga->direccionColision);
                }
            }
        }

        // Seguir actualizando hormigas infectadas débiles
        for (HormigaInfectada* hormiga : mundos[mundoActual].hormigasInfectadasDebiles) {
            if (hormiga->estaViva()) {
                hormiga->moverErraticamente();

                for (Bloque& bloque : mundos[mundoActual].bloques) {
                    if (bloque.getColisionador().comprobarColision(hormiga->getColisionador(), hormiga->direccionColision, 1.0f)) {
                        hormiga->enColision(hormiga->direccionColision);
                    }
                }
            }
        }

        // Seguir actualizando hormigas infectadas fuertes
        for (HormigaInfectada* hormiga : mundos[mundoActual].hormigasInfectadasFuertes) {
            if (hormiga->estaViva()) {
                hormiga->moverErraticamente();

                for (Bloque& bloque : mundos[mundoActual].bloques) {
                    if (bloque.getColisionador().comprobarColision(hormiga->getColisionador(), hormiga->direccionColision, 1.0f)) {
                        hormiga->enColision(hormiga->direccionColision);
                    }
                }
            }
        }

        // Seguir actualizando reyes hongo
        for (ReyHongo* rey : mundos[mundoActual].reyesHongo) {
            if (rey->getSalud() > 0) {
                // Movimiento errático de los reyes hongo cuando el jugador está muerto
                static std::map<ReyHongo*, sf::Clock> relojesMovimiento;
                static std::map<ReyHongo*, sf::Clock> relojesCambioDireccion;
                static std::map<ReyHongo*, int> direccionesActuales;
                static std::map<ReyHongo*, float> tiemposCambioDireccion;

                if (relojesMovimiento.find(rey) == relojesMovimiento.end()) {
                    relojesMovimiento[rey] = sf::Clock();
                    relojesCambioDireccion[rey] = sf::Clock();
                    direccionesActuales[rey] = 0;
                    tiemposCambioDireccion[rey] = 2.0f;
                }

                if (relojesCambioDireccion[rey].getElapsedTime().asSeconds() >= tiemposCambioDireccion[rey]) {
                    direccionesActuales[rey] = rand() % 3 - 1;
                    tiemposCambioDireccion[rey] = 2.0f + (rand() % 3000) / 1000.0f;
                    relojesCambioDireccion[rey].restart();
                }

                float velocidadMovimiento = 0.3f;
                switch(direccionesActuales[rey]) {
                    case -1:
                        rey->setVelocidadX(-velocidadMovimiento);
                        rey->setAccion(Accion::CAMINANDO);
                        break;
                    case 1:
                        rey->setVelocidadX(velocidadMovimiento);
                        rey->setAccion(Accion::CAMINANDO);
                        break;
                    case 0:
                    default:
                        rey->setVelocidadX(0);
                        rey->setAccion(Accion::NINGUNA);
                        break;
                }

                for (Bloque& bloque : mundos[mundoActual].bloques) {
                    if (bloque.getColisionador().comprobarColision(rey->getColisionador(), rey->direccionColision, 1.0f)) {
                        rey->enColision(rey->direccionColision);
                    }
                }
            }
        }

        interfaz.actualizar();
        jugador.actualizar();
        mundos[mundoActual].actualizar();

        return;
    }

    // Lógica cuando el jugador está vivo

    // Colisiones del jugador con bloques
    for (Bloque& bloque : mundos[mundoActual].bloques) {
        if (bloque.getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 1.0f)) {
            jugador.enColision(jugador.direccionColision);
        }
    }

    // Colisiones con hormigas NPC (inmortales)
    for (HormigaNPC* hormiga : mundos[mundoActual].hormigasNPC) {
        if (hormiga->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 1.0f)) {
            jugador.enColision(jugador.direccionColision);
        }
    }

    // Colisiones físicas de hormigas NPC con bloques
    for (HormigaNPC* hormiga : mundos[mundoActual].hormigasNPC) {
        for (Bloque& bloque : mundos[mundoActual].bloques) {
            if (bloque.getColisionador().comprobarColision(hormiga->getColisionador(), hormiga->direccionColision, 1.0f)) {
                hormiga->enColision(hormiga->direccionColision);
            }
        }
    }

    // Combate con hormigas infectadas débiles
    for (HormigaInfectada* hormiga : mundos[mundoActual].hormigasInfectadasDebiles) {
        if (hormiga->estaViva()) {
            // Detectar y perseguir al jugador
            hormiga->detectarYPerseguirJugador(jugador.getPosicion());

            // Colisiones físicas con bloques
            for (Bloque& bloque : mundos[mundoActual].bloques) {
                if (bloque.getColisionador().comprobarColision(hormiga->getColisionador(), hormiga->direccionColision, 1.0f)) {
                    hormiga->enColision(hormiga->direccionColision);
                }
            }

            // Combate cuerpo a cuerpo
            if (hormiga->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 0.0f)) {
                // El jugador puede atacar a la hormiga
                if (jugador.getAccion() == Accion::ATACANDO && jugador.puedeAtacar()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && jugador.getLuz() >= 10) {
                        // Super golpe de luz
                        hormiga->cambiarSalud(-10);
                        GestorAudio::getInstance()->reproducirSonido("superGolpe");
                    } else {
                        // Ataque normal
                        hormiga->cambiarSalud(-1);
                    }
                    jugador.atacar(hormiga);
                }

                // La hormiga puede atacar al jugador
                if (hormiga->estaViva()) {
                    if (hormiga->relojAtaque.getElapsedTime() > sf::seconds(0.8f)) {
                        hormiga->relojAtaque.restart();
                    }

                    hormiga->setAccion(Accion::ATACANDO);
                    if (hormiga->puedeAtacar()) {
                        hormiga->atacar(&jugador);
                    }
                }
            }
            // Ataque a distancia (1 cuadro)
            else if (hormiga->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 40.0f)) {
                if (jugador.getAccion() == Accion::ATACANDO && jugador.puedeAtacar()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && jugador.getLuz() >= 10) {
                        hormiga->cambiarSalud(-10);
                        GestorAudio::getInstance()->reproducirSonido("superGolpe");
                    } else {
                        hormiga->cambiarSalud(-1);
                    }
                    jugador.atacar(hormiga);
                }
            } else if (!hormiga->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 120.0f)) {
                hormiga->setAccion(Accion::NINGUNA);
            }
        }
    }

    // Combate con hormigas infectadas fuertes (lógica similar)
    for (HormigaInfectada* hormiga : mundos[mundoActual].hormigasInfectadasFuertes) {
        if (hormiga->estaViva()) {
            hormiga->detectarYPerseguirJugador(jugador.getPosicion());

            for (Bloque& bloque : mundos[mundoActual].bloques) {
                if (bloque.getColisionador().comprobarColision(hormiga->getColisionador(), hormiga->direccionColision, 1.0f)) {
                    hormiga->enColision(hormiga->direccionColision);
                }
            }

            if (hormiga->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 0.0f)) {
                if (jugador.getAccion() == Accion::ATACANDO && jugador.puedeAtacar()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && jugador.getLuz() >= 10) {
                        hormiga->cambiarSalud(-10);
                        GestorAudio::getInstance()->reproducirSonido("superGolpe");
                    } else {
                        hormiga->cambiarSalud(-1);
                    }
                    jugador.atacar(hormiga);
                }

                if (hormiga->estaViva()) {
                    if (hormiga->relojAtaque.getElapsedTime() > sf::seconds(1.0f)) {
                        hormiga->relojAtaque.restart();
                    }

                    hormiga->setAccion(Accion::ATACANDO);
                    if (hormiga->puedeAtacar()) {
                        hormiga->atacar(&jugador);
                    }
                }
            } else if (hormiga->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 40.0f)) {
                if (jugador.getAccion() == Accion::ATACANDO && jugador.puedeAtacar()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && jugador.getLuz() >= 10) {
                        hormiga->cambiarSalud(-10);
                        GestorAudio::getInstance()->reproducirSonido("superGolpe");
                    } else {
                        hormiga->cambiarSalud(-1);
                    }
                    jugador.atacar(hormiga);
                }
            } else if (!hormiga->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 120.0f)) {
                hormiga->setAccion(Accion::NINGUNA);
            }
        }
    }

    // Combate con reyes hongo (jefes)
    for (ReyHongo* rey : mundos[mundoActual].reyesHongo) {
        if (rey->estaVivo()) {
            // Detectar y perseguir al jugador
            sf::Vector2f posicionRey = rey->getPosicion();
            sf::Vector2f posicionJugador = jugador.getPosicion();

            float dx = posicionJugador.x - posicionRey.x;
            float dy = posicionJugador.y - posicionRey.y;
            float distancia = std::sqrt(dx * dx + dy * dy);

            float distanciaDeteccion = 160.0f;

            if (distancia <= distanciaDeteccion) {
                // Perseguir al jugador
                float velocidadPersecucion = 1.0f;

                if (posicionJugador.x > posicionRey.x) {
                    rey->setVelocidadX(velocidadPersecucion);
                    rey->setAccion(Accion::CAMINANDO);
                } else if (posicionJugador.x < posicionRey.x) {
                    rey->setVelocidadX(-velocidadPersecucion);
                    rey->setAccion(Accion::CAMINANDO);
                } else {
                    rey->setVelocidadX(0);
                    rey->setAccion(Accion::NINGUNA);
                }
            } else {
                // Movimiento errático cuando está lejos
                static std::map<ReyHongo*, sf::Clock> relojesMovimiento;
                static std::map<ReyHongo*, sf::Clock> relojesCambioDireccion;
                static std::map<ReyHongo*, int> direccionesActuales;
                static std::map<ReyHongo*, float> tiemposCambioDireccion;

                if (relojesMovimiento.find(rey) == relojesMovimiento.end()) {
                    relojesMovimiento[rey] = sf::Clock();
                    relojesCambioDireccion[rey] = sf::Clock();
                    direccionesActuales[rey] = 0;
                    tiemposCambioDireccion[rey] = 2.0f;
                }

                if (relojesCambioDireccion[rey].getElapsedTime().asSeconds() >= tiemposCambioDireccion[rey]) {
                    direccionesActuales[rey] = rand() % 3 - 1;
                    tiemposCambioDireccion[rey] = 2.0f + (rand() % 3000) / 1000.0f;
                    relojesCambioDireccion[rey].restart();
                }

                float velocidadMovimiento = 0.3f;
                switch(direccionesActuales[rey]) {
                    case -1:
                        rey->setVelocidadX(-velocidadMovimiento);
                        rey->setAccion(Accion::CAMINANDO);
                        break;
                    case 1:
                        rey->setVelocidadX(velocidadMovimiento);
                        rey->setAccion(Accion::CAMINANDO);
                        break;
                    case 0:
                    default:
                        rey->setVelocidadX(0);
                        rey->setAccion(Accion::NINGUNA);
                        break;
                }
            }

            // Colisiones físicas con bloques
            for (Bloque& bloque : mundos[mundoActual].bloques) {
                if (bloque.getColisionador().comprobarColision(rey->getColisionador(), rey->direccionColision, 1.0f)) {
                    rey->enColision(rey->direccionColision);
                }
            }

            // Combate cuerpo a cuerpo
            if (rey->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 0.0f)) {
                if (jugador.getAccion() == Accion::ATACANDO && jugador.puedeAtacar()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && jugador.getPuntuacion() >= 10) {
                        rey->cambiarSalud(-10);
                        GestorAudio::getInstance()->reproducirSonido("superGolpe");
                    } else {
                        rey->cambiarSalud(-1);
                    }
                    jugador.atacar(rey);
                }

                if (rey->relojAtaque.getElapsedTime() > sf::seconds(1.2f)) {
                    rey->relojAtaque.restart();
                }

                rey->setAccion(Accion::ATACANDO);
                if (rey->puedeAtacar()) {
                    rey->atacar(&jugador);
                }
            }
            // Ataque a distancia
            else if (rey->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 40.0f)) {
                if (jugador.getAccion() == Accion::ATACANDO && jugador.puedeAtacar()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && jugador.getPuntuacion() >= 10) {
                        rey->cambiarSalud(-10);
                        GestorAudio::getInstance()->reproducirSonido("superGolpe");
                    } else {
                        rey->cambiarSalud(-1);
                    }
                    jugador.atacar(rey);
                }
            }
        } else {
            // Colisiones físicas para reyes muertos
            for (Bloque& bloque : mundos[mundoActual].bloques) {
                if (bloque.getColisionador().comprobarColision(rey->getColisionador(), rey->direccionColision, 1.0f)) {
                    rey->enColision(rey->direccionColision);
                }
            }
        }
    }

    // Otorgar puntos cuando mueren enemigos (solo una vez)
    for (HormigaInfectada* hormiga : mundos[mundoActual].hormigasInfectadasDebiles) {
        if (hormiga->acabaDeMorir()) {
            jugador.cambiarPuntuacion(5);
            GestorAudio::getInstance()->reproducirSonido("enemigoMuere");
        }
    }

    for (HormigaInfectada* hormiga : mundos[mundoActual].hormigasInfectadasFuertes) {
        if (hormiga->acabaDeMorir()) {
            jugador.cambiarPuntuacion(5);
            GestorAudio::getInstance()->reproducirSonido("enemigoMuere");
        }
    }

    for (ReyHongo* rey : mundos[mundoActual].reyesHongo) {
        if (rey->getSalud() <= 0 && rey->estaVivo()) {
            jugador.cambiarPuntuacion(50);
            GestorAudio::getInstance()->reproducirSonido("enemigoMuere");
        }
    }

    // Recoger luces (aumentan puntaje)
    for (auto it = mundos[mundoActual].luces.begin(); it != mundos[mundoActual].luces.end();) {
        if ((*it)->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 0.0f)) {
            it = mundos[mundoActual].luces.erase(it);
            jugador.cambiarPuntuacion(1);
            GestorAudio::getInstance()->reproducirSonido("recogerItem");
        } else {
            ++it;
        }
    }

    // Recoger semillas (aumentan luz)
    for (auto it = mundos[mundoActual].semillas.begin(); it != mundos[mundoActual].semillas.end();) {
        if ((*it)->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 0.0f)) {
            it = mundos[mundoActual].semillas.erase(it);
            jugador.cambiarLuz(1);
            GestorAudio::getInstance()->reproducirSonido("recogerItem");
        } else {
            ++it;
        }
    }

    // Usar portales para cambiar de nivel
    for (Portal* portal : mundos[mundoActual].portales) {
        if (portal->getColisionador().comprobarColision(jugador.getColisionador(), jugador.direccionColision, 0.0f)) {
            if (portal->getTipo() == 1 && portal->relojPortal.getElapsedTime() > sf::seconds(1.0f)) {
                portal->relojPortal.restart();
            }

            if (portal->getTipo() == 1 && portal->puedeTeletransportar()) {
                int mundoAnterior = mundoActual;

                // Verificar si estamos en goodjob (victoria)
                if (mundoActual == 3) {
                    if (gestorNombres != nullptr) {
                        gestorNombres->actualizarPuntajeUltimoJugador(jugador.getPuntuacion());
                    }

                    juegoGanado = true;
                    return;
                }

                // Avanzar al siguiente mundo
                mundoActual++;

                if (mundoActual >= mundos.size()) {
                    if (gestorNombres != nullptr) {
                        gestorNombres->actualizarPuntajeUltimoJugador(jugador.getPuntuacion());
                    }

                    juegoGanado = true;
                    mundoActual = mundos.size() - 1;
                    return;
                }

                jugador.setPosicion(mundos[mundoActual].posicionInicialJugador);

                if (mundoActual != mundoAnterior) {
                    cambiarMusicaNivel(mundoActual);
                }
            }
        }
    }

    // Actualizar interfaz y jugador
    interfaz.actualizar();
    jugador.actualizar();

    // Manejar acción de curación
    if (jugador.getAccion() == Accion::CURANDO) {
        GestorAudio::getInstance()->reproducirSonido("rayCurando");
        interfaz.agregarVidaSprite();
        jugador.setAccion(Accion::NINGUNA);
    }

    // Manejar acción de super golpe
    if (jugador.getAccion() == Accion::SUPERGOLPE) {
        GestorAudio::getInstance()->reproducirSonido("superGolpe");
        jugador.setAccion(Accion::NINGUNA);
    }

    mundos[mundoActual].actualizar();
}

// Verifica si el jugador perdió
bool Juego::jugadorPerdio() {
    return jugador.getSalud() <= 0;
}

// Verifica si el jugador ganó
bool Juego::jugadorGano() {
    return juegoGanado;
}

// Dibuja todos los elementos del juego en pantalla
void Juego::dibujar() {
    ventana.iniciarDibujo();

    // Proteger: solo dibujar mundo si existe
    if (mundoActual < mundos.size()) {
        mundos[mundoActual].dibujar(*ventana.getVentanaRender());
    }

    interfaz.dibujar(*ventana.getVentanaRender());
    jugador.dibujar(*ventana.getVentanaRender());

    ventana.finalizarDibujo();
}

// Obtiene referencia a la ventana principal
Ventana* Juego::getVentana() {
    return &ventana;
}

// Función auxiliar para agregar vida a la interfaz desde fuera de la clase
void agregarVidaSpriteInterfaz(void* interfaz) {
    InterfazUsuario* interfazUsuario = static_cast<InterfazUsuario*>(interfaz);
    interfazUsuario->agregarVidaSprite();
}