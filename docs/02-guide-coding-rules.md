# Coding Rules

This document defines the coding conventions used throughout the **Flappy Bird Game** project. Following these guidelines helps maintain consistency, readability, and scalability across the entire codebase.

The coding style in this project follows the conventions used by the **AK Embedded Framework**, allowing every module to integrate consistently with the event-driven architecture.

---

# I. Naming Conventions

## 1. Source Files

Every source file should use lowercase letters with words separated by underscores.

Example:

```text
scr_flappy_menu.cpp
scr_flappy_mode.cpp
scr_flappy_game.cpp
scr_settings.cpp
scr_about.cpp
scr_high_score.cpp
```

Source file names should clearly describe their functionality.

---

## 2. Header Files

Header files should have the same base name as their corresponding source file.

Example

```text
scr_flappy_menu.h
scr_flappy_mode.h
scr_flappy_game.h
scr_settings.h
scr_about.h
scr_high_score.h
```

---

## 3. Header Guards

Every header file must define a unique include guard.

Example

```cpp
#ifndef __SCR_FLAPPY_GAME_H__
#define __SCR_FLAPPY_GAME_H__

...

#endif
```

---

## 4. Macro Definitions

Macro names should be written in uppercase with words separated by underscores.

Example

```cpp
#define SCREEN_WIDTH           128
#define SCREEN_HEIGHT          64

#define PIPE_WIDTH             12
#define PIPE_GAP               24

#define BIRD_WIDTH             12
#define BIRD_HEIGHT            10

#define ARROW_SPEED            3
```

Avoid using magic numbers directly inside the source code.

---

## 5. Enumerations

Enumeration values should use uppercase letters and include a meaningful prefix.

Example

```cpp
typedef enum
{
    GAME_PHASE_PIPE,
    GAME_PHASE_ARROW,
    GAME_PHASE_GAME_OVER
} game_phase_t;
```

---

## 6. Structures

Structure names should end with `_t`.

Example

```cpp
typedef struct
{
    int16_t x;
    int16_t y;
    float velocity;
} bird_t;
```

---

## 7. Functions

Function names should use lowercase letters separated by underscores.

Examples

```cpp
bird_update()

pipe_update()

arrow_update()

bird_reset()

game_reset()

check_collision()
```

Each function should perform only one responsibility.

---

## 8. Variables

Variable names should be descriptive and written in lowercase.

Example

```cpp
bird

pipe

arrow

score

high_score

current_level

current_mode
```

---

## 9. Constants

Constants should be declared using uppercase letters.

Example

```cpp
MAX_LEVEL

PIPE_DISTANCE

START_SPEED

ARROW_INTERVAL
```

---

## 10. Signals

Application signals should follow a common naming convention.

Example

```cpp
FLAPPY_GAME_SETUP

FLAPPY_GAME_UPDATE

FLAPPY_GAME_RENDER

FLAPPY_GAME_COLLISION

FLAPPY_GAME_GAME_OVER

FLAPPY_GAME_RESET
```

---

## 11. Screen Files

Every screen should begin with the prefix `scr_`.

Example

```text
scr_startup.cpp

scr_flappy_menu.cpp

scr_flappy_mode.cpp

scr_flappy_game.cpp

scr_settings.cpp

scr_about.cpp

scr_high_score.cpp
```

Each screen is responsible only for its own user interface and event processing.

# II. Code Style

A consistent coding style improves readability, reduces maintenance effort, and helps developers understand the source code more easily. The Flappy Bird Game project follows a unified formatting style across all source files.

---

## 1. Indentation

Use **4 spaces** for each indentation level.

Do not use tabs.

```cpp
void bird_update()
{
    bird_move();
    check_collision();
}
```


---

## 2. Braces

Opening braces should always appear on a new line.


```cpp
if (bird.y < 0)
{
    game_over();
}
```

---

## 3. Blank Lines

Use blank lines to separate logical sections of code.

Example

```cpp
bird_update();

pipe_update();

arrow_update();

render_game();
```

Avoid excessive blank lines.

---

## 4. Line Length

Keep each source code line reasonably short.

Recommended maximum:

```
100 characters
```

Long expressions should be wrapped across multiple lines.

---

## 5. Function Size

Each function should perform **one specific task**.


```cpp
bird_update();
```

```cpp
pipe_update();
```

```cpp
render_score();
```


Large functions should be divided into smaller helper functions.

---

## 6. Variable Declaration

Declare variables close to where they are first used.


```cpp
int score = 0;

bird_update();
```


when the variables are not immediately required.

---

## 7. Magic Numbers

Avoid hard-coded values inside the source code.


```cpp
#define PIPE_GAP      24
#define BIRD_SPEED     3
```

```cpp
pipe.y += PIPE_GAP;
```

---

## 8. Comments

Comments should explain **why**, not **what**.


```cpp
/* Increase pipe speed after each level */
level++;
```


The code itself should already describe what it is doing.

---

## 9. Naming Consistency

Use the same naming style throughout the project.

Examples

```cpp
bird_update()

pipe_update()

arrow_update()

game_reset()

game_render()
```

Do not mix different naming styles.

---

## 10. Object Responsibilities

Each gameplay object should only manage its own data.

| Object | Responsibility |
|---------|----------------|
| Bird | Movement and collision detection |
| Pipe | Obstacle generation and movement |
| Arrow | Arrow phase obstacle |
| Cloud | Background animation |
| Star | Background animation |
| Tree | Foreground decoration |

Game objects should communicate through the Game Controller rather than modifying each other's internal state directly.

---

## 11. Screen Responsibilities

Each screen should contain only the logic required for that screen.

Examples:

- Startup Screen
- Main Menu
- Mode Selection
- Gameplay
- Settings
- About
- High Score
- Game Over

Avoid placing gameplay logic inside menu screens.

---

## 12. Formatting

All source files should be formatted using **clang-format** before being committed.

The project uses the `.clang-format` configuration located in the repository root.

Example

```bash
clang-format -i application/**/*.cpp
```

or

```bash
clang-format -i application/**/*.h
```

Always format the source code before opening a Pull Request or committing major changes.

# III. Installing clang-format

The Flappy Bird Game project uses **clang-format** to automatically format source code according to the project's coding style.

Developers should install **clang-format** before contributing to the project.

---

## 1. Windows

Download LLVM from the official website:

https://llvm.org/releases/

or install it using **Visual Studio Installer** by selecting:

```
Desktop development with C++
    └── C++ Clang tools for Windows
```

After installation, verify that `clang-format` is available.

```bash
clang-format --version
```

Example output:

```text
clang-format version 20.1.8
```

---

## 2. Ubuntu

Install clang-format using:

```bash
sudo apt update

sudo apt install clang-format
```

Verify the installation.

```bash
clang-format --version
```

---

## 3. macOS

Install using Homebrew.

```bash
brew install clang-format
```

Verify installation.

```bash
clang-format --version
```

---

## 4. Visual Studio Code

Install the following extension.

```
Clang-Format
```

or

```
C/C++
```

Then enable automatic formatting.

```
Settings

↓

Editor: Format On Save

↓

Enable
```

Every time a source file is saved, the code will automatically follow the project's `.clang-format` configuration.

---

## 5. Project Configuration

The repository contains a `.clang-format` file in the project root.

```
flappy-bird-game
│
├── .clang-format
├── application
├── boot
├── hardware
└── README.md
```

No additional configuration is required.

`clang-format` automatically detects this file when formatting the source code.

---

## 6. Verify Installation

To ensure everything is correctly configured, execute

```bash
clang-format --version
```

and format one source file.

```bash
clang-format -i application/sources/app/screens/scr_flappy_game.cpp
```

If the command completes without errors, the installation is successful.

# IV. Running clang-format

After installing **clang-format**, all source files should be formatted before committing or pushing changes to the repository.

---

## 1. Format a Single File

Use the following command to format a single source file.

```bash
clang-format -i application/sources/app/screens/scr_flappy_game.cpp
```

Example for a header file.

```bash
clang-format -i application/sources/app/screens/scr_flappy_game.h
```

---

## 2. Format Multiple Files

Linux

```bash
find application -name "*.cpp" -exec clang-format -i {} \;

find application -name "*.h" -exec clang-format -i {} \;
```

Windows PowerShell

```powershell
Get-ChildItem application -Recurse -Include *.cpp,*.h |
ForEach-Object {
    clang-format -i $_.FullName
}
```

---

## 3. Verify Formatting

Before committing, review the formatted files.

```bash
git diff
```

Ensure that formatting changes do not introduce unintended modifications.

---

## 4. Recommended Workflow

The recommended development workflow is:

```
Implement Feature

↓

Build Project

↓

Test Gameplay

↓

Run clang-format

↓

Review Changes

↓

Commit

↓

Push to GitHub
```

Following this workflow keeps the codebase clean and consistent across all contributors.

---

# V. Commit Message Convention

Commit messages should be concise, meaningful, and describe a single logical change.

Every commit should focus on **one feature, one improvement, or one bug fix**.

---

## 1. Commit Format

Use the following format.

```
[TYPE] Short description
```

---

## 2. Commit Types

| Type | Description |
|------|-------------|
| **ADD** | Add a new feature or module |
| **UPDATE** | Improve an existing feature |
| **FIX** | Fix a bug |
| **REFACTOR** | Refactor source code without changing behavior |
| **DOC** | Update project documentation |
| **STYLE** | Code formatting only (no logic changes) |
| **REMOVE** | Remove unused code or resources |

---

## 3. Examples

Add a new gameplay feature.

```text
[ADD] Implement Arrow Phase
```

Fix a collision issue.

```text
[FIX] Correct Bird and Pipe collision detection
```

Improve gameplay.

```text
[UPDATE] Increase Pipe movement smoothness
```

Update documentation.

```text
[DOC] Add runtime sequence diagram
```

Format source code.

```text
[STYLE] Apply clang-format to gameplay modules
```

Refactor the rendering code.

```text
[REFACTOR] Simplify OLED rendering pipeline
```

---

## 4. Commit Guidelines

A good commit should:

- Modify only one logical feature.
- Build successfully.
- Be tested before committing.
- Include a clear and descriptive message.
- Update documentation when necessary.

Avoid commit messages such as:

```text
update

fix

bug

change

test

abc
```

These messages do not clearly describe the purpose of the commit.

---

## 5. Example Development History

```text
[ADD] Create Main Menu screen

[ADD] Implement Bird object

[ADD] Implement Pipe obstacle

[ADD] Add Reverse Mode

[ADD] Implement Arrow Phase

[UPDATE] Improve gameplay difficulty

[FIX] Correct score calculation

[FIX] Prevent Bird leaving screen

[DOC] Complete runtime documentation

[STYLE] Format all source files
```

# VI. Documentation Naming Convention

Project documentation should follow a consistent naming convention to improve readability and simplify navigation.

Documentation files are prefixed with a two-digit index indicating the recommended reading order.

Current documentation:

| File | Description |
|------|-------------|
| README.md | Project overview, gameplay introduction, hardware information, and game objects. |
| 01-guide-getting-started.md | Build environment, project structure, compilation, and flashing guide. |
| 02-guide-coding-rules.md | Coding conventions and development guidelines. |
| 03-design-game-objects.md | Design and behavior of gameplay objects, including Bird, Pipe, Arrow, Cloud, Star, and Tree. |
| 04-design-runtime.md | Runtime architecture, game loop, state transitions, event handling, and sequence diagrams. |

Documentation filenames should use:

- lowercase letters
- words separated by hyphens (`-`)
- numeric prefixes for ordering

Example:

```text
01-guide-getting-started.md
02-guide-coding-rules.md
03-design-game-objects.md
04-design-runtime.md
```

Avoid filenames such as:

```text
GettingStarted.md

Guide.docx

FinalVersion2.md

GameObjectsNEW.md
```

Documentation should always be updated whenever new gameplay features are introduced.

---

# VII. References

The following resources were referenced during the development of this project.

| Topic | Reference |
|------|-----------|
| AK Embedded Framework | https://github.com/the-ak-foundation |
| STM32L151 Reference Manual | https://www.st.com |
| GNU Arm Embedded Toolchain | https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads |
| LLVM / clang-format | https://clang.llvm.org/docs/ClangFormat.html |
| Mermaid | https://mermaid.js.org |
| Git | https://git-scm.com |

These references provide additional information about the embedded framework, development tools, and documentation techniques used throughout the project.

---

# VIII. Contact

If you discover a bug, have suggestions for improvement, or would like to contribute to the project, please create an Issue or Pull Request on GitHub.

Repository:

```text
https://github.com/TrieuHzang/flappy-bird-game
```

Project Maintainer

```text
Triệu Hà Giang
```

Contributions are always welcome.
