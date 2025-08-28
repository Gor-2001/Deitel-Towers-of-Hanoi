# Deitel Towers of Hanoi

A C++ implementation of the classic **Towers of Hanoi** puzzle, inspired by the *Deitel C++ Book*.  
This project uses **CMake** for building and supports **Windows** and **Linux**.

---

## Features

- Multiple game modes based on:
  - Number of disks.
  - Starting positions of disks.
- Interactive gameplay with on-screen instructions.
- Cross-platform support.
- Easy to extend or modify for different variations of the game.

---

***

## 🛠️ Building the Project

The project can be built on both Windows and Linux using a standard CMake workflow.

### Windows 💻

1.  **Generate build files:** Open a command prompt or terminal and run the following command to generate the build files in a new directory named `out`.
    ```bash
    cmake -S . -B out
    ```

2.  **Build the project:** Use CMake to build the project from the `out` directory.
    ```bash
    cmake --build out
    ```

### Linux 🐧

1.  **Install ncurses:** First, you need to install the **ncurses** library to handle console input and output. Open your terminal and run:
    ```bash
    sudo apt-get install libncurses5-dev
    ```

2.  **Generate build files:** Generate the build files in the `out` directory:
    ```bash
    cmake -S . -B out
    ```

3.  **Build the project:** Build the project using CMake:
    ```bash
    cmake --build out
    ```

***

## ▶️ Running the Executable

Once the project is successfully built, you can run the executable from the terminal.

### Windows 💻

The executable is located in the `out/Debug/` directory.

```bash
out\Debug\DeitelTowersOfHanoi.exe

### Gameplay Instructions: Follow the on-screen prompts to select number of disks, and starting positions. Use the keys shown during the game to control it.

### Notes: Tested on Windows with Visual Studio. Linux support requires ncurses. Designed for educational purposes and to demonstrate C++ concepts from Deitel's book.

## Project Structure

```mermaid
flowchart TD
    A[cross_platform_conio.h] --> B[canvas.h]
    B --> C[game.h]
    C --> D[hanoi_tower.h]
    D --> E[main.cpp]
