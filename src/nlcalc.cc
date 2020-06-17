// Copyright 2020 ICLUE @ UIUC. All rights reserved.

#include <cstdint>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

extern "C" {
#include <lrcalc/vector.h>
#include <lrcalc/symfcn.h>
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

int64_t lrcoef(
    const std::vector<int>& outer,
    const std::vector<int>& inner1,
    const std::vector<int>& inner2) {
  vector* o = to_vector(outer);
  vector* i1 = to_vector(inner1);
  vector* i2 = to_vector(inner2);

  int64_t result = lrcoef(o, i1, i2);

  v_free(o);
  v_free(i1);
  v_free(i2);

  return result;
}

}  // namespace nlcalc

