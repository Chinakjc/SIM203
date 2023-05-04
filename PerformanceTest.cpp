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

void PerformanceTest::change_size_test(int num_t, int pMin, int pMax, int step, prim_mode mode, int loop_num) {
    omp_set_num_threads(num_t);
    output += "popMin, running_time, Gflops, network_size\n";
    for(int popMin = pMin; popMin < pMax; popMin+= step){
        Prim * prim;
        switch (mode) {
            case naive:
                prim = new Prim_std(popMin);
                break;
            case mem_saver:
                prim = new Prim_memory_saver(popMin);
                break;
            case dep:
                prim = new Prim_dep(popMin);
                break;
        }
        int cities_num = prim->size();
        double res_t = 0;
        double  res_size = 0;
        for(int i = 0; i< loop_num; i++){
            auto res = prim->prim_f(false);
            res_t += res.first;
            res_size += res.second;
        }
        res_t /= (double)loop_num;
        res_size /= (double)loop_num;
        double gflops = (2.0 * cities_num - 2.0)/(100000.0 * res_t)*(cities_num - 1.0);
        output += to_string(popMin);
        output += ",";
        output += to_string(res_t);
        output += ",";
        output += to_string(gflops);
        output += ",";
        output += to_string(res_size);
        output += "\n";

    }
    write();
}

void PerformanceTest::change_threads_test(int popMin, int tMin, int tMax, int step, prim_mode mode, int loop_num) {
    output += "threads, running_time, Gflops, network_size\n";
    for(int number = tMin; number < tMax; number += step){
        Prim * prim;
        switch (mode) {
            case naive:
                prim = new Prim_std(popMin);
                break;
            case mem_saver:
                prim = new Prim_memory_saver(popMin);
                break;
            case dep:
                prim = new Prim_dep(popMin);
                break;
        }
        int cities_num = prim->size();
        omp_set_num_threads(number);
        double res_t = 0;
        double  res_size = 0;
        for(int i = 0; i< loop_num; i++){
            auto res = prim->prim_f(false);
            res_t += res.first;
            res_size += res.second;
        }
        res_t /= (double)loop_num;
        res_size /= (double)loop_num;
        double gflops = (2.0 * cities_num - 2.0)/(100000.0 * res_t)*(cities_num - 1.0);
        output += to_string(number);
        output += ",";
        output += to_string(res_t);
        output += ",";
        output += to_string(gflops);
        output += ",";
        output += to_string(res_size);
        output += "\n";

    }
    write();
}

void PerformanceTest::speedup_change_threads_test(int popMin, int tMin, int tMax, int step, prim_mode mode1,
                                                  prim_mode mode2, int loop_num) {
    output += "threads, speedup\n";
    for(int number = tMin; number < tMax; number += step){
        Prim * prim1;
        Prim * prim2;
        switch (mode1) {
            case naive:
                prim1 = new Prim_std(popMin);
                break;
            case mem_saver:
                prim1 = new Prim_memory_saver(popMin);
                break;
            case dep:
                prim1 = new Prim_dep(popMin);
                break;
        }
        switch (mode2) {
            case naive:
                prim2 = new Prim_std(popMin);
                break;
            case mem_saver:
                prim2 = new Prim_memory_saver(popMin);
                break;
            case dep:
                prim2 = new Prim_dep(popMin);
                break;
        }
        omp_set_num_threads(number);
        double res_t1 = 0;
        double res_t2 = 0;
        for(int i = 0; i< loop_num; i++){
            auto res1 = prim1->prim_f(false);
            res_t1 += res1.first;
            auto res2 = prim2->prim_f(false);
            res_t2 += res2.first;
        }
        res_t1 /= (double)loop_num;
        res_t2 /= (double)loop_num;
        output += to_string(number);
        output += ",";
        output += to_string(res_t1 / res_t2);
        output += "\n";

    }
    write();
}
