//
// Created by kjc on 2023/5/3.
//

#ifndef SIM203_PERFORMANCETEST_HPP
#define SIM203_PERFORMANCETEST_HPP


#include <string>
#include "Util.hpp"
#include "Prim.hpp"
#include "Prim_std.hpp"
#include "Prim_memory_saver.hpp"
#include "Prim_dep.hpp"

class PerformanceTest {
private:
    string output;
    string output_name;
    bool write();
public:
    explicit PerformanceTest(string op_name);
    void change_size_test(int num_t, int pMin, int pMax, int step, int mode);// mode 0 std, mode 1 ms, mode 2 dep
    void change_threads_test(int popMin, int tMin, int tMax, int step, int mode);
    void speedup_change_threads_test(int popMin, int tMin, int tMax, int step, prim_mode mode1 = naive, prim_mode mode2 = dep);

};


#endif //SIM203_PERFORMANCETEST_HPP
