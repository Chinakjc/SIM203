//
// Created by kjc on 2023/5/3.
//

#include "PerformanceTest.hpp"

PerformanceTest::PerformanceTest(string op_name):output_name(op_name), output("") {

}

bool PerformanceTest::write() {
    ofstream outputFile(output_name+".csv");
    if (outputFile.is_open()){
        outputFile << output << endl;
        outputFile.close();
        return true;
    }
    return false;
}

void PerformanceTest::change_size_test(int num_t, int pMin, int pMax, int step, int mode) {
    omp_set_num_threads(num_t);
    output += "popMin, running_time, network_size\n";
    for(int popMin = pMin; popMin < pMax; popMin+= step){
        Prim * prim;
        switch (mode) {
            case 0:
                prim = new Prim_std(popMin);
                break;
            case 1:
                prim = new Prim_memory_saver(popMin);
                break;
            case 2:
                prim = new Prim_dep(popMin);
                break;
        }
        auto res = prim->prim_f(false);
        double res_t = res.first;
        double  res_size = res.second;
        output += to_string(popMin);
        output += ",";
        output += to_string(res_t);
        output += ",";
        output += to_string(res_size);
        output += "\n";

    }
    write();
}

void PerformanceTest::change_threads_test(int popMin, int tMin, int tMax, int step, int mode) {
    output += "threads, running_time, network_size\n";
    for(int number = tMin; number < tMax; number += step){
        Prim * prim;
        switch (mode) {
            case 0:
                prim = new Prim_std(popMin);
                break;
            case 1:
                prim = new Prim_memory_saver(popMin);
                break;
            case 2:
                prim = new Prim_dep(popMin);
                break;
        }
        omp_set_num_threads(number);
        auto res = prim->prim_f(false);
        double res_t = res.first;
        double  res_size = res.second;
        output += to_string(number);
        output += ",";
        output += to_string(res_t);
        output += ",";
        output += to_string(res_size);
        output += "\n";

    }
    write();
}

void PerformanceTest::speedup_change_threads_test(int popMin, int tMin, int tMax, int step, prim_mode mode1,
                                                  prim_mode mode2) {
    output += "threads, speedup\n";
    for(int number = tMin; number < tMax; number += step){
        Prim * prim1;
        Prim * prim2;
        switch (mode1) {
            case 0:
                prim1 = new Prim_std(popMin);
                break;
            case 1:
                prim1 = new Prim_memory_saver(popMin);
                break;
            case 2:
                prim1 = new Prim_dep(popMin);
                break;
        }
        switch (mode2) {
            case 0:
                prim2 = new Prim_std(popMin);
                break;
            case 1:
                prim2 = new Prim_memory_saver(popMin);
                break;
            case 2:
                prim2 = new Prim_dep(popMin);
                break;
        }
        omp_set_num_threads(number);
        auto res1 = prim1->prim_f(false);
        double res_t1 = res1.first;
        auto res2 = prim2->prim_f(false);
        double res_t2 = res2.first;
        output += to_string(number);
        output += ",";
        output += to_string(res_t1 / res_t2);
        output += "\n";

    }
    write();
}
