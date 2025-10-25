#include "Aplicacion.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

Aplicacion::Aplicacion() {
    gestorUsuarios = new GestorUsuarios();
    gestorCanciones = new GestorCanciones();
    gestorArtistas = new GestorArtistas();
    gestorAlbumes = new GestorAlbumes();
    usuarioActual = nullptr;
    cargarDatos();
}

Aplicacion::~Aplicacion() {
    delete gestorUsuarios;
    delete gestorCanciones;
    delete gestorArtistas;
    delete gestorAlbumes;
}

void Aplicacion::ejecutar() {
    int opcion;

    do {
        mostrarMenuPrincipal();
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();                       // Limpiar el '\n' restante

        switch(opcion) {
        case 1:
            login();
            break;
        case 2:
            registrarUsuario();
            break;
        case 3:
            gestorUsuarios->mostrarTodos();
            cout << "\nPresione Enter...";
            cin.get();
            break;
        case 0:
            salir();
            break;
        default:
            cout << "\nOpcion invalida\n";
            cout << "Presione Enter...";
            cin.get();
        }

    } while(opcion != 0);
}

void Aplicacion::cargarDatos() {
    cout << "\n[SISTEMA] Cargando datos...\n" << endl;
    gestorUsuarios->cargarDesdeArchivo("data/usuarios.txt");
    gestorCanciones->cargarDesdeArchivo("data/canciones.txt");
    gestorArtistas->cargarDesdeArchivo("data/artistas.txt");      // NUEVO
    gestorAlbumes->cargarDesdeArchivo("data/albunes.txt");
    cout << endl;
}

void Aplicacion::mostrarMenuPrincipal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "\n========================================" << endl;
    cout << "          U d e A T u n e s             " << endl;
    cout << "    Sistema de Streaming Musical       " << endl;
    cout << "========================================" << endl;
    cout << "\n    Vive la musica con nosotros\n" << endl;
    cout << "========================================" << endl;
    cout << "\n1. Iniciar Sesion" << endl;
    cout << "2. Registrarse" << endl;
    cout << "3. Ver usuarios registrados" << endl;
    cout << "0. Salir" << endl;
    cout << "========================================" << endl;
}

void Aplicacion::mostrarMenuUsuarioEstandar() {
    int opcion;

    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "\n========================================" << endl;
        cout << "          U d e A T u n e s             " << endl;
        cout << "        USUARIO ESTANDAR (GRATIS)       " << endl;
        cout << "========================================" << endl;
        cout << "\nBienvenido: " << usuarioActual->getNickname() << endl;
        cout << "Ciudad: " << usuarioActual->getCiudad() << ", " << usuarioActual->getPais() << endl;
        cout << "Calidad de audio: 128 kbps" << endl;
        cout << "========================================" << endl;

        cout << "\n--- REPRODUCCION ---" << endl;
        cout << "1. Reproduccion aleatoria" << endl;
        cout << "   (Con publicidad cada 2 canciones)" << endl;

        cout << "\n--- BUSQUEDA ---" << endl;
        cout << "2. Buscar cancion por ID" << endl;
        cout << "3. Ver todos los artistas" << endl;
        cout << "4. Ver todos los albumes" << endl;
        cout << "5. Ver todas las canciones" << endl;

        cout << "\n--- MI CUENTA ---" << endl;
        cout << "6. Ver mi informacion" << endl;
        cout << "7. Hazte Premium! ($19,900/mes)" << endl;

        cout << "\n8. Cerrar sesion" << endl;
        cout << "0. Salir de la aplicacion" << endl;
        cout << "========================================" << endl;

        cout << "\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
        case 1:
            cout << "\n[INFO] Reproduccion aleatoria..." << endl;
            reproduccionAleatoriaEstandar();
            cout << "Presione Enter...";
            cin.get();
            break;
        case 2:
        {
            string idInput;
            cout << "\n=== BUSCAR CANCION POR ID ===" << endl;
            cout << "Ingrese el ID de la cancion: ";
            getline(cin, idInput);

            long idCancion;
            try {
                idCancion = stol(idInput);
            } catch (...) {
                cout << "\n[ERROR] ID invalido. Debe ser un numero." << endl;
                cout << "Presione Enter...";
                cin.get();
                break;
            }

            Cancion* cancion = gestorCanciones->buscarPorId(idCancion);

            if (cancion != nullptr) {
                cout << "\n=== CANCION ENCONTRADA ===" << endl;
                cancion->mostrarInfo();

                cout << "\n¿Que desea hacer?" << endl;
                cout << "1. Reproducir" << endl;
                cout << "0. Volver al menu" << endl;
                cout << "Opcion: ";

                int subOpcion;
                cin >> subOpcion;
                cin.ignore();

                if (subOpcion == 1) {
                    reproducirCancion(cancion, true);
                }
             else {
                cout << "\n[ERROR] No se encontro ninguna cancion con ese ID." << endl;
            }
        }
            cout << "\nPresione Enter...";
            cin.get();
        }
        case 3:
            cout << "\n=== LISTA DE ARTISTAS ===" << endl;
            cout << "Total de artistas: " << gestorArtistas->getCantidadArtistas() << endl;
            cout << "========================================" << endl;
            gestorArtistas->mostrarOrdenadoPorTendencia();
            cout << "\nPresione Enter...";
            cin.get();
            break;
        case 4:
            cout << "\n=== LISTA DE ALBUMES ===" << endl;
            cout << "Total de albumes: " << gestorAlbumes->getCantidadAlbumes() << endl;
            cout << "========================================" << endl;
            gestorAlbumes->mostrarTodos();
            cout << "\nPresione Enter...";
            cin.get();
            break;
        case 5:
            cout << "\n=== TODAS LAS CANCIONES ===" << endl;
            cout << "Total de canciones: " << gestorCanciones->getCantidadCanciones() << endl;
            cout << "========================================" << endl;
            gestorCanciones->mostrarTodas();
            cout << "\nPresione Enter...";
            cin.get();
            break;
        case 6:
            usuarioActual->mostrarInfo();
            cout << "Presione Enter...";
            cin.get();
            break;
        case 7:
            cout << "\n========================================" << endl;
            cout << "        ¡HAZTE PREMIUM HOY!             " << endl;
            cout << "========================================" << endl;
            cout << "\nBeneficios Premium:" << endl;
            cout << "Sin anuncios publicitarios" << endl;
            cout << "Calidad de audio HD (320 kbps)" << endl;
            cout << "Lista de favoritos (hasta 10,000 canciones)" << endl;
            cout << "Seguir listas de otros usuarios premium" << endl;
            cout << "Controles avanzados de reproduccion" << endl;
            cout << "\nPrecio: $19,900 COP/mes" << endl;
            cout << "¿Deseas subscribirte?"<< endl;
            cout << "\n 1. Si.\n 2. No."<< endl;
            cin >> preguntaMembresia;
            if (preguntaMembresia == "1"){
                usuarioActual->setTipoMembresia("premium" );
                cout << usuarioActual->getTipoMembresia()<<endl;
                gestorUsuarios->guardarEnArchivo("data/usuarios.txt");
                cout << "Disfrute de su Membresia, el cobro sera automatico a su tarjeta de credito"<< endl;
                cout << "Cierre sesión para actualizar membresia" << endl;
                cin.get();
            }

            cout << "Presione Enter...";
            cin.get();
            break;
        case 8:
            cerrarSesion();
            return;
        case 0:
            salir();
            exit(0);
            break;
        default:
            cout << "\n[ERROR] Opcion invalida." << endl;
            cout << "Presione Enter...";
            cin.get();
        }

    } while(opcion != 8 && opcion != 0);
}

void Aplicacion::mostrarMenuUsuarioPremium() {
    int opcion;

    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "\n========================================" << endl;
        cout << "          U d e A T u n e s             " << endl;
        cout << "           USUARIO PREMIUM          " << endl;
        cout << "========================================" << endl;
        cout << "\nBienvenido: " << usuarioActual->getNickname() << endl;
        cout << "Ciudad: " << usuarioActual->getCiudad() << ", " << usuarioActual->getPais() << endl;
        cout << "Calidad de audio: 320 kbps (HD)" << endl;
        cout << "========================================" << endl;

        cout << "\n--- REPRODUCCION ---" << endl;
        cout << "1. Reproduccion aleatoria" << endl;
        cout << "   (Sin anuncios, controles avanzados)" << endl;

        cout << "\n--- MIS FAVORITOS ---" << endl;
        cout << "2. Ver mi lista de favoritos" << endl;
        cout << "3. Agregar cancion a favoritos" << endl;
        cout << "4. Eliminar cancion de favoritos" << endl;
        cout << "5. Seguir lista de otro usuario" << endl;
        cout << "6. Reproducir mis favoritos" << endl;

        cout << "\n--- BUSQUEDA ---" << endl;
        cout << "7. Buscar cancion por ID" << endl;
        cout << "8. Ver todos los artistas" << endl;
        cout << "9. Ver todos los albumes" << endl;
        cout << "10. Ver todas las canciones" << endl;

        cout << "\n--- MI CUENTA ---" << endl;
        cout << "11. Ver mi informacion" << endl;

        cout << "\n12. Cerrar sesion" << endl;
        cout << "0. Salir de la aplicacion" << endl;
        cout << "========================================" << endl;

        cout << "\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
        case 1:
            cout <<"Reproduccion Aleatoria..."<<endl;
            reproduccionAleatoriaPremium();

            break;

        case 2:
            cout << "TUS FAVORITOS"<<endl;
            verMisFavoritos();

            break;

        case 3:
            cout << "AGREGAR CANCION A FAVORITOS"<<endl;
            agregarAFavoritos();

            break;

        case 4:
            cout<<"ELIMINAR CANCION DE FAVORITOS"<<endl;
            eliminarDeFavoritos();

            break;

        case 5:
            cout<<"SEGUIR A OTRO USUARIO"<<endl;
            seguirUsuario();

            break;

        case 6:
            cout<<"REPRODUCIR MIS FAVORITOS"<<endl;
            reproducirMisFavoritos();

            break;

        case 7:
        {
            string idInput;
            cout << "\n=== BUSCAR CANCION POR ID ===" << endl;
            cout << "Ingrese el ID de la cancion: ";
            getline(cin, idInput);

            long idCancion;
            try {
                idCancion = stol(idInput);
            } catch (...) {
                cout << "\n[ERROR] ID invalido. Debe ser un numero." << endl;
                cout << "Presione Enter...";
                cin.get();
                break;
            }

            Cancion* cancion = gestorCanciones->buscarPorId(idCancion);

            if (cancion != nullptr) {
                cout << "\n=== CANCION ENCONTRADA ===" << endl;
                cancion->mostrarInfo();

                cout << "\n¿Que desea hacer?" << endl;
                cout << "1. Reproducir" << endl;
                cout << "2. Agregar a favoritos" << endl;
                cout << "0. Volver al menu" << endl;
                cout << "Opcion: ";

                int subOpcion;
                cin >> subOpcion;
                cin.ignore();

                if (subOpcion == 1) {
                    reproducirCancion(cancion, true);
                } else if (subOpcion == 2) {
                    if (usuarioActual->getListaFavoritos()->agregarCancion(idCancion)) {
                        string rutaFavoritos = "data/favoritos_" + usuarioActual->getNickname() + ".txt";
                        usuarioActual->getListaFavoritos()->guardarEnArchivo(rutaFavoritos);
                        cout << "\n[EXITO] Cancion agregada a favoritos!" << endl;
                    } else {
                        cout << "\n[ERROR] La cancion ya esta en favoritos." << endl;
                    }
                }
            } else {
                cout << "\n[ERROR] No se encontro ninguna cancion con ese ID." << endl;
            }

            cout << "\nPresione Enter...";
            cin.get();
        }
        break;

        case 8:
            cout << "\n=== LISTA DE ARTISTAS ===" << endl;
            cout << "Total de artistas: " << gestorArtistas->getCantidadArtistas() << endl;
            cout << "========================================" << endl;
            gestorArtistas->mostrarOrdenadoPorTendencia();
            cout << "\nPresione Enter...";
            cin.get();
            break;

        case 9:
            cout << "\n=== LISTA DE ALBUMES ===" << endl;
            cout << "Total de albumes: " << gestorAlbumes->getCantidadAlbumes() << endl;
            cout << "========================================" << endl;
            gestorAlbumes->mostrarTodos();
            cout << "\nPresione Enter...";
            cin.get();
            break;

        case 10:
            cout << "\n=== TODAS LAS CANCIONES ===" << endl;
            cout << "Total de canciones: " << gestorCanciones->getCantidadCanciones() << endl;
            cout << "========================================" << endl;
            gestorCanciones->mostrarTodas();
            cout << "\nPresione Enter...";
            cin.get();
            break;

        case 11:
            usuarioActual->mostrarInfo();
            cout << "Presione Enter...";
            cin.get();
            break;

        case 12:
            cerrarSesion();
            return;
        case 0:
            salir();
            exit(0);
            break;
        default:
            cout << "\n[ERROR] Opcion invalida." << endl;
            cout << "Presione Enter...";
            cin.get();
        }

    } while(opcion != 12 && opcion != 0);
}

void Aplicacion::login() {
    string nickname, contrasena;

    cout << "\n=== INICIAR SESION ===" << endl;
    cout << "Nickname: ";
    getline(cin, nickname);
    cout << "Contrasena: ";
    getline(cin, contrasena);

    Usuario* usuario = gestorUsuarios->buscarUsuario(nickname);

    if (usuario != nullptr) {
        if (usuario->validarContrasena(contrasena)) {
            usuarioActual = usuario;

            // CARGAR FAVORITOS Y SEGUIDOS (solo para premium)
            if (usuarioActual->esPremium()) {
                string rutaFavoritos = "data/favoritos_" + nickname + ".txt";
                string rutaSeguidos = "data/seguidos_" + nickname + ".txt";

                usuarioActual->getListaFavoritos()->cargarDesdeArchivo(rutaFavoritos);
                usuarioActual->getGestorSeguimiento()->cargarDesdeArchivo(rutaSeguidos);
            }
            cout << "\nLogin exitoso!" << endl;
            cout << "Redirigiendo..." << endl;

// Pequeña pausa
#ifdef _WIN32
            system("timeout /t 1 >nul");
#else
            system("sleep 1");
#endif

            // Redirigir según tipo de usuario
            if (usuarioActual->esPremium()) {
                mostrarMenuUsuarioPremium();
            } else {
                mostrarMenuUsuarioEstandar();
            }
        } else {
            cout << "\n[ERROR] Contrasena incorrecta." << endl;
            cout << "Presione Enter...";
            cin.get();
        }
    } else {
        cout << "\n[ERROR] Usuario no encontrado." << endl;
        cout << "Presione Enter...";
        cin.get();
    }
}

void Aplicacion::registrarUsuario() {
    string nickname, contrasena, ciudad, pais;
    int tipoMembresia;

    cout << "\n=== REGISTRO DE NUEVO USUARIO ===" << endl;

    cout << "Ingrese nickname: ";
    getline(cin, nickname);

    if (gestorUsuarios->existeUsuario(nickname)) {
        cout << "\n[ERROR] El nickname ya existe. Intente con otro." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    if (nickname.empty()) {
        cout << "\n[ERROR] El nickname no puede estar vacio." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "Ingrese contrasena: ";
    getline(cin, contrasena);

    if (contrasena.empty()) {
        cout << "\n[ERROR] La contrasena no puede estar vacia." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "\nTipo de membresia:" << endl;
    cout << "1. Estandar (Gratis - 128 kbps con publicidad)" << endl;
    cout << "2. Premium ($19,900/mes - 320 kbps sin publicidad)" << endl;
    cout << "Opcion: ";
    cin >> tipoMembresia;
    cin.ignore();

    string tipo = (tipoMembresia == 2) ? "premium" : "estandar";

    cout << "Ingrese ciudad: ";
    getline(cin, ciudad);

    cout << "Ingrese pais: ";
    getline(cin, pais);

    string fechaActual = obtenerFechaActual();

    Usuario* nuevoUsuario = new Usuario(nickname, contrasena, tipo, ciudad, pais, fechaActual);
    gestorUsuarios->agregarUsuario(nuevoUsuario);

    if (gestorUsuarios->guardarEnArchivo("data/usuarios.txt")) {
        cout << "\n¡Usuario registrado exitosamente!" << endl;
        cout << "\nDatos del usuario:" << endl;
        nuevoUsuario->mostrarInfo();
    } else {
        cout << "\n[ERROR] No se pudo guardar el usuario." << endl;
    }

    cout << "Presione Enter...";
    cin.get();
}

void Aplicacion::cerrarSesion() {
    cout << "\n[SISTEMA] Cerrando sesion..." << endl;
    cout << "¡Hasta pronto, " << usuarioActual->getNickname() << "!" << endl;
    usuarioActual = nullptr;

#ifdef _WIN32
    system("timeout /t 1 >nul");
#else
    system("sleep 1");
#endif
}

string Aplicacion::obtenerFechaActual() {
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);

    stringstream ss;
    ss << (tiempoLocal->tm_year + 1900) << "-"
       << setfill('0') << setw(2) << (tiempoLocal->tm_mon + 1) << "-"
       << setfill('0') << setw(2) << tiempoLocal->tm_mday;

    return ss.str();
}

void Aplicacion::salir() {
    cout << "\n[SISTEMA] Guardando datos..." << endl;
    gestorUsuarios->guardarEnArchivo("data/usuarios.txt");
    cout << "¡Gracias por usar UdeATunes!" << endl;
    cout << "Vive la musica con nosotros.\n" << endl;
}

void Aplicacion::reproducirCancion(Cancion* cancion, bool esCalidadAlta) {
    cout << "\n REPRODUCIENDO " << endl;
    cout << "================================" << endl;
    cout << "Cancion: " << cancion->getNombre() << endl;
    cout << "Duracion: " << cancion->formatearDuracion() << endl;
    cout << "Calidad: " << (esCalidadAlta ? "320 kbps (HD)" : "128 kbps") << endl;
    cout << "================================" << endl;
    cout << "\nArchivo de audio:" << endl;
    cout << cancion->getRutaCompleta(esCalidadAlta) << endl;
    cout << "================================\n" << endl;

    cancion->incrementarReproducciones();
}

void Aplicacion::reproduccionAleatoriaEstandar() {
    cout << "\n=== REPRODUCCION ALEATORIA (ESTANDAR) ===" << endl;
    cout << "Calidad: 128 kbps | Con publicidad cada 2 canciones" << endl;
    cout << "Reproduciendo 5 canciones...\n" << endl;

    int cancionesReproducidas = 0;
    int totalCanciones = 10;

    for (int i = 0; i < totalCanciones; i++) {
        Cancion* cancion = gestorCanciones->obtenerCancionAleatoria();

        if (cancion == nullptr) {
            cout << "[ERROR] No hay canciones disponibles." << endl;
            break;
        }

        cout << "\n--- Cancion " << (i + 1) << " de " << totalCanciones << " ---" << endl;
        reproducirCancion(cancion, false); // Calidad estándar

        cancionesReproducidas++;

        // Mostrar publicidad cada 2 canciones
        if (cancionesReproducidas % 2 == 0 && i < totalCanciones - 1) {
            cout << "\n========================================" << endl;
            cout << "           ANUNCIO PUBLICITARIO         " << endl;
            cout << "========================================" << endl;
            cout << "¡Hazte Premium y disfruta sin anuncios!" << endl;
            cout << "Solo $19,900/mes - Calidad HD 320 kbps" << endl;
            cout << "========================================\n" << endl;
#ifdef _WIN32
            system("timeout /t 1 >nul");
#else
            system("sleep 1");
#endif
        }

        // Simular tiempo de reproducción (3 segundos)
        cout << "Reproduciendo";
        for (int j = 0; j < 3; j++) {
            cout << ".";

#ifdef _WIN32
            system("timeout /t 1 >nul");
#else
            system("sleep 1");
#endif
        }
        cout << " \n" << endl;
    }

    cout << "\n=== REPRODUCCION FINALIZADA ===" << endl;
    cout << "Total reproducido: " << cancionesReproducidas << " canciones" << endl;
    cout << "\nPresione Enter...";
    cin.get();
}

// METODOS PREMIUM:
void Aplicacion::reproduccionAleatoriaPremium() {
    cout << "\n=== REPRODUCCION ALEATORIA (PREMIUM) ===" << endl;
    cout << " Calidad: 320 kbps HD | Sin publicidad " << endl;
    cout << "Reproduciendo 5 canciones...\n" << endl;

    int totalCanciones = 5;

    for (int i = 0; i < totalCanciones; i++) {
        Cancion* cancion = gestorCanciones->obtenerCancionAleatoria();

        if (cancion == nullptr) {
            cout << "[ERROR] No hay canciones disponibles." << endl;
            break;
        }

        cout << "\n--- Cancion " << (i + 1) << " de " << totalCanciones << " ---" << endl;
        reproducirCancion(cancion, true); // Calidad HD

        // Simular tiempo de reproducción (3 segundos)
        cout << "Reproduciendo";
        for (int j = 0; j < 3; j++) {
            cout << ".";
            cout.flush();
#ifdef _WIN32
            system("timeout /t 1 >nul");
#else
            system("sleep 1");
#endif
        }
        cout << " ✓\n" << endl;
    }

    cout << "\n=== REPRODUCCION FINALIZADA ===" << endl;
    cout << "Total reproducido: " << totalCanciones << " canciones" << endl;
    cout << "\nPresione Enter...";
    cin.get();
}

void Aplicacion::agregarAFavoritos() {
    string idInput;

    cout << "\n=== AGREGAR CANCION A FAVORITOS ===" << endl;
    cout << "Ingrese el ID de la cancion: ";
    getline(cin, idInput);

    long idCancion;
    try {
        idCancion = stol(idInput);
    } catch (...) {
        cout << "\n[ERROR] ID invalido. Debe ser un numero." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    Cancion* cancion = gestorCanciones->buscarPorId(idCancion);

    if (cancion == nullptr) {
        cout << "\n[ERROR] No se encontro ninguna cancion con el ID: " << idCancion << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "\n=== CANCION ENCONTRADA ===" << endl;
    cancion->mostrarInfo();

    cout << "\nQue desea hacer?" << endl;
    cout << "1. Agregar a favoritos" << endl;
    cout << "2. Reproducir esta cancion" << endl;
    cout << "0. Cancelar" << endl;
    cout << "Opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore();

    switch(opcion) {
    case 1:
        if (usuarioActual->getListaFavoritos()->agregarCancion(idCancion)) {
            string rutaFavoritos = "data/favoritos_" + usuarioActual->getNickname() + ".txt";

            if (usuarioActual->getListaFavoritos()->guardarEnArchivo(rutaFavoritos)) {
                cout << "\n[EXITO] Cancion agregada a favoritos!" << endl;
                cout << "Total: " << usuarioActual->getListaFavoritos()->getCantidadCanciones()
                     << " / 10,000" << endl;
            } else {
                cout << "\n[ERROR] No se pudo guardar en el archivo." << endl;
            }
        } else {
            cout << "\n[ERROR] La cancion ya esta en favoritos o alcanzaste el limite." << endl;
        }
        break;

    case 2:
        reproducirCancion(cancion, true);
        break;

    case 0:
        cout << "\nOperacion cancelada." << endl;
        break;
    }

    cout << "\nPresione Enter...";
    cin.get();
}

void Aplicacion::verMisFavoritos() {
    cout << "\n=== MI LISTA DE FAVORITOS ===" << endl;

    ListaFavoritos* favoritos = usuarioActual->getListaFavoritos();

    if (favoritos->getCantidadCanciones() == 0) {
        cout << "No tienes canciones en favoritos aun." << endl;
    } else {
        cout << "Total: " << favoritos->getCantidadCanciones() << " / 10,000\n" << endl;

        vector<long> ids = favoritos->getIdsCanciones();

        for (size_t i = 0; i < ids.size(); i++) {
            Cancion* cancion = gestorCanciones->buscarPorId(ids[i]);

            if (cancion != nullptr) {
                cout << "----------------------------------------" << endl;
                cout << "[" << (i + 1) << "] ";
                cancion->mostrarInfo();
            }
        }
        cout << "----------------------------------------" << endl;
    }

    cout << "\nPresione Enter...";
    cin.get();
}

void Aplicacion::eliminarDeFavoritos() {
    string idInput;

    cout << "\n=== ELIMINAR CANCION DE FAVORITOS ===" << endl;

    ListaFavoritos* favoritos = usuarioActual->getListaFavoritos();

    if (favoritos->getCantidadCanciones() == 0) {
        cout << "No tienes canciones en favoritos." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "Tus canciones favoritas:\n" << endl;
    vector<long> ids = favoritos->getIdsCanciones();

    for (size_t i = 0; i < ids.size(); i++) {
        Cancion* c = gestorCanciones->buscarPorId(ids[i]);
        if (c != nullptr) {
            cout << "[" << (i + 1) << "] ID: " << ids[i]
                 << " - " << c->getNombre() << endl;
        }
    }

    cout << "\nIngrese el ID de la cancion a eliminar: ";
    getline(cin, idInput);

    long idCancion;
    try {
        idCancion = stol(idInput);
    } catch (...) {
        cout << "\n[ERROR] ID invalido." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    if (favoritos->eliminarCancion(idCancion)) {
        string rutaFavoritos = "data/favoritos_" + usuarioActual->getNickname() + ".txt";
        favoritos->guardarEnArchivo(rutaFavoritos);
        cout << "\n[EXITO] Cancion eliminada de favoritos." << endl;
    } else {
        cout << "\n[ERROR] No se encontro esa cancion en tus favoritos." << endl;
    }

    cout << "Presione Enter...";
    cin.get();
}

void Aplicacion::seguirUsuario() {
    string nicknameASeguir;

    cout << "\n=== SEGUIR LISTA DE OTRO USUARIO ===" << endl;
    cout << "Ingrese el nickname del usuario: ";
    getline(cin, nicknameASeguir);

    // Verificar que no se siga a sí mismo
    if (nicknameASeguir == usuarioActual->getNickname()) {
        cout << "\n[ERROR] No puedes seguirte a ti mismo." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    Usuario* usuarioSeguir = gestorUsuarios->buscarUsuario(nicknameASeguir);

    if (usuarioSeguir == nullptr) {
        cout << "\n[ERROR] El usuario no existe." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    if (!usuarioSeguir->esPremium()) {
        cout << "\n[ERROR] Solo puedes seguir usuarios Premium." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    GestorSeguimiento* gestor = usuarioActual->getGestorSeguimiento();

    if (gestor->seguirUsuario(nicknameASeguir)) {
        string rutaSeguidos = "data/seguidos_" + usuarioActual->getNickname() + ".txt";
        gestor->guardarEnArchivo(rutaSeguidos);
        cout << "\n[EXITO] Ahora sigues a " << nicknameASeguir << endl;
    } else {
        cout << "\n[ERROR] Ya sigues a este usuario." << endl;
    }

    cout << "Presione Enter...";
    cin.get();
}

void Aplicacion::reproducirMisFavoritos() {
    cout << "\n=== REPRODUCIR FAVORITOS ===" << endl;

    vector<Cancion*> todasCanciones;

    // Mis favoritos
    vector<long> misFavoritos = usuarioActual->getListaFavoritos()->getIdsCanciones();
    for (size_t i = 0; i < misFavoritos.size(); i++) {
        Cancion* c = gestorCanciones->buscarPorId(misFavoritos[i]);
        if (c != nullptr) {
            todasCanciones.push_back(c);
        }
    }

    // Favoritos de usuarios seguidos
    vector<string> seguidos = usuarioActual->getGestorSeguimiento()->getUsuariosSeguidos();
    for (size_t i = 0; i < seguidos.size(); i++) {
        Usuario* usuarioSeguido = gestorUsuarios->buscarUsuario(seguidos[i]);
        if (usuarioSeguido != nullptr && usuarioSeguido->esPremium()) {
            vector<long> favoritosSeguido = usuarioSeguido->getListaFavoritos()->getIdsCanciones();
            for (size_t j = 0; j < favoritosSeguido.size(); j++) {
                Cancion* c = gestorCanciones->buscarPorId(favoritosSeguido[j]);
                if (c != nullptr) {
                    todasCanciones.push_back(c);
                }
            }
        }
    }

    if (todasCanciones.empty()) {
        cout << "No hay canciones para reproducir." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "Total de canciones: " << todasCanciones.size() << endl;
    cout << "\nModo de reproduccion:" << endl;
    cout << "1. Orden original" << endl;
    cout << "2. Aleatorio" << endl;
    cout << "Opcion: ";

    int modo;
    cin >> modo;
    cin.ignore();

    if (modo == 2) {
        srand(time(0));
        for (size_t i = todasCanciones.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(todasCanciones[i], todasCanciones[j]);
        }
        cout << "\n🔀 Reproduccion aleatoria\n" << endl;
    } else {
        cout << "\n▶️ Reproduccion en orden\n" << endl;
    }

    for (size_t i = 0; i < todasCanciones.size(); i++) {
        cout << "\n--- Cancion " << (i + 1) << " de " << todasCanciones.size() << " ---" << endl;
        reproducirCancion(todasCanciones[i], true);

        cout << "Reproduciendo";
        for (int j = 0; j < 3; j++) {
            cout << ".";
            cout.flush();
#ifdef _WIN32
            system("timeout /t 1 >nul");
#else
            system("sleep 1");
#endif
        }
        cout << " ✓\n" << endl;
    }

    cout << "\n=== REPRODUCCION FINALIZADA ===" << endl;
    cout << "Presione Enter...";
    cin.get();
}
