#include "Cell.h"

#include <iostream>

int main() {
    std::string s = "emp";
    int k = 45;
   // Cell cell1("string"); // isnt work correctly
    Cell cell1(8.25);
    Cell cell2 = cell1;
    Cell cell3(cell1);
    std::cout << cell1 << std::endl;
    std::cout << cell2 << std::endl;
    std::cout << cell3 << std::endl;
    return 0;
}
