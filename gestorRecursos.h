/*
La clase GestorRecursos maneja la carga, almacenamiento y distribución de todos los recursos gráficos y de audio
de Ray y el Reino Perdido usando el patrón Singleton. Se encarga de cargar texturas desde archivos PNG para
personajes, bloques y objetos, fuentes tipográficas para la interfaz de usuario, efectos de sonido en formato WAV
y música de fondo en formato OGG. La clase GestorRecursos implementa un sistema robusto de manejo de excepciones
que crea rectángulos de colores como texturas de respaldo cuando falla la carga de recursos, garantizando que
el juego pueda continuar funcionando sin interrupciones visuales. Los rectángulos de respaldo usan colores
específicos: verde para Ray, café para Hormigas NPC, rojo para enemigos y otros colores para diferentes objetos.
*/

#ifndef GESTOR_RECURSOS_H
#define GESTOR_RECURSOS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>  // *** NUEVO: Para audio ***
#include <map>
#include <string>
#include <cstdint>

class GestorRecursos
{
private:
    // Atributos
    std::map<std::string, sf::Texture> texturas;
    std::map<std::string, sf::Font> fuentes;
    // *** NUEVO: Mapas para audio ***
    std::map<std::string, sf::SoundBuffer> buffersSonido;
    std::map<std::string, sf::Music*> musicas;

    // Constructor privado (singleton)
    GestorRecursos();
    void cargarTextura(std::string ruta, std::string nombre);
    void cargarTexturaDesdeMemoria(const void* datos, std::size_t tamaño, const std::string& nombreTextura);
    void cargarFuente(std::string ruta, std::string nombre);
    void cargarFuenteDesdeMemoria(const void* datos, std::size_t tamaño, const std::string& nombreFuente);
    // *** NUEVO: Métodos para audio ***
    void cargarSonido(std::string ruta, std::string nombre);
    void cargarMusica(std::string ruta, std::string nombre);

public:
    // Métodos
    ~GestorRecursos();
    static GestorRecursos* getInstance()
    {
        static GestorRecursos instancia;
        return &instancia;
    }

    void limpiar();

    sf::Texture& obtenerTextura(std::string nombre)
    {
        return this->texturas[nombre];
    }

    sf::Font& obtenerFuente(std::string nombre)
    {
        return this->fuentes[nombre];
    }

    // *** NUEVO: Métodos para obtener audio ***
    sf::SoundBuffer& obtenerSonido(std::string nombre)
    {
        return this->buffersSonido[nombre];
    }

    sf::Music* obtenerMusica(std::string nombre)
    {
        return this->musicas[nombre];
    }
};

#endif // GESTOR_RECURSOS_H