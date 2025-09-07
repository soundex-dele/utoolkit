# μToolkit 智能构建系统

μToolkit 提供了一个强大的Python构建系统，支持跨平台构建和模块化配置。

## 🚀 快速开始

### 1. 使用默认配置构建
```bash
# 使用默认发布配置
python build.py

# 或者使用构建帮助器
python build_helper.py --create-configs
python build.py
```

### 2. 使用预定义配置
```bash
# 开发调试配置
python build.py --config build_config.dev.json

# 最小化配置（仅核心功能）
python build.py --config build_config.minimal.json

# 完整配置（所有功能）
python build.py --config build_config.full.json
```

### 3. 交互式配置
```bash
# 启动交互式配置向导
python build_helper.py --interactive

# 使用生成的配置
python build.py --config build_config_custom.json
```

## 📋 配置文件结构

### build_config.json
```json
{
  "platform": "auto",           // 平台: auto/windows/macos/linux
  "build_type": "Release",      // 构建类型: Debug/Release/RelWithDebInfo/MinSizeRel
  "modules": {
    "logging": {
      "enabled": true,           // 启用模块
      "tests": true,             // 包含测试
      "examples": true           // 包含示例
    }
  },
  "third_party": {
    "fmt": {
      "enabled": true,           // 启用第三方库
      "examples": true           // 包含示例
    }
  },
  "cmake_options": {
    "CMAKE_INSTALL_PREFIX": "/usr/local",
    "BUILD_SHARED_LIBS": false
  }
}
```

## 🔧 构建命令

### 基本命令
```bash
# 清理并重新构建
python build.py --clean

# 安装到系统
python build.py --install

# 显示当前配置
python build.py --show-config

# 初始化子模块
python build.py --init-submodules
```

### 高级用法
```bash
# 使用特定配置文件
python build.py --config my_config.json

# 组合使用
python build.py --config debug.json --clean --install
```

## 🌍 跨平台支持

### Windows
```bash
# 使用Visual Studio
python build.py
# 生成 Visual Studio 17 2022 解决方案
```

### macOS
```bash
# 使用Xcode工具链
python build.py
# 生成 Unix Makefiles
```

### Linux
```bash
# 使用GCC/Clang
python build.py
# 生成 Unix Makefiles
```

## 📦 预定义配置

| 配置文件 | 描述 | 用途 |
|----------|------|------|
| `build_config.json` | 默认发布配置 | 生产环境 |
| `build_config.dev.json` | 开发调试配置 | 开发调试 |
| `build_config.minimal.json` | 最小化配置 | 嵌入式系统 |
| `build_config.full.json` | 完整配置 | 测试所有功能 |

## 🎯 模块说明

### 核心模块
- **logging**: 日志系统
- **threadpool**: 线程池
- **utils**: 工具函数（字符串、文件、时间）

### 第三方库
- **fmt**: 现代C++格式化库
- **spdlog**: 快速C++日志库
- **googletest**: Google C++测试框架
- **benchmark**: Google基准测试库

## 🔍 故障排除

### 子模块问题
```bash
# 手动初始化子模块
git submodule update --init --recursive

# 或者使用脚本
python build.py --init-submodules
```

### 构建失败
```bash
# 清理构建目录
python build.py --clean

# 检查配置
python build.py --show-config
```

### 依赖问题
```bash
# 检查系统依赖
python build_helper.py --create-configs
python build_helper.py --usage
```

## 📝 示例工作流

### 1. 首次构建
```bash
# 克隆项目
git clone --recurse-submodules https://github.com/your-username/utoolkit.git
cd utoolkit

# 创建配置
python build_helper.py --create-configs

# 构建项目
python build.py
```

### 2. 开发工作流
```bash
# 交互式配置
python build_helper.py --interactive

# 使用开发配置
python build.py --config build_config_custom.json --clean

# 运行测试
python build.py --config build_config.dev.json
```

### 3. 发布构建
```bash
# 使用发布配置
python build.py --config build_config.json --clean --install
```

## 🎨 自定义配置

### 创建自定义配置
```bash
# 方法1: 复制并修改
cp build_config.json my_config.json
# 编辑 my_config.json

# 方法2: 交互式创建
python build_helper.py --interactive
```

### 环境特定配置
```json
{
  "platform": "windows",
  "build_type": "Release",
  "cmake_options": {
    "CMAKE_TOOLCHAIN_FILE": "vcpkg.cmake",
    "VCPKG_TARGET_TRIPLET": "x64-windows"
  }
}
```

## 📞 支持

如果遇到问题，请检查：
1. Python 3.6+ 已安装
2. CMake 3.15+ 已安装
3. 编译器工具链已配置
4. 子模块已正确初始化

查看详细帮助：
```bash
python build_helper.py --usage
```