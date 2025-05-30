/*
La clase GestorNombres maneja la persistencia de datos de jugadores de Ray y el Reino Perdido usando archivos JSON.
Se encarga de almacenar nombres de jugadores, puntajes finales, fechas de última partida y orden de registro para
crear un sistema de ranking persistente. La clase GestorNombres carga datos existentes al inicio del programa,
actualiza puntajes cuando los jugadores completan partidas, genera el Top 10 de mejores puntajes ordenados de
mayor a menor, y guarda automáticamente los cambios al archivo JSON. Incluye validación de entrada de nombres
con límites de caracteres y manejo de caracteres ASCII válidos para evitar corrupción de datos. Los datos
persisten entre sesiones del juego y se muestran en la pantalla YouWon cuando Ray completa su aventura.
*/

#ifndef GESTOR_NOMBRES_H
#define GESTOR_NOMBRES_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

// Estructura para almacenar información completa del jugador
struct DatosJugador {
    std::string nombre;
    int puntaje;
    std::string fechaUltimoJuego;
    int orden;

    DatosJugador(const std::string& n = "", int p = 0, int o = 0)
        : nombre(n), puntaje(p), orden(o) {}
};

class GestorNombres {
private:
    std::string archivoNombres;
    std::vector<DatosJugador> jugadores;

    void cargarNombres();

public:
    GestorNombres(const std::string& archivo = "nombres_jugadores.json");
    ~GestorNombres();

    // Métodos principales
    void agregarJugador(const std::string& nombre, int puntaje = 0);
    void actualizarPuntajeUltimoJugador(int nuevoPuntaje);
    void guardarNombres();

    // Métodos de consulta
    const std::vector<DatosJugador>& obtenerJugadores() const;
    DatosJugador obtenerUltimoJugador() const;
    bool nombreExiste(const std::string& nombre) const;

    // Métodos para Top 10
    std::vector<DatosJugador> obtenerTop10() const;

    // Métodos de utilidad
    size_t obtenerCantidadJugadores() const { return jugadores.size(); }
    void limpiarJugadores() { jugadores.clear(); }
    bool estaVacio() const { return jugadores.empty(); }
};


#endif // GESTOR_NOMBRES_H