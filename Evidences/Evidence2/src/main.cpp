#include <chrono>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

struct RawLine {
    size_t number = 0;
    string text;
};

struct Record {
    string original, ip, event, dateText;
    int year = 0, month = 0, day = 0;
    long long dayKey = 0, timeKey = 0;
    size_t arrivalIndex = 0;
};

string trim(const string& s) {
    size_t begin = s.find_first_not_of(" \t\r\n");
    if (begin == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(begin, end - begin + 1);
}

bool digitsOnly(const string& s) {
    if (s.empty()) return false;
    for (unsigned char c : s) if (!isdigit(c)) return false;
    return true;
}

int monthNumber(const string& month) {
    static const char* names[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; ++i) if (month == names[i]) return i + 1;
    return 0;
}

bool validDate(int y, int m, int d) {
    if (y < 1 || y > 9999 || m < 1 || m > 12 || d < 1) return false;
    static const int days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
    return d <= days[m] + ((m == 2 && leap) ? 1 : 0);
}

bool parseDay(const string& input, int& y, int& m, int& d, string& error) {
    string s = trim(input), name, ds, ys, extra;
    istringstream in(s);
    if (!(in >> name >> ds >> ys) || (in >> extra)) {
        error = "Usa exactamente Mmm DD AAAA (ejemplo Sep 14 2024).";
        return false;
    }
    m = monthNumber(name);
    if (!m) { error = "Mes invalido (ejemplo: Jan, Feb, Sep)."; return false; }
    if (ds.size() != 2 || ys.size() != 4 || !digitsOnly(ds) || !digitsOnly(ys)) {
        error = "Dia de 2 digitos y anio de 4 digitos requeridos.";
        return false;
    }
    d = stoi(ds); y = stoi(ys);
    if (!validDate(y, m, d)) { error = "Dia inexistente o fecha fuera de rango."; return false; }
    return true;
}

bool parseTime(const string& time, int& h, int& min, int& sec) {
    if (time.size() != 8 || time[2] != ':' || time[5] != ':') return false;
    string hs = time.substr(0,2), ms = time.substr(3,2), ss = time.substr(6,2);
    if (!digitsOnly(hs) || !digitsOnly(ms) || !digitsOnly(ss)) return false;
    h = stoi(hs); min = stoi(ms); sec = stoi(ss);
    return h >= 0 && h <= 23 && min >= 0 && min <= 59 && sec >= 0 && sec <= 59;
}

bool validIP(const string& ip) {
    istringstream in(ip);
    string part;
    int count = 0;
    while (getline(in, part, '.')) {
        if (++count > 4 || part.size() > 3 || !digitsOnly(part)) return false;
        int octet = stoi(part);
        if (octet < 0 || octet > 255) return false;
    }
    return count == 4 && !ip.empty() && ip.back() != '.';
}

bool parseRecord(const RawLine& raw, Record& r, string& error) {
    string mmm, dd, yyyy, hhmmss, ip, event;
    istringstream in(trim(raw.text));
    if (!(in >> mmm >> dd >> yyyy >> hhmmss >> ip)) {
        error = "faltan campos de fecha, hora o IP";
        return false;
    }
    getline(in, event);
    event = trim(event);
    if (event.empty()) { error = "descripcion de evento vacia"; return false; }
    int year = 0, month = 0, day = 0;
    if (!parseDay(mmm + " " + dd + " " + yyyy, year, month, day, error)) return false;
    int h = 0, minute = 0, second = 0;
    if (!parseTime(hhmmss, h, minute, second)) {
        error = "hora invalida, se espera HH:MM:SS";
        return false;
    }
    if (!validIP(ip)) { error = "IP IPv4 invalida"; return false; }
    r.year = year;
    r.month = month;
    r.day = day;
    r.dayKey = ((static_cast<long long>(year) * 13 + month) * 32 + day);
    r.timeKey = (((r.dayKey * 24 + h) * 60 + minute) * 60 + second);
    r.dateText = mmm + " " + dd + " " + yyyy;
    r.ip = ip;
    r.event = event;
    r.original = trim(raw.text);
    r.arrivalIndex = raw.number;
    return true;
}

bool earlier(const Record& a, const Record& b) { return a.timeKey < b.timeKey; }

bool writeOutput(const DoublyLinkedList<Record>& records) {
    ofstream out("out/output608.out");
    if (!out) {
        cerr << "No se pudo crear out/output608.out. Ejecuta desde la carpeta raiz del proyecto.\n";
        return false;
    }
    for (auto* p = records.head(); p; p = p->next) out << p->data.original << '\n';
    return static_cast<bool>(out);
}

bool stableTies(const DoublyLinkedList<Record>& records) {
    for (auto* p = records.head(); p && p->next; p = p->next)
        if (p->data.timeKey == p->next->data.timeKey &&
            p->data.arrivalIndex > p->next->data.arrivalIndex) return false;
    return true;
}

bool readChoice(const string& prompt, string& result) {
    cout << prompt;
    if (!getline(cin, result)) return false;
    result = trim(result);
    return true;
}

bool loadFile(DoublyLinkedList<Record>& records, string& file,
              size_t& skipped) {
    while (true) {
        cout << "\n=== ARCHIVOS DISPONIBLES ===\n"
             << "1) log607-1.txt (desordenado)\n"
             << "2) log607-2.txt (casi ordenado)\n"
             << "3) Escribir ruta de otro archivo\n"
             << "0) Salir\n";
        string answer;
        if (!readChoice("Selecciona archivo: ", answer)) return false;
        if (answer == "0") return false;
        if (answer == "1") file = "data/log607-1.txt";
        else if (answer == "2") file = "data/log607-2.txt";
        else if (answer == "3") {
            if (!readChoice("Ruta del archivo: ", file)) return false;
            if (file.empty()) { cout << "La ruta no puede estar vacia.\n"; continue; }
        } else { cout << "Opcion invalida, intenta nuevamente.\n"; continue; }
        ifstream input(file);
        if (!input) { cout << "ERROR: el archivo no existe o no se puede abrir: " << file << '\n'; continue; }

        Queue<RawLine> incoming;
        string line;
        size_t lineNumber = 0;
        while (getline(input, line)) incoming.enqueue(RawLine{++lineNumber, line});
        if (input.bad()) { cerr << "Error de lectura del archivo.\n"; return false; }

        RawLine raw;
        skipped = 0;
        while (incoming.dequeue(raw)) {
            Record record;
            string error;
            if (!parseRecord(raw, record, error)) {
                ++skipped;
                cout << "[OMITIDA] Linea " << raw.number << ": " << error << '\n';
            } else {
                records.pushBack(record);  // respeta orden original de llegada
            }
        }
        cout << "\nArchivo: " << file << '\n'
             << "Registros cargados: " << records.size() << '\n'
             << "Lineas omitidas: " << skipped << '\n';
        return true;
    }
}

bool askDay(int& year, int& month, int& day) {
    string answer, error;
    if (!readChoice("Escribe el dia (Mmm DD AAAA): ", answer)) return false;
    if (!parseDay(answer, year, month, day, error)) {
        cout << "Fecha invalida: " << error << '\n';
        return false;
    }
    return true;
}

size_t searchDay(const DoublyLinkedList<Record>& records, long long key,
                 bool descending) {
    size_t found = 0;
    Stack<const NodeD<Record>*> stack;
    for (auto* p = records.head(); p; p = p->next) {
        if (p->data.dayKey > key) break; // optimizacion por lista ordenada
        if (p->data.dayKey == key) {
            ++found;
            if (descending) stack.push(p);
            else cout << p->data.original << '\n';
        }
    }
    if (descending) {
        const NodeD<Record>* p = nullptr;
        while (stack.pop(p)) cout << p->data.original << '\n';
    }
    cout << "Total de registros del dia: " << found << '\n';
    if (found == 0) cout << "No hay registros para ese dia.\n";
    return found;
}

void printMaxima(const map<string, size_t>& freq, const string& title) {
    size_t maximum = 0;
    for (const auto& item : freq) if (item.second > maximum) maximum = item.second;
    cout << title << " (" << maximum << " apariciones):\n";
    for (const auto& item : freq)
        if (item.second == maximum) cout << "  - " << item.first << " : " << item.second << '\n';
}

void statistics(const DoublyLinkedList<Record>& records) {
    map<string, size_t> days, events, ips;
    for (auto* p = records.head(); p; p = p->next) {
        ++days[p->data.dateText];
        ++events[p->data.event];
        ++ips[p->data.ip];
    }
    cout << "\n=== ESTADISTICAS ===\nTotal de registros: " << records.size() << '\n';
    if (records.empty()) { cout << "Sin datos para analizar.\n"; return; }
    printMaxima(days, "Dia(s) con mas incidentes");
    printMaxima(events, "Evento(s) mas frecuente(s)");
    printMaxima(ips, "IP(s) mas frecuente(s)");
}

int main() {
    cout << "=== ANALIZADOR DE EVENTOS DE RED ===\n";
    DoublyLinkedList<Record> records;
    string file;
    size_t skipped = 0;
    if (!loadFile(records, file, skipped)) return 0;

    // Un archivo ya cronologico no requiere ordenar (aun si hay empates de hora).
    bool sorted = records.isSorted(earlier);
    bool hadDaySearch = false;
    long long lastDayKey = 0;
    while (true) {
        cout << "\n========== MENU PRINCIPAL ==========\n"
             << "1. Ordenar por fecha y hora\n"
             << "2. Buscar logs por dia\n"
             << "3. Mostrar logs del dia descendente (Pila)\n"
             << "4. Estadisticas del archivo\n"
             << "5. Salir\n";
        string option;
        if (!readChoice("Elige una opcion: ", option)) break;
        if (option == "1") {
            if (records.empty()) { cout << "No hay registros validos para ordenar.\n"; continue; }
            if (sorted) {
                cout << "La lista ya esta ordenada; no se ejecuta Merge Sort otra vez.\n";
                if (writeOutput(records)) cout << "Archivo actualizado: out/output608.out\n";
                continue;
            }
            string prediction;
            if (!readChoice("Prediccion de comparaciones (1=n*log2(n), 2=n^2): ", prediction)) break;
            if (prediction != "1" && prediction != "2") {
                cout << "Prediccion invalida. Escribe 1 o 2.\n";
                continue;
            }
            auto start = chrono::steady_clock::now();
            SortMetrics metrics = records.sortStable(earlier);
            auto end = chrono::steady_clock::now();
            double milliseconds = chrono::duration<double, milli>(end - start).count();
            sorted = records.isSorted(earlier);
            cout << fixed << setprecision(3)
                 << "\n--- RESULTADO DEL ORDENAMIENTO ---\n"
                 << "Algoritmo: Merge Sort estable sobre nodos\n"
                 << "Archivo: " << file << '\n'
                 << "Registros: " << records.size() << '\n'
                 << "Tiempo (ms): " << milliseconds << '\n'
                 << "Comparaciones: " << metrics.comparisons << '\n'
                 << "Profundidad maxima de recursion: " << metrics.maxDepth << '\n'
                 << "Prediccion: " << (prediction == "1" ? "n*log2(n)" : "n^2") << '\n'
                 << "Coincide con la COMPLEJIDAD TEORICA: "
                 << (prediction == "1" ? "SI" : "NO") << '\n'
                 << "Verificacion de orden: " << (sorted ? "CORRECTO" : "ERROR") << '\n'
                 << "Empates preservan el orden de llegada: " << (stableTies(records) ? "SI" : "NO") << '\n';
            // Una sola corrida no demuestra el crecimiento asintotico.
            if (writeOutput(records)) cout << "Generado: out/output608.out\n";
        } else if (option == "2" || option == "3") {
            if (!sorted) { cout << "Primero debes ordenar la lista con la opcion 1.\n"; continue; }
            int year = 0, month = 0, day = 0;
            if (option == "2" || !hadDaySearch) {
                if (!askDay(year, month, day)) continue;
                lastDayKey = ((static_cast<long long>(year) * 13 + month) * 32 + day);
                hadDaySearch = true;
            }
            if (option == "2") cout << "\nRegistros del dia (ascendente):\n";
            else cout << "\nRegistros del ultimo dia buscado (descendente con Pila):\n";
            searchDay(records, lastDayKey, option == "3");
        } else if (option == "4") {
            statistics(records);
        } else if (option == "5") {
            cout << "Programa finalizado.\n";
            break;
        } else {
            cout << "Opcion invalida; elige del 1 al 5.\n";
        }
    }
    return 0;
}
