//Pamela Hernández Camacho
//A01771362
#include <iostream>
using namespace std;
#include "LinkedList.h"

int main() {

    LinkedList<string> list;
    list.push_front("b");
    list.push_front("a");
    list.push_front("@");
    list.push_front("&");
    list.print();


    return 0;
}
