#include <cassert>
#include <iostream>
#include <vector>

#include "array.h"
#include "mathfunc.h"

using namespace nnv2;

void test_func_add(void) {
    Array a({ 3, 3, 3 }, -1.0);
    Array b({ 3, 3, 3 }, 1.0);
    Array res({ 3, 3, 3 }, 0.5);

    func_add(&res, &a, &b);
    assert(res.get_vec() == std::vector<float>(27, 0.0));

    std::cout << "test_func_add: Passed" << std::endl;
}

void test_func_sub(void) {
    Array a({ 3, 3, 3 }, 1.0);
    Array b({ 3, 3, 3 }, 1.0);
    Array res({ 3, 3, 3 }, 0.5);

    func_sub(&res, &a, &b);
    assert(res.get_vec() == std::vector<float>(27, 0.0));

    std::cout << "test_func_sub: Passed" << std::endl;
}

void test_func_mul(void) {
    Array a({ 3, 3, 3 }, -1.5);
    Array b({ 3, 3, 3 }, 2.0);
    Array res({ 3, 3, 3 }, 0.5);

    func_mul(&res, &a, &b);
    assert(res.get_vec() == std::vector<float>(27, -3.0));

    std::cout << "test_func_mul: Passed" << std::endl;
}

void test_func_div(void) {
    Array a({ 3, 3, 3 }, 1.0);
    Array b({ 3, 3, 3 }, 2.0);
    Array res({ 3, 3, 3 }, -1.0);

    func_div(&res, &a, &b);
    assert(res.get_vec() == std::vector<float>(27, 0.5));

    std::cout << "test_func_div: Passed" << std::endl;
}

void test_func_matmul(void) {
    Array a({ 2, 3 }, { 0, 1, 2, 3, 4, 5 });
    Array b({ 3, 3 }, { 0, 3, 6, 1, 4, 7, 2, 5, 8 });
    Array c({ 2, 3 });

    func_matmul(&c, &a, &b);
    assert(c.get_vec() == std::vector<float>({ 5, 14, 23, 14, 50, 86 }));

    // batch matrix
    Array u({ 2, 1, 2, 3 }, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });
    Array v({ 1, 2, 3, 2 }, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });
    Array t({ 2, 1, 2, 2 });

    func_matmul(&t, &u, &v);
    assert(t.get_vec() == std::vector<float>({ 10, 13, 28, 40, 172, 193, 244, 274 }));

    std::cout << "test_func_matmul: Passed" << std::endl;
}

void test_func_sum(void) {
    // A = [[[1, 2],
    //       [1, 3],
    //       [1, 4],
    //       [1, 1]],
    // 
    //      [[2, 2],
    //       [4, 2],
    //       [7, 6],
    //       [0, 1]]]
    Array a({ 2, 4, 2 },
            { 1, 2, 1, 3, 1, 4, 1, 1, 2, 2, 4, 2, 7, 6, 0, 1 });

    // sum of array over axis 0 should be equal to sum of all submatrices
    // A0 = [[3,  4],
    //       [5,  5],
    //       [8, 10],
    //       [1,  2]]
    Array res({ 4, 2 });
    func_sum(&res, &a, 0);
    assert(res.get_vec() == std::vector<float>({ 3, 4, 5, 5, 8, 10, 1, 2 }));

    // sum of array over axis 1 should be equal to sum of all columns
    res.resize({ 2, 2 });
    func_sum(&res, &a, 1);
    assert(res.get_vec() == std::vector<float>({ 4, 10, 13, 11 }));

    // sum of array over axis 2 should be equal to sum of all rows
    res.resize({ 2, 4 });
    func_sum(&res, &a, 2);
    assert(res.get_vec() == std::vector<float>({ 3, 4, 5, 2, 4, 6, 13, 1 }));

    std::cout << "test_func_sum: Passed" << std::endl;
}

void test_func_mean(void) {
    // A = [[[1, 2],
    //       [1, 3],
    //       [1, 4],
    //       [1, 1]],
    // 
    //      [[2, 2],
    //       [4, 2],
    //       [7, 6],
    //       [0, 1]]]
    Array a({ 2, 4, 2 },
            { 1, 2, 1, 3, 1, 4, 1, 1, 2, 2, 4, 2, 7, 6, 0, 1 });

    // mean of array over axis 0
    Array res({ 4, 2 });
    func_mean(&res, &a, 0);
    assert(res.get_vec() == std::vector<float>({ 1.5, 2, 2.5, 2.5, 4, 5, 0.5, 1 }));

    // mean of array over axis 1
    res.resize({ 2, 2 });
    func_mean(&res, &a, 1);
    assert(res.get_vec() == std::vector<float>({ 1, 2.5, 3.25, 2.75 }));

    // mean of array over axis 2
    res.resize({ 2, 4 });
    func_mean(&res, &a, 2);
    assert(res.get_vec() == std::vector<float>({ 1.5, 2, 2.5, 1, 2, 3, 6.5, 0.5 }));

    std::cout << "test_func_mean: Passed" << std::endl;
}

int main(void) {
    test_func_add();
    test_func_sub();
    test_func_mul();
    test_func_div();
    test_func_matmul();
    test_func_sum();
    test_func_mean();
}