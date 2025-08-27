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

Building the Project

Windows: Generate build files with cmake -S . -B out, build the project with cmake --build out, and run the executable (Debug mode) using out\Debug\DeitelTowersOfHanoi.exe.

Linux: Install the ncurses library with sudo apt-get install libncurses5-dev, generate build files with cmake -S . -B out, build the project with cmake --build out, and run the executable via out/DeitelTowersOfHanoi.

Gameplay Instructions: Follow the on-screen prompts to select number of disks, and starting positions. Use the keys shown during the game to control it.

Notes: Tested on Windows with Visual Studio. Linux support requires ncurses. Designed for educational purposes and to demonstrate C++ concepts from Deitel's book.

## Project Structure

```mermaid
flowchart TD
    A[cross_platform_conio.h] --> B[tower.h]
    B --> C[game.h]
    C --> D[hanoi_tower.h]
    D --> E[main.cpp]
