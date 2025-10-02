#include <bits/stdc++.h>
using namespace std;

const char SEP = '|';

struct Autor {
    int id;
    string nombre;
    string nacionalidad;
};

struct Libro {
    int id;
    string titulo;
    string isbn;
    int ano;
    int id_autor; // FK -> Autor.id
};

struct Estudiante {
    int id;
    string nombre;
    string grado;
};

struct Prestamo {
    int id;
    int id_libro;      // FK -> Libro.id
    int id_estudiante; // FK -> Estudiante.id
    string fecha_prestamo;
    string fecha_devolucion; // empty if no devolución
};

vector<Autor> autores;
vector<Libro> libros;
vector<Estudiante> estudiantes;
vector<Prestamo> prestamos;

int nextId(const vector<int>& used) {
    int id = 1;
    unordered_set<int> s(used.begin(), used.end());
    while (s.count(id)) ++id;
    return id;
}

int nextIdGenericInt(const vector<int>& usedSet) { return nextId(usedSet); }

int findAutorIndexById(int id) {
    for (size_t i = 0; i < autores.size(); ++i) if (autores[i].id == id) return (int)i;
    return -1;
}
int findLibroIndexById(int id) {
    for (size_t i = 0; i < libros.size(); ++i) if (libros[i].id == id) return (int)i;
    return -1;
}
int findEstudianteIndexById(int id) {
    for (size_t i = 0; i < estudiantes.size(); ++i) if (estudiantes[i].id == id) return (int)i;
    return -1;
}
int findPrestamoIndexById(int id) {
    for (size_t i = 0; i < prestamos.size(); ++i) if (prestamos[i].id == id) return (int)i;
    return -1;
}

bool libroDisponible(int id_libro) {
    for (auto &p: prestamos) {
        if (p.id_libro == id_libro && p.fecha_devolucion.empty()) return false;
    }
    return true;
}

string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\n\r");
    if (a==string::npos) return string();
    size_t b = s.find_last_not_of(" \t\n\r");
    return s.substr(a, b-a+1);
}

vector<string> splitLine(const string &line, char sep) {
    vector<string> out;
    string cur;
    for (char c : line) {
        if (c == sep) { out.push_back(cur); cur.clear(); }
        else cur.push_back(c);
    }
    out.push_back(cur);
    return out;
}

string escapeField(const string &s) {

    string r = s;
    for (char &c : r) if (c == SEP) c = ' ';
    return r;
}

void saveAutores(const string &filename="autores.txt") {
    ofstream f(filename);
    for (auto &a : autores) {
        f << a.id << SEP << escapeField(a.nombre) << SEP << escapeField(a.nacionalidad) << "\n";
    }
}
void loadAutores(const string &filename="autores.txt") {
    autores.clear();
    ifstream f(filename);
    if (!f) return;
    string line;
    while (getline(f,line)) {
        if (trim(line).empty()) continue;
        auto parts = splitLine(line, SEP);
        if (parts.size() < 3) continue;
        Autor a;
        a.id = stoi(parts[0]);
        a.nombre = parts[1];
        a.nacionalidad = parts[2];
        autores.push_back(a);
    }
}

void saveLibros(const string &filename="libros.txt") {
    ofstream f(filename);
    for (auto &l : libros) {
        f << l.id << SEP << escapeField(l.titulo) << SEP << escapeField(l.isbn) << SEP << l.ano << SEP << l.id_autor << "\n";
    }
}
void loadLibros(const string &filename="libros.txt") {
    libros.clear();
    ifstream f(filename);
    if (!f) return;
    string line;
    while (getline(f,line)) {
        if (trim(line).empty()) continue;
        auto parts = splitLine(line, SEP);
        if (parts.size() < 5) continue;
        Libro l;
        l.id = stoi(parts[0]);
        l.titulo = parts[1];
        l.isbn = parts[2];
        l.ano = stoi(parts[3]);
        l.id_autor = stoi(parts[4]);
        libros.push_back(l);
    }
}

void saveEstudiantes(const string &filename="estudiantes.txt") {
    ofstream f(filename);
    for (auto &e : estudiantes) {
        f << e.id << SEP << escapeField(e.nombre) << SEP << escapeField(e.grado) << "\n";
    }
}
void loadEstudiantes(const string &filename="estudiantes.txt") {
    estudiantes.clear();
    ifstream f(filename);
    if (!f) return;
    string line;
    while (getline(f,line)) {
        if (trim(line).empty()) continue;
        auto parts = splitLine(line, SEP);
        if (parts.size() < 3) continue;
        Estudiante e;
        e.id = stoi(parts[0]);
        e.nombre = parts[1];
        e.grado = parts[2];
        estudiantes.push_back(e);
    }
}

void savePrestamos(const string &filename="prestamos.txt") {
    ofstream f(filename);
    for (auto &p : prestamos) {
        f << p.id << SEP << p.id_libro << SEP << p.id_estudiante << SEP << escapeField(p.fecha_prestamo) << SEP << escapeField(p.fecha_devolucion) << "\n";
    }
}
void loadPrestamos(const string &filename="prestamos.txt") {
    prestamos.clear();
    ifstream f(filename);
    if (!f) return;
    string line;
    while (getline(f,line)) {
        if (trim(line).empty()) continue;
        auto parts = splitLine(line, SEP);
        if (parts.size() < 5) continue;
        Prestamo p;
        p.id = stoi(parts[0]);
        p.id_libro = stoi(parts[1]);
        p.id_estudiante = stoi(parts[2]);
        p.fecha_prestamo = parts[3];
        p.fecha_devolucion = parts[4];
        prestamos.push_back(p);
    }
}

void guardarTodo() {
    saveAutores(); saveLibros(); saveEstudiantes(); savePrestamos();
}
void cargarTodo() {
    loadAutores(); loadLibros(); loadEstudiantes(); loadPrestamos();
}

void agregarAutor() {
    Autor a;
    cout << "Nuevo Autor\nID (numero entero): "; cin >> a.id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (findAutorIndexById(a.id) != -1) { cout << "El ID ya existe.\n"; return; }
    cout << "Nombre: "; getline(cin, a.nombre);
    cout << "Nacionalidad: "; getline(cin, a.nacionalidad);
    autores.push_back(a);
    cout << "Autor agregado.\n";
}

void listarAutores() {
    cout << "Autores:\n";
    for (auto &a: autores) cout << a.id << ": " << a.nombre << " (" << a.nacionalidad << ")\n";
}

void actualizarAutor() {
    cout << "Actualizar Autor - ID: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idx = findAutorIndexById(id);
    if (idx == -1) { cout << "No existe Autor con ese ID\n"; return; }
    cout << "Nuevo nombre (ENTER para mantener: " << autores[idx].nombre << ") : ";
    string s; getline(cin, s); if (!s.empty()) autores[idx].nombre = s;
    cout << "Nueva nacionalidad (ENTER para mantener: " << autores[idx].nacionalidad << ") : ";
    getline(cin, s); if (!s.empty()) autores[idx].nacionalidad = s;
    cout << "Autor actualizado.\n";
}

void eliminarAutor() {
    cout << "Eliminar Autor - ID: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idx = findAutorIndexById(id);
    if (idx == -1) { cout << "No existe Autor con ese ID\n"; return; }

    for (auto &l: libros) if (l.id_autor == id) { cout << "No se puede eliminar: autor tiene libros asociados.\n"; return; }
    autores.erase(autores.begin()+idx);
    cout << "Autor eliminado.\n";
}

void agregarLibro() {
    Libro l;
    cout << "Nuevo Libro\nID (numero entero): "; cin >> l.id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (findLibroIndexById(l.id) != -1) { cout << "ID ya existe.\n"; return; }
    cout << "Titulo: "; getline(cin, l.titulo);
    cout << "ISBN: "; getline(cin, l.isbn);
    cout << "Año de publicacion: "; cin >> l.ano; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "ID_Autor: "; cin >> l.id_autor; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (findAutorIndexById(l.id_autor) == -1) { cout << "El autor no existe. Agrega el autor primero.\n"; return; }
    libros.push_back(l);
    cout << "Libro agregado.\n";
}

void listarLibros(bool mostrarDisponibilidad = true) {
    cout << "Libros:\n";
    for (auto &l: libros) {
        int idxA = findAutorIndexById(l.id_autor);
        string autorNombre = (idxA==-1?"(desconocido)":autores[idxA].nombre);
        cout << l.id << ": " << l.titulo << " -- ISBN:" << l.isbn << " -- " << l.ano << " -- Autor: " << autorNombre;
        if (mostrarDisponibilidad) cout << " -- " << (libroDisponible(l.id) ? "Disponible" : "Prestado");
        cout << "\n";
    }
}

void actualizarLibro() {
    cout << "Actualizar Libro - ID: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idx = findLibroIndexById(id);
    if (idx == -1) { cout << "No existe libro con ese ID\n"; return; }
    string s;
    cout << "Nuevo titulo (ENTER para mantener: " << libros[idx].titulo << ") : "; getline(cin, s); if (!s.empty()) libros[idx].titulo = s;
    cout << "Nuevo ISBN (ENTER para mantener: " << libros[idx].isbn << ") : "; getline(cin, s); if (!s.empty()) libros[idx].isbn = s;
    cout << "Nuevo año (0 para mantener: " << libros[idx].ano << ") : "; int a; cin >> a; cin.ignore(numeric_limits<streamsize>::max(), '\n'); if (a!=0) libros[idx].ano = a;
    cout << "Nuevo ID_Autor (0 para mantener: " << libros[idx].id_autor << ") : "; int ida; cin >> ida; cin.ignore(numeric_limits<streamsize>::max(), '\n'); if (ida!=0) {
        if (findAutorIndexById(ida)==-1) cout << "Autor no existe. Manteniendo anterior.\n"; else libros[idx].id_autor = ida;
    }
    cout << "Libro actualizado.\n";
}

void eliminarLibro() {
    cout << "Eliminar Libro - ID: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idx = findLibroIndexById(id);
    if (idx == -1) { cout << "No existe libro con ese ID\n"; return; }

    if (!libroDisponible(id)) { cout << "No se puede eliminar: libro está prestado actualmente.\n"; return; }
    libros.erase(libros.begin()+idx);
    cout << "Libro eliminado.\n";
}

void agregarEstudiante() {
    Estudiante e;
    cout << "Nuevo Estudiante\nID (numero entero): "; cin >> e.id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (findEstudianteIndexById(e.id) != -1) { cout << "ID ya existe.\n"; return; }
    cout << "Nombre: "; getline(cin, e.nombre);
    cout << "Grado: "; getline(cin, e.grado);
    estudiantes.push_back(e);
    cout << "Estudiante agregado.\n";
}

void listarEstudiantes() {
    cout << "Estudiantes:\n";
    for (auto &e: estudiantes) cout << e.id << ": " << e.nombre << " (" << e.grado << ")\n";
}

void actualizarEstudiante() {
    cout << "Actualizar Estudiante - ID: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idx = findEstudianteIndexById(id);
    if (idx == -1) { cout << "No existe Estudiante con ese ID\n"; return; }
    string s;
    cout << "Nuevo nombre (ENTER para mantener: " << estudiantes[idx].nombre << ") : "; getline(cin, s); if (!s.empty()) estudiantes[idx].nombre = s;
    cout << "Nuevo grado (ENTER para mantener: " << estudiantes[idx].grado << ") : "; getline(cin, s); if (!s.empty()) estudiantes[idx].grado = s;
    cout << "Estudiante actualizado.\n";
}

void eliminarEstudiante() {
    cout << "Eliminar Estudiante - ID: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idx = findEstudianteIndexById(id);
    if (idx == -1) { cout << "No existe Estudiante con ese ID\n"; return; }

    for (auto &p: prestamos) if (p.id_estudiante == id && p.fecha_devolucion.empty()) { cout << "No se puede eliminar: estudiante tiene préstamos activos.\n"; return; }
    estudiantes.erase(estudiantes.begin()+idx);
    cout << "Estudiante eliminado.\n";
}

void agregarPrestamo() {
    Prestamo p;
    cout << "Nuevo Prestamo\nID (numero entero): "; cin >> p.id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (findPrestamoIndexById(p.id) != -1) { cout << "ID ya existe.\n"; return; }
    cout << "ID_Libro: "; cin >> p.id_libro; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (findLibroIndexById(p.id_libro) == -1) { cout << "Libro no existe.\n"; return; }
    if (!libroDisponible(p.id_libro)) { cout << "Libro no disponible (ya prestado).\n"; return; }
    cout << "ID_Estudiante: "; cin >> p.id_estudiante; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (findEstudianteIndexById(p.id_estudiante) == -1) { cout << "Estudiante no existe.\n"; return; }
    cout << "Fecha Prestamo (YYYY-MM-DD): "; getline(cin, p.fecha_prestamo);
    p.fecha_devolucion = "";
    prestamos.push_back(p);
    cout << "Prestamo agregado.\n";
}

void listarPrestamos(bool mostrarSoloActivos=false) {
    cout << "Prestamos:\n";
    for (auto &p : prestamos) {
        if (mostrarSoloActivos && !p.fecha_devolucion.empty()) continue;
        int idxL = findLibroIndexById(p.id_libro);
        int idxE = findEstudianteIndexById(p.id_estudiante);
        string titulo = (idxL==-1?"(libro?)":libros[idxL].titulo);
        string nombreE = (idxE==-1?"(estudiante?)":estudiantes[idxE].nombre);
        cout << p.id << ": Libro[" << p.id_libro << "] " << titulo << " -- Estudiante[" << p.id_estudiante << "] " << nombreE
             << " -- Prestado: " << p.fecha_prestamo << " -- Devolucion: " << (p.fecha_devolucion.empty()?"(pendiente)":p.fecha_devolucion) << "\n";
    }
}

void devolverPrestamo() {
    cout << "Devolver Prestamo - ID: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idx = findPrestamoIndexById(id);
    if (idx == -1) { cout << "No existe prestamo con ese ID\n"; return; }
    if (!prestamos[idx].fecha_devolucion.empty()) { cout << "Prestamo ya devuelto.\n"; return; }
    cout << "Fecha devolucion (YYYY-MM-DD): "; getline(cin, prestamos[idx].fecha_devolucion);
    cout << "El libro ha sido devuelto.\n";
}

void actualizarPrestamo() {
    cout << "Actualizar Prestamo - ID: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idx = findPrestamoIndexById(id);
    if (idx == -1) { cout << "No existe prestamo con ese ID\n"; return; }
    string s;
    cout << "Nuevo fecha_prestamo (ENTER para mantener: " << prestamos[idx].fecha_prestamo << ") : "; getline(cin, s); if (!s.empty()) prestamos[idx].fecha_prestamo = s;
    cout << "Nueva fecha_devolucion (ENTER para mantener: " << prestamos[idx].fecha_devolucion << ") : "; getline(cin, s); if (!s.empty()) prestamos[idx].fecha_devolucion = s;
    cout << "Prestamo actualizado.\n";
}

void eliminarPrestamo() {
    cout << "Eliminar Prestamo - ID: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idx = findPrestamoIndexById(id);
    if (idx == -1) { cout << "No existe prestamo con ese ID\n"; return; }
    prestamos.erase(prestamos.begin()+idx);
    cout << "Prestamo eliminado.\n";
}

void listarLibrosPrestadosPorEstudiante() {
    cout << "ID Estudiante: "; int id; cin >> id; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int idxE = findEstudianteIndexById(id);
    if (idxE == -1) { cout << "El estudiante no existe.\n"; return; }
    cout << "Prestamos activos del estudiante " << estudiantes[idxE].nombre << ":\n";
    for (auto &p: prestamos) {
        if (p.id_estudiante == id && p.fecha_devolucion.empty()) {
            int idxL = findLibroIndexById(p.id_libro);
            cout << "Prestamo " << p.id << ": Libro[" << p.id_libro << "] " << (idxL==-1?"(libro?)":libros[idxL].titulo) << " Fecha: " << p.fecha_prestamo << "\n";
        }
    }
}

void autoresConMasLibros() {
    unordered_map<int,int> count;
    for (auto &l: libros) count[l.id_autor]++;

    vector<pair<int,int>> arr;
    for (auto &kv : count) arr.push_back(kv);
    sort(arr.begin(), arr.end(), [](auto &a, auto &b){ return a.second > b.second; });
    cout << "Autores por numero de libros:\n";
    for (auto &p: arr) {
        int idx = findAutorIndexById(p.first);
        string nombre = (idx==-1?"(desconocido)":autores[idx].nombre);
        cout << nombre << " (ID=" << p.first << ") -> " << p.second << " libros\n";
    }
}

void menuAutores() {
    while (true) {
        cout << "\n------ AUTOR ------\n1 Agregar \n2 Listar \n3 Actualizar \n4 Eliminar \n0 Volver\nOpcion: ";
        int op; cin >> op; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (op==0) break;
        switch(op) {
            case 1: agregarAutor(); break;
            case 2: listarAutores(); break;
            case 3: actualizarAutor(); break;
            case 4: eliminarAutor(); break;
            default: cout << "Opcion no valida\n"; break;
        }
        guardarTodo();
    }
}

void menuLibros() {
    while (true) {
        cout << "\n------ LIBROS ------\n1 Agregar \n2 Listar \n3 Actualizar \n4 Eliminar \n0 Volver\nOpcion: ";
        int op; cin >> op; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (op==0) break;
        switch(op) {
            case 1: agregarLibro(); break;
            case 2: listarLibros(); break;
            case 3: actualizarLibro(); break;
            case 4: eliminarLibro(); break;
            default: cout << "Opcion no valida\n"; break;
        }
        guardarTodo();
    }
}

void menuEstudiantes() {
    while (true) {
        cout << "\n------ ESTUDIANTES ------\n1 Agregar \n2 Listar \n3 Actualizar \n4 Eliminar \n0 Volver\nOpcion: ";
        int op; cin >> op; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (op==0) break;
        switch(op) {
            case 1: agregarEstudiante(); break;
            case 2: listarEstudiantes(); break;
            case 3: actualizarEstudiante(); break;
            case 4: eliminarEstudiante(); break;
            default: cout << "Opcion no valida\n"; break;
        }
        guardarTodo();
    }
}

void menuPrestamos() {
    while (true) {
        cout << "\n------ PRESTAMOS ------\n1 Agregar \n2 Listar Todos \n3 Listar Activos \n4 Devolver \n5 Actualizar \n6 Eliminar \n0 Volver\nOpcion: ";
        int op; cin >> op; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (op==0) break;
        switch(op) {
            case 1: agregarPrestamo(); break;
            case 2: listarPrestamos(false); break;
            case 3: listarPrestamos(true); break;
            case 4: devolverPrestamo(); break;
            case 5: actualizarPrestamo(); break;
            case 6: eliminarPrestamo(); break;
            default: cout << "Opcion no valida\n"; break;
        }
        guardarTodo();
    }
}

void menuConsultas() {
    while (true) {
        cout << "\n------ CONSULTAS ------\n1 Libros prestados por estudiante \n2 Autores con mas libros \n0 Volver\nOpcion: ";
        int op; cin >> op; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (op==0) break;
        switch(op) {
            case 1: listarLibrosPrestadosPorEstudiante(); break;
            case 2: autoresConMasLibros(); break;
            default: cout << "Opcion no valida\n"; break;
        }
    }
}

int main() {
    cout << "Cargando datos...\n";
    cargarTodo();
    cout << "Bienvenido al sistema de gestion de biblioteca virtual\n";
    while (true) {
        cout << "\n------ MENU PRINCIPAL ------\n1 Autores\n2 Libros\n3 Estudiantes\n4 Prestamos\n5 Consultas \n0 Salir\nOpcion: ";
        int op; cin >> op; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (op==0) { guardarTodo(); break; }
        switch(op) {
            case 1: menuAutores(); break;
            case 2: menuLibros(); break;
            case 3: menuEstudiantes(); break;
            case 4: menuPrestamos(); break;
            case 5: menuConsultas(); break;
            default: cout << "Opcion no valida\n"; break;
        }
    }
    return 0;
}
