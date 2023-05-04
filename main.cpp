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
    PerformanceTest performanceTest("test6");
    //performanceTest.speedup_change_threads_test(5000,1,30,1,mem_saver,dep);
    performanceTest.change_threads_test(500,1,30,1,dep);
    //performanceTest.change_size_test(24,2000,100000,2000,dep,3);
    return 0;
}
