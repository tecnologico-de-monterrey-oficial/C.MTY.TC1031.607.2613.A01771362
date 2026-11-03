// Pruebas automaticas y reproducibles para LinkedList<T>.
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "LinkedList.h"
using namespace std;

int passed = 0;
int failed = 0;

void check(const string& name, bool condition) {
    cout << (condition ? "[PASS] " : "[FAIL] ") << name << "\n";
    if (condition) ++passed;
    else ++failed;
}

bool throwsRange(const function<void()>& action) {
    try {
        action();
    } catch (const out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
    return false;
}

int main() {
    cout << "=== TESTS DEL ADT LINKED LIST ===\n";
    LinkedList<int> list;
    check("01 Lista inicialmente vacia", list.empty());
    check("02 Tamano inicialmente cero", list.getSize() == 0);
    check("03 deleteData en lista vacia retorna false", !list.deleteData(5));
    check("04 deleteAt en lista vacia retorna false", !list.deleteAt(0));
    check("05 findData en lista vacia retorna -1", list.findData(5) == -1);
    check("06 getData invalido lanza out_of_range", throwsRange([&] { (void)list.getData(0); }));
    check("07 operator[] invalido lanza out_of_range", throwsRange([&] { (void)list[0]; }));

    list.addFirst(20);
    check("08 addFirst agrega al inicio", list.getData(0) == 20);
    check("09 addFirst incrementa size", list.getSize() == 1);
    list.addLast(40);
    check("10 addLast agrega al final", list.getData(1) == 40);
    check("11 addLast incrementa size", list.getSize() == 2);
    list.insert(0, 10);  // [10,20,40]
    check("12 insert en posicion 0", list.getData(0) == 10);
    list.insert(2, 30);  // [10,20,30,40]
    check("13 insert intermedio", list.getData(2) == 30 && list.getSize() == 4);
    list.insert(4, 50);
    check("14 insert al final", list.getData(4) == 50);
    check("15 insert negativo lanza out_of_range", throwsRange([&] { list.insert(-1, 9); }));
    check("16 insert mayor a size lanza out_of_range", throwsRange([&] { list.insert(7, 9); }));
    check("17 getData regresa posicion correcta", list.getData(3) == 40);
    list.updateData(30, 35);
    check("18 updateData reemplaza primera coincidencia", list.getData(2) == 35);
    check("19 updateData ausente lanza out_of_range", throwsRange([&] { list.updateData(999, 5); }));
    list.updateAt(3, 45);
    check("20 updateAt reemplaza por indice", list.getData(3) == 45);
    check("21 updateAt fuera de rango lanza", throwsRange([&] { list.updateAt(9, 7); }));
    check("22 findData encuentra indice", list.findData(45) == 3);
    check("23 findData ausente retorna -1", list.findData(99) == -1);
    check("24 deleteData borra coincidencia", list.deleteData(35) && list.findData(35) == -1);
    check("25 deleteData sin coincidencia false", !list.deleteData(35));
    check("26 deleteAt borra cabeza", list.deleteAt(0) && list.getData(0) == 20);
    check("27 deleteAt borra ultimo", list.deleteAt(list.getSize()-1) && list.getSize() == 2);
    check("28 deleteAt invalido retorna false", !list.deleteAt(100));
    check("29 operator[] permite leer", list[0] == 20);
    list[0] = 25;
    check("30 operator[] permite actualizar", list.getData(0) == 25);
    const LinkedList<int>& constList = list;
    check("31 operator[] const permite leer", constList[1] == 45);
    check("32 operator[] negativo lanza", throwsRange([&] { (void)list[-1]; }));

    LinkedList<int> copy;
    copy.addFirst(-1);
    copy = list;
    check("33 operator= copia el contenido", copy.getSize() == 2 && copy[0] == 25 && copy[1] == 45);
    list[0] = 999;
    check("34 Copia independiente del original", copy[0] == 25);
    copy[1] = 777;
    check("35 Original independiente de la copia", list[1] == 45);
    copy = copy;
    check("36 Autoasignacion segura", copy[0] == 25 && copy[1] == 777);
    LinkedList<int> constructed(copy);
    constructed[0] = 111;
    check("37 Constructor de copia es profundo", copy[0] == 25 && constructed[0] == 111);
    constructed.clear();
    check("38 clear libera y deja lista vacia", constructed.empty() && constructed.getSize() == 0);
    constructed.push_front(7);
    check("39 Alias push_front funciona", constructed[0] == 7);
    constructed.push_back(8);
    check("40 Alias push_back funciona", constructed[1] == 8);

    LinkedList<string> words;
    words.addFirst("luna");
    check("41 Template string: addFirst", words[0] == "luna");
    words.addLast("sol");
    check("42 Template string: addLast", words[1] == "sol");
    check("43 Template string: getData", words.getData(0) == "luna");
    check("44 Template string: findData", words.findData("sol") == 1);
    words.updateData("sol", "mar");
    check("45 Template string: updateData", words[1] == "mar");
    check("46 Template string: deleteData", words.deleteData("luna") && words[0] == "mar");
    LinkedList<string> wordsCopy;
    wordsCopy = words;
    words[0] = "rio";
    check("47 Template string: copia profunda", wordsCopy[0] == "mar");

    ostringstream output;
    constructed.print(output);
    check("48 print muestra flechas", output.str() == "[7 -> 8]\n");
    LinkedList<int> duplicate;
    duplicate.addLast(5);
    duplicate.addLast(5);
    duplicate.addLast(8);
    check("49 deleteData elimina solo primera repeticion", duplicate.deleteData(5) && duplicate.getSize() == 2 && duplicate[0] == 5);
    check("50 deleteAt elimina ultimo nodo", duplicate.deleteAt(1) && duplicate.getSize() == 1 && duplicate[0] == 5);
    check("51 deleteAt elimina unico nodo", duplicate.deleteAt(0) && duplicate.empty());
    check("52 getData negativo lanza", throwsRange([&] { (void)list.getData(-1); }));
    check("53 operator[] const fuera de rango lanza", throwsRange([&] { (void)constList[99]; }));
    cout << "\nRESULTADO: " << passed << " aprobadas, " << failed << " fallidas.\n";
    return failed == 0 ? 0 : 1;
}