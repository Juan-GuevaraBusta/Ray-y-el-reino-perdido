/*
    RAY Y EL REINO PERDIDO
    PROYECTO FINAL PROGRAMACIÓN ORIENTADA A OBJETOS

    Archivo principal que coordina el flujo completo entre menús y juego, manejando
    la inicialización de sistemas, transiciones entre estados, y resultados de partida.

    DESCRIPCIÓN DEL FLUJO:
    1. Inicialización de ventana y sistemas de audio/recursos
    2. Ejecución del menú principal con entrada de nombres
    3. Transición al motor de juego principal
    4. Manejo de resultados (victoria/derrota) con persistencia de datos
    5. Retorno al menú principal para nueva partida

    CARACTERÍSTICAS TÉCNICAS:
    - Bucle principal persistente para múltiples partidas
    - Gestión de memoria automática entre transiciones
    - Sistema de persistencia JSON para Top 10 de jugadores
    - Manejo robusto de estados de ventana y eventos

    Créditos:
    - Juan Guevara
    - Isabel Adrada
    - María Gil
*/

// ===== ELEMENTOS DEL SISTEMA =====
// Gestores principales de recursos y funcionalidad del juego
#include "ventana.h"           // Manejo de ventana SFML con eventos y configuración
#include "configuracion.h"     // Constantes globales de configuración del juego
#include "gestorRecursos.h"    // Singleton para carga de texturas, audio y fuentes
#include "gestorAudio.h"       // Sistema de audio con música y efectos de sonido
#include "gestorNombres.h"     // Persistencia JSON para Top 10 de jugadores
#include "MenuManager.h"       // Sistema completo de menús con validación de entrada
#include "juego.h"            // Motor principal del gameplay

// ===== PERSONAJES =====
#include "personaje.h"

// Personaje principal Ray controlado por el jugador
#include "jugador.h"          // Ray con sistema de salud visual y controles

// Jefe final del juego
#include "reyHongo.h"         // Rey Hongo con 10 puntos de salud y IA de persecución

// Enemigos activos que persiguen al jugador
#include "hormigaInfectada.h" // Hormigas cubiertas de esporas con detección de Ray

// NPCs aliados que proporcionan ambientación
#include "hormigaNPC.h"       // Hormigas normales con movimiento errático pacífico

// ===== LIBRERÍAS SFML =====
// Framework gráfico y de audio para el desarrollo del juego
#include <SFML/Graphics.hpp>  // Renderizado, sprites, texturas y ventanas
#include <SFML/System.hpp>    // Vectores, relojes y utilidades del sistema
#include <SFML/Window.hpp>    // Eventos de ventana y entrada de usuario

#include <string>

int main() {
    while (true) {
        // Crear ventana para el menú
        sf::RenderWindow ventana(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), TITULO_VENTANA);
        ventana.setVerticalSyncEnabled(true);

        // Crear y ejecutar menú principal
        MenuManager menu(ventana);
        if (!menu.inicializar()) {
            return EXIT_FAILURE;
        }

        // Ejecutar el menú principal
        menu.ejecutarMenu();

        // Si el usuario quiere jugar
        if (menu.debeIniciarJuego()) {
            ventana.close(); // Cerrar ventana del menú

            // *** IMPORTANTE: Crear juego COMPLETAMENTE NUEVO cada vez ***
            std::cout << "🎮 === CREANDO NUEVA INSTANCIA DEL JUEGO ===" << std::endl;

            Juego juego;  // Nueva instancia cada vez
            juego.setGestorNombres(&menu.getGestorNombres()); // Reconectar gestor

            std::cout << "✓ Nueva instancia del juego creada" << std::endl;
            std::cout << "✓ GestorNombres reconectado" << std::endl;

            // *** OPCIONAL: Reiniciar completo por seguridad ***
            juego.reiniciarCompleto();

            juego.ejecutar();

            // Manejar resultado del juego
            if (juego.jugadorPerdio()) {
                std::cout << "💀 Jugador perdió - Mostrando You Lost" << std::endl;

                sf::RenderWindow ventanaGameOver(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), TITULO_VENTANA);
                ventanaGameOver.setVerticalSyncEnabled(true);

                MenuManager menuGameOver(ventanaGameOver);
                menuGameOver.inicializar();
                menuGameOver.cambiarEstado(EstadoMenu::YOU_LOST);
                menuGameOver.ejecutarMenu();

                ventanaGameOver.close();

                if (menuGameOver.getEstadoActual() == EstadoMenu::PANTALLA_PRINCIPAL) {
                    std::cout << "🔄 Volviendo al menú principal..." << std::endl;
                } else {
                    std::cout << "👋 Cerrando juego..." << std::endl;
                    break;
                }
            }
            else if (juego.jugadorGano()) {
                std::cout << "🏆 Jugador ganó - Mostrando You Won" << std::endl;

                sf::RenderWindow ventanaYouWon(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), TITULO_VENTANA);
                ventanaYouWon.setVerticalSyncEnabled(true);

                MenuManager menuYouWon(ventanaYouWon);
                menuYouWon.inicializar();
                menuYouWon.cambiarEstado(EstadoMenu::YOU_WON);
                menuYouWon.ejecutarMenu();

                ventanaYouWon.close();

                if (menuYouWon.getEstadoActual() == EstadoMenu::PANTALLA_PRINCIPAL) {
                    std::cout << "🏆 Victoria! Volviendo al menú principal..." << std::endl;
                } else {
                    std::cout << "👋 Cerrando juego tras victoria..." << std::endl;
                    break;
                }
            }
            else {
                std::cout << "🎮 Juego terminado normalmente" << std::endl;
            }
        } else {
            ventana.close();
            break;
        }
    }
    return EXIT_SUCCESS;
}