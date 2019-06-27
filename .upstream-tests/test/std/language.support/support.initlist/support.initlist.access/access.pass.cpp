//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++98, c++03

// template<class E> class initializer_list;

// const E* begin() const;
// const E* end() const;
// size_t size() const;

#include <cuda/std/initializer_list>
#include <cuda/std/cassert>
#include <cuda/std/cstddef>

#include "test_macros.h"

struct A
{
    __host__ __device__
    A(cuda::std::initializer_list<int> il)
    {
        const int* b = il.begin();
        const int* e = il.end();
        assert(il.size() == 3);
        assert(static_cast<cuda::std::size_t>(e - b) == il.size());
        assert(*b++ == 3);
        assert(*b++ == 2);
        assert(*b++ == 1);
    }
};

#if TEST_STD_VER > 11
#ifndef __CUDACC_RTC__
struct B
{
    __host__ __device__
    constexpr B(cuda::std::initializer_list<int> il)
    {
        const int* b = il.begin();
        const int* e = il.end();
        assert(il.size() == 3);
        assert(static_cast<cuda::std::size_t>(e - b) == il.size());
        assert(*b++ == 3);
        assert(*b++ == 2);
        assert(*b++ == 1);
    }
};
#endif
#endif  // TEST_STD_VER > 11

int main(int, char**)
{
    A test1 = {3, 2, 1};
#if TEST_STD_VER > 11
#ifndef __CUDACC_RTC__
    constexpr B test2 = {3, 2, 1};
    (void)test2;
#endif
#endif  // TEST_STD_VER > 11

  return 0;
}
