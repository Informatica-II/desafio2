#include "Aplicacion.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

Aplicacion::Aplicacion() {
    gestorUsuarios = new GestorUsuarios();
    gestorCanciones = new GestorCanciones();
    gestorPublicidades = new GestorPublicidades();
    gestorArtistas = new GestorArtistas();
    gestorAlbumes = new GestorAlbumes();
    reproductor = new Reproductor(gestorCanciones, gestorPublicidades);
    medidor = new MedidorRecursos();
    usuarioActual = nullptr;
    cargarDatos();
}

Aplicacion::~Aplicacion() {
    delete gestorUsuarios;
    delete gestorCanciones;
    delete gestorArtistas;
    delete gestorAlbumes;
    delete gestorPublicidades;
    delete reproductor;
    delete medidor;
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
    gestorArtistas->cargarDesdeArchivo("data/artistas.txt");
    gestorAlbumes->cargarDesdeArchivo("data/albunes.txt");
    gestorPublicidades->cargarDesdeArchivo("data/publicidad.txt");
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
        case 1:{
            MedidorRecursos::iniciarMedicion();
            cout << "\n[INFO] Reproduccion aleatoria..." << endl;
            reproductor->reproduccionAleatoriaEstandar(5);

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("REPRODUCCION ALEATORIA ESTANDAR", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();

            cout << "Presione Enter...";
            cin.get();
        }
        break;

        case 2:
        {
            MedidorRecursos::iniciarMedicion();
            string idInput;
            size_t memoriaLocales = sizeof(idInput) + sizeof(long) + sizeof(Cancion*) + sizeof(int);

            cout << "\n=== BUSCAR CANCION POR ID ===" << endl;
            cout << "Ingrese el ID de la cancion: ";
            getline(cin, idInput);
            MedidorRecursos::registrarIteracion();
            memoriaLocales += idInput.capacity();

            long idCancion;
            try {
                idCancion = stol(idInput);
                MedidorRecursos::registrarIteracion();
            } catch (...) {
                cout << "\n[ERROR] ID invalido." << endl;
                size_t memoriaTotal = medidor->calcularMemoriaTotal(
                    gestorUsuarios, gestorCanciones, gestorArtistas,
                    gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                    );
                medidor->mostrarReporteCompleto("BUSCAR CANCION (ERROR)", memoriaTotal, memoriaLocales);
                MedidorRecursos::detenerMedicion();

                cout << "Presione Enter...";
                cin.get();
                break;
            }

            Cancion* cancion = gestorCanciones->buscarPorId(idCancion);
            MedidorRecursos::registrarIteracion();

            if (cancion != nullptr) {
                MedidorRecursos::registrarIteracion();
                cout << "\n=== CANCION ENCONTRADA ===" << endl;
                cancion->mostrarInfo();
                cancion->mostrarCreditos();
                cancion->calcularRegaliasTotales();


                cout << "\nQue desea hacer?" << endl;
                cout << "1. Reproducir" << endl;
                cout << "0. Volver al menu" << endl;
                cout << "Opcion: ";

                int subOpcion;
                cin >> subOpcion;
                cin.ignore();
                MedidorRecursos::registrarIteracion();

                if (subOpcion == 1) {
                    MedidorRecursos::registrarIteracion();
                    reproductor->reproducirCancion(cancion, false);
                }
            } else {
                cout << "\n[ERROR] No se encontro ninguna cancion con ese ID." << endl;
            }

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("BUSCAR CANCION", memoriaTotal, memoriaLocales);
            MedidorRecursos::detenerMedicion();

            cout << "\nPresione Enter...";
            cin.get();
        }
        break;
        case 3:
        {   MedidorRecursos::iniciarMedicion();
            cout << "\n=== LISTA DE ARTISTAS ===" << endl;
            cout << "Total de artistas: " << gestorArtistas->getCantidadArtistas() << endl;
            cout << "========================================" << endl;
            gestorArtistas->mostrarOrdenadoPorTendencia();
            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("VER ARTISTAS", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();
            cout << "\nPresione Enter...";
            cin.get();}
        break;
        case 4:{
            MedidorRecursos::iniciarMedicion();
            cout << "\n=== LISTA DE ALBUMES ===" << endl;
            cout << "Total de albumes: " << gestorAlbumes->getCantidadAlbumes() << endl;
            cout << "========================================" << endl;
            gestorAlbumes->mostrarTodos();

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("VER ALBUMES", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();

            cout << "\nPresione Enter...";
            cin.get();
        }
        break;

        case 5:
        {
            MedidorRecursos::iniciarMedicion();
            cout << "\n=== TODAS LAS CANCIONES ===" << endl;
            cout << "Total de canciones: " << gestorCanciones->getCantidadCanciones() << endl;
            cout << "========================================" << endl;
            gestorCanciones->mostrarTodas();

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("VER CANCIONES", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();

            cout << "\nPresione Enter...";
            cin.get();
        }
        break;

        case 6:
        {
            MedidorRecursos::iniciarMedicion();
            usuarioActual->mostrarInfo();

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("VER INFORMACION", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();

            cout << "Presione Enter...";
            cin.get();
        }
        break;

        case 7:
        {
            MedidorRecursos::iniciarMedicion();
            string preguntaMembresia;
            size_t memoriaLocales = sizeof(string);
            memoriaLocales += preguntaMembresia.capacity();

            cout << "\n========================================" << endl;
            cout << "        HAZTE PREMIUM HOY!             " << endl;
            cout << "========================================" << endl;
            cout << "\nBeneficios Premium:" << endl;
            cout << "Sin anuncios publicitarios" << endl;
            cout << "Calidad de audio HD (320 kbps)" << endl;
            cout << "Lista de favoritos (hasta 10,000 canciones)" << endl;
            cout << "Seguir listas de otros usuarios premium" << endl;
            cout << "Controles avanzados de reproduccion" << endl;
            cout << "\nPrecio: 19,900 COP/mes" << endl;
            cout << "Deseas subscribirte?"<< endl;
            cout << "\n 1. Si.\n 2. No."<< endl;
            cin >> preguntaMembresia;
            MedidorRecursos::registrarIteracion();

            if (preguntaMembresia == "1"){
                MedidorRecursos::registrarIteracion();
                usuarioActual->setTipoMembresia("premium" );
                MedidorRecursos::registrarIteracion();

                cout << usuarioActual->getTipoMembresia()<<endl;
                gestorUsuarios->guardarEnArchivo("data/usuarios.txt");
                cout << "Disfrute de su Membresia, el cobro sera automatico a su tarjeta de credito"<< endl;
                cout << "Cierre sesión para actualizar membresia" << endl;
                cin.get();

                size_t memoriaTotal = medidor->calcularMemoriaTotal(
                    gestorUsuarios, gestorCanciones, gestorArtistas,
                    gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                    );
                medidor->mostrarReporteCompleto("UPGRADE A PREMIUM", memoriaTotal, memoriaLocales);
                MedidorRecursos::detenerMedicion();
            }

            cout << "Presione Enter...";
            cin.get();
        }
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
        case 1: {
            MedidorRecursos::iniciarMedicion();
            cout << "Reproduccion Aleatoria..." << endl;
            reproductor->reproduccionAleatoriaPremium(5);

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("REPRODUCCION ALEATORIA PREMIUM", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();
            cout << "Presione Enter...";
            cin.get();
        }
        break;

        case 2:{
            MedidorRecursos::iniciarMedicion();
            cout << "TUS FAVORITOS"<<endl;
            verMisFavoritos();

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("VER FAVORITOS", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();
            cout << "Presione Enter...";
            cin.get();
        }
        break;

        case 3:
        {
            MedidorRecursos::iniciarMedicion();

            cout << "AGREGAR CANCION A FAVORITOS"<<endl;
            agregarAFavoritos();

            size_t memoriaFinal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );

            size_t memoriaVariablesLocales = sizeof(string) * 2 + sizeof(long) + sizeof(int);
            medidor->mostrarReporteCompleto("AGREGAR A FAVORITOS", memoriaFinal, memoriaVariablesLocales);
            MedidorRecursos::detenerMedicion();
            cout << "Presione Enter...";
            cin.get();
        }
        break;


        case 4:
        {
            MedidorRecursos::iniciarMedicion();
            cout<<"ELIMINAR CANCION DE FAVORITOS"<<endl;
            eliminarDeFavoritos();

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            size_t memoriaVariables = sizeof(string) + sizeof(long);
            medidor->mostrarReporteCompleto("ELIMINAR DE FAVORITOS", memoriaTotal, memoriaVariables);
            MedidorRecursos::detenerMedicion();
            cout << "Presione Enter...";
            cin.get();
        }
        break;

        case 5: {
            MedidorRecursos::iniciarMedicion();
            cout<<"SEGUIR A OTRO USUARIO"<<endl;
            seguirUsuario();

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            size_t memoriaVariables = sizeof(string) + sizeof(Usuario*);
            medidor->mostrarReporteCompleto("SEGUIR USUARIO", memoriaTotal, memoriaVariables);
            MedidorRecursos::detenerMedicion();
            cout << "Presione Enter...";
            cin.get();
        }
        break;
        case 6:{
            MedidorRecursos::iniciarMedicion();
            cout<<"REPRODUCIR MIS FAVORITOS"<<endl;
            reproducirMisFavoritos();

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            size_t memoriaVariables = 10000 * sizeof(Cancion*) + sizeof(int) * 4;
            medidor->mostrarReporteCompleto("REPRODUCIR FAVORITOS", memoriaTotal, memoriaVariables);
            MedidorRecursos::detenerMedicion();
            cout << "Presione Enter...";
            cin.get();
        }
        break;

        case 7:
        {
            string idInput;
            MedidorRecursos::iniciarMedicion();
            size_t memoriaLocales = sizeof(idInput) + sizeof(long) + sizeof(Cancion*) + sizeof(int);

            cout << "\n=== BUSCAR CANCION POR ID ===" << endl;
            cout << "Ingrese el ID de la cancion: ";
            getline(cin, idInput);
            MedidorRecursos::registrarIteracion();
            memoriaLocales += idInput.capacity();

            long idCancion;
            try {
                idCancion = stol(idInput);
                MedidorRecursos::registrarIteracion();
            } catch (...) {
                cout << "\n[ERROR] ID invalido." << endl;
                size_t memoriaTotal = medidor->calcularMemoriaTotal(
                    gestorUsuarios, gestorCanciones, gestorArtistas,
                    gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                    );
                medidor->mostrarReporteCompleto("BUSCAR CANCION (ERROR)", memoriaTotal, memoriaLocales);
                MedidorRecursos::detenerMedicion();
                cout << "Presione Enter...";
                cin.get();
                break;
            }

            Cancion* cancion = gestorCanciones->buscarPorId(idCancion);
            MedidorRecursos::registrarIteracion();

            if (cancion != nullptr) {
                MedidorRecursos::registrarIteracion();
                cout << "\n=== CANCION ENCONTRADA ===" << endl;
                cancion->mostrarInfo();
                cancion->mostrarCreditos();
                cancion->calcularRegaliasTotales();

                cout << "\n¿Que desea hacer?" << endl;
                cout << "1. Reproducir" << endl;
                cout << "2. Agregar a favoritos" << endl;
                cout << "0. Volver al menu" << endl;
                cout << "Opcion: ";

                int subOpcion;
                cin >> subOpcion;
                cin.ignore();
                MedidorRecursos::registrarIteracion();

                if (subOpcion == 1) {
                    MedidorRecursos::registrarIteracion();
                    reproductor->reproducirCancion(cancion, true);  // NUEVO
                } else if (subOpcion == 2) {
                    if (usuarioActual->getListaFavoritos()->agregarCancion(idCancion)) {
                        MedidorRecursos::registrarIteracion();
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

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("BUSCAR CANCION", memoriaTotal, memoriaLocales);
            MedidorRecursos::detenerMedicion();

            cout << "\nPresione Enter...";
            cin.get();
        }
        break;
        case 8:
        {
            // INICIO MEDICIÓN
            MedidorRecursos::iniciarMedicion();

            cout << "\n=== LISTA DE ARTISTAS ===" << endl;
            cout << "Total de artistas: " << gestorArtistas->getCantidadArtistas() << endl;
            cout << "========================================" << endl;
            gestorArtistas->mostrarOrdenadoPorTendencia();

            // FIN MEDICIÓN Y REPORTE
            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("VER ARTISTAS PREMIUM", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();

            cout << "\nPresione Enter...";
            cin.get();
            break;
        }

        case 9:
        {
            // INICIO MEDICIÓN
            MedidorRecursos::iniciarMedicion();

            cout << "\n=== LISTA DE ALBUMES ===" << endl;
            cout << "Total de albumes: " << gestorAlbumes->getCantidadAlbumes() << endl;
            cout << "========================================" << endl;
            gestorAlbumes->mostrarTodos();

            // FIN MEDICIÓN Y REPORTE
            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("VER ALBUMES PREMIUM", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();

            cout << "\nPresione Enter...";
            cin.get();
            break;
        }

        case 10:
        {
            // INICIO MEDICIÓN
            MedidorRecursos::iniciarMedicion();

            cout << "\n=== TODAS LAS CANCIONES ===" << endl;
            cout << "Total de canciones: " << gestorCanciones->getCantidadCanciones() << endl;
            cout << "========================================" << endl;
            gestorCanciones->mostrarTodas();

            // FIN MEDICIÓN Y REPORTE
            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("VER CANCIONES PREMIUM", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();

            cout << "\nPresione Enter...";
            cin.get();
            break;
        }

        case 11:
        {
            // INICIO MEDICIÓN
            MedidorRecursos::iniciarMedicion();

            usuarioActual->mostrarInfo();

            // FIN MEDICIÓN Y REPORTE
            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("VER INFORMACION PREMIUM", memoriaTotal, 0);
            MedidorRecursos::detenerMedicion();

            cout << "Presione Enter...";
            cin.get();
            break;
        }

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
    // INICIAR MEDICIÓN
    MedidorRecursos::iniciarMedicion();
    string nickname, contrasena;
    size_t memoriaLocales = sizeof(nickname) + sizeof(contrasena) + nickname.capacity() + contrasena.capacity();


    cout << "\n=== INICIAR SESION ===" << endl;
    cout << "Nickname: ";
    getline(cin, nickname);
    MedidorRecursos::registrarIteracion();
    cout << "Contrasena: ";
    getline(cin, contrasena);
    MedidorRecursos::registrarIteracion();

    Usuario* usuario = gestorUsuarios->buscarUsuario(nickname);

    if (usuario != nullptr) {
        MedidorRecursos::registrarIteracion();
        if (usuario->validarContrasena(contrasena)) {
            MedidorRecursos::registrarIteracion();
            usuarioActual = usuario;

            // CARGAR FAVORITOS Y SEGUIDOS (solo para premium)
            if (usuarioActual->esPremium()) {
                MedidorRecursos::registrarIteracion();
                string rutaFavoritos = "data/favoritos_" + nickname + ".txt";
                string rutaSeguidos = "data/seguidos_" + nickname + ".txt";

                usuarioActual->getListaFavoritos()->cargarDesdeArchivo(rutaFavoritos);
                usuarioActual->getGestorSeguimiento()->cargarDesdeArchivo(rutaSeguidos);
            }
            cout << "\nLogin exitoso!" << endl;
            cout << "Redirigiendo..." << endl;

            // CALCULAR MEMORIA TOTAL
            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            // MOSTRAR REPORTE
            medidor->mostrarReporteCompleto("LOGIN", memoriaTotal, memoriaLocales);
            MedidorRecursos::detenerMedicion();


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

            size_t memoriaTotal = medidor->calcularMemoriaTotal(
                gestorUsuarios, gestorCanciones, gestorArtistas,
                gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
                );
            medidor->mostrarReporteCompleto("LOGIN (FALLIDO)", memoriaTotal, memoriaLocales);
            MedidorRecursos::detenerMedicion();

            cout << "Presione Enter...";
            cin.get();
        }
    } else {
        cout << "\n[ERROR] Usuario no encontrado." << endl;
        size_t memoriaTotal = medidor->calcularMemoriaTotal(
            gestorUsuarios, gestorCanciones, gestorArtistas,
            gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
            );
        medidor->mostrarReporteCompleto("LOGIN (FALLIDO)", memoriaTotal, memoriaLocales);
        MedidorRecursos::detenerMedicion();

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
        cout << "\nUsuario registrado exitosamente!" << endl;
        cout << "\nDatos del usuario:" << endl;
        nuevoUsuario->mostrarInfo();
    } else {
        cout << "\n[ERROR] No se pudo guardar el usuario." << endl;
    }

    cout << "Presione Enter...";
    cin.get();
}

void Aplicacion::cerrarSesion() {
    // 1. Iniciar medición
    MedidorRecursos::iniciarMedicion();

    cout << "\n[SISTEMA] Cerrando sesion..." << endl;
    cout << "Hasta pronto, " << usuarioActual->getNickname() << "!" << endl;

    // 2. Calcular y mostrar reporte (usuarioActual todavía es válido)
    size_t memoriaTotal = medidor->calcularMemoriaTotal(
        gestorUsuarios, gestorCanciones, gestorArtistas,
        gestorAlbumes, gestorPublicidades, reproductor, usuarioActual
        );

    // 0 para variables locales, ya que la memoria principal es la de las estructuras de la clase Aplicacion
    medidor->mostrarReporteCompleto("CIERRE DE SESION", memoriaTotal, 0);

    MedidorRecursos::detenerMedicion();

    // PAUSA: Importante para que el usuario pueda ver el reporte
    cout << "Presione Enter para volver al menu principal...";
    cin.get();

    // 3. Cerrar sesión
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

// METODOS PREMIUM:
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
    cout << "ID Cancion: " << cancion->getIdCancion() << endl;
    cout << "Nombre: " << cancion->getNombre() << endl;
    cout << "Duracion: " << cancion->formatearDuracion() << endl;
    cout << "Reproducciones: " << cancion->getReproducciones() << endl;
    cout << "========================================" << endl;

    cout << "\n¿Que desea hacer?" << endl;
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
            cout << "\n[ERROR] La cancion ya esta en favoritos o alcanzaste el limite (10,000)." << endl;
        }
        break;

    case 2:
        reproductor->reproducirCancion(cancion, true);
        break;

    case 0:
        cout << "\nOperacion cancelada." << endl;
        break;

    default:
        cout << "\n[ERROR] Opcion invalida." << endl;
    }

    cout << "\nPresione Enter...";
    cin.get();
}

void Aplicacion::verMisFavoritos() {
    cout << "\n=== MI LISTA DE FAVORITOS ===" << endl;

    ListaFavoritos* favoritos = usuarioActual->getListaFavoritos();
    MedidorRecursos::registrarIteracion();

    if (favoritos->getCantidadCanciones() == 0) {
        MedidorRecursos::registrarIteracion();
        cout << "No tienes canciones en favoritos aun." << endl;
    } else {
        cout << "Total: " << favoritos->getCantidadCanciones() << " / 10,000\n" << endl;

        long* ids = favoritos->getIdsCanciones();
        int cantidad = favoritos->getCantidadCanciones();

        for (int i = 0; i < cantidad; i++) {
            MedidorRecursos::registrarIteracion();
            Cancion* cancion = gestorCanciones->buscarPorId(ids[i]);

            if (cancion != nullptr) {
                MedidorRecursos::registrarIteracion();
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
    MedidorRecursos::registrarIteracion();

    if (favoritos->getCantidadCanciones() == 0) {
        MedidorRecursos::registrarIteracion();
        cout << "No tienes canciones en favoritos." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "Tus canciones favoritas:\n" << endl;
    long* ids = favoritos->getIdsCanciones();
    int cantidad = favoritos->getCantidadCanciones();

    for (int i = 0; i < cantidad; i++) {
        MedidorRecursos::registrarIteracion();
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
        MedidorRecursos::registrarIteracion();
    } catch (...) {
        cout << "\n[ERROR] ID invalido." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    if (favoritos->eliminarCancion(idCancion)) {
        MedidorRecursos::registrarIteracion();
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
    MedidorRecursos::registrarIteracion();

    if (nicknameASeguir == usuarioActual->getNickname()) {
        MedidorRecursos::registrarIteracion();
        cout << "\n[ERROR] No puedes seguirte a ti mismo." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    Usuario* usuarioSeguir = gestorUsuarios->buscarUsuario(nicknameASeguir);

    if (usuarioSeguir == nullptr) {
        MedidorRecursos::registrarIteracion();
        cout << "\n[ERROR] El usuario no existe." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    if (!usuarioSeguir->esPremium()) {
        MedidorRecursos::registrarIteracion();
        cout << "\n[ERROR] Solo puedes seguir usuarios Premium." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    GestorSeguimiento* gestor = usuarioActual->getGestorSeguimiento();

    if (gestor->seguirUsuario(nicknameASeguir)) {
        MedidorRecursos::registrarIteracion();
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

    int capacidadTotal = 10000;
    Cancion** todasCanciones = new Cancion*[capacidadTotal];
    int totalCanciones = 0;

    // Recolectar favoritos propios
    long* misFavoritos = usuarioActual->getListaFavoritos()->getIdsCanciones();
    int cantMisFavoritos = usuarioActual->getListaFavoritos()->getCantidadCanciones();

    for (int i = 0; i < cantMisFavoritos; i++) {
        Cancion* c = gestorCanciones->buscarPorId(misFavoritos[i]);
        if (c != nullptr && totalCanciones < capacidadTotal) {
            todasCanciones[totalCanciones++] = c;
        }
    }

    // Recolectar favoritos de usuarios seguidos
    string* seguidos = usuarioActual->getGestorSeguimiento()->getUsuariosSeguidos();
    int cantSeguidos = usuarioActual->getGestorSeguimiento()->getCantidadSeguidos();

    for (int i = 0; i < cantSeguidos; i++) {
        Usuario* usuarioSeguido = gestorUsuarios->buscarUsuario(seguidos[i]);
        if (usuarioSeguido != nullptr && usuarioSeguido->esPremium()) {
            long* favoritosSeguido = usuarioSeguido->getListaFavoritos()->getIdsCanciones();
            int cantFavoritosSeguido = usuarioSeguido->getListaFavoritos()->getCantidadCanciones();

            for (int j = 0; j < cantFavoritosSeguido; j++) {
                Cancion* c = gestorCanciones->buscarPorId(favoritosSeguido[j]);
                if (c != nullptr && totalCanciones < capacidadTotal) {
                    todasCanciones[totalCanciones++] = c;
                }
            }
        }
    }

    if (totalCanciones == 0) {
        cout << "No hay canciones para reproducir." << endl;
        delete[] todasCanciones;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "Total de canciones: " << totalCanciones << endl;
    cout << "\nModo de reproduccion:" << endl;
    cout << "1. Orden original" << endl;
    cout << "2. Aleatorio" << endl;
    cout << "Opcion: ";

    int modo;
    cin >> modo;
    cin.ignore();

    // Mezclar si es aleatorio
    if (modo == 2) {
        srand(time(0));
        for (int i = totalCanciones - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Cancion* temp = todasCanciones[i];
            todasCanciones[i] = todasCanciones[j];
            todasCanciones[j] = temp;
        }
        cout << "\n Reproduccion aleatoria\n" << endl;
    } else {
        cout << "\n Reproduccion en orden\n" << endl;
    }

    //  Delegar al reproductor
    reproductor->reproducirListaConControles(todasCanciones, totalCanciones);

    delete[] todasCanciones;

    cout << "\n=== REPRODUCCION FINALIZADA ===" << endl;
    cout << "Presione Enter...";
    cin.get();
}
