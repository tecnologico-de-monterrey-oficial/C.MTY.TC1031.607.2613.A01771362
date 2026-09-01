//Pamela Hernández Camacho
//A01771362

#include <iostream>
#include <string>
#include <utility>

using namespace std;

// Búsqueda secuencial: recorre el string comparando caracteres de dos en dos
// (ya que, salvo el único, todos los caracteres vienen duplicados y seguidos).
// Cada comparación de un par cuenta como 1 comparación.
pair<char, int> buscarSecuencial(const string& s) {
    int n = (int)s.size();
    int comparaciones = 0;
    int i = 0;
    while (i < n - 1) {
        comparaciones++;
        if (s[i] == s[i + 1]) {
            i += 2; // el par coincide, se avanza al siguiente par
        } else {
            return {s[i], comparaciones}; // el par se rompe: aqui esta el unico
        }
    }
    // Si se recorrieron todos los pares sin romperse, el unico es el ultimo caracter
    return {s[n - 1], comparaciones};
}

// Búsqueda binaria: aprovecha que antes del carácter único cada par empieza
// en un índice PAR, y después del único cada par empieza en un índice IMPAR.
// Se hace la búsqueda binaria clásica O(log n) sobre esa propiedad.
pair<char, int> buscarBinaria(const string& s) {
    int n = (int)s.size();
    int comparaciones = 0;
    int lo = 0, hi = n - 1;
    while (lo < hi) {
        int medio = lo + (hi - lo) / 2;
        if (medio % 2 == 1) medio--; // alinear al inicio de un par (indice par)
        comparaciones++;
        if (s[medio] == s[medio + 1]) {
            lo = medio + 2; // el par esta intacto, el unico esta a la derecha
        } else {
            hi = medio; // el par esta roto, el unico esta aqui o a la izquierda
        }
    }
    return {s[lo], comparaciones};
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for (int caso = 0; caso < n; caso++) {
        string s;
        getline(cin, s);

        pair<char, int> resSecuencial = buscarSecuencial(s);
        pair<char, int> resBinaria = buscarBinaria(s);

        cout << resSecuencial.first << " " << resSecuencial.second << " "
             << resBinaria.first << " " << resBinaria.second << "\n";
    }

    return 0;
}
