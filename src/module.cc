// Copyright 2020 ICLUE @ UIUC. All rights reserved.

#include <pybind11/pybind11.h>
#include <nlcalc/nlcalc.h>

namespace py = pybind11;

int add(int i, int j) {
  return i + j;
}

PYBIND11_MODULE(nlcalc, m) {
  m.doc() = R"pbdoc(
    Pybind11 example plugin
    -----------------------
    .. currentmodule:: cmake_example
    .. autosummary::
       :toctree: _generate
       add
       subtract
    )pbdoc";

  m.def("add", &add, R"pbdoc(
            Add two numbers
            Some other explanation about the add function.
        )pbdoc");

  m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
            Subtract two numbers
            Some other explanation about the subtract function.
        )pbdoc");

  m.def("lrcoef", &nlcalc::lrcoef, R"pbdoc(
    Compute a single Littlewood-Richardson coefficient.
    Return the coefficient of ``outer`` in the product of the Schur
    functions indexed by ``inner1`` and ``inner2``.
    INPUT:
    - ``outer`` -- a partition (weakly decreasing list of non-negative integers).
    - ``inner1`` -- a partition.
    - ``inner2`` -- a partition.
    .. note::
       This function converts its inputs into :func:`Partition`'s.  If
       you don't need these checks and your inputs are valid, then you
       can use :func:`lrcoef_unsafe`.
    EXAMPLES::
        python: from python.libs.lrcalc.lrcalc import lrcoef   #optional - lrcalc
        python: lrcoef([3,2,1], [2,1], [2,1])                #optional - lrcalc
        2
        python: lrcoef([3,3], [2,1], [2,1])                  #optional - lrcalc
        1
        python: lrcoef([2,1,1,1,1], [2,1], [2,1])            #optional - lrcalc
        0
  )pbdoc");

  #ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
  #else
  m.attr("__version__") = "dev";
  #endif
}
