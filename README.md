# How to compile GMI

To compile GMI the way it was meant to be compiled, you'll need CMake and Qt5.12.
To be honest I am no expert in C++ compilation and I only use the tools that my IDE provides me (I use CLion).

## Windows
GMI has to be compatible with Windows in order to reach the maximum of GORN players, so it requires to be compiled on Windows. I've always compiled C++ on linux, so I've struggled quite a lot to make things work for me on this platform.
These are the steps I've followed:
* Install [MinGW for Windows 64 bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/rubenvb/gcc-4.8-release/) (select the 64 bit version during the installation and leave the rest by default)
* Install [Qt5.12](https://www.qt.io/download) (select the open source version and during the installation only select the Qt5.12 for MinGW checkbox)
* Add `C:\Qt\5.12.0\mingw73_64\bin` to your PATH and restart your computer.
* Use Qt5.12's CMake to compile the project, located at `C:\Qt\5.12.0\mingw73_64\lib\cmake`

At this point, you should be able to compile GMI and launch it.

## Linux
Not tried yet. Feel free to try and write down your process here.
