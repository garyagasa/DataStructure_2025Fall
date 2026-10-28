from setuptools import setup, Extension
import pybind11
import os

ext_modules = [
    Extension(
        "metro_core",
        [
            "src/bindings/pybind_module.cpp",
            "src/graph/utils.cpp",
            "src/path/floyd_warshall.cpp",
            "src/path/dijkstra.cpp",
            "src/path/astar.cpp",
            "src/mst/prim.cpp",
            "src/mst/kruskal.cpp"
        ],
        include_dirs=[
            "src/core",
            pybind11.get_include(),
        ],
        language="c++",
        extra_compile_args=["-std=c++17", "-O2", "-Wall"],
    ),
]

setup(
    name="chengdu_metro_map",
    version="0.1.0",
    author="Shiqiang Wu",
    author_email="24300810019@m.fudan.edu.cn",
    description="C++ accelerated metro algorithms",
    long_description="Metro path finding algorithms with C++ backend and Python interface",
    ext_modules=ext_modules,
    zip_safe=False,
    python_requires=">=3.7",
    install_requires=[
        "numpy",
        "pandas", 
        "matplotlib",
        "PyQt5",
        "pybind11>=2.6.0",
    ],
)