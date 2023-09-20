# 说明

本工具主要用于[Q/GDW 12184](doc/QGDW 12184—2021 输变电设备物联网传感器数据规范-数据规约一致性-4.pdf)标准开发过程中的辅助工作。主要目的为符合本人习惯。

## 源代码下载

由于本源代码包含第三方源代码,故直接下载可能有部分源代码缺失，需要通过以下方法解决:

- 在进行git clone 使用--recurse-submodules参数。

- 若已通过git clone下载,则在源代码目录中执行以下命令下载子模块:

  ```bash
   git submodule update --init --recursive
  ```


# 依赖库

- [wxWidgets](https://github.com/wxWidgets/wxWidgets):C++ GUI库。

