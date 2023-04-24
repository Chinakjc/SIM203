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

    /*int popMin;
    cout << "Minimal population? ";
    cin >> popMin;
    //Prim_std p(popMin);
    Prim_memory_saver p(popMin);
    p.prim_f(true);*/
    map<int,string> map1;
    map1[2]="1";
    cout<<map1[2]<<endl;
    cout << map1[5] << endl;
    return 0;
}
