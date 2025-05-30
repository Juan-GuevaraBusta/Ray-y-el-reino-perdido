#include "gestorRecursos.h"
#include <iostream>
#include <fstream>

GestorRecursos::GestorRecursos()
{
    std::cout << "Inicializando GestorRecursos: Las texturas, fuentes y audio se cargarán cuando se soliciten." << std::endl;

    // Cargar fuentes
    cargarFuente("texto/04B_30__.TTF", "interfaz");

    // Cargar texturas (mantener las existentes)
    cargarTextura("escenarios/fondo1.png", "fondo1");
    cargarTextura("escenarios/fondo2.png", "fondo2");
    cargarTextura("escenarios/fondo3.png", "fondo3");
    cargarTextura("bloques/bloque1.png", "bloque1");
    cargarTextura("bloques/bloque2.png", "bloque2");
    cargarTextura("bloques/bloque3.png", "bloque3");
    cargarTextura("hormigaInfectada/hormigaInfectadaViva/INFleft_1.png", "hI_vivaizq1");
    cargarTextura("hormigaInfectada/hormigaInfectadaViva/INFleft_2.png", "hI_vivaizq2");
    cargarTextura("hormigaInfectada/hormigaInfectadaViva/INFright_1.png", "hI_vivader1");
    cargarTextura("hormigaInfectada/hormigaInfectadaViva/INFright_2.png", "hI_vivader2");
    cargarTextura("hormigaInfectada/hormigaInfectadaMuerta/INFMleft.png", "hI_muertaizq");
    cargarTextura("hormigaInfectada/hormigaInfectadaMuerta/INFMright.png", "hI_muertader");
    cargarTextura("hormigaNormal/antleft_1.png", "hN_izq1");
    cargarTextura("hormigaNormal/antleft_2.png", "hN_izq2");
    cargarTextura("hormigaNormal/antright_1.png", "hN_der1");
    cargarTextura("hormigaNormal/antright_2.png", "hN_der2");
    cargarTextura("otros/espora1.png", "espora1");
    cargarTextura("otros/espora2.png", "espora2");
    cargarTextura("otros/lumiazul.png", "lumiazul");
    cargarTextura("otros/semilla.png", "semilla");
    cargarTextura("otros/portal1.png", "portal1");
    cargarTextura("otros/portal2.png", "portal2");
    cargarTextura("otros/portal3.png", "portal3");
    cargarTextura("otros/portal4.png", "portal4");
    cargarTextura("otros/portal5.png", "portal5");
    cargarTextura("otros/portal6.png", "portal6");
    cargarTextura("otros/portal7.png", "portal7");
    cargarTextura("otros/portal8.png", "portal8");
    cargarTextura("otros/portal9.png", "portal9");
    cargarTextura("ray/rayHerido/RHAleft.png", "rHA_izq");
    cargarTextura("ray/rayHerido/RHAright.png", "rHA_der");
    cargarTextura("ray/rayHerido/RHfront_1.png", "rH_front1");
    cargarTextura("ray/rayHerido/RHfront_2.png", "rH_front2");
    cargarTextura("ray/rayHerido/RHleft_1.png", "rH_izq1");
    cargarTextura("ray/rayHerido/RHleft_2.png", "rH_izq2");
    cargarTextura("ray/rayHerido/RHright_1.png", "rH_der1");
    cargarTextura("ray/rayHerido/RHright_2.png", "rH_der2");
    cargarTextura("ray/raySano/RSAleft.png", "rSA_izq");
    cargarTextura("ray/raySano/RSAright.png", "rSA_der");
    cargarTextura("ray/raySano/RSfront_1.png", "rS_front1");
    cargarTextura("ray/raySano/RSfront_2.png", "rS_front2");
    cargarTextura("ray/raySano/RSleft_1.png", "rS_izq1");
    cargarTextura("ray/raySano/RSleft_2.png", "rS_izq2");
    cargarTextura("ray/raySano/RSright_1.png", "rS_der1");
    cargarTextura("ray/raySano/RSright_2.png", "rS_der2");
    cargarTextura("ray/raySinCasco/RAleft.png", "rA_izq");
    cargarTextura("ray/raySinCasco/RAright.png", "rA_der");
    cargarTextura("ray/raySinCasco/Rfront_1.png", "r_front1");
    cargarTextura("ray/raySinCasco/Rfront_2.png", "r_front2");
    cargarTextura("ray/raySinCasco/Rleft_1.png", "r_izq1");
    cargarTextura("ray/raySinCasco/Rleft_2.png", "r_izq2");
    cargarTextura("ray/raySinCasco/Rright_1.png", "r_right1");
    cargarTextura("ray/raySinCasco/Rright_2.png", "r_right2");
    cargarTextura("ray/rayMuerto/RMleft.png", "rM_izq");
    cargarTextura("ray/rayMuerto/RMright.png", "rM_der");
    cargarTextura("reyHongo/hongoVivo/hongoataque_1.png", "hVA_1");
    cargarTextura("reyHongo/hongoVivo/hongoataque_2.png", "hVA_2");
    cargarTextura("reyHongo/hongoVivo/hongofront_1.png", "hV_front1");
    cargarTextura("reyHongo/hongoVivo/hongofront_2.png", "hV_front2");
    cargarTextura("reyHongo/hongoVivo/hongoleft_1.png", "hV_izq1");
    cargarTextura("reyHongo/hongoVivo/hongoleft_2.png", "hV_izq2");
    cargarTextura("reyHongo/hongoMuerto/hongoMfront_1.png", "hM_front1");
    cargarTextura("reyHongo/hongoMuerto/hongoMfront_2.png", "hM_front2");
    cargarTextura("reyHongo/hongoMuerto/hongoMleft_1.png", "hM_izq1");
    cargarTextura("reyHongo/hongoMuerto/hongoMleft_2.png", "hM_izq2");
    cargarTextura("pantallas/pantallaprincipal.png", "pantallaprincipal");
    cargarTextura("pantallas/ingresarnombre.png", "ingresarnombre");
    cargarTextura("pantallas/creditos.png", "creditos");
    cargarTextura("pantallas/info.png", "info");
    cargarTextura("pantallas/opciones11.png", "opciones11");
    cargarTextura("pantallas/opciones00.png", "opciones00");
    cargarTextura("pantallas/opciones01.png", "opciones01");
    cargarTextura("pantallas/opciones10.png", "opciones10");
    cargarTextura("pantallas/YouLost.png", "youlost");
    cargarTextura("pantallas/YouWon.png", "youwon");

    // *** MEJORADO: Cargar efectos de sonido con manejo de errores ***
    std::cout << "Cargando efectos de sonido..." << std::endl;
    cargarSonido("audio/efectos/ataque.wav", "rayAtaque");
    cargarSonido("audio/efectos/recibirDano.wav", "rayHerido");
    cargarSonido("audio/efectos/muerte.wav", "rayMuerte");
    cargarSonido("audio/efectos/salto.wav", "raySalto");
    cargarSonido("audio/efectos/rayCaminando.wav", "rayCaminando");
    cargarSonido("audio/efectos/rayCurando.wav", "rayCurando");
    cargarSonido("audio/efectos/recogerItem.wav", "recogerItem");
    cargarSonido("audio/efectos/superGolpe.wav", "superGolpe");
    cargarSonido("audio/efectos/enemigoMuere.wav", "enemigoMuere");
    cargarSonido("audio/efectos/recogerItem.wav", "click");

    // *** MEJORADO: Cargar música de fondo con manejo de errores ***
    std::cout << "Cargando música de fondo..." << std::endl;
    cargarMusica("audio/musica/nivel1.ogg", "musicaNivel1");
    cargarMusica("audio/musica/nivel2.ogg", "musicaNivel2");
    cargarMusica("audio/musica/nivel3.ogg", "musicaNivel3");
    cargarMusica("audio/musica/musicamenu.ogg", "musicaMenu");

    std::cout << "GestorRecursos inicializado correctamente." << std::endl;
}

GestorRecursos::~GestorRecursos()
{
    // *** NUEVO: Limpiar música ***
    for (auto& par : musicas) {
        delete par.second;
    }
}

void GestorRecursos::limpiar()
{
    texturas.clear();
    fuentes.clear();
    buffersSonido.clear();

    // *** NUEVO: Limpiar música ***
    for (auto& par : musicas) {
        delete par.second;
    }
    musicas.clear();
}

void GestorRecursos::cargarTextura(std::string ruta, std::string nombre)
{
    sf::Texture textura;
    if (textura.loadFromFile(ruta))
        this->texturas[nombre] = textura;
    else
        std::cerr << "Error al cargar textura: " << ruta << std::endl;
}

void GestorRecursos::cargarTexturaDesdeMemoria(const void* datos, std::size_t tamaño, const std::string& nombreTextura)
{
    sf::Texture textura;
    if (textura.loadFromMemory(datos, tamaño))
    {
        this->texturas[nombreTextura] = textura;
    }
    else
    {
        std::cerr << "Error al cargar textura desde memoria: " << nombreTextura << std::endl;
    }
}

void GestorRecursos::cargarFuente(std::string ruta, std::string nombre)
{
    sf::Font fuente;
    if (fuente.loadFromFile(ruta))
        this->fuentes[nombre] = fuente;
    else
        std::cerr << "Error al cargar fuente: " << ruta << std::endl;
}

void GestorRecursos::cargarFuenteDesdeMemoria(const void* datos, std::size_t tamaño, const std::string& nombreFuente)
{
    sf::Font fuente;
    if (fuente.loadFromMemory(datos, tamaño))
    {
        this->fuentes[nombreFuente] = fuente;
    }
    else
    {
        std::cerr << "Error al cargar fuente desde memoria: " << nombreFuente << std::endl;
    }
}

// *** MEJORADO: Método para cargar audio con mejor manejo de errores ***
void GestorRecursos::cargarSonido(std::string ruta, std::string nombre)
{
    // Verificar si el archivo existe
    std::ifstream archivo(ruta);
    if (!archivo.good()) {
        std::cerr << "ERROR: El archivo de sonido no existe: " << ruta << std::endl;

        // Crear un buffer de sonido silencioso como respaldo
        sf::SoundBuffer bufferSilencioso;
        sf::Int16 silencio[1000] = {0}; // 1000 muestras de silencio
        if (bufferSilencioso.loadFromSamples(silencio, 1000, 1, 44100)) {
            this->buffersSonido[nombre] = bufferSilencioso;
            std::cout << "Cargado sonido silencioso como respaldo para: " << nombre << std::endl;
        }
        return;
    }
    archivo.close();

    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(ruta))
    {
        this->buffersSonido[nombre] = buffer;
        std::cout << "✓ Sonido cargado exitosamente: " << nombre << " desde " << ruta << std::endl;
    }
    else
    {
        std::cerr << "✗ Error al cargar sonido: " << ruta << std::endl;
        std::cerr << "  Formatos soportados por SFML: OGG, WAV (16-bit PCM), FLAC" << std::endl;
        std::cerr << "  Asegúrate de que el archivo WAV sea de 16-bit PCM" << std::endl;

        // Crear un buffer de sonido silencioso como respaldo
        sf::SoundBuffer bufferSilencioso;
        sf::Int16 silencio[1000] = {0}; // 1000 muestras de silencio
        if (bufferSilencioso.loadFromSamples(silencio, 1000, 1, 44100)) {
            this->buffersSonido[nombre] = bufferSilencioso;
            std::cout << "Cargado sonido silencioso como respaldo para: " << nombre << std::endl;
        }
    }
}

void GestorRecursos::cargarMusica(std::string ruta, std::string nombre)
{
    // Verificar si el archivo existe
    std::ifstream archivo(ruta);
    if (!archivo.good()) {
        std::cerr << "ERROR: El archivo de música no existe: " << ruta << std::endl;
        return;
    }
    archivo.close();

    sf::Music* musica = new sf::Music();
    if (musica->openFromFile(ruta))
    {
        this->musicas[nombre] = musica;
        std::cout << "✓ Música cargada exitosamente: " << nombre << " desde " << ruta << std::endl;
    }
    else
    {
        std::cerr << "✗ Error al cargar música: " << ruta << std::endl;
        std::cerr << "  Formatos soportados: OGG, FLAC, WAV" << std::endl;
        delete musica;
    }
}