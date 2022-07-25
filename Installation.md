# Installation
Setting up Visual Studio Code for writing and executing C and C++ programs

## 1. Compiler Setup

[source](https://www.youtube.com/watch?v=0HD0pqVtsmw)

### **Installing the Package Manager**

1. Go to https://www.mingw-w64.org/downloads/
2. Select MSYS2 for Windows
3. (Follow instruction) download the installer
4. Run the installer and install (msys2-x86_64-yyyymmhh.exe)

### **Updating package database and base package**

1. Run MSYS2 64bit
2. Update the package database: `pacman -Syu`
3. Press `y` to proceed with installation
4. Press `y` to update all MSYS2 processes which will close the current terminal
5. Open MSYS2 MSYS again
6. Update the base packages: `pacman -Su`
7. Press `y` to proceed with installation

### **Installing GCC and G++**

1. After updating packages, open MSYS2 MinGW 62-bit (or 32-bit depending on your system)
2. Type `pacman -Ss gcc` to search gcc packages
3. Search for these criteria
    - **mingw64/** or **mingw32/** as the package name, 
    - GNUC Compiler Collection **(C, C++, OpenMP)** for MinGW-w64
    - for 64-bit its `mingw64/mingw-w64-x86_64-gcc`
    - for 32-bit its `mingw32/mingw-w64-i686-gcc`
4. Install package using `pacman -S <packagename>` without angle bracket
    - for 64-bit its `pacman -S mingw-w64-x86_64-gcc`
    - for 32-bit its `pacman -S mingw-w64-i686-gcc`
5. Press `y` to proceed installation
6. In MSYS MINGW64, Type `gcc --version` or `g++ --version` to find the installed version.

## 2. Debugger Setup

[source](https://www.youtube.com/watch?v=0HD0pqVtsmw)

### **Installing the Debugger**

1. In MSYS MINGW64, Type `pacman -Ss gcc` to search gcc packages
2. Search for these criteria
    - **mingw64/** or **mingw32/**
    - GNU Debugger **(mingw-w64)**
3. Install package using `pacman -S <packagename>` without angle bracket
    - for 64-bit its `pacman -S mingw-w64-x86_64-gdb`
    - for 32-bit its `pacman -S mingw-w64-i686-gdb`
4. Check debugger version, type `gdb --version`

## 3. PATH Environment variable
Setting up the PATH environment variable with the location that we have installed GCC and GDB

- Running `gcc --version` in any CMD will not work.

To fix this,

1. Go to the installation path of Mingw64 (default: `C:/msys64`) and go to `/bin` folder.
2. Copy the path
3. Search fo Environment variable and open up **Edit the system environment variables** from Control Panel
4. Go to **Environment Varaibles**
5. Go to System variables and search for **Path**
6. Edit the **Path** and add new variable
7. Paste the path of the `mingw64/bin` folder
8. Click **OK**, **OK** and **OK** again

Open up command prompt and type `gcc --version` and it should work.

## 4. Visual Studio Setup

[source](https://www.youtube.com/watch?v=77v-Poud_io)

1. Install Visual Studio Code
2. Install C/C++ VSC Extension by Microsoft
3. Install Code Runner VSC Extension by Jun Han
4. Restart VSC

