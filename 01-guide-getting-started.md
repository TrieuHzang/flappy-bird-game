# Getting Started

## Overview

This document provides a quick guide to build and run the **Flappy Bird Game** on the **AK Embedded Base Kit (STM32L151)**.

## Prerequisites

Before building the project, make sure the following tools are installed:

- GCC ARM Embedded Toolchain
- Make
- Git
- ST-Link Utility (or STM32CubeProgrammer)
- Visual Studio Code (recommended)

## Clone the Repository

Clone the project from GitHub.

```bash
git clone https://github.com/TrieuHzang/flappy-bird-game.git
cd flappy-bird-game
```

## Project Structure

```
flappy-bird-game
│
├── docs/
├── hardware/
├── sources/
├── Makefile
└── README.md
```

- **docs/** – Project documentation.
- **hardware/** – Hardware-related resources.
- **sources/** – Game source code.
- **Makefile** – Build configuration.

## Build the Project

Compile the firmware using Make.

```bash
make
```

If the compilation succeeds, the application binary will be generated automatically.

## Flash the Firmware

Connect the AK Embedded Base Kit to the computer and flash the firmware.

Example:

```bash
make flash dev=/dev/ttyUSB0
```

or flash the generated binary using **STM32CubeProgrammer**.

## Run the Game

After flashing is complete:

1. Power on the AK Embedded Base Kit.
2. The startup screen will appear.
3. Press **MODE** to enter the Main Menu.
4. Select **Start Game**.
5. Choose **Normal Mode** or **Reverse Mode**.
6. Enjoy the game.

## Troubleshooting

### Build Failed

- Verify the ARM GCC toolchain is installed.
- Check the Makefile configuration.
- Ensure all project files are available.

### Flash Failed

- Check the USB connection.
- Verify the correct serial port.
- Restart the board and try again.

## Next Step

Continue with:

- **02-guide-coding-rules.md** – Coding conventions.
- **03-design-game-objects.md** – Gameplay object design.
- **04-design-runtime.md** – Runtime architecture and game flow.
