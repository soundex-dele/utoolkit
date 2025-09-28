#include <string>
#include <vector>
#include <iostream>

// 如果benchmark可用，包含头文件
#ifdef HAVE_BENCHMARK
#include <benchmark/benchmark.h>
#endif

#ifdef HAVE_BENCHMARK
// 字符串创建基准测试
static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state) {
        std::string empty_string;
        benchmark::DoNotOptimize(empty_string);
    }
}

// 字符串复制基准测试
static void BM_StringCopy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state) {
        std::string copy(x);
        benchmark::DoNotOptimize(copy);
    }
}

// vector push_back基准测试
static void BM_VectorPushBack(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        v.reserve(1);
        v.push_back(42);
        benchmark::DoNotOptimize(v);
    }
}

// 注册基准测试
BENCHMARK(BM_StringCreation);
BENCHMARK(BM_StringCopy);
BENCHMARK(BM_VectorPushBack);

BENCHMARK_MAIN();
#else
int main() {
    std::cout << "Google Benchmark library not available" << std::endl;
    return 0;
}
#endif