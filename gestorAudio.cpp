#include "gestorAudio.h"
#include "gestorRecursos.h"
#include <iostream>

GestorAudio::GestorAudio()
{
    musicaActual = nullptr;
    volumenMusica = 60.0f;  // Volumen medio por defecto
    volumenEfectos = 65.0f; // Efectos un poco más altos
}

GestorAudio::~GestorAudio()
{
    detenerTodo();
}

void GestorAudio::reproducirMusica(const std::string& nombre, bool loop)
{
    if (!musicaActiva) return;
    try {
        // Detener música actual si está reproduciéndose
        if (musicaActual && musicaActual->getStatus() == sf::Music::Playing) {
            musicaActual->stop();
        }

        // Obtener nueva música del gestor de recursos
        musicaActual = GestorRecursos::getInstance()->obtenerMusica(nombre);

        if (musicaActual) {
            musicaActual->setLoop(loop);
            musicaActual->setVolume(volumenMusica);
            musicaActual->play();
            std::cout << "♪ Reproduciendo música: " << nombre << std::endl;
        } else {
            std::cout << "⚠ No se pudo encontrar la música: " << nombre << " (el juego continuará sin música)" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error al reproducir música " << nombre << ": " << e.what() << std::endl;
    }
}

void GestorAudio::detenerMusica()
{
    if (musicaActual && musicaActual->getStatus() != sf::Music::Stopped) {
        musicaActual->stop();
    }
}

void GestorAudio::pausarMusica()
{
    if (musicaActual && musicaActual->getStatus() == sf::Music::Playing) {
        musicaActual->pause();
    }
}

void GestorAudio::reanudarMusica()
{
    if (musicaActual && musicaActual->getStatus() == sf::Music::Paused) {
        musicaActual->play();
    }
}

void GestorAudio::setVolumenMusica(float volumen)
{
    volumenMusica = std::max(0.0f, std::min(100.0f, volumen));
    if (musicaActual) {
        musicaActual->setVolume(volumenMusica);
    }
}

void GestorAudio::reproducirSonido(const std::string& nombre)
{
    if (!sonidosActivos) return; // No reproducir si están desactivados
    try {
        // Buscar si ya tenemos este sonido cargado
        if (sonidos.find(nombre) == sonidos.end()) {
            // Verificar que el sonido existe en el gestor de recursos
            try {
                sf::SoundBuffer& buffer = GestorRecursos::getInstance()->obtenerSonido(nombre);
                sonidos[nombre].setBuffer(buffer);
                sonidos[nombre].setVolume(volumenEfectos);
            } catch (const std::exception& e) {
                std::cout << "⚠ Sonido no disponible: " << nombre << " (continuando sin sonido)" << std::endl;
                return;
            }
        }

        // Reproducir el sonido
        sf::Sound& sonido = sonidos[nombre];

        // Si ya está reproduciéndose, reiniciarlo
        if (sonido.getStatus() == sf::Sound::Playing) {
            sonido.stop();
        }

        sonido.play();

    } catch (const std::exception& e) {
        std::cout << "⚠ Error al reproducir sonido " << nombre << ": " << e.what() << " (continuando sin sonido)" << std::endl;
    }
}

void GestorAudio::setVolumenEfectos(float volumen)
{
    volumenEfectos = std::max(0.0f, std::min(100.0f, volumen));

    // Actualizar volumen de todos los sonidos cargados
    for (auto& par : sonidos) {
        par.second.setVolume(volumenEfectos);
    }
}

bool GestorAudio::musicaReproduciendose()
{
    return musicaActual && musicaActual->getStatus() == sf::Music::Playing;
}

void GestorAudio::detenerTodo()
{
    // Detener música
    detenerMusica();

    // Detener todos los sonidos
    for (auto& par : sonidos) {
        if (par.second.getStatus() == sf::Sound::Playing) {
            par.second.stop();
        }
    }
}

void GestorAudio::setSonidosActivos(bool activos) {
    sonidosActivos = activos;
    if (!activos) {
        // Detener todos los sonidos que estén reproduciéndose
        for (auto& par : sonidos) {
            if (par.second.getStatus() == sf::Sound::Playing) {
                par.second.stop();
            }
        }
    }
}

void GestorAudio::setMusicaActiva(bool activa) {
    musicaActiva = activa;
    if (!activa && musicaActual && musicaActual->getStatus() == sf::Music::Playing) {
        musicaActual->stop();
    }
}

bool GestorAudio::getSonidosActivos() const {
    return sonidosActivos;
}

bool GestorAudio::getMusicaActiva() const {
    return musicaActiva;
}