// Compilation:
//   icpc -O3 -qopenmp main.cpp citiesReader.cpp
// Execution:
//   ./a.out


#include "Util.hpp"
#include "Prim_std.hpp"
#include "Prim_memory_saver.hpp"
#include "Prim_dep.hpp"
#include "PerformanceTest.hpp"


int main() {
    //-----------------------------------------------------------------
    //--- READING cities
    //-----------------------------------------------------------------

    /*int popMin;
    cout << "Minimal population? ";
    cin >> popMin;
    Prim_std p1(popMin);
    //Prim_memory_saver p(popMin);
    Prim_dep p(popMin);
    p.prim_f(false);
    p1.prim_f(false);*/
    PerformanceTest performanceTest("test5");
    performanceTest.speedup_change_threads_test(5000,1,17,1,mem_saver,dep);
    //performanceTest.change_threads_test(5000,1,16,1,2);
    return 0;
}
