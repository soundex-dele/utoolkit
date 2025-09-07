# Third-Party Dependencies

This directory contains third-party libraries used by μToolkit, managed via Git submodules.

## Libraries

### 1. fmt (Modern C++ formatting)
- **Source**: https://github.com/fmtlib/fmt
- **Purpose**: Fast and safe C++ formatting library
- **Version**: Latest master

### 2. spdlog (Fast C++ logging)
- **Source**: https://github.com/gabime/spdlog
- **Purpose**: Header-only, super fast C++ logging library
- **Version**: v1.x branch

### 3. GoogleTest (C++ testing framework)
- **Source**: https://github.com/google/googletest
- **Purpose**: Google's C++ testing and mocking framework
- **Version**: main branch

### 4. Google Benchmark (C++ benchmarking)
- **Source**: https://github.com/google/benchmark
- **Purpose**: Microbenchmark support for C++
- **Version**: main branch

## Initial Setup

### First Time Clone
If you're cloning the repository for the first time, run:

```bash
# Clone with submodules
git clone --recurse-submodules https://github.com/your-username/utoolkit.git

# Or if you already cloned without submodules
git submodule update --init --recursive
```

### Adding New Dependencies

1. Add submodule:
```bash
git submodule add https://github.com/user/repo.git third_party/repo_name
```

2. Add to `.gitmodules` if not automatically added

3. Add to `third_party/CMakeLists.txt` with appropriate build options

## Build Instructions

### Automatic Build
The CMake build system automatically handles third-party libraries:

```bash
mkdir build && cd build
cmake ..
make
```

### Manual Submodule Update

```bash
# Update all submodules to latest commits
git submodule update --remote --merge

# Update specific submodule
cd third_party/spdlog
git checkout v1.x
git pull origin v1.x
```

### Build Options

You can control third-party builds with CMake options:

```bash
# Disable specific libraries
cmake -DUTOOLKIT_BUILD_TESTS=OFF ..  # Skip GoogleTest build

# Custom build flags for third-party libs
cmake -DSPDLOG_BUILD_EXAMPLES=OFF -DSPDLOG_BUILD_TESTS=OFF ..
```

## Usage in μToolkit

### Linking with Libraries

In your CMakeLists.txt:

```cmake
# Link with fmt
target_link_libraries(your_target PRIVATE fmt::fmt)

# Link with spdlog
target_link_libraries(your_target PRIVATE spdlog::spdlog)

# Link with GoogleTest (for tests)
target_link_libraries(your_test PRIVATE GTest::gtest GTest::gtest_main)

# Link with benchmark
target_link_libraries(your_benchmark PRIVATE benchmark::benchmark)
```

### Example Usage

```cpp
// Using fmt
#include <fmt/core.h>
std::string message = fmt::format("Hello {}!", "World");

// Using spdlog
#include <spdlog/spdlog.h>
spdlog::info("This is a log message: {}", 42);

// Using GoogleTest
#include <gtest/gtest.h>
TEST(MyTest, BasicAssertions) {
    EXPECT_EQ(2 + 2, 4);
}

// Using benchmark
#include <benchmark/benchmark.h>
static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state)
        std::string empty_string;
}
BENCHMARK(BM_StringCreation);
```

## Troubleshooting

### Submodule Issues

If you encounter submodule-related build errors:

1. **Missing submodules**:
   ```bash
   git submodule update --init --recursive
   ```

2. **Outdated submodules**:
   ```bash
   git submodule update --remote --merge
   ```

3. **Clean rebuild**:
   ```bash
   rm -rf build
   mkdir build && cd build
   cmake ..
   make
   ```

### Build Errors

1. **fmt not found**: Ensure fmt submodule is initialized
2. **spdlog compilation errors**: Check that SPDLOG_BUILD_* options are properly set
3. **GoogleTest linking issues**: Verify GTest::gtest target exists

## Maintenance

### Updating Dependencies

To update all third-party libraries to their latest versions:

```bash
git submodule update --remote --merge
git add third_party/
git commit -m "Update third-party dependencies"
```

### Adding New Libraries

1. Add the submodule
2. Update `third_party/CMakeLists.txt`
3. Update this README.md
4. Test the build
5. Commit changes

## License

Each third-party library maintains its own license. Please refer to their respective LICENSE files in the submodule directories.