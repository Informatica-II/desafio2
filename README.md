# UdeATunes


# 🎵 Vive la música con \*\*UdeATunes\*\*
---

## 

## > Proyecto académico — Programación Orientada a Objetos en C++  

## > Universidad de Antioquia – 2025  

## > Revisado por los profesores \*\*Aníbal Guerra\*\* y \*\*Augusto Salazar\*\*

## 

## ---

## 

## \## 📖 Descripción General

## 

## \*\*UdeATunes\*\* es un prototipo de sistema de \*streaming musical\* diseñado como ejercicio académico para modelar un escenario real mediante el paradigma de \*\*Programación Orientada a Objetos (POO)\*\* en \*\*C++\*\*.

## 

## El programa emula el funcionamiento de una plataforma de música digital similar a Spotify o Deezer, gestionando usuarios, artistas, álbumes, canciones, listas de reproducción y mensajes publicitarios, todo mediante estructuras de datos dinámicas propias (sin uso de STL).

## 

## El desarrollo se centra en la correcta aplicación de los principios de POO:  

## \*\*abstracción, encapsulación, relaciones, herencia, polimorfismo, sobrecarga y uso de plantillas.\*\*

## 

## ---

## 

## \## 🎯 Objetivos

## 

## \- Desarrollar la capacidad de \*\*análisis y solución de problemas\*\* modelando un contexto real.  

## \- Verificar la adquisición de \*\*competencias en POO con C++\*\*.  

## \- Evaluar la \*\*eficiencia en el uso de estructuras de datos dinámicas\*\*.  

## \- Implementar un sistema \*\*modular, escalable y bien documentado\*\*.

## 

## ---

## 

## \## 🧠 Contexto

## 

## La música impacta positivamente la salud y el bienestar emocional. En la actualidad, los servicios de streaming concentran la mayor parte del consumo musical.  

## \*\*UdeATunes\*\* busca simular este entorno digital y proporcionar una experiencia completa de usuario dentro de una aplicación de consola.

## 

## Cada usuario puede ser:

## \- \*\*Estándar\*\*: escucha canciones a 128 kbps, con publicidad.  

## \- \*\*Premium\*\*: escucha en 320 kbps, sin publicidad, y tiene funciones exclusivas como listas personalizadas y seguimiento de favoritos.

## 

## ---

## 

## \## 🧩 Características Principales

## 

## \### 🧱 I. Carga / Actualización de Datos

## \- Manejo de archivos externos para almacenar información persistente.  

## \- Estructuras propias para usuarios, artistas, álbumes, canciones y publicidad.

## 

## \### 🔐 II. Inicio de Sesión

## \- Validación de credenciales de usuario.  

## \- Menús dinámicos según tipo de cuenta (estándar o premium).

## 

## \### 🔀 III. Reproducción Aleatoria

## \- Reproduce canciones de toda la plataforma al azar.  

## \- Muestra rutas completas de los archivos `.ogg` y portadas `.png`.  

## \- Simula anuncios con prioridad según categoría (C, B, AAA).  

## \- Temporizador automático de cambio de canción (3 segundos).  

## 

## \### 💛 IV. Mi Lista de Favoritos (solo Premium)

## \- Agregar o eliminar canciones favoritas (sin duplicados).  

## \- Seguir listas de otros usuarios premium.  

## \- Reproducir la lista en orden o aleatorio.  

## \- Control de navegación (previa, siguiente, repetir, detener).  

## 

## \### ⚙️ V. Medición del Consumo de Recursos

## \- Cálculo de:  

## &nbsp; - 🔁 Iteraciones ejecutadas.  

## &nbsp; - 💾 Memoria total en uso (estructuras + variables locales).  

## \- Métricas mostradas en consola al finalizar cada funcionalidad.

## 

## ---

## 

## \## 🧮 Requisitos Técnicos

## 

## \- Lenguaje: \*\*C++ (POO)\*\*  

## \- Interfaz: \*\*Consola (CLI)\*\*  

## \- \*\*No se permite el uso de la STL\*\*  

## \- Uso obligatorio de:

## &nbsp; - Constructores de copia  

## &nbsp; - Getters / Setters  

## &nbsp; - Sobrecarga de métodos y operadores (mínimo 2)  

## &nbsp; - Memoria dinámica  

## \- Estructuras de datos diseñadas a medida (listas, arreglos, etc.)

## 

## ---

## 

## \## 🧰 Estructura del Proyecto

## 

## 📁 UdeATunes/

## ├── src/

## │ ├── main.cpp

## │ ├── GestorUsuarios.cpp

## │ ├── GestorArtistas.cpp

## │ ├── GestorCanciones.cpp

## │ └── ...

## ├── include/

## │ ├── Usuario.h

## │ ├── Artista.h

## │ ├── Album.h

## │ ├── Cancion.h

## │ └── ...

## ├── data/

## │ ├── usuarios.txt

## │ ├── artistas.txt

## │ ├── canciones.txt

## │ └── publicidad.txt

## ├── docs/

## │ ├── Diagrama\_Clases\_UML.pdf

## │ ├── Informe\_Analisis.pdf

## │ └── README.md

## └── CMakeLists.txt (o .pro file)

## 

## \##🧾 Evaluación del Proyecto

## Criterio	Descripción	Ponderación

## 📘 Diagrama UML	Diseño y modelado del sistema	10%

## ⚙️ Eficiencia	Selección y optimización de estructuras de datos	25%

## 📊 Métricas de Recursos	Medición de iteraciones y memoria	15%

## 💻 Implementación	Correctitud, modularidad y menú funcional	50%

## 

## 📹 Evidencia del Proyecto

## 🎥 Video de presentación y demostración (YouTube)

## 

## 💾 Repositorio en GitHub

## 

## 🧑‍💻 Autores

## Equipo de desarrollo:

## 

## 👤 Sergio Chaves

## sergio.chavesr@udea.edu.co



## 👤Óscar Sepulveda

## oscar.sepulveda2@udea.edu.co

## 

## Universidad de Antioquia — Facultad de Ingeniería

## Curso: INFORMATICA II - 2025-2

## 

## 🪪 Licencia

## Este proyecto es de carácter académico.

## © 2025 Universidad de Antioquia. Todos los derechos reservados.

