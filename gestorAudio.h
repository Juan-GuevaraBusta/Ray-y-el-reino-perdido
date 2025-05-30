/*
La clase GestorAudio gestiona todo el sistema de audio de Ray y el Reino Perdido.
Se encarga de reproducir música de fondo que cambia según el nivel actual del juego, efectos de sonido para
acciones de Ray como ataques, saltos y recibir daño, sonidos ambientales para recolección de objetos y
eliminación de enemigos, y controles de volumen independientes para música y efectos. La clase GestorAudio
proporciona configuración de audio desde el sistema de menús permitiendo activar o desactivar música y sonidos
por separado, manejo de múltiples sonidos simultáneos, y reproducción en bucle automático para música de fondo.
Incluye manejo robusto de errores para continuar el juego sin audio cuando los archivos no están disponibles.
*/

#ifndef GESTOR_AUDIO_H
#define GESTOR_AUDIO_H

#include <SFML/Audio.hpp>
#include <map>
#include <string>

class GestorAudio
{
private:
    // Atributos
    sf::Music* musicaActual;
    std::map<std::string, sf::Sound> sonidos;
    float volumenMusica;
    float volumenEfectos;
    bool sonidosActivos = true;
    bool musicaActiva = true;

    // Constructor privado (singleton)
    GestorAudio();

public:
    // Métodos
    ~GestorAudio();
    static GestorAudio* getInstance()
    {
        static GestorAudio instancia;
        return &instancia;
    }

    // Métodos para música
    void reproducirMusica(const std::string& nombre, bool loop = true);
    void detenerMusica();
    void pausarMusica();
    void reanudarMusica();
    void setVolumenMusica(float volumen); // 0.0f a 100.0f

    // Métodos para efectos de sonido
    void reproducirSonido(const std::string& nombre);
    void setVolumenEfectos(float volumen); // 0.0f a 100.0f

    // Métodos de utilidad
    bool musicaReproduciendose();
    void detenerTodo();

    // Métodos para gestión del menú
    void setSonidosActivos(bool activos);
    void setMusicaActiva(bool activa);
    bool getSonidosActivos() const;
    bool getMusicaActiva() const;
};

#endif // GESTOR_AUDIO_H