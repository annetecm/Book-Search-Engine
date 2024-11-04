#include <iostream>
#include <fstream>
#include <sstream>
#include "DynamicArray_SR.hpp"
#include "LinkedList_SR.hpp"
#include "DoublyLinkedList_SR.hpp"
#include "Stack_array.hpp"
#include "Queue_Array.hpp"
#include "Priority_Queue.hpp"

using namespace std;

struct Libro {
    int id;
    string title;
    string author;
    string genre;
    float average_rating;
    int num_page;
    int ratings_count;
    string publication_date;
    string publisher;

    friend ostream& operator<<(ostream& os, const Libro& libro) {
        os << "ID: " << libro.id << "\n"
           << "Titulo: " << libro.title << "\n"
           << "Autor: " << libro.author << "\n"
           << "Genero: " << libro.genre << "\n"
           << "Calificacion promedio: " << libro.average_rating << "\n"
           << "Numero de paginas: " << libro.num_page << "\n"
           << "Numero de calificaciones: " << libro.ratings_count << "\n"
           << "Fecha de publicacion: " << libro.publication_date << "\n"
           << "Publisher: " << libro.publisher << "\n";
        return os;
    }
};

string cleanString(const string& str) { //Se tuvo que recurrir a esta funcion para limpiar los caracteres ya que al parecer algunos tenian caracteres invisibles
    string cleaned;
    for (char c : str) {
        if (isdigit(c)) {
            cleaned += c;  // Solo agrega caracteres numéricos
        }
    }
    return cleaned;
}

void loadDataIntoArray(const string& filename, DynamicArray<Libro>& arr) {
    ifstream file(filename);
    string line;
    int lineNumber = 0;  // Contador para el número de línea

    if (!file) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    while (getline(file, line)) {

        stringstream ss(line);
        string temp;
        Libro libro;

        getline(ss, temp, ',');
        temp = cleanString(temp);  // Limpia el ID de caracteres invisibles
        libro.id = stoi(temp);

        getline(ss, libro.title, ',');

        getline(ss, libro.author, ',');

        getline(ss, libro.genre, ',');

        getline(ss, temp, ',');
        libro.average_rating = stof(temp);

        getline(ss, temp, ',');
        libro.num_page = stoi(temp);

        getline(ss, temp, ',');
        libro.ratings_count = stoi(temp);

        getline(ss, libro.publication_date, ',');

        getline(ss, libro.publisher, ',');

        arr.push_back(libro);
    }

    file.close();
}

void ordenarPorPuntaje(DynamicArray<Libro>& libros) {
    for (size_t i = 0; i < libros.size() - 1; i++) {
        for (size_t j = 0; j < libros.size() - i - 1; j++) {
            if (libros[j].average_rating < libros[j + 1].average_rating) {
                Libro temp = libros[j];
                libros[j] = libros[j + 1];
                libros[j + 1] = temp;
            }
        }
    }
}

void capturarCategorias(string categorias[], string valores[], int& numFiltros) {
    cout << "Cuantas categorias desea aplicar? (3 posibles) ";
    cin >> numFiltros;
    cin.ignore();

    for (int i = 0; i < numFiltros; ++i) {
        cout << "Ingrese la categoria de filtro (author, genre, publisher): ";
        getline(cin, categorias[i]);
        cout << "Ingrese que " << categorias[i] << " quiere buscar: ";
        getline(cin, valores[i]);
    }
}

bool cumpleFiltros(const Libro& libro, string categorias[], string valores[], int numFiltros) {
    for (int i = 0; i < numFiltros; ++i) {
        if (categorias[i] == "author" && libro.author != valores[i]) return false;
        if (categorias[i] == "genre" && libro.genre != valores[i]) return false;
        if (categorias[i] == "publisher" && libro.publisher != valores[i]) return false;
    }
    return true;
}

void loadDataIntoLinkedList(const string& filename, LinkedList<Libro>& list) {
    ifstream file(filename);
    string line;

    if (!file) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Libro libro;

        getline(ss, temp, ',');
        temp = cleanString(temp);
        libro.id = std::stoi(temp);

        getline(ss, libro.title, ',');

        getline(ss, libro.author, ',');

        getline(ss, libro.genre, ',');

        getline(ss, temp, ',');
        libro.average_rating = stof(temp);

        getline(ss, temp, ',');
        libro.num_page = stoi(temp);

        getline(ss, temp, ',');
        libro.ratings_count = stoi(temp);

        getline(ss, libro.publication_date, ',');

        getline(ss, libro.publisher, ',');

        list.push_back(libro);
    }

    file.close();
}

void loadDataIntoDoublyLinkedList(const string& filename, DoublyLinkedList<Libro>& list) {
    ifstream file(filename);
    string line;

    if (!file) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Libro libro;

        getline(ss, temp, ',');
        temp = cleanString(temp);
        libro.id = std::stoi(temp);

        getline(ss, libro.title, ',');

        getline(ss, libro.author, ',');

        getline(ss, libro.genre, ',');

        getline(ss, temp, ',');
        libro.average_rating = stof(temp);

        getline(ss, temp, ',');
        libro.num_page = stoi(temp);

        getline(ss, temp, ',');
        libro.ratings_count = stoi(temp);

        getline(ss, libro.publication_date, ',');

        getline(ss, libro.publisher, ',');

        list.push_back(libro);
    }

    file.close();
}

void buscarPorIDLista(const LinkedList<Libro>& list, int id) {
    Node<Libro>* current = list.getHead();

    while (current != nullptr) {
        if (current->data.id == id) {
            cout << current->data << endl;
            return;
        }
        current = current->next;
    }
    cout << "Libro con ID " << id << " no encontrado." << endl;
}

void buscarPorIDDobleLista(const DoublyLinkedList<Libro>& list, int id) {
    DoublyNode<Libro>* current = list.getHead();

    while (current != nullptr) {
        if (current->data.id == id) {
            cout << current->data << endl;
            return;
        }
        current = current->next;
    }
    cout << "Libro con ID " << id << " no encontrado." << endl;
}

void buscarPorIDDesdeElFinal(const DoublyLinkedList<Libro>& list, int id) {
    DoublyNode<Libro>* current = list.getTail();

    while (current != nullptr) {
        if (current->data.id == id) {
            cout << current->data << endl;
            return;
        }
        current = current->prev;
    }
    cout << "Libro con ID " << id << " no encontrado." << endl;
}

void buscarPorID(const DynamicArray<Libro>& arr, int id) {
    for (unsigned int i = 0; i < arr.size(); i++) {
        if (arr[i].id == id) {
            cout << arr[i] << endl;
            return;
        }
    }
    cout << "Libro con ID " << id << " no encontrado." << std::endl;
}

////////////////////////////QUEUE///////////////////
/*
void agruparPorCategoriasMixtas(const DynamicArray<Libro>& libros, QueueA<Libro>* categorias, int& numCategorias, string categoriasFiltros[], string valoresFiltros[], int numFiltros, int topN = 5) {
    for (size_t i = 0; i < libros.size(); ++i) {
        const Libro& libro = libros[i];

        if (cumpleFiltros(libro, categoriasFiltros, valoresFiltros, numFiltros)) {
            bool found = false;
            int categoriaIndex = -1;

            for (int j = 0; j < numCategorias; ++j) {
                if (categorias[j].front().author == libro.author) {
                    categoriaIndex = j;
                    found = true;
                    break;
                }
            }

            if (!found && numCategorias < 10) {
                categoriaIndex = numCategorias++;
                categorias[categoriaIndex].push(libro);
            } else if (found && categorias[categoriaIndex].size() < topN) {
                categorias[categoriaIndex].push(libro);
            }
        }
    }
}

void mostrarPorCategoria(QueueA<Libro>* categorias, int numCategorias) {
    for (int i = 0; i < numCategorias; ++i) {
        cout << "\nProductos mas relevantes:\n";

        QueueA<Libro> tempQueue = categorias[i];
        DynamicArray<Libro> librosTemp;
        while (!tempQueue.empty()) {
            librosTemp.push_back(tempQueue.front());
            tempQueue.pop();
        }

        ordenarPorPuntaje(librosTemp);

        for (size_t j = 0; j < librosTemp.size(); ++j) {
            Libro libro = librosTemp[j];
            cout << "Titulo: " << libro.title << "\n"
                 << "Calificacion promedio: " << libro.average_rating << "\n"
                 << "Numero de paginas: " << libro.num_page << "\n"
                 << "Fecha de publicacion: " << libro.publication_date << "\n"
                 << "Editorial: " << libro.publisher << "\n\n";
        }
    }
}
*/


/////////////////////////////STACK///////////////////////////////
/*
void agruparPorCategoriasMixtas(const DynamicArray<Libro>& libros, StackA<Libro>* categorias, int& numCategorias, string categoriasFiltros[], string valoresFiltros[], int numFiltros, int topN = 5) {
    for (size_t i = 0; i < libros.size(); ++i) {
        const Libro& libro = libros[i];

        if (cumpleFiltros(libro, categoriasFiltros, valoresFiltros, numFiltros)) {
            bool found = false;
            int categoriaIndex = -1;

            for (int j = 0; j < numCategorias; ++j) {
                if (categorias[j].top().author == libro.author) {
                    categoriaIndex = j;
                    found = true;
                    break;
                }
            }

            if (!found && numCategorias < 10) {
                categoriaIndex = numCategorias++;
                categorias[categoriaIndex].push(libro);
            } else if (found && categorias[categoriaIndex].size() < topN) {
                categorias[categoriaIndex].push(libro);
            }
        }
    }
}

void mostrarPorCategoria(StackA<Libro>* categorias, int numCategorias) {
    for (int i = 0; i < numCategorias; ++i) {
        cout << "\nProductos mas relevantes:\n";

        StackA<Libro> tempStack = categorias[i];
        DynamicArray<Libro> librosTemp;

        while (!tempStack.empty()) {
            librosTemp.push_back(tempStack.top());
            tempStack.pop();
        }

        ordenarPorPuntaje(librosTemp);

        for (size_t j = 0; j < librosTemp.size(); ++j) {
            Libro libro = librosTemp[j];
            cout << "Titulo: " << libro.title << "\n"
                 << "Calificacion promedio: " << libro.average_rating << "\n"
                 << "Numero de paginas: " << libro.num_page << "\n"
                 << "Fecha de publicacion: " << libro.publication_date << "\n"
                 << "Editorial: " << libro.publisher << "\n\n";
        }
    }
}
*/

////////////////////PRIORITY QUEUE//////////////////////////7
void agruparPorCategoriasMixtas(const DynamicArray<Libro>& libros, PriorityQueue* categorias, int& numCategorias, string categoriasFiltros[], string valoresFiltros[], int numFiltros, int topN = 5) {
    for (size_t i = 0; i < libros.size(); ++i) {
        const Libro& libro = libros[i];

        if (cumpleFiltros(libro, categoriasFiltros, valoresFiltros, numFiltros)) {
            bool found = false;
            int categoriaIndex = -1;

            for (int j = 0; j < numCategorias; ++j) {
                if (categorias[j].top() == libro.id) {
                    categoriaIndex = j;
                    found = true;
                    break;
                }
            }

            //Convierte la calificación a prioridad. Se usa static_cast para convirtir la variable en float
            //Se multiplica por 10 para que se convierta en entero y se pueda usar como la prioridad
            int priority = static_cast<int>(libro.average_rating * 10);

            if (!found && numCategorias < 10) {
                categoriaIndex = numCategorias++;
                categorias[categoriaIndex].push(libro.id, priority);
            } else if (found && categorias[categoriaIndex].size() < topN) {
                categorias[categoriaIndex].push(libro.id, priority);
            }
        }
    }
}

void mostrarPorCategoria(PriorityQueue* categorias, int numCategorias, const DynamicArray<Libro>& libros) {
    for (int i = 0; i < numCategorias; ++i) {
        cout << ":\nProductos más relevantes:\n";

        PriorityQueue tempQueue = categorias[i];
        DynamicArray<Libro> librosTemp;

        //Se busca el libro según su id para tener toda la info antes de su uso
        while (!tempQueue.empty()) {
            int libroId = tempQueue.top();
            for (size_t j = 0; j < libros.size(); ++j) {
                if (libros[j].id == libroId) {
                    librosTemp.push_back(libros[j]);
                    break;
                }
            }
            tempQueue.pop();
        }

        ordenarPorPuntaje(librosTemp);

        for (size_t j = 0; j < librosTemp.size(); ++j) {
            Libro libro = librosTemp[j];
            cout << "Titulo: " << libro.title << "\n"
                 << "Calificacion promedio: " << libro.average_rating << "\n"
                 << "Numero de paginas: " << libro.num_page << "\n"
                 << "Fecha de publicacion: " << libro.publication_date << "\n"
                 << "Editorial: " << libro.publisher << "\n\n";
        }
    }
}

//BUSQUEDA BINARIA
int particion(DynamicArray<Libro>& arr, int low, int high, const string& categoria) {
    Libro pivote = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        bool condicion = false;
        if (categoria == "id") condicion = (arr[j].id < pivote.id);
        else if (categoria == "title") condicion = (arr[j].title < pivote.title);
        else if (categoria == "author") condicion = (arr[j].author < pivote.author);
        else if (categoria == "genre") condicion = (arr[j].genre < pivote.genre);
        else if (categoria == "average_rating") condicion = (arr[j].average_rating < pivote.average_rating);
        else if (categoria == "num_page") condicion = (arr[j].num_page < pivote.num_page);
        else if (categoria == "ratings_count") condicion = (arr[j].ratings_count < pivote.ratings_count);
        else if (categoria == "publication_date") condicion = (arr[j].publication_date < pivote.publication_date);
        else if (categoria == "publisher") condicion = (arr[j].publisher < pivote.publisher);

        if (condicion) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(DynamicArray<Libro>& arr, int low, int high, const string& categoria) {
    if (low < high) {
        int pi = particion(arr, low, high, categoria);
        quickSort(arr, low, pi - 1, categoria);
        quickSort(arr, pi + 1, high, categoria);
    }
}

int busquedaBinariaPrimeraCoincidencia(const DynamicArray<Libro>& arr, int inicio, int fin, const string& categoria, const string& valor) {
    int indiceResultado = -1;
    while (inicio <= fin) {
        int mitad = inicio + (fin - inicio) / 2;
        bool coincide = false;
        if (categoria == "id") coincide = (arr[mitad].id == stoi(valor));
        else if (categoria == "title") coincide = (arr[mitad].title == valor);
        else if (categoria == "author") coincide = (arr[mitad].author == valor);
        else if (categoria == "genre") coincide = (arr[mitad].genre == valor);
        else if (categoria == "average_rating") coincide = (arr[mitad].average_rating == stof(valor));
        else if (categoria == "num_page") coincide = (arr[mitad].num_page == stoi(valor));
        else if (categoria == "ratings_count") coincide = (arr[mitad].ratings_count == stoi(valor));
        else if (categoria == "publication_date") coincide = (arr[mitad].publication_date == valor);
        else if (categoria == "publisher") coincide = (arr[mitad].publisher == valor);

        if (coincide) {
            indiceResultado = mitad;
            fin = mitad - 1;
        } else {
            bool menorQueMitad = false;
            if (categoria == "id") menorQueMitad = (arr[mitad].id < stoi(valor));
            else if (categoria == "title") menorQueMitad = (arr[mitad].title < valor);
            else if (categoria == "author") menorQueMitad = (arr[mitad].author < valor);
            else if (categoria == "genre") menorQueMitad = (arr[mitad].genre < valor);
            else if (categoria == "average_rating") menorQueMitad = (arr[mitad].average_rating < stof(valor));
            else if (categoria == "num_page") menorQueMitad = (arr[mitad].num_page < stoi(valor));
            else if (categoria == "ratings_count") menorQueMitad = (arr[mitad].ratings_count < stoi(valor));
            else if (categoria == "publication_date") menorQueMitad = (arr[mitad].publication_date < valor);
            else if (categoria == "publisher") menorQueMitad = (arr[mitad].publisher < valor);

            if (menorQueMitad) inicio = mitad + 1;
            else fin = mitad - 1;
        }
    }
    return indiceResultado;
}


int busquedaBinariaUltimaCoincidencia(const DynamicArray<Libro>& arr, int inicio, int fin, const string& categoria, const string& valor) {
    int indiceResultado = -1;
    while (inicio <= fin) {
        int mitad = inicio + (fin - inicio) / 2;
        bool coincide = false;
        if (categoria == "id") coincide = (arr[mitad].id == stoi(valor));
        else if (categoria == "title") coincide = (arr[mitad].title == valor);
        else if (categoria == "author") coincide = (arr[mitad].author == valor);
        else if (categoria == "genre") coincide = (arr[mitad].genre == valor);
        else if (categoria == "average_rating") coincide = (arr[mitad].average_rating == stof(valor));
        else if (categoria == "num_page") coincide = (arr[mitad].num_page == stoi(valor));
        else if (categoria == "ratings_count") coincide = (arr[mitad].ratings_count == stoi(valor));
        else if (categoria == "publication_date") coincide = (arr[mitad].publication_date == valor);
        else if (categoria == "publisher") coincide = (arr[mitad].publisher == valor);

        if (coincide) {
            indiceResultado = mitad;
            inicio = mitad + 1;
        } else {
            bool menorQueMitad = false;
            if (categoria == "id") menorQueMitad = (arr[mitad].id < stoi(valor));
            else if (categoria == "title") menorQueMitad = (arr[mitad].title < valor);
            else if (categoria == "author") menorQueMitad = (arr[mitad].author < valor);
            else if (categoria == "genre") menorQueMitad = (arr[mitad].genre < valor);
            else if (categoria == "average_rating") menorQueMitad = (arr[mitad].average_rating < stof(valor));
            else if (categoria == "num_page") menorQueMitad = (arr[mitad].num_page < stoi(valor));
            else if (categoria == "ratings_count") menorQueMitad = (arr[mitad].ratings_count < stoi(valor));
            else if (categoria == "publication_date") menorQueMitad = (arr[mitad].publication_date < valor);
            else if (categoria == "publisher") menorQueMitad = (arr[mitad].publisher < valor);

            if (menorQueMitad) inicio = mitad + 1;
            else fin = mitad - 1;
        }
    }
    return indiceResultado;
}


void buscarTodosPorCategoria(const DynamicArray<Libro>& arr, const string& categoria, const string& dato) {
    int primerIndice = busquedaBinariaPrimeraCoincidencia(arr, 0, arr.size() - 1, categoria, dato);
    if (primerIndice == -1) {
        cout << "Libro con " << categoria << " " << dato << " no encontrado." << endl;
        return;
    }

    int ultimoIndice = busquedaBinariaUltimaCoincidencia(arr, 0, arr.size() - 1, categoria, dato);

    for (int i = primerIndice; i <= ultimoIndice; i++) {
        cout << arr[i] << endl;
    }
}

//BUSQUEDA SECUENCIAL
void SequentialSearch(const DynamicArray<Libro>& arr, const string& categoria, const string& valorBusqueda) {
    bool encontradoValor = false;

    for (unsigned int indice = 0; indice < arr.size(); indice++) {
        bool coincide = false;
        if (categoria == "id") coincide = (arr[indice].id == stoi(valorBusqueda));
        else if (categoria == "title") coincide = (arr[indice].title == valorBusqueda);
        else if (categoria == "author") coincide = (arr[indice].author == valorBusqueda);
        else if (categoria == "genre") coincide = (arr[indice].genre == valorBusqueda);
        else if (categoria == "average_rating") coincide = (arr[indice].average_rating == stof(valorBusqueda));
        else if (categoria == "num_page") coincide = (arr[indice].num_page == stoi(valorBusqueda));
        else if (categoria == "ratings_count") coincide = (arr[indice].ratings_count == stoi(valorBusqueda));
        else if (categoria == "publication_date") coincide = (arr[indice].publication_date == valorBusqueda);
        else if (categoria == "publisher") coincide = (arr[indice].publisher == valorBusqueda);

        if (coincide) {
            cout << arr[indice] << endl;
            encontradoValor = true;
        }
    }

    if (!encontradoValor) {
        cout << "Libro con " << categoria << " " << valorBusqueda << " no encontrado." << endl;
    }
}

int main()
{
    DynamicArray<Libro> libros1;
    loadDataIntoArray("libro_final.csv", libros1);

    int id_search;
    cout << "Ingresa el ID del libro que deseas buscar: ";
    cin >> id_search;

    cout << "Información del libro (Arreglo):" << endl;
    buscarPorID(libros1, id_search);

    /*
    cout << "Información del libro (Lista ligada):" << endl;
    buscarPorIDLista(libros1, id_search);

    cout << "Información del libro (Lista doblemente ligada desde inicio):" << endl;
    buscarPorIDDobleLista(libros1, id_search);

    cout << "Información del libro (Lista doblemente ligada desde final):" << endl;
    buscarPorIDDesdeElFinal(libros1, id_search);
    */

//BUSQUEDA BINARIA
    string continuar1;
    do {
        int opcion;
        string categoria, value;
         cout << "/////////BÚSQUEDA BINARIA/////////\n";
        cout << "Selecciona la categoria por la que deseas buscar en el formato indicado:\n";
        cout << "1. ID\n";
        cout << "2. Titulo(Titulo_Libro): \n";
        cout << "3. Autor(Nombre_Apellido): \n";
        cout << "4. Genero(Genero del Libro): \n";
        cout << "5. Calificacion promedio(1-5): \n";
        cout << "6. Numero de paginas\n";
        cout << "7. Numero de calificaciones\n";
        cout << "8. Fecha de publicacion: MM-DD-AAAA\n";
        cout << "9. Publisher: Nombre_Publisher\n";
        cout << "Ingresa el numero de tu opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: categoria = "id"; break;
            case 2: categoria = "title"; break;
            case 3: categoria = "author"; break;
            case 4: categoria = "genre"; break;
            case 5: categoria = "average_rating"; break;
            case 6: categoria = "num_page"; break;
            case 7: categoria = "ratings_count"; break;
            case 8: categoria = "publication_date"; break;
            case 9: categoria = "publisher"; break;
            default: cout << "Opcion invalida. Saliendo..." << endl; return 0;
        }

        cout << "Ingresa el valor para buscar: ";
        cin >> value;

        quickSort(libros1, 0, libros1.size() - 1, categoria);
        buscarTodosPorCategoria(libros1, categoria, value);

        cout << "¿Deseas buscar otra vez? (s/n): ";
        cin >> continuar1;
    } while (continuar1 == "s");


//BUSQUEDA SECUENCIAL
/* Cargar la base de datos
    DynamicArray<Libro> libros2; // Crea un array dinámico de libros
    loadDataIntoArray("libro_final.csv", libros2); // Carga datos en el array

    string continuar2; // Variable para manejar el ciclo del menú
    do {
        int opcion;     
        string categoria;   
        string dato;   

        // Muestra el menú de opciones
        cout << "/////////BÚSQUEDA SECUENCIAL/////////\n";
        cout << "Selecciona la categoria por la que deseas buscar en el formato indicado:\n";
        cout << "1. ID\n";
        cout << "2. Titulo(Titulo_Libro): \n";
        cout << "3. Autor(Nombre_Apellido): \n";
        cout << "4. Genero(Genero del Libro): \n";
        cout << "5. Calificacion promedio(1-5): \n";
        cout << "6. Numero de paginas\n";
        cout << "7. Numero de calificaciones\n";
        cout << "8. Fecha de publicacion: MM-DD-AAAA\n";
        cout << "9. Publisher: Nombre_Publisher\n";
        cout << "Ingresa el numero de tu opcion: ";
        cin >> opcion;

        // Asigna la categoria de búsqueda según la opción seleccionada
        switch (opcion) {
            case 1: categoria = "id"; break;
            case 2: categoria = "title"; break;
            case 3: categoria = "author"; break;
            case 4: categoria= "genre"; break;
            case 5: categoria= "average_rating"; break;
            case 6: categoria = "num_page"; break;
            case 7: categoria = "ratings_count"; break;
            case 8: categoria = "publication_date"; break;
            case 9: categoria = "publisher"; break;
            default: cout << "Opcion invalida. Saliendo..." << endl; return 0;
        }

        cout << "Ingresa el dato para buscar: "; //Solicita el dato a buscar
        cin >> dato;

        SequentialSearch(libros2, categoria, dato); 

        cout << "¿Deseas buscar otra vez? (s/n): "; 
        cin >> continuar2;
    } while (continuar2 == "s"); 
    */
   const int maxCategorias = 5;
    ordenarPorPuntaje(libros1);

    string categoriasFiltros[maxCategorias];
    string valoresFiltros[maxCategorias];
    int numFiltros = 0;
    capturarCategorias(categoriasFiltros, valoresFiltros, numFiltros);

    PriorityQueue categorias[maxCategorias];
    int numCategorias = 0;
    agruparPorCategoriasMixtas(libros1, categorias, numCategorias, categoriasFiltros, valoresFiltros, numFiltros);

    mostrarPorCategoria(categorias, numCategorias, libros1);


    return 0;
};