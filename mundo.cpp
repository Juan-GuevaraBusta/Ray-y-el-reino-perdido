#include "mundo.h"
#include "gestorRecursos.h"
#include <cstdint>

// Constructor: cargar nivel desde archivo y crear entidades
Mundo::Mundo(std::string nombreArchivo, int nivel) {
    nivelActual = nivel;

    std::ifstream nivelArchivo;
    nivelArchivo.open(nombreArchivo.c_str());

    float r, g, b; // Valores RGB para distinguir tipos y colores de bloques
    int tipoBloque;

    // Leer la matriz del nivel (18x32)
    for (int bloqueY = 0; bloqueY < 18; bloqueY++) {
        for (int bloqueX = 0; bloqueX < 32; bloqueX++) {
            nivelArchivo >> tipoBloque;
            switch (tipoBloque) {
                case 1:
                    // Crear bloque sólido con textura según el nivel
                    bloques.push_back(Bloque(
                        sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 20 + bloqueY * TAMAÑO_BLOQUE),
                        obtenerTexturaBloque(nivelActual)));
                    break;
                case 2:
                    // Portal de entrada + posición inicial del jugador
                    posicionInicialJugador = sf::Vector2f(23 + bloqueX * TAMAÑO_BLOQUE, 20 + bloqueY * TAMAÑO_BLOQUE);
                    portales.push_back(
                        new Portal(sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 8 + bloqueY * TAMAÑO_BLOQUE), 0));
                    break;
                case 3:
                    // Portal de salida
                    portales.push_back(
                        new Portal(sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 8 + bloqueY * TAMAÑO_BLOQUE), 1));
                    break;
                case 4:
                    // Fuente de luz
                    luces.push_back(new Luz(sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 20 + bloqueY * TAMAÑO_BLOQUE)));
                    break;
                case 5:
                    // Semilla coleccionable
                    semillas.push_back(new Semilla(sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 20 + bloqueY * TAMAÑO_BLOQUE)));
                    break;
                case 6:
                    // Hormiga NPC tipo 6
                    hormigasNPC.push_back(
                        new HormigaNPC(6, sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 20 + bloqueY * TAMAÑO_BLOQUE)));
                    break;
                case 7:
                    // Hormiga NPC tipo 7
                    hormigasNPC.push_back(
                        new HormigaNPC(7, sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 20 + bloqueY * TAMAÑO_BLOQUE)));
                    break;
                case 8:
                    // Hormiga infectada débil (tipo 8, velocidad 1, daño 3)
                    hormigasInfectadasDebiles.push_back(
                        new HormigaInfectada(8, sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 20 + bloqueY * TAMAÑO_BLOQUE), 1, 3));
                    break;
                case 9:
                    // Hormiga infectada fuerte (tipo 9, velocidad 1, daño 3)
                    hormigasInfectadasFuertes.push_back(
                        new HormigaInfectada(9, sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 20 + bloqueY * TAMAÑO_BLOQUE), 1, 3));
                    break;
                case 10:
                    // Rey hongo (jefe final, velocidad 1, vida 15)
                    reyesHongo.push_back(
                        new ReyHongo(sf::Vector2f(20 + bloqueX * TAMAÑO_BLOQUE, 20 + bloqueY * TAMAÑO_BLOQUE), 1, 15));
                    break;
                default:
                    break;
            }
        }
    }

    // Leer información adicional del archivo
    nivelArchivo >> nombreFondo;
    nivelArchivo >> r >> g >> b;
    nivelArchivo.close();

    // Configurar sprite del fondo
    spriteFondo.setTexture(GestorRecursos::getInstance()->obtenerTextura(nombreFondo), true);
}

// Obtener nombre de textura de bloque según el nivel
std::string Mundo::obtenerTexturaBloque(int nivel) {
    switch(nivel) {
        case 1: return "bloque1";  // Nivel 1 usa bloque1.png
        case 2: return "bloque2";  // Nivel 2 usa bloque2.png
        case 3: return "bloque3";  // Nivel 3 usa bloque3.png
        default: return "bloque1"; // Por defecto usar bloque1
    }
}

// Destructor: limpiar vectores de punteros
Mundo::~Mundo() {
    bloques.clear();
    portales.clear();
    luces.clear();
    semillas.clear();
    hormigasNPC.clear();
    hormigasInfectadasDebiles.clear();
    hormigasInfectadasFuertes.clear();
    reyesHongo.clear();
}

// Actualizar todas las entidades del mundo
void Mundo::actualizar() {
    // Actualizar portales
    for (Portal* portal : portales) {
        portal->actualizar();
    }

    // Actualizar luces
    for (Luz* luz : luces) {
        luz->actualizar();
    }

    // Actualizar semillas
    for (Semilla* semilla : semillas) {
        semilla->actualizar();
    }

    // Actualizar hormigas NPC
    for (HormigaNPC* hormiga : hormigasNPC) {
        hormiga->actualizar();
    }

    // Actualizar hormigas infectadas débiles
    for (HormigaInfectada* hormiga : hormigasInfectadasDebiles) {
        hormiga->actualizar();
    }

    // Actualizar hormigas infectadas fuertes
    for (HormigaInfectada* hormiga : hormigasInfectadasFuertes) {
        hormiga->actualizar();
    }

    // Actualizar reyes hongo
    for (ReyHongo* rey : reyesHongo) {
        rey->actualizar();
    }
}

// Dibujar todos los elementos del mundo
void Mundo::dibujar(sf::RenderWindow& ventana) {
    // Dibujar fondo primero
    ventana.draw(spriteFondo);

    // Dibujar bloques
    for (Bloque& bloque : bloques) {
        bloque.dibujar(ventana);
    }

    // Dibujar portales
    for (Portal* portal : portales) {
        portal->dibujar(ventana);
    }

    // Dibujar luces
    for (Luz* luz : luces) {
        luz->dibujar(ventana);
    }

    // Dibujar semillas
    for (Semilla* semilla : semillas) {
        semilla->dibujar(ventana);
    }

    // Dibujar hormigas NPC
    for (HormigaNPC* hormiga : hormigasNPC) {
        hormiga->dibujar(ventana);
    }

    // Dibujar hormigas infectadas débiles
    for (HormigaInfectada* hormiga : hormigasInfectadasDebiles) {
        hormiga->dibujar(ventana);
    }

    // Dibujar hormigas infectadas fuertes
    for (HormigaInfectada* hormiga : hormigasInfectadasFuertes) {
        hormiga->dibujar(ventana);
    }

    // Dibujar reyes hongo
    for (ReyHongo* rey : reyesHongo) {
        rey->dibujar(ventana);
    }
}

// Obtener nombre del fondo del nivel
std::string Mundo::getNombreFondo() {
    return nombreFondo;
}