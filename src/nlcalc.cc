// Copyright 2020 [Your Name]. All rights reserved.

#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

extern "C" {
#include <lrcalc/vector.h>
}

#include <nlcalc/nlcalc.h>

namespace py = pybind11;

namespace nlcalc {

vector* to_vector(const std::vector<int>& vec) {
  vector* v = v_new(static_cast<int>(vec.size()));
  for (size_t i = 0; i < vec.size(); ++i) {
    v->array[i] = vec[i];
  }
  return v;
}

}  // namespace nlcalc

