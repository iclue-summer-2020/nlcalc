// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

extern "C" {
#include <lrcalc/vector.h>
}
#include <nlcalc/nlcalc.h>

namespace py = pybind11;

TEST_CASE("Create a vector from an iterable", "[iterable_to_vector]") {
  const std::vector<int> vec = {1, 2, 3, 4};
  vector* v = nlcalc::to_vector(vec);

  REQUIRE(v->length == 4);
  for (size_t i = 0; i < v->length; i++) {
    REQUIRE(v->array[i] == vec[i]);
  }

  v_free(v);
}
