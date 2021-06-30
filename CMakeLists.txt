cmake_minimum_required(VERSION 2.8)
project(cptp CXX)
set(CMAKE_CXX_FLAGS "-O2 -std=c++20 -Wall")
add_library(cptp SHARED ./include/cptp/forward.cpp ./include/cptp/vec2.cpp ./include/cptp/rgb.cpp ./include/cptp/color.cpp ./include/cptp/figure.cpp ./include/cptp/label.cpp ./include/cptp/scale.cpp ./include/cptp/title.cpp ./include/cptp/line.cpp ./include/cptp/data.cpp ./include/cptp/point.cpp ./include/cptp/range.cpp ./include/cptp/key.cpp ./include/cptp/plot_spec.cpp ./include/cptp/position.cpp ./include/cptp/table_parallel_plots.cpp)
