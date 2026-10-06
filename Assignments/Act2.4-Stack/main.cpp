#include <iostream>
#include <string>

#include "Stack.h"

using namespace std;


// Estructura PaginaWeb
struct PaginaWeb {

    string titulo;
    string url;

};


int main() {

    // Stack que guarda paginas web
    Stack<PaginaWeb> historial;

    int opcion;


    do {

        cout << "\n===== HISTORIAL DEL NAVEGADOR =====" << endl;

        cout << "1. Visitar una nueva pagina" << endl;
        cout << "2. Retroceder a la pagina anterior" << endl;
        cout << "3. Ver la pagina actual" << endl;
        cout << "4. Mostrar paginas en el historial" << endl;
        cout << "5. Salir" << endl;

        cout << "\nSelecciona una opcion: ";

        cin >> opcion;


        switch (opcion) {


            // --------------------------------
            // VISITAR NUEVA PAGINA
            // --------------------------------

            case 1: {

                PaginaWeb nueva;

                cout << "\nTitulo de la pagina: ";

                cin.ignore();

                getline(cin, nueva.titulo);

                cout << "URL: ";

                getline(cin, nueva.url);


                // Agregamos la pagina al Stack
                historial.push(nueva);


                cout << "\nPagina agregada al historial."
                     << endl;

                break;
            }



            // --------------------------------
            // RETROCEDER
            // --------------------------------

            case 2: {

                try {

                    // pop elimina y regresa
                    // la pagina que estaba arriba
                    PaginaWeb cerrada = historial.pop();


                    cout << "\nPagina cerrada:" << endl;

                    cout << "Titulo: "
                         << cerrada.titulo
                         << endl;

                    cout << "URL: "
                         << cerrada.url
                         << endl;


                    // Si todavía quedan paginas
                    if (historial.size() > 0) {

                        PaginaWeb actual = historial.top();

                        cout << "\nRegresaste a:" << endl;

                        cout << "Titulo: "
                             << actual.titulo
                             << endl;

                        cout << "URL: "
                             << actual.url
                             << endl;
                    }

                }

                catch (runtime_error& error) {

                    cout << "\n"
                         << error.what()
                         << endl;

                }

                break;
            }



            // --------------------------------
            // VER PAGINA ACTUAL
            // --------------------------------

            case 3: {

                try {

                    PaginaWeb actual = historial.top();


                    cout << "\nPagina actual:" << endl;

                    cout << "Titulo: "
                         << actual.titulo
                         << endl;

                    cout << "URL: "
                         << actual.url
                         << endl;

                }

                catch (runtime_error& error) {

                    cout << "\n"
                         << error.what()
                         << endl;

                }

                break;
            }



            // --------------------------------
            // MOSTRAR CANTIDAD
            // --------------------------------

            case 4: {

                cout << "\nPaginas en el historial: "
                     << historial.size()
                     << endl;

                break;
            }



            // --------------------------------
            // SALIR
            // --------------------------------

            case 5: {

                cout << "\nSaliendo del programa..."
                     << endl;

                break;
            }



            default: {

                cout << "\nOpcion invalida."
                     << endl;

            }

        }


    } while (opcion != 5);


    return 0;
}