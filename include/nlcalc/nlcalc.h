// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef NLCALC_H_
#define NLCALC_H_

#include <vector>

#include <pybind11/pybind11.h>
#include <lrcalc/vector.h>

namespace py = pybind11;

namespace nlcalc {
vector* to_vector(const std::vector<int>&);
}  // namespace nlcalc

#endif  // NLCALC_H_
