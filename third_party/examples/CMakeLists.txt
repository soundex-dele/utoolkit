# Third-party library usage examples

# fmt example
add_executable(fmt_example fmt_example.cpp)
if(TARGET fmt::fmt)
    target_link_libraries(fmt_example PRIVATE fmt::fmt)
    target_compile_definitions(fmt_example PRIVATE HAVE_FMT=1)
    target_include_directories(fmt_example PRIVATE ${FMT_INCLUDE_DIRS})
elseif(FMT_FOUND)
    target_link_libraries(fmt_example PRIVATE ${FMT_LIBRARIES})
    target_compile_definitions(fmt_example PRIVATE HAVE_FMT=1)
    target_include_directories(fmt_example PRIVATE ${FMT_INCLUDE_DIRS})
endif()

# spdlog example
add_executable(spdlog_example spdlog_example.cpp)
if(TARGET spdlog::spdlog)
    target_link_libraries(spdlog_example PRIVATE spdlog::spdlog)
    target_compile_definitions(spdlog_example PRIVATE HAVE_SPDLOG=1)
    target_include_directories(spdlog_example PRIVATE ${SPDLOG_INCLUDE_DIRS})
elseif(SPDLOG_FOUND)
    target_link_libraries(spdlog_example PRIVATE ${SPDLOG_LIBRARIES})
    target_compile_definitions(spdlog_example PRIVATE HAVE_SPDLOG=1)
    target_include_directories(spdlog_example PRIVATE ${SPDLOG_INCLUDE_DIRS})
endif()

# benchmark example
add_executable(benchmark_example benchmark_example.cpp)
if(TARGET benchmark::benchmark)
    target_link_libraries(benchmark_example PRIVATE benchmark::benchmark)
    target_compile_definitions(benchmark_example PRIVATE HAVE_BENCHMARK=1)
    target_include_directories(benchmark_example PRIVATE ${BENCHMARK_INCLUDE_DIRS})
elseif(BENCHMARK_FOUND)
    target_link_libraries(benchmark_example PRIVATE ${BENCHMARK_LIBRARIES})
    target_compile_definitions(benchmark_example PRIVATE HAVE_BENCHMARK=1)
    target_include_directories(benchmark_example PRIVATE ${BENCHMARK_INCLUDE_DIRS})
endif()

# POCO example
add_executable(poco_example poco_example.cpp)
if(TARGET utoolkit::poco)
    target_link_libraries(poco_example PRIVATE utoolkit::poco)
    target_compile_definitions(poco_example PRIVATE UTOOLKIT_ENABLE_POCO=1)
elseif(POCO_FOUND)
    target_link_libraries(poco_example PRIVATE ${POCO_LIBRARIES})
    target_compile_definitions(poco_example PRIVATE UTOOLKIT_ENABLE_POCO=1)
    target_include_directories(poco_example PRIVATE ${POCO_INCLUDE_DIRS})
endif()