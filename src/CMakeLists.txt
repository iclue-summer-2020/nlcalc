# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS
        "${NLCalc_SOURCE_DIR}/include/nlcalc/*.h"
        "${NLCalc_SOURCE_DIR}/include/nlcalc/*.hpp")

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
        "${NLCalc_SOURCE_DIR}/src/*.h"
        "${NLCalc_SOURCE_DIR}/src/*.hpp"
        "${NLCalc_SOURCE_DIR}/src/*.cc"
        "${NLCalc_SOURCE_DIR}/src/*.cpp")

file(GLOB MODULE_FILES CONFIGURE_DEPENDS
        "${NLCalc_SOURCE_DIR}/src/module.cc")

list(REMOVE_ITEM SOURCE_LIST ${MODULE_FILES})

add_library(nlcalc-lib ${SOURCE_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(nlcalc-lib PUBLIC "${NLCalc_SOURCE_DIR}/include/")

target_link_libraries(nlcalc-lib PUBLIC lrcalc PRIVATE python3.6m pybind11)

# All users of this library will need at least C++11
target_compile_features(nlcalc-lib PUBLIC cxx_std_11)

# Cross-platform compiler lints
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
        OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(nlcalc-lib PRIVATE
            -Wall
            -Wextra
            -Wswitch
            -Wconversion
            -Wparentheses
            -Wfloat-equal
            -Wzero-as-null-pointer-constant
            -Wpedantic
            -pedantic
            -pedantic-errors)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(nlcalc-lib PRIVATE /W3)
endif ()

# Enable fPIC.
set_property(TARGET nlcalc-lib PROPERTY POSITION_INDEPENDENT_CODE ON)



#############################
# Create the pybind module. #
#############################

# Make an automatic library - will be static or dynamic based on user setting
pybind11_add_module(nlcalc ${MODULE_FILES})

# We need this directory, and users of our library will need it too
# target_include_directories(nlcalc-module PUBLIC ../include)

target_link_libraries(nlcalc PRIVATE nlcalc-lib)

# All users of this library will need at least C++11
target_compile_features(nlcalc PUBLIC cxx_std_11)

# Cross-platform compiler lints
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"
        OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(nlcalc PRIVATE
            -Wall
            -Wextra
            -Wswitch
            -Wconversion
            -Wparentheses
            -Wfloat-equal
            -Wzero-as-null-pointer-constant
            -Wpedantic
            -pedantic
            -pedantic-errors)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(nlcalc PRIVATE /W3)
endif ()

set_property(TARGET nlcalc PROPERTY POSITION_INDEPENDENT_CODE ON)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
