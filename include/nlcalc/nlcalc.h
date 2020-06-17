// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef NLCALC_H_
#define NLCALC_H_

#include <cstdint>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <lrcalc/vector.h>

namespace py = pybind11;

namespace nlcalc {
// Converts a C++ vector into a C vector defined by lrcalc.
vector* to_vector(const std::vector<int>&);

// Computes the Littlewood-Richardson coefficient.
int64_t lrcoef(
    const std::vector<int>& outer,
    const std::vector<int>& inner1,
    const std::vector<int>& inner2);

}  // namespace nlcalc

#endif  // NLCALC_H_
