#include <iostream>
#include <string>
#include <vector>

class Libro {
    public:
        std::string titulo;
        std::string autor;
        int anioPublicacion;
        bool estaDisponible;

        void mostrarDetallesCompletos() {
            std::cout << "----------------------------------" << std::endl;
            std::cout << "Titulo: " << titulo << std::endl;
            std::cout << "Autor: " << autor << std::endl;
            std::cout << "Anio de publicacion: " << anioPublicacion << std::endl;
            std::cout << "Disponibilidad: " << estaDisponible << std::endl;
        }
};

class Biblioteca {
    private:
        std::vector<Libro> coleccion;
    
    public:
        
        void agregarLibro(const Libro& nuevoLibro) {
            coleccion.push_back(nuevoLibro);
        };

        void mostrarInventario() {
            for (int i = 0; i < coleccion.size(); i++) {
                coleccion[i].mostrarDetallesCompletos();
            }
        };

        Libro* buscarLibro(const std::string& tituloBuscado) {
            for (Libro& libro: coleccion) {
                if (libro.titulo == tituloBuscado) {
                    return &libro;
                }
            }
            return nullptr;
        };

        void prestarLibro(const std::string& tituloPrestamo) {
            Libro* libro = buscarLibro(tituloPrestamo);

            if (libro == nullptr) {
                std::cout << "El libro no existe." << std::endl;
                return;
            };

            if (libro->estaDisponible == true) {
                libro->estaDisponible = false;
            } else {
                std::cout << "El libro no esta disponible para prestamo." << std::endl;
            };

        };

        void devolverLibro(const std::string& tituloDevolucion) {
            Libro* libro = buscarLibro(tituloDevolucion);

            if (libro == nullptr) {
                std::cout << "El libro no existe." << std::endl;
                return;
            };

            if (libro->estaDisponible == false) {
                libro->estaDisponible = true;
            } else {
                std::cout << "El libro ya fue devuelto." << std::endl;
            } 
        }
};

int main () {
    Biblioteca labiblio;
    Libro libro1;
    Libro libro2;
    Libro libro3;

    int opcion = 0;

    libro1.titulo = "La Biblia";
    libro1.autor = "Anonimo";
    libro1.anioPublicacion = -1000;
    libro1.estaDisponible = true;

    libro2.titulo = "Rayuela";
    libro2.autor = "Julio Cortazar";
    libro2.anioPublicacion = 1959;
    libro2.estaDisponible = true;

    libro3.titulo = "Pedro Paramo";
    libro3.autor = "Juan Rulfo";
    libro3.anioPublicacion = 1945;
    libro3.estaDisponible = false;

    labiblio.agregarLibro(libro1);
    labiblio.agregarLibro(libro2);
    labiblio.agregarLibro(libro3);

    while (opcion != 5) {
        std::cout << "\n-----------BIBLIOTECA DIGITAL------------" << std::endl;
        std::cout << "1. Anadir libro" << std::endl;
        std::cout << "2. Mostrar inventario" << std::endl;
        std::cout << "3. Prestar libro" << std::endl;
        std::cout << "4. Devolver libro" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        std::cin.ignore();
        
        if (opcion == 1) {
            Libro newLibro;
            std::string newTitle;
            std::string newAuthor;
            int newYear;
            bool newAvailable;

            std::cout << "Agregue el titulo de su libro: ";
            std::getline(std::cin, newTitle);
            newLibro.titulo = newTitle;

            std::cout << "Agregue el autor de su libro: ";
            std::getline(std::cin, newAuthor);
            newLibro.autor = newAuthor;

            std::cout << "Agregue el anio de publicacion: ";
            std::cin >> newYear;
            newLibro.anioPublicacion = newYear;

            std::cout << "Agregue la disponibilidad de su libro (true = 1 /false = 0): ";
            std::cin >> newAvailable;
            newLibro.estaDisponible = newAvailable;

            labiblio.agregarLibro(newLibro);
        };

        if (opcion == 2) {
            labiblio.mostrarInventario();
        };
        
        if (opcion == 3) {
            std::string tryTitulo;

            std::cout << "Introduzca el titulo del libro: ";
            std::getline(std::cin, tryTitulo);
            labiblio.prestarLibro(tryTitulo);
        };

        if (opcion == 4) {
            std::string intentoTitulo;

            std::cout << "Introduzca el titulo del libro: ";
            std::getline(std::cin, intentoTitulo);
            labiblio.devolverLibro(intentoTitulo);
        }
    }
}