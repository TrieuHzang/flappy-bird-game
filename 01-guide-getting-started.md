# Getting Started

## 1. Introduction

The **Flappy Bird Game** is developed on top of the **AK Embedded Base Kit** using the STM32L151 microcontroller. The project demonstrates the application of event-driven programming, finite-state machines, software timers, and object-oriented design in an embedded system.

The game is designed to run on the AK Embedded Base Kit with a **128 × 64 OLED display**, three push buttons, and a buzzer. The project is written in C/C++ and built using the GNU ARM Embedded Toolchain.

This document explains how to prepare the development environment, build the project, flash the firmware, and run the game.

---

# 2. Development Environment

The following software is required before building the project.

| Software | Version | Purpose |
|----------|---------|---------|
| Git | Latest | Clone the repository |
| GNU ARM Embedded Toolchain | 10.x or later | Compile the firmware |
| Make | Latest | Build automation |
| STM32CubeProgrammer | Latest | Flash firmware |
| Visual Studio Code | Latest | Source code editing |

---

# 3. Hardware Requirements

The project is designed for the following hardware.

| Hardware | Description |
|----------|-------------|
| AK Embedded Base Kit | STM32L151 evaluation board |
| OLED Display | 128 × 64 pixels |
| Push Buttons | User input |
| Buzzer | Audio feedback |
| USB Cable | Power and programming |

Figure 1 shows the AK Embedded Base Kit used in this project.

<p align="center">
<img src="images/board.png" width="650">
</p>

<p align="center">
<b>Figure 1.</b> AK Embedded Base Kit.
</p>

---

# 4. Clone the Repository

Clone the repository from GitHub.

```bash
git clone https://github.com/TrieuHzang/flappy-bird-game.git
```

Move into the project directory.

```bash
cd flappy-bird-game
```

---

# 5. Project Structure

The repository is organized as follows.

```
flappy-bird-game
│
├── docs
├── hardware
├── sources
├── Makefile
├── README.md
└── .clang-format
```

The purpose of each directory is summarized below.

| Folder | Description |
|---------|-------------|
| docs | Project documentation |
| hardware | Hardware resources |
| sources | Application source code |
| Makefile | Build configuration |
| README.md | Project overview |

---

# 6. Build the Project

Compile the application by executing

```bash
make
```

During the build process, the GNU ARM Embedded Toolchain compiles all application sources, links the executable, and generates the binary image.

If the compilation succeeds, the generated firmware is placed in the build output directory.

---

# 7. Flash the Firmware

Connect the AK Embedded Base Kit to the computer.

Flash the firmware by executing

```bash
make flash dev=/dev/ttyUSB0
```

Alternatively, open STM32CubeProgrammer and manually program the generated binary into the application memory.

---

# 8. Running the Game

After programming the firmware,

1. Restart the board.
2. The Startup Screen is displayed.
3. Press the MODE button to open the Main Menu.
4. Select **Start Game**.
5. Choose **Normal Mode** or **Reverse Mode**.
6. The gameplay begins immediately.

---

# 9. Gameplay Overview

The player controls a Bird and attempts to fly through incoming Pipes.

After every six successfully cleared Pipes, the game switches to the Arrow Phase, introducing a new obstacle. Once all Arrows have passed, the game advances to the next level and increases the game speed.

The objective is to achieve the highest possible score before colliding with a Pipe, an Arrow, or leaving the playable area.

---

# 10. Troubleshooting

## Build Errors

Possible causes include

- Missing ARM GCC Toolchain
- Incorrect Make version
- Missing project dependencies

## Flash Errors

Possible causes include

- Incorrect serial port
- USB connection failure
- Device reset required

---

# 11. Next Document

Continue reading

- 02-guide-coding-rules.md
- 03-design-game-objects.md
- 04-design-runtime.md
