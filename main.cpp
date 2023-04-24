// Compilation:
//   icpc -O3 -qopenmp main.cpp citiesReader.cpp
// Execution:
//   ./a.out


#include "Util.hpp"
#include "Prim_std.hpp"
#include "Prim_memory_saver.hpp"



int main() {
    //-----------------------------------------------------------------
    //--- READING cities
    //-----------------------------------------------------------------

    int popMin;
    cout << "Minimal population? ";
    cin >> popMin;
    //Prim_std p(popMin);
    Prim_memory_saver p(popMin);
    p.prim_f(true);
    return 0;
}
