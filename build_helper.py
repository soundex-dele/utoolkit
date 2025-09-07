#!/usr/bin/env python3
"""
μToolkit 构建辅助工具
提供交互式配置和快速构建命令
"""

import json
import os
import sys
from pathlib import Path

def create_default_configs():
    """创建默认配置文件"""
    configs = {
        "build_config.json": {
            "platform": "auto",
            "build_type": "Release",
            "modules": {
                "logging": {"enabled": True, "tests": False, "examples": True},
                "threadpool": {"enabled": True, "tests": False, "examples": True},
                "utils": {"enabled": True, "tests": False, "examples": True}
            },
            "third_party": {
                "fmt": {"enabled": True, "examples": True},
                "spdlog": {"enabled": True, "examples": True},
                "googletest": {"enabled": False, "tests": False},
                "benchmark": {"enabled": True, "examples": True}
            },
            "cmake_options": {
                "CMAKE_INSTALL_PREFIX": "/usr/local",
                "UTOOLKIT_BUILD_TESTS": False,
                "UTOOLKIT_BUILD_EXAMPLES": True,
                "BUILD_SHARED_LIBS": False
            }
        },
        "build_config.minimal.json": {
            "platform": "auto",
            "build_type": "Release",
            "modules": {
                "logging": {"enabled": True, "tests": False, "examples": False},
                "threadpool": {"enabled": False, "tests": False, "examples": False},
                "utils": {"enabled": True, "tests": False, "examples": False}
            },
            "third_party": {
                "fmt": {"enabled": False, "examples": False},
                "spdlog": {"enabled": False, "examples": False},
                "googletest": {"enabled": False, "tests": False},
                "benchmark": {"enabled": False, "examples": False}
            },
            "cmake_options": {
                "CMAKE_INSTALL_PREFIX": "/usr/local",
                "UTOOLKIT_BUILD_TESTS": False,
                "UTOOLKIT_BUILD_EXAMPLES": False,
                "BUILD_SHARED_LIBS": False
            }
        },
        "build_config.full.json": {
            "platform": "auto",
            "build_type": "Release",
            "modules": {
                "logging": {"enabled": True, "tests": True, "examples": True},
                "threadpool": {"enabled": True, "tests": True, "examples": True},
                "utils": {"enabled": True, "tests": True, "examples": True}
            },
            "third_party": {
                "fmt": {"enabled": True, "examples": True},
                "spdlog": {"enabled": True, "examples": True},
                "googletest": {"enabled": True, "tests": True},
                "benchmark": {"enabled": True, "examples": True}
            },
            "cmake_options": {
                "CMAKE_INSTALL_PREFIX": "/usr/local",
                "UTOOLKIT_BUILD_TESTS": True,
                "UTOOLKIT_BUILD_EXAMPLES": True,
                "BUILD_SHARED_LIBS": False
            }
        }
    }
    
    for filename, config in configs.items():
        filepath = Path(filename)
        if not filepath.exists():
            with open(filepath, 'w', encoding='utf-8') as f:
                json.dump(config, f, indent=2, ensure_ascii=False)
            print(f"已创建 {filename}")

def interactive_config():
    """交互式配置"""
    print("μToolkit 交互式配置工具")
    print("=" * 30)
    
    config = {
        "platform": "auto",
        "build_type": "Release",
        "modules": {},
        "third_party": {},
        "cmake_options": {}
    }
    
    # 构建类型
    build_type = input("构建类型 [Release/Debug/RelWithDebInfo/MinSizeRel] (默认: Release): ").strip()
    if build_type in ["Release", "Debug", "RelWithDebInfo", "MinSizeRel"]:
        config["build_type"] = build_type
    
    # 模块配置
    modules = ["logging", "threadpool", "utils"]
    for module in modules:
        enabled = input(f"启用 {module} 模块? [y/n] (默认: y): ").strip().lower()
        config["modules"][module] = {
            "enabled": enabled != 'n',
            "tests": False,
            "examples": False
        }
        
        if enabled != 'n':
            tests = input(f"  包含 {module} 测试? [y/n] (默认: n): ").strip().lower()
            examples = input(f"  包含 {module} 示例? [y/n] (默认: y): ").strip().lower()
            config["modules"][module]["tests"] = tests == 'y'
            config["modules"][module]["examples"] = examples != 'n'
    
    # 第三方库配置
    third_party_libs = ["fmt", "spdlog", "googletest", "benchmark"]
    for lib in third_party_libs:
        enabled = input(f"启用 {lib}? [y/n] (默认: y): ").strip().lower()
        config["third_party"][lib] = {
            "enabled": enabled != 'n',
            "examples": False,
            "tests": False
        }
        
        if enabled != 'n' and lib in ["fmt", "spdlog", "benchmark"]:
            examples = input(f"  包含 {lib} 示例? [y/n] (默认: y): ").strip().lower()
            config["third_party"][lib]["examples"] = examples != 'n'
        
        if enabled != 'n' and lib == "googletest":
            tests = input(f"  包含 googletest 测试? [y/n] (默认: y): ").strip().lower()
            config["third_party"][lib]["tests"] = tests != 'n'
    
    # 保存配置
    filename = input("保存为配置文件名 (默认: build_config_custom.json): ").strip()
    if not filename:
        filename = "build_config_custom.json"
    if not filename.endswith('.json'):
        filename += '.json'
    
    with open(filename, 'w', encoding='utf-8') as f:
        json.dump(config, f, indent=2, ensure_ascii=False)
    
    print(f"配置已保存到 {filename}")
    return filename

def show_usage():
    """显示使用帮助"""
    print("μToolkit 构建系统使用帮助")
    print("=" * 30)
    print()
    print("快速开始:")
    print("  python build.py                    # 使用默认配置构建")
    print("  python build.py --config dev.json  # 使用自定义配置")
    print("  python build.py --clean            # 清理并重新构建")
    print("  python build.py --install          # 安装到系统")
    print()
    print("配置文件:")
    print("  build_config.json         # 默认发布配置")
    print("  build_config.dev.json     # 开发调试配置")
    print("  build_config.minimal.json # 最小化配置")
    print("  build_config.full.json    # 完整配置")
    print()
    print("交互式配置:")
    print("  python build_helper.py --interactive")
    print()
    print("创建默认配置:")
    print("  python build_helper.py --create-configs")

def main():
    import argparse
    
    parser = argparse.ArgumentParser(description="μToolkit 构建辅助工具")
    parser.add_argument("--create-configs", action="store_true", 
                       help="创建默认配置文件")
    parser.add_argument("--interactive", action="store_true", 
                       help="交互式配置")
    parser.add_argument("--usage", action="store_true", 
                       help="显示使用帮助")
    
    args = parser.parse_args()
    
    if args.create_configs:
        create_default_configs()
    elif args.interactive:
        interactive_config()
    elif args.usage:
        show_usage()
    else:
        show_usage()

if __name__ == "__main__":
    main()