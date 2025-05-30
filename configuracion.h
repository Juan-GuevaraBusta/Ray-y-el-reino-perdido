/*
El archivo configuracion.h contiene todas las constantes de configuración globales de Ray y el Reino Perdido.
Define parámetros fundamentales del juego incluyendo dimensiones de ventana, velocidad de cuadros, tamaños de sprites,
colores de interfaz, y propiedades visuales de todos los elementos del juego. Esta centralización de configuración
permite ajustar fácilmente aspectos técnicos y visuales del juego desde un solo archivo, facilitando el mantenimiento
y la modificación de parámetros sin buscar valores dispersos por todo el código. Las constantes están organizadas
por categorías para mejorar la legibilidad y localización de configuraciones específicas.
*/

// Ventana:
#define ANCHO_VENTANA     1280
#define ALTO_VENTANA      720
#define TITULO_VENTANA    "Aventura de Hormigas"
#define VELOCIDAD_CUADROS 60
#define TAMAÑO_BLOQUE     40

// Menú:
#define CONTADOR_BOTONES  3
#define BOTON_ANCHO       320
#define BOTON_ALTO        80
#define SELECCIONADO      sf::Color::Red
#define NO_SELECCIONADO   sf::Color::White

// Mundo:
#define COLOR_BORDE       sf::Color(20, 24, 30)
#define COLOR_COLECCIONABLE sf::Color(180, 250, 0, 100)

// Jugador (Ray):
#define TAMAÑO_CUADRO_JUGADOR  sf::Vector2i(24, 32)
#define ORIGEN_JUGADOR         sf::Vector2f(12, 16)

// HormigaInfectada:
#define TAMAÑO_CUADRO_HORMIGA_INFECTADA  sf::Vector2i(24, 21)
#define ORIGEN_HORMIGA_INFECTADA         sf::Vector2f(12, 10.5)

// Hormiga Sana

#define TAMAÑO_CUADRO_HORMIGA_SANA  sf::Vector2i(24, 21)
#define ORIGEN_HORMIGA_SANA         sf::Vector2f(12, 10.5)

// Coleccionables:
#define TAMAÑO_CUADRO_LUZ      sf::Vector2i(200, 200)
#define TAMAÑO_CUADRO_SEMILLA  sf::Vector2i(200, 200)

// HormigaInfectada:
#define TAMAÑO_CUADRO_REY_HONGO  sf::Vector2i(48, 42)
#define ORIGEN_REY_HONGO       sf::Vector2f(24, 21)