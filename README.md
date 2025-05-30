# RAY Y EL REINO PERDIDO

**PROYECTO FINAL PROGRAMACIÓN ORIENTADA A OBJETOS**

**Créditos:**
- Juan Guevara
- Isabel Adrada
- María Gil

## **Introducción**

En las profundidades subterráneas del Reino de Paradise, una próspera colonia de hormigas vivía en perfecta armonía hasta que una amenaza siniestra comenzó a propagarse. Las hormigas que antes marchaban en formación perfecta ahora se comportan de manera errática, como títeres controlados por una fuerza invisible. Un hongo letal ha comenzado su invasión, infectando a las trabajadoras y amenazando con destruir todo el reino. La reina convocó a Ray, una valiente hormiga exploradora equipada con un casco protector de hojas y un bastón luminoso, para descubrir el origen de esta plaga y enfrentar al Rey Hongo en una batalla final.

## **Historia del Juego**

Ray debe caminar por el laberinto del hormiguero, defenderse de las Hormigas Infectadas cubiertas de esporas que lo atacan al colisionar con él, y acabar con el Rey Hongo que está dañando al hormiguero. Las Hormigas Infectadas detectan a Ray cuando está cerca y lo persiguen. El juego termina cuando Ray mata al Rey Hongo y atraviesa el último portal, mostrando la pantalla YouWon con el Top 10 de jugadores.

## **Características del Juego**

### **Personajes Principales**

**Ray (Personaje Jugable)**
- Hormiga exploradora controlada por el jugador
- Porta un casco protector de hojas y un bastón que emite luz
- Tiene 3 estados de salud visual: Ray Sano (casco completo), Ray Herido (casco dañado), Ray Sin Casco
- Cuando llega a 0 de salud se muere y el jugador pierde
- Se mueve por el laberinto del hormiguero usando controles de teclado

**Rey Hongo (Jefe Final)**
- Entidad maligna con 15 puntos de salud
- Hace 1 punto de daño a Ray cuando ataca
- Al morir otorga 50 puntos al puntaje del jugador 
- Debe ser derrotado para completar el juego

**Hormigas Infectadas**
- Enemigos cubiertos de esporas del hongo
- Detectan a Ray cuando está cerca y lo persiguen
- Hacen 1 punto de daño cuando colisionan con Ray
- Existen variantes débiles (2 salud) y fuertes (4 salud)
- Al morir otorgan 5 puntos equivalentes a su salud inicial

**Hormigas Normales NPC**
- Hormigas aliadas que se mueven de forma aleatoria por el hormiguero
- No pueden ser atacadas ni atacan a Ray
- Representan la vida normal del hormiguero

### **Sistema de Juego**

**Mecánicas de Movimiento**
- Plataformas 2D con física de gravedad implementada con SFML
- Ray puede caminar izquierda/derecha y saltar
- Sistema de colisiones entre personajes y bloques del terreno

**Sistema de Salud Visual**
- Ray Sano: casco de hojas completo (3 puntos de salud)
- Ray Herido: casco dañado (2 puntos de salud)
- Ray Sin Casco: sin protección (1 punto de salud)
- Ray Muerto: fin del juego (0 puntos de salud)

**Sistema de Puntuación**

Ray comienza con 0 puntos, 0 luz y 3 de salud:

- **Recolectar luz**: +1 punto por cada luz bioluminiscente
- **Semillas**: Si Ray está herido (salud < 3), se realiza la curación de Ray (salud +1) al presionar X con un requerimiento de 10 semillas.
- **Eliminar enemigos**: Puntos = salud inicial del enemigo
    - Hormigas infectadas: 5 puntos
    - Rey Hongo: 50 puntos
- **Perder**: Si Ray muere, el puntaje se guarda en el archivo json.

### **Objetos del Mundo**

- **Luces Bioluminiscentes**: Incrementan puntuación y pueden potenciar ataques
- **Semillas**: Restauran salud o dan puntos según el estado de Ray
- **Portales**: Permiten transición entre niveles del hormiguero
- **Bloques**: Terreno sólido con diferentes texturas por nivel

### **Controles Implementados**

- **A/D**: Movimiento izquierda/derecha
- **W**: Saltar
- **X**: Curación de Ray
- **Espacio**: Ataque con bastón
- **Espacio + E**: Super golpe de Luz
- **R**: Reiniciar nivel
- **P**: Pausar juego
- **F**: Alternar pantalla completa
- **ESC**: Salir del juego

## **Arquitectura Técnica**

### **Tecnologías Utilizadas**

- **Lenguaje**: C++20
- **Gráficos y Audio**: SFML 2.5
- **Persistencia**: nlohmann/json para almacenamiento de datos
- **Build System**: CMake 3.30+

### **Implementación de SFML**

El juego utiliza SFML 2.5 para:

- **Gráficos**: sf::RenderWindow para la ventana principal, sf::Sprite para personajes y objetos, sf::Texture para imágenes
- **Eventos**: sf::Event para capturar input de teclado y eventos de ventana
- **Audio**: sf::Music para música de fondo y sf::Sound para efectos sonoros
- **Tiempo**: sf::Clock para controlar animaciones y temporizadores
- **Física**: sf::RectangleShape para cajas de colisión y detección de contacto

### **Estructura del Código**

**Gestores Principales**
- `GestorRecursos`: Carga texturas, fuentes y sonidos
- `GestorAudio`: Controla música de fondo y efectos de sonido
- `GestorNombres`: Maneja persistencia de jugadores en JSON

**Sistema de Juego**
- `Juego`: Motor principal que coordina toda la lógica
- `Mundo`: Carga niveles desde archivos de configuración
- `Ventana`: Manejo de ventana SFML y eventos del sistema

**Personajes**
- `Jugador`: Ray con sistema de salud visual y controles
- `HormigaInfectada`: Enemigos con IA de detección y persecución
- `HormigaNPC`: Hormigas aliadas con movimiento errático
- `ReyHongo`: Jefe final con 10 puntos de salud

**Interfaz**
- `MenuManager`: Gestiona menús y entrada de nombres
- `InterfazUsuario`: HUD con salud, puntuación y luz

### **Sistema de Persistencia y Top 10**

- Los nombres de jugadores se almacenan en `nombres_jugadores.json`
- Se guarda nombre, puntaje, fecha y orden de cada partida
- Al completar el juego o perder, se muestra el Top 10 de mejores puntajes

### **Administración de Excepciones**

**GestorRecursos - Manejo de Texturas Faltantes:**

Si falla la carga de una textura, se genera un rectángulo sf::RectangleShape del tamaño apropiado:
- Ray: rectángulo verde (24x32 píxeles)
- Hormigas NPC: rectángulo café (24x21 píxeles)
- Hormigas Infectadas: rectángulo rojo (24x21 píxeles)
- Rey Hongo: rectángulo rojo más grande (48x42 píxeles)

Este sistema garantiza continuidad del juego aunque falten recursos gráficos.

**Entrada de Nombres:**
- Validación de caracteres permitidos (ASCII 32-127)
- Límite de 15 caracteres por nombre

## **Instalación y Compilación**

### **Requisitos**

- Compilador C++20
- SFML 2.5+
- CMake 3.30+
- nlohmann/json (descarga automática)

### **Compilación**

```bash
mkdir build && cd build
cmake ..
make
./practica_sfml
```

## **Estructura de Archivos**

```
proyectoFinalPOO-main/
├── cmake-build-debug/         # Archivos de compilación
│   ├── _deps/                 # Dependencias (nlohmann/json)
│   ├── audio/                 # Música y efectos de sonido
│   │   ├── efectos/           # Archivos WAV de efectos
│   │   └── musica/            # Archivos OGG de música de fondo
│   ├── bloques/               # Texturas de bloques por nivel
│   ├── escenarios/            # Texturas de fondos de niveles
│   ├── hormigaInfectada/      # Sprites de Hormigas Infectadas
│   │   ├── hormigaInfectadaMuerta/
│   │   └── hormigaInfectadaViva/
│   ├── hormigaNormal/         # Sprites de Hormigas Normales NPC
│   ├── niveles/               # Archivos de configuración de escenarios
│   ├── otros/                 # Objetos coleccionables y portales
│   ├── Pantallas/             # Imágenes de menús y pantallas
│   ├── ray/                   # Sprites de Ray
│   │   ├── rayHerido/
│   │   ├── rayMuerto/
│   │   ├── raySano/
│   │   └── raySinCasco/
│   ├── reyHongo/              # Sprites del Rey Hongo
│   │   ├── hongoMuerto/
│   │   └── hongoVivo/
│   ├── Testing/               # Archivos de pruebas
│   ├── texto/                 # Fuentes tipográficas
|   └── nombres_jugadores.json # Base de datos de jugadores  
├── [archivos .h y .cpp]       # Código fuente del juego
└── CMakeLists.txt             # Configuración de compilación
```

## **Flujo del Juego**

### **Nivel 1**
Inicio de la aventura en el laberinto del hormiguero. Todo parece normal y Ray se encuentra principalmente con Hormigas Normales NPC que se mueven pacíficamente por los túneles. Este nivel sirve como introducción a los controles y mecánicas básicas del juego.

### **Nivel 2**
Ray comienza a ver el daño hecho por el hongo al empezar a encontrar las primeras Hormigas Infectadas. Estas criaturas cubiertas de esporas detectan y persiguen a Ray, siendo una antesala a la batalla final. El nivel aumenta la dificultad introduciendo enemigos activos.

### **Nivel 3**
La batalla final contra el Rey Hongo. Ray debe enfrentar al jefe final en su guarida, utilizando todas las habilidades aprendidas y la luz recolectada para derrotar a esta poderosa amenaza y restaurar la paz en el Reino de Paradise.

*"Algo se pudre en el corazón del hormiguero... y Ray debe enfrentarlo"*