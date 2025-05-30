#include "MenuManager.h"
#include <iostream>
#include <cmath>

// Constructor: inicializa el sistema de menús con ventana y configuración por defecto
MenuManager::MenuManager(sf::RenderWindow& ventana)
    : ventana(ventana), estadoActual(EstadoMenu::PANTALLA_PRINCIPAL),
      configuracionAudio(ConfiguracionAudio::MUSICA_ON_SONIDO_ON),
      musicaActivada(true), sonidosActivados(true) {
    // Calcular factores de escala: de 330x242 a 1280x720
    factorEscalaX = static_cast<float>(ANCHO_VENTANA) / 330.0f;
    factorEscalaY = static_cast<float>(ALTO_VENTANA) / 242.0f;
    escribiendoNombre = false;
    configurarTextoNombre();
    configurarRanking();
}

MenuManager::~MenuManager() {
    // El GestorAudio se encarga de limpiar
}

// Configurar elementos visuales del ranking
void MenuManager::configurarRanking() {
    // Configurar título del ranking
    tituloRanking.setFont(GestorRecursos::getInstance()->obtenerFuente("interfaz"));
    tituloRanking.setCharacterSize(static_cast<unsigned int>(18 * factorEscalaY));
    tituloRanking.setFillColor(sf::Color::Yellow);
    tituloRanking.setString("TOP 10 MEJORES PUNTAJES");

    // Centrar el título
    sf::FloatRect boundsTitle = tituloRanking.getLocalBounds();
    tituloRanking.setPosition(
        (ANCHO_VENTANA - boundsTitle.width) / 2.0f,
        escalarY(10)
    );

    // Configurar fondo del ranking
    fondoRanking.setSize(sf::Vector2f(escalarAncho(290), escalarAlto(210)));
    fondoRanking.setPosition(escalarX(20), escalarY(30));
    fondoRanking.setFillColor(sf::Color(0, 0, 0, 200));
    fondoRanking.setOutlineThickness(2);
    fondoRanking.setOutlineColor(sf::Color::White);

    // Configurar textos del ranking (10 posiciones)
    textosRanking.resize(10);
    for (int i = 0; i < 10; i++) {
        textosRanking[i].setFont(GestorRecursos::getInstance()->obtenerFuente("interfaz"));
        textosRanking[i].setCharacterSize(static_cast<unsigned int>(11 * factorEscalaY));
        textosRanking[i].setFillColor(sf::Color::White);

        // Posición de cada línea del ranking
        textosRanking[i].setPosition(
            escalarX(30),
            escalarY(40 + i * 19)
        );
    }
}

// Actualizar contenido del ranking con los mejores puntajes
void MenuManager::actualizarRanking() {
    std::vector<DatosJugador> top10 = gestorNombres.obtenerTop10();

    for (int i = 0; i < 10; i++) {
        if (i < top10.size()) {
            // Formatear: "1. NombreJugador............1234"
            std::string nombre = top10[i].nombre;
            if (nombre.length() > 12) {
                nombre = nombre.substr(0, 12); // Truncar nombre si es muy largo
            }

            std::string linea = std::to_string(i + 1) + ". " + nombre;

            // Agregar puntos para alinear mejor
            while (linea.length() < 20) {
                linea += ".";
            }

            linea += std::to_string(top10[i].puntaje);

            textosRanking[i].setString(linea);

            // Resaltar al jugador actual (último en la lista)
            if (!gestorNombres.estaVacio() &&
                top10[i].nombre == gestorNombres.obtenerUltimoJugador().nombre) {
                textosRanking[i].setFillColor(sf::Color::Green);
            } else {
                textosRanking[i].setFillColor(sf::Color::White);
            }
        } else {
            // Posición vacía
            std::string linea = std::to_string(i + 1) + ". ---";
            textosRanking[i].setString(linea);
            textosRanking[i].setFillColor(sf::Color(128, 128, 128));
        }
    }
}

// Inicializar el sistema de menús
bool MenuManager::inicializar() {
    cambiarEstado(EstadoMenu::PANTALLA_PRINCIPAL);
    aplicarConfiguracionAudio();
    return true;
}

// Manejar eventos de entrada del usuario
void MenuManager::manejarEventos(sf::Event& evento) {
    manejarEntradaTexto(evento);

    if (evento.type == sf::Event::MouseButtonPressed) {
        if (evento.mouseButton.button == sf::Mouse::Left) {
            int x = evento.mouseButton.x;
            int y = evento.mouseButton.y;

            switch (estadoActual) {
                case EstadoMenu::PANTALLA_PRINCIPAL:
                    manejarClicPantallaPrincipal(x, y);
                    break;
                case EstadoMenu::CREDITOS:
                    manejarClicCreditos(x, y);
                    break;
                case EstadoMenu::INFO:
                    manejarClicInfo(x, y);
                    break;
                case EstadoMenu::OPCIONES_11:
                    manejarClicOpciones11(x, y);
                    break;
                case EstadoMenu::OPCIONES_00:
                    manejarClicOpciones00(x, y);
                    break;
                case EstadoMenu::OPCIONES_01:
                    manejarClicOpciones01(x, y);
                    break;
                case EstadoMenu::OPCIONES_10:
                    manejarClicOpciones10(x, y);
                    break;
                case EstadoMenu::YOU_LOST:
                    manejarClicYouLost(x, y);
                    break;
                case EstadoMenu::YOU_WON:
                    manejarClicYouWon(x, y);
                    break;
                case EstadoMenu::INGRESA_NOMBRE:
                    if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Enter) {
                        cambiarEstado(EstadoMenu::JUEGO);
                    }
                    break;
                case EstadoMenu::JUEGO:
                    break;
            }
        }
    }
}

// Manejar clics en la pantalla principal
void MenuManager::manejarClicPantallaPrincipal(int x, int y) {
    // Botón Iniciar Juego: 110, 137, tamaño 106x13
    if (estaDentroDelArea(x, y, escalarX(110), escalarY(137), escalarAncho(106), escalarAlto(13))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::INGRESA_NOMBRE);
    }
    // Botón Opciones: 130, 155, tamaño 68x13
    else if (estaDentroDelArea(x, y, escalarX(130), escalarY(155), escalarAncho(68), escalarAlto(13))) {
        reproducirSonidoClick();
        // Abrir según la última configuración
        switch (configuracionAudio) {
            case ConfiguracionAudio::MUSICA_ON_SONIDO_ON:
                cambiarEstado(EstadoMenu::OPCIONES_11);
                break;
            case ConfiguracionAudio::MUSICA_OFF_SONIDO_OFF:
                cambiarEstado(EstadoMenu::OPCIONES_00);
                break;
            case ConfiguracionAudio::MUSICA_OFF_SONIDO_ON:
                cambiarEstado(EstadoMenu::OPCIONES_01);
                break;
            case ConfiguracionAudio::MUSICA_ON_SONIDO_OFF:
                cambiarEstado(EstadoMenu::OPCIONES_10);
                break;
        }
    }
    // Botón Créditos: 131, 172, tamaño 67x13
    else if (estaDentroDelArea(x, y, escalarX(131), escalarY(172), escalarAncho(67), escalarAlto(13))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::CREDITOS);
    }
}

// Manejar clics en la pantalla de créditos
void MenuManager::manejarClicCreditos(int x, int y) {
    // Botón X cerrar: 217, 69, tamaño 11x11
    if (estaDentroDelArea(x, y, escalarX(217), escalarY(69), escalarAncho(11), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::PANTALLA_PRINCIPAL);
    }
}

// Manejar clics en la pantalla de información
void MenuManager::manejarClicInfo(int x, int y) {
    // Botón X cerrar: 217, 69, tamaño 11x11
    if (estaDentroDelArea(x, y, escalarX(217), escalarY(69), escalarAncho(11), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::PANTALLA_PRINCIPAL);
    }
}

// Manejar clics en opciones con música y sonido activados
void MenuManager::manejarClicOpciones11(int x, int y) {
    // Botón X cerrar: 217, 69, tamaño 11x11
    if (estaDentroDelArea(x, y, escalarX(217), escalarY(69), escalarAncho(11), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::PANTALLA_PRINCIPAL);
    }
    // Toggle música: 185, 111, tamaño 17x10
    else if (estaDentroDelArea(x, y, escalarX(185), escalarY(111), escalarAncho(17), escalarAlto(10))) {
        reproducirSonidoClick();
        configuracionAudio = ConfiguracionAudio::MUSICA_OFF_SONIDO_ON;
        aplicarConfiguracionAudio();
        cambiarEstado(EstadoMenu::OPCIONES_01);
    }
    // Toggle sonido: 186, 127, tamaño 17x10
    else if (estaDentroDelArea(x, y, escalarX(186), escalarY(127), escalarAncho(17), escalarAlto(10))) {
        reproducirSonidoClick();
        configuracionAudio = ConfiguracionAudio::MUSICA_ON_SONIDO_OFF;
        aplicarConfiguracionAudio();
        cambiarEstado(EstadoMenu::OPCIONES_10);
    }
    // Botón Info: 145, 141, tamaño 36x11
    else if (estaDentroDelArea(x, y, escalarX(145), escalarY(141), escalarAncho(36), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::INFO);
    }
}

// Manejar clics en opciones con música y sonido desactivados
void MenuManager::manejarClicOpciones00(int x, int y) {
    // Botón X cerrar: 217, 69, tamaño 11x11
    if (estaDentroDelArea(x, y, escalarX(217), escalarY(69), escalarAncho(11), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::PANTALLA_PRINCIPAL);
    }
    // Toggle música: 185, 111, tamaño 17x10
    else if (estaDentroDelArea(x, y, escalarX(185), escalarY(111), escalarAncho(17), escalarAlto(10))) {
        reproducirSonidoClick();
        configuracionAudio = ConfiguracionAudio::MUSICA_ON_SONIDO_OFF;
        aplicarConfiguracionAudio();
        cambiarEstado(EstadoMenu::OPCIONES_10);
    }
    // Toggle sonido: 186, 127, tamaño 17x10
    else if (estaDentroDelArea(x, y, escalarX(186), escalarY(127), escalarAncho(17), escalarAlto(10))) {
        reproducirSonidoClick();
        configuracionAudio = ConfiguracionAudio::MUSICA_OFF_SONIDO_ON;
        aplicarConfiguracionAudio();
        cambiarEstado(EstadoMenu::OPCIONES_01);
    }
    // Botón Info: 145, 141, tamaño 36x11
    else if (estaDentroDelArea(x, y, escalarX(145), escalarY(141), escalarAncho(36), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::INFO);
    }
}

// Manejar clics en opciones con música desactivada y sonido activado
void MenuManager::manejarClicOpciones01(int x, int y) {
    // Botón X cerrar: 217, 69, tamaño 11x11
    if (estaDentroDelArea(x, y, escalarX(217), escalarY(69), escalarAncho(11), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::PANTALLA_PRINCIPAL);
    }
    // Toggle música: 185, 111, tamaño 17x10
    else if (estaDentroDelArea(x, y, escalarX(185), escalarY(111), escalarAncho(17), escalarAlto(10))) {
        reproducirSonidoClick();
        configuracionAudio = ConfiguracionAudio::MUSICA_ON_SONIDO_ON;
        aplicarConfiguracionAudio();
        cambiarEstado(EstadoMenu::OPCIONES_11);
    }
    // Toggle sonido: 186, 127, tamaño 17x10
    else if (estaDentroDelArea(x, y, escalarX(186), escalarY(127), escalarAncho(17), escalarAlto(10))) {
        reproducirSonidoClick();
        configuracionAudio = ConfiguracionAudio::MUSICA_OFF_SONIDO_OFF;
        aplicarConfiguracionAudio();
        cambiarEstado(EstadoMenu::OPCIONES_00);
    }
    // Botón Info: 145, 141, tamaño 36x11
    else if (estaDentroDelArea(x, y, escalarX(145), escalarY(141), escalarAncho(36), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::INFO);
    }
}

// Manejar clics en opciones con música activada y sonido desactivado
void MenuManager::manejarClicOpciones10(int x, int y) {
    // Botón X cerrar: 217, 69, tamaño 11x11
    if (estaDentroDelArea(x, y, escalarX(217), escalarY(69), escalarAncho(11), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::PANTALLA_PRINCIPAL);
    }
    // Toggle música: 185, 111, tamaño 17x10
    else if (estaDentroDelArea(x, y, escalarX(185), escalarY(111), escalarAncho(17), escalarAlto(10))) {
        reproducirSonidoClick();
        configuracionAudio = ConfiguracionAudio::MUSICA_OFF_SONIDO_OFF;
        aplicarConfiguracionAudio();
        cambiarEstado(EstadoMenu::OPCIONES_00);
    }
    // Toggle sonido: 186, 127, tamaño 17x10
    else if (estaDentroDelArea(x, y, escalarX(186), escalarY(127), escalarAncho(17), escalarAlto(10))) {
        reproducirSonidoClick();
        configuracionAudio = ConfiguracionAudio::MUSICA_ON_SONIDO_ON;
        aplicarConfiguracionAudio();
        cambiarEstado(EstadoMenu::OPCIONES_11);
    }
    // Botón Info: 145, 141, tamaño 36x11
    else if (estaDentroDelArea(x, y, escalarX(145), escalarY(141), escalarAncho(36), escalarAlto(11))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::INFO);
    }
}

// Cambiar estado del menú y configurar elementos correspondientes
void MenuManager::cambiarEstado(EstadoMenu nuevoEstado) {
    estadoAnterior = estadoActual;
    estadoActual = nuevoEstado;

    if (nuevoEstado == EstadoMenu::INGRESA_NOMBRE) {
        escribiendoNombre = true;
        nombreJugador.clear();
        textoNombre.setString("_");
        cursorParpadeo.restart();
    } else {
        escribiendoNombre = false;
    }

    // Actualizar ranking para pantallas de resultado
    if (nuevoEstado == EstadoMenu::YOU_LOST || nuevoEstado == EstadoMenu::YOU_WON) {
        actualizarRanking();
    }

    // Configurar sprite según el estado
    switch (estadoActual) {
        case EstadoMenu::PANTALLA_PRINCIPAL:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("pantallaprincipal"));
            break;
        case EstadoMenu::INGRESA_NOMBRE:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("ingresarnombre"));
            break;
        case EstadoMenu::CREDITOS:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("creditos"));
            break;
        case EstadoMenu::INFO:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("info"));
            break;
        case EstadoMenu::OPCIONES_11:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("opciones11"));
            break;
        case EstadoMenu::OPCIONES_00:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("opciones00"));
            break;
        case EstadoMenu::OPCIONES_01:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("opciones01"));
            break;
        case EstadoMenu::OPCIONES_10:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("opciones10"));
            break;
        case EstadoMenu::YOU_LOST:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("youlost"));
            break;
        case EstadoMenu::YOU_WON:
            spritePantalla.setTexture(GestorRecursos::getInstance()->obtenerTextura("youwon"));
            break;
        case EstadoMenu::JUEGO:
            return; // Salir temprano para evitar el escalado
    }

    // Escalar las imágenes para llenar la ventana
    if (spritePantalla.getTexture()) {
        spritePantalla.setScale(factorEscalaX, factorEscalaY);
    }
}

// Aplicar configuración de audio al sistema
void MenuManager::aplicarConfiguracionAudio() {
    GestorAudio* audio = GestorAudio::getInstance();

    switch (configuracionAudio) {
        case ConfiguracionAudio::MUSICA_ON_SONIDO_ON:
            musicaActivada = true;
            sonidosActivados = true;
            break;
        case ConfiguracionAudio::MUSICA_OFF_SONIDO_OFF:
            musicaActivada = false;
            sonidosActivados = false;
            break;
        case ConfiguracionAudio::MUSICA_OFF_SONIDO_ON:
            musicaActivada = false;
            sonidosActivados = true;
            break;
        case ConfiguracionAudio::MUSICA_ON_SONIDO_OFF:
            musicaActivada = true;
            sonidosActivados = false;
            break;
    }

    // Aplicar configuración al GestorAudio
    audio->setMusicaActiva(musicaActivada);
    audio->setSonidosActivos(sonidosActivados);

    // Iniciar música del menú si está activada
    if (musicaActivada) {
        audio->reproducirMusica("musicaMenu");
    } else {
        audio->detenerMusica();
    }
}

// Reproducir sonido de clic si está habilitado
void MenuManager::reproducirSonidoClick() {
    if (sonidosActivados) {
        GestorAudio::getInstance()->reproducirSonido("click");
    }
}

// Verificar si un punto está dentro de un área rectangular
bool MenuManager::estaDentroDelArea(int x, int y, int areaX, int areaY, int ancho, int alto) {
    return (x >= areaX && x <= areaX + ancho && y >= areaY && y <= areaY + alto);
}

// Escalar coordenada X de resolución original a actual
int MenuManager::escalarX(int coordenadaOriginal) {
    return static_cast<int>(std::round(coordenadaOriginal * factorEscalaX));
}

// Escalar coordenada Y de resolución original a actual
int MenuManager::escalarY(int coordenadaOriginal) {
    return static_cast<int>(std::round(coordenadaOriginal * factorEscalaY));
}

// Escalar ancho de resolución original a actual
int MenuManager::escalarAncho(int anchoOriginal) {
    return static_cast<int>(std::round(anchoOriginal * factorEscalaX));
}

// Escalar alto de resolución original a actual
int MenuManager::escalarAlto(int altoOriginal) {
    return static_cast<int>(std::round(altoOriginal * factorEscalaY));
}

// Actualizar lógica del menú
void MenuManager::actualizar() {
    // Lógica de actualización si es necesaria
}

// Dibujar todos los elementos del menú
void MenuManager::dibujar() {
    ventana.clear();
    ventana.draw(spritePantalla);

    // Si estamos en la pantalla de ingreso de nombre, dibujar la caja y el texto
    if (estadoActual == EstadoMenu::INGRESA_NOMBRE) {
        ventana.draw(cajaTexto);
        ventana.draw(textoNombre);
    }

    // Dibujar ranking en pantallas de resultado
    if (estadoActual == EstadoMenu::YOU_LOST || estadoActual == EstadoMenu::YOU_WON) {
        ventana.draw(fondoRanking);
        ventana.draw(tituloRanking);

        for (const auto& texto : textosRanking) {
            ventana.draw(texto);
        }
    }

    ventana.display();
}

// Obtener estado actual del menú
EstadoMenu MenuManager::getEstadoActual() const {
    return estadoActual;
}

// Verificar si debe iniciar el juego
bool MenuManager::debeIniciarJuego() const {
    return estadoActual == EstadoMenu::JUEGO;
}

// Configurar elementos de entrada de texto
void MenuManager::configurarTextoNombre() {
    // Configurar texto para mostrar el nombre
    textoNombre.setFont(GestorRecursos::getInstance()->obtenerFuente("interfaz"));
    textoNombre.setCharacterSize(static_cast<unsigned int>(24 * factorEscalaY));
    textoNombre.setFillColor(sf::Color::White);

    // Posición del texto
    float textoPosX = escalarX(92);
    float textoPosY = escalarY(118);
    textoNombre.setPosition(textoPosX, textoPosY);

    // Configurar caja de texto visual
    cajaTexto.setSize(sf::Vector2f(escalarAncho(154), escalarAlto(30)));
    cajaTexto.setPosition(textoPosX - 10, textoPosY - 5);
    cajaTexto.setFillColor(sf::Color(0, 0, 0, 100));
    cajaTexto.setOutlineThickness(2);
    cajaTexto.setOutlineColor(sf::Color::White);
}

// Manejar entrada de texto del teclado
void MenuManager::manejarEntradaTexto(sf::Event& evento) {
    if (estadoActual != EstadoMenu::INGRESA_NOMBRE) return;

    if (evento.type == sf::Event::TextEntered) {
        if (evento.text.unicode == 8) { // Backspace
            if (!nombreJugador.empty()) {
                nombreJugador.pop_back();
            }
        }
        else if (evento.text.unicode == 13 || evento.text.unicode == 10) { // Enter
            if (!nombreJugador.empty()) {
                // Guardar nuevo jugador con puntaje inicial 0
                gestorNombres.agregarJugador(nombreJugador, 0);
                cambiarEstado(EstadoMenu::JUEGO);
                return;
            }
        }
        else if (evento.text.unicode >= 32 && evento.text.unicode < 127) { // Caracteres válidos
            if (nombreJugador.length() < 15) { // Límite de caracteres
                nombreJugador += static_cast<char>(evento.text.unicode);
            }
        }

        // Actualizar texto mostrado con cursor parpadeante
        std::string textoMostrado = nombreJugador;
        if (cursorParpadeo.getElapsedTime().asSeconds() < 0.5f) {
            textoMostrado += "_";
        }
        textoNombre.setString(textoMostrado);

        // Reiniciar reloj del cursor
        if (cursorParpadeo.getElapsedTime().asSeconds() >= 1.0f) {
            cursorParpadeo.restart();
        }
    }
}

// Ejecutar bucle principal del menú
void MenuManager::ejecutarMenu() {
    while (ventana.isOpen() && estadoActual != EstadoMenu::JUEGO) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
                return;
            }

            manejarEventos(evento);
        }

        actualizar();
        dibujar();
    }
}

// Manejar clics en pantalla de derrota
void MenuManager::manejarClicYouLost(int x, int y) {
    // Botón "Inicio": 126, 151, tamaño 79x15
    if (estaDentroDelArea(x, y, escalarX(126), escalarY(151), escalarAncho(79), escalarAlto(15))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::PANTALLA_PRINCIPAL);
    }
}

// Manejar clics en pantalla de victoria
void MenuManager::manejarClicYouWon(int x, int y) {
    // Botón "Inicio": área ampliada para mejor detección
    if (estaDentroDelArea(x, y, escalarX(120), escalarY(145), escalarAncho(90), escalarAlto(25))) {
        reproducirSonidoClick();
        cambiarEstado(EstadoMenu::PANTALLA_PRINCIPAL);
    }
}