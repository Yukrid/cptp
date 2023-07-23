cmake_minimum_required(VERSION 2.8)
project(CPTP CXX)

add_library(cptp SHARED ./src/cptp/forward.cpp ./src/cptp/vec2.cpp ./src/cptp/rgb.cpp ./src/cptp/color.cpp ./src/cptp/figure.cpp ./src/cptp/label.cpp ./src/cptp/scale.cpp ./src/cptp/title.cpp ./src/cptp/line.cpp ./src/cptp/data.cpp ./src/cptp/point.cpp ./src/cptp/range.cpp ./src/cptp/key.cpp ./src/cptp/plot_spec.cpp ./src/cptp/position.cpp ./src/cptp/table_parallel_plots.cpp ./src/cptp/single_plots.cpp)
target_include_directories(cptp PUBLIC ./include)
target_compile_features(cptp PUBLIC cxx_std_11)

add_library(cptp_a STATIC ./src/cptp/forward.cpp ./src/cptp/vec2.cpp ./src/cptp/rgb.cpp ./src/cptp/color.cpp ./src/cptp/figure.cpp ./src/cptp/label.cpp ./src/cptp/scale.cpp ./src/cptp/title.cpp ./src/cptp/line.cpp ./src/cptp/data.cpp ./src/cptp/point.cpp ./src/cptp/range.cpp ./src/cptp/key.cpp ./src/cptp/plot_spec.cpp ./src/cptp/position.cpp ./src/cptp/table_parallel_plots.cpp ./src/cptp/single_plots.cpp)
target_include_directories(cptp_a PUBLIC ./include)
target_compile_features(cptp_a PUBLIC cxx_std_11)

install(TARGETS cptp cptp_a LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

add_executable(example1 ./src/example1/example1.cpp)
target_include_directories(example1 PUBLIC ./include)
target_compile_features(example1 PUBLIC cxx_std_11)
target_link_libraries(example1 cptp)

add_executable(example2 ./src/example2/example2.cpp)
target_include_directories(example2 PUBLIC ./include)
target_compile_features(example2 PUBLIC cxx_std_11)
target_link_libraries(example2 cptp)

add_executable(example3 ./src/example3/example3.cpp)
target_include_directories(example3 PUBLIC ./include)
target_compile_features(example3 PUBLIC cxx_std_11)
target_link_libraries(example3 cptp)
