#!/bin/bash

# μToolkit Third-Party Dependencies Initialization Script

set -e

echo "🚀 Initializing μToolkit third-party dependencies..."

# Check if .gitmodules exists
if [ ! -f ".gitmodules" ]; then
    echo "❌ .gitmodules not found. Please ensure you're in the project root."
    exit 1
fi

# Initialize and update submodules
echo "📦 Initializing submodules..."
git submodule update --init --recursive

# Verify all submodules are present
submodules=("fmt" "spdlog" "googletest" "benchmark")
missing=()

for submodule in "${submodules[@]}"; do
    if [ ! -d "third_party/$submodule" ]; then
        missing+=("$submodule")
    fi
done

if [ ${#missing[@]} -ne 0 ]; then
    echo "❌ Missing submodules: ${missing[*]}"
    echo "Please run: git submodule update --init --recursive"
    exit 1
fi

echo "✅ All third-party dependencies initialized successfully!"
echo ""
echo "📋 Available libraries:"
echo "  • fmt: Modern C++ formatting"
echo "  • spdlog: Fast C++ logging"
echo "  • googletest: C++ testing framework"
echo "  • benchmark: C++ microbenchmarking"
echo ""
echo "🔧 Build instructions:"
echo "  mkdir build && cd build"
echo "  cmake .."
echo "  make"