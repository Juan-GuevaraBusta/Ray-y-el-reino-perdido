#include "gestorNombres.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>

using json = nlohmann::json;

GestorNombres::GestorNombres(const std::string& archivo) : archivoNombres(archivo) {
    cargarNombres();
}

GestorNombres::~GestorNombres() {
    guardarNombres();
}

void GestorNombres::cargarNombres() {
    std::ifstream archivo(archivoNombres);
    if (archivo.is_open()) {
        try {
            json j;
            archivo >> j;

            if (j.contains("jugadores") && j["jugadores"].is_array()) {
                for (const auto& jugador : j["jugadores"]) {
                    DatosJugador datos;

                    if (jugador.contains("nombre") && jugador["nombre"].is_string()) {
                        datos.nombre = jugador["nombre"];
                    }

                    // Cargar puntaje (nuevo campo)
                    if (jugador.contains("puntaje") && jugador["puntaje"].is_number()) {
                        datos.puntaje = jugador["puntaje"];
                    } else {
                        datos.puntaje = 0; // Valor por defecto para registros antiguos
                    }

                    if (jugador.contains("orden") && jugador["orden"].is_number()) {
                        datos.orden = jugador["orden"];
                    }

                    if (jugador.contains("fecha_ultimo_juego") && jugador["fecha_ultimo_juego"].is_string()) {
                        datos.fechaUltimoJuego = jugador["fecha_ultimo_juego"];
                    }

                    jugadores.push_back(datos);
                }
            }

            std::cout << "✓ Cargados " << jugadores.size() << " jugadores desde " << archivoNombres << std::endl;
        } catch (const std::exception& e) {
            std::cout << "⚠ Error al leer archivo JSON: " << e.what() << std::endl;
            jugadores.clear();
        }
    } else {
        std::cout << "ℹ Archivo " << archivoNombres << " no encontrado. Se creará uno nuevo." << std::endl;
    }
    archivo.close();
}

void GestorNombres::agregarJugador(const std::string& nombre, int puntaje) {
    if (!nombre.empty() && nombre.length() <= 20) {
        std::cout << "👤 === AGREGANDO NUEVO JUGADOR ===" << std::endl;
        std::cout << "   Nombre: '" << nombre << "'" << std::endl;
        std::cout << "   Puntaje inicial: " << puntaje << std::endl;

        DatosJugador nuevoJugador;
        nuevoJugador.nombre = nombre;
        nuevoJugador.puntaje = puntaje;
        nuevoJugador.orden = jugadores.size() + 1;

        // Agregar timestamp actual
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        nuevoJugador.fechaUltimoJuego = ss.str();

        jugadores.push_back(nuevoJugador);

        std::cout << "✓ Jugador agregado a la lista interna" << std::endl;
        std::cout << "   Total jugadores: " << jugadores.size() << std::endl;

        // Guardar inmediatamente
        guardarNombres();

        std::cout << "👤 === FIN AGREGAR JUGADOR ===" << std::endl;
    } else {
        std::cout << "❌ ERROR: Nombre inválido" << std::endl;
        std::cout << "   Nombre: '" << nombre << "'" << std::endl;
        std::cout << "   Longitud: " << nombre.length() << std::endl;
    }
}

void GestorNombres::actualizarPuntajeUltimoJugador(int nuevoPuntaje) {
    if (!jugadores.empty()) {
        DatosJugador& ultimoJugador = jugadores.back();

        std::cout << "🔄 === ACTUALIZANDO PUNTAJE ===" << std::endl;
        std::cout << "   👤 Jugador: " << ultimoJugador.nombre << std::endl;
        std::cout << "   📊 Puntaje anterior: " << ultimoJugador.puntaje << std::endl;
        std::cout << "   📈 Puntaje nuevo: " << nuevoPuntaje << std::endl;

        ultimoJugador.puntaje = nuevoPuntaje;

        // Actualizar timestamp
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        ultimoJugador.fechaUltimoJuego = ss.str();

        std::cout << "✓ Puntaje actualizado exitosamente" << std::endl;

        // Guardar inmediatamente
        guardarNombres();

        // Verificar que se guardó correctamente
        std::cout << "📁 Verificando archivo guardado..." << std::endl;
        std::vector<DatosJugador> verificacion = obtenerTop10();

        if (!verificacion.empty()) {
            std::cout << "✓ Archivo verificado. Mejores puntajes:" << std::endl;
            for (int i = 0; i < std::min(3, (int)verificacion.size()); i++) {
                std::cout << "   " << (i+1) << ". " << verificacion[i].nombre
                          << " - " << verificacion[i].puntaje << " pts" << std::endl;
            }
        } else {
            std::cout << "❌ Error: El archivo parece estar vacío tras guardar" << std::endl;
        }

        std::cout << "🔄 === FIN ACTUALIZACIÓN ===" << std::endl;

    } else {
        std::cout << "❌ ERROR: No hay jugadores registrados para actualizar puntaje" << std::endl;
        std::cout << "   Cantidad de jugadores: " << jugadores.size() << std::endl;
    }
}

void GestorNombres::guardarNombres() {
    try {
        json j;
        j["jugadores"] = json::array();

        for (const auto& jugador : jugadores) {
            json jugadorJson;
            jugadorJson["nombre"] = jugador.nombre;
            jugadorJson["puntaje"] = jugador.puntaje;
            jugadorJson["orden"] = jugador.orden;

            if (!jugador.fechaUltimoJuego.empty()) {
                jugadorJson["fecha_ultimo_juego"] = jugador.fechaUltimoJuego;
            }

            j["jugadores"].push_back(jugadorJson);
        }

        std::ofstream archivo(archivoNombres);
        if (archivo.is_open()) {
            archivo << j.dump(4); // Formato bonito con indentación
            std::cout << "✓ Datos de jugadores guardados en " << archivoNombres << std::endl;
        } else {
            std::cerr << "✗ Error al abrir archivo para escritura: " << archivoNombres << std::endl;
        }
        archivo.close();

    } catch (const std::exception& e) {
        std::cerr << "✗ Error al guardar datos de jugadores: " << e.what() << std::endl;
    }
}

const std::vector<DatosJugador>& GestorNombres::obtenerJugadores() const {
    return jugadores;
}

DatosJugador GestorNombres::obtenerUltimoJugador() const {
    return jugadores.empty() ? DatosJugador() : jugadores.back();
}

bool GestorNombres::nombreExiste(const std::string& nombre) const {
    for (const auto& jugador : jugadores) {
        if (jugador.nombre == nombre) {
            return true;
        }
    }
    return false;
}

std::vector<DatosJugador> GestorNombres::obtenerTop10() const {
    std::vector<DatosJugador> ranking = jugadores;

    // Ordenar por puntaje de mayor a menor
    std::sort(ranking.begin(), ranking.end(),
              [](const DatosJugador& a, const DatosJugador& b) {
                  return a.puntaje > b.puntaje;
              });

    // Tomar solo los primeros 10
    if (ranking.size() > 10) {
        ranking.resize(10);
    }

    return ranking;
}