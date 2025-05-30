/*
La clase MenuManager gestiona todo el sistema de menús y navegación de Ray y el Reino Perdido.
Se encarga de mostrar la pantalla principal con opciones de juego, configuraciones de audio
independientes para música y efectos de sonido, entrada de nombres de jugadores con validación
de caracteres ASCII, pantallas de créditos e información del juego, pantallas de victoria y
derrota con rankings, y transición fluida entre estados de menú y juego. La clase MenuManager
maneja eventos de ratón y teclado, reproduce efectos de sonido para interacciones, y mantiene persistencia
de configuraciones entre sesiones del juego.
*/

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "gestorRecursos.h"
#include "gestorAudio.h"
#include "configuracion.h"
#include "gestorNombres.h"

enum class EstadoMenu {
    PANTALLA_PRINCIPAL,
    INGRESA_NOMBRE,
    CREDITOS,
    INFO,
    OPCIONES_11,
    OPCIONES_00,
    OPCIONES_01,
    OPCIONES_10,
    JUEGO,
    YOU_LOST,
    YOU_WON
};

enum class ConfiguracionAudio {
    MUSICA_ON_SONIDO_ON,
    MUSICA_OFF_SONIDO_OFF,
    MUSICA_OFF_SONIDO_ON,
    MUSICA_ON_SONIDO_OFF
};

class MenuManager {
private:
    sf::RenderWindow& ventana;                     // Referencia a la ventana principal
    EstadoMenu estadoActual;                       // Estado actual del menú
    EstadoMenu estadoAnterior;                     // Estado previo del menú
    ConfiguracionAudio configuracionAudio;         // Configuración de audio actual

    sf::Sprite spritePantalla;                     // Sprite para mostrar las pantallas

    std::string nombreJugador;                     // Nombre ingresado por el jugador
    sf::Text textoNombre;                          // Texto para mostrar el nombre
    sf::RectangleShape cajaTexto;                  // Caja visual para entrada de texto
    bool escribiendoNombre;                        // Flag para entrada de texto activa
    sf::Clock cursorParpadeo;                      // Reloj para animación del cursor

    GestorNombres gestorNombres;                   // Gestor de nombres y puntajes

    bool musicaActivada;                           // Estado de la música
    bool sonidosActivados;                         // Estado de los sonidos

    float factorEscalaX;                           // Factor de escala horizontal (330->1280)
    float factorEscalaY;                           // Factor de escala vertical (242->720)

    std::vector<sf::Text> textosRanking;           // Textos del ranking
    sf::Text tituloRanking;                        // Título del ranking
    sf::RectangleShape fondoRanking;               // Fondo del ranking

    // Configurar elementos del ranking
    void configurarRanking();
    // Actualizar contenido del ranking
    void actualizarRanking();

public:
    MenuManager(sf::RenderWindow& ventana);
    ~MenuManager();

    // Inicializar el sistema de menús
    bool inicializar();
    // Manejar eventos del menú
    void manejarEventos(sf::Event& evento);
    // Actualizar lógica del menú
    void actualizar();
    // Dibujar elementos del menú
    void dibujar();

    // Obtener estado actual
    EstadoMenu getEstadoActual() const;
    // Verificar si debe iniciar el juego
    bool debeIniciarJuego() const;
    // Cambiar estado del menú
    void cambiarEstado(EstadoMenu nuevoEstado);

    // Ejecutar bucle principal del menú
    void ejecutarMenu();

    // Manejadores de clics por pantalla
    void manejarClicPantallaPrincipal(int x, int y);
    void manejarClicCreditos(int x, int y);
    void manejarClicInfo(int x, int y);
    void manejarClicOpciones11(int x, int y);
    void manejarClicOpciones00(int x, int y);
    void manejarClicOpciones01(int x, int y);
    void manejarClicOpciones10(int x, int y);
    void manejarClicYouLost(int x, int y);
    void manejarClicYouWon(int x, int y);

    // Aplicar configuración de audio
    void aplicarConfiguracionAudio();
    // Reproducir sonido de clic
    void reproducirSonidoClick();

    // Configurar elementos de entrada de texto
    void configurarTextoNombre();
    // Manejar entrada de texto del teclado
    void manejarEntradaTexto(sf::Event& evento);

    // Verificar si un punto está dentro de un área
    bool estaDentroDelArea(int x, int y, int areaX, int areaY, int ancho, int alto);

    // Métodos de escalado de coordenadas
    int escalarX(int coordenadaOriginal);
    int escalarY(int coordenadaOriginal);
    int escalarAncho(int anchoOriginal);
    int escalarAlto(int altoOriginal);

    // Obtener referencia al gestor de nombres
    GestorNombres& getGestorNombres() { return gestorNombres; }
};

#endif