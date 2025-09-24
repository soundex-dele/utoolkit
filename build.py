#!/usr/bin/env python3
"""
μToolkit 智能构建脚本
支持跨平台构建，模块化编译控制
"""

import os
import sys
import json
import subprocess
import platform
import argparse
from pathlib import Path
from typing import Dict, List, Any

class UToolkitBuilder:
    def __init__(self, config_file: str = "build_config.json"):
        self.root_dir = Path(__file__).parent
        self.config_file = self.root_dir / config_file
        self.build_dir = self.root_dir / "build"
        self.config = self.load_config()
        
    def load_config(self) -> Dict[str, Any]:
        """加载构建配置"""
        try:
            with open(self.config_file, 'r', encoding='utf-8') as f:
                return json.load(f)
        except FileNotFoundError:
            print(f"配置文件 {self.config_file} 不存在，使用默认配置")
            return self.get_default_config()
        except json.JSONDecodeError as e:
            print(f"配置文件格式错误: {e}")
            sys.exit(1)
    
    def get_default_config(self) -> Dict[str, Any]:
        """获取默认配置"""
        return {
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
    
    def detect_platform(self) -> str:
        """检测当前平台"""
        system = platform.system().lower()
        machine = platform.machine().lower()
        
        if system == "windows":
            return "windows"
        elif system == "darwin":
            return "macos"
        elif system == "linux":
            return "linux"
        else:
            return system
    
    def get_cmake_generator(self) -> str:
        """获取适合的CMake生成器"""
        system = platform.system()
        if system == "Windows":
            return "Visual Studio 17 2022"
        elif system == "Darwin":
            return "Unix Makefiles"
        else:
            return "Unix Makefiles"
    
    def generate_cmake_command(self) -> List[str]:
        """生成CMake配置命令"""
        cmd = ["cmake", ".."]
        
        # 平台检测
        platform = self.config.get("platform", "auto")
        if platform == "auto":
            platform = self.detect_platform()
        
        # 构建类型
        build_type = self.config.get("build_type", "Release")
        cmd.extend([f"-DCMAKE_BUILD_TYPE={build_type}"])
        
        # CMake选项
        cmake_options = self.config.get("cmake_options", {})
        for key, value in cmake_options.items():
            if isinstance(value, bool):
                value = "ON" if value else "OFF"
            cmd.extend([f"-D{key}={value}"])
        
        # 模块配置
        modules = self.config.get("modules", {})
        third_party = self.config.get("third_party", {})
        
        # 根据配置设置CMake变量
        enabled_modules = [name for name, config in modules.items() 
                          if config.get("enabled", True)]
        
        # 第三方库配置
        for lib, config in third_party.items():
            enabled = config.get("enabled", True)
            cmd.extend([f"-DUTOOLKIT_ENABLE_{lib.upper()}={'ON' if enabled else 'OFF'}"])
        
        return cmd
    
    def setup_build_environment(self):
        """设置构建环境"""
        if not self.build_dir.exists():
            self.build_dir.mkdir()
        
        # 检查子模块
        self.check_submodules()
    
    def check_submodules(self):
        """检查并初始化子模块"""
        third_party_dir = self.root_dir / "third_party"
        
        # 检查git子模块状态
        try:
            result = subprocess.run(
                ["git", "submodule", "status"], 
                cwd=self.root_dir,
                capture_output=True, 
                text=True
            )
            
            if result.returncode == 0:
                lines = result.stdout.strip().split('\n')
                missing_submodules = []
                
                for line in lines:
                    if line.startswith('-'):
                        # 子模块未初始化
                        missing_submodules.append(line.split()[1])
                
                if missing_submodules:
                    print("检测到未初始化的子模块:")
                    for submodule in missing_submodules:
                        print(f"  - {submodule}")
                    
                    init_choice = input("是否初始化子模块? (y/N): ").lower()
                    if init_choice == 'y':
                        self.init_submodules()
                        
        except subprocess.CalledProcessError:
            print("警告: 无法检查git子模块状态")
    
    def init_submodules(self):
        """初始化子模块"""
        print("正在初始化子模块...")
        try:
            subprocess.run(["git", "submodule", "update", "--init", "--recursive"], 
                         cwd=self.root_dir, check=True)
            print("子模块初始化完成")
        except subprocess.CalledProcessError as e:
            print(f"子模块初始化失败: {e}")
            sys.exit(1)
    
    def build(self, clean: bool = False):
        """执行构建"""
        if clean and self.build_dir.exists():
            import shutil
            shutil.rmtree(self.build_dir)
            print("清理构建目录")
        
        self.setup_build_environment()
        
        # CMake配置
        cmake_cmd = self.generate_cmake_command()
        print("正在配置项目...")
        print("CMake命令:", " ".join(cmake_cmd))
        
        try:
            result = subprocess.run(cmake_cmd, cwd=self.build_dir, check=True)
            print("CMake配置完成")
            
            # 构建
            build_cmd = ["cmake", "--build", ".", "--config", 
                        self.config.get("build_type", "Release")]
            
            # 检测CPU核心数
            try:
                cpu_count = os.cpu_count() or 4
                build_cmd.extend(["--parallel", str(cpu_count)])
            except:
                pass
            
            print("正在构建项目...")
            result = subprocess.run(build_cmd, cwd=self.build_dir, check=True)
            print("构建完成")
            
            # 运行测试
            self.run_tests()
            
        except subprocess.CalledProcessError as e:
            print(f"构建失败: {e}")
            sys.exit(1)
    
    def run_tests(self):
        """运行测试"""
        if not self.config.get("cmake_options", {}).get("UTOOLKIT_BUILD_TESTS", True):
            return
        
        print("运行测试...")
        try:
            # 运行CTest
            subprocess.run(["ctest", "--output-on-failure", "-j", str(os.cpu_count() or 4)], 
                         cwd=self.build_dir, check=True)
            print("所有测试通过")
        except subprocess.CalledProcessError as e:
            print(f"测试失败: {e}")
            # 允许测试失败但不中断流程
            pass
    
    def install(self):
        """安装项目"""
        print("正在安装...")
        try:
            install_cmd = ["cmake", "--install", "."]
            subprocess.run(install_cmd, cwd=self.build_dir, check=True)
            print("安装完成")
        except subprocess.CalledProcessError as e:
            print(f"安装失败: {e}")
            sys.exit(1)
    
    def show_config(self):
        """显示当前配置"""
        print("当前构建配置:")
        print(f"  平台: {self.config.get('platform', 'auto')} (自动检测: {self.detect_platform()})")
        print(f"  构建类型: {self.config.get('build_type', 'Release')}")
        print()
        
        print("模块配置:")
        modules = self.config.get("modules", {})
        for name, config in modules.items():
            enabled = config.get("enabled", True)
            tests = config.get("tests", True)
            examples = config.get("examples", True)
            print(f"  {name}: {'✓' if enabled else '✗'} "
                  f"(测试: {'✓' if tests else '✗'}, 示例: {'✓' if examples else '✗'})")
        
        print()
        print("第三方库配置:")
        third_party = self.config.get("third_party", {})
        for name, config in third_party.items():
            enabled = config.get("enabled", True)
            print(f"  {name}: {'✓' if enabled else '✗'}")
    
    def save_config(self):
        """保存配置到文件"""
        with open(self.config_file, 'w', encoding='utf-8') as f:
            json.dump(self.config, f, indent=2, ensure_ascii=False)
        print(f"配置已保存到 {self.config_file}")

def main():
    parser = argparse.ArgumentParser(description="μToolkit 构建工具")
    parser.add_argument("--config", default="build_config.json", 
                       help="配置文件路径")
    parser.add_argument("--clean", action="store_true", 
                       help="清理并重新构建")
    parser.add_argument("--install", action="store_true", 
                       help="安装项目")
    parser.add_argument("--show-config", action="store_true", 
                       help="显示当前配置")
    parser.add_argument("--init-submodules", action="store_true", 
                       help="初始化子模块")
    
    args = parser.parse_args()
    
    builder = UToolkitBuilder(args.config)
    
    if args.show_config:
        builder.show_config()
        return
    
    if args.init_submodules:
        builder.init_submodules()
        return
    
    if args.install:
        builder.install()
    else:
        builder.build(clean=args.clean)

if __name__ == "__main__":
    main()