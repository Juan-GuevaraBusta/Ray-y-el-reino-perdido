/*
La clase Mundo gestiona la carga y administración de niveles individuales de Ray y el Reino Perdido desde
archivos de configuración de texto. Se encarga de interpretar mapas numéricos que definen la ubicación de
bloques, portales, objetos coleccionables y personajes, crear instancias de todas las entidades del nivel
incluyendo Hormigas Infectadas, Hormigas NPC y Reyes Hongo, configurar diferentes texturas de bloques según
el nivel actual para variedad visual, y establecer la posición inicial de Ray en cada mundo. La clase Mundo
mantiene vectores de todas las entidades para facilitar las iteraciones de actualización y gestiona fondos
únicos para cada nivel creando ambientación visual progresiva a través de la aventura de Ray.
*/

#ifndef MUNDO_H
#define MUNDO_H

#include "bloque.h"
#include "luz.h"
#include "colisionador.h"
#include "hormigaInfectada.h"
#include "hormigaNPC.h"
#include "reyHongo.h"
#include "semilla.h"
#include "portal.h"
#include "configuracion.h"
#include <cstdint>

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

class Mundo {
private:
    sf::Sprite spriteFondo;               // Sprite del fondo del nivel
    std::string nombreFondo;              // Nombre del archivo de textura del fondo
    int nivelActual;                      // Número del nivel actual

public:
    // Vectores de entidades del mundo
    std::vector<Bloque> bloques;                               // Bloques sólidos del nivel
    std::vector<Portal*> portales;                             // Portales de entrada y salida
    std::vector<Luz*> luces;                                   // Fuentes de luz
    std::vector<Semilla*> semillas;                            // Semillas coleccionables
    std::vector<HormigaNPC*> hormigasNPC;                      // Hormigas no hostiles
    std::vector<HormigaInfectada*> hormigasInfectadasDebiles;   // Hormigas infectadas débiles
    std::vector<HormigaInfectada*> hormigasInfectadasFuertes;   // Hormigas infectadas fuertes
    std::vector<ReyHongo*> reyesHongo;                         // Jefes del nivel

    std::string siguienteNivel;           // Nombre del siguiente nivel
    sf::Vector2f posicionInicialJugador;  // Posición inicial del jugador

    // Constructor: carga nivel desde archivo
    Mundo(std::string nombreArchivo, int nivel = 1);
    ~Mundo();

    // Obtener nombre del fondo
    std::string getNombreFondo();
    // Obtener textura de bloque según nivel
    std::string obtenerTexturaBloque(int nivel);
    // Actualizar todas las entidades del mundo
    void actualizar();
    // Dibujar el mundo completo
    void dibujar(sf::RenderWindow& ventana);
};

#endif // MUNDO_H