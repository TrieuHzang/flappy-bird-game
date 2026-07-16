# Game Objects Design

## Introduction

This document describes the design of the gameplay objects used in the **Flappy Bird Game**. Each object is responsible for a specific task and interacts with the game controller through the event-driven framework.

The purpose of this document is to explain the behavior, properties, and relationships of all gameplay objects.

---


# Object Summary

| Object | Module | Main Responsibility |
|---------|--------|---------------------|
| Bird | `scr_flappy_game.cpp` | Controls the Bird movement, processes player input, applies gravity (or reverse gravity), and detects collisions with obstacles. |
| Pipe | `scr_flappy_game.cpp` | Generates pipe obstacles, updates their movement, randomizes the gap position, and increases the score when the Bird successfully passes through. |
| Arrow | `scr_flappy_game.cpp` | Manages the Arrow Phase, launches arrows after the required score is reached, detects collisions with the Bird, and signals the completion of the phase. |
| Cloud | `scr_flappy_game.cpp` | Updates cloud positions to create a continuous scrolling background animation. |
| Star | `scr_flappy_game.cpp` | Draws decorative stars in the background to enhance the visual appearance of the game. |
| Tree | `scr_flappy_game.cpp` | Scrolls foreground trees continuously to improve the environmental animation. |
| Game Controller | `scr_flappy_game.cpp` | Coordinates the gameplay loop, updates all objects, manages score and level progression, processes collisions, controls game states, and handles screen transitions. |

---

# Bird

## Description

The Bird is the player-controlled character. It responds to button input, moves vertically according to the selected game mode, and performs collision detection with obstacles and screen boundaries.

<p align="center">
<img src="images/.png" width="120">
</p>

<p align="center">
<b>Figure 2.</b> Bird object.
</p>

### Properties

| Property | Description |
|----------|-------------|
| Position | Current position on the screen |
| Velocity | Vertical movement speed |
| Gravity | Downward (or reverse) acceleration |
| State | Alive or Game Over |

### Responsibilities

- Process player input.
- Apply gravity.
- Move vertically.
- Detect collisions.
- Notify the Game Controller when a collision occurs.

---

# Pipe

## Description

Pipes are the primary obstacles during the Pipe Phase. They move continuously from right to left and are regenerated after leaving the screen.

<p align="center">
<img src="images/pipe.png" width="180">
</p>

<p align="center">
<b>Figure 3.</b> Pipe object.
</p>

### Properties

| Property | Description |
|----------|-------------|
| Position | Current horizontal position |
| Gap | Opening for the Bird |
| Speed | Movement speed |

### Responsibilities

- Generate random gaps.
- Move left.
- Respawn after leaving the screen.
- Increase the player's score when successfully passed.

---

# Arrow

## Description

The Arrow is a special obstacle introduced after the Bird reaches a predefined score. Unlike Pipes, Arrows move at higher speed and create a temporary challenge before the next level begins.

<p align="center">
<img src="images/arrow.png" width="150">
</p>

<p align="center">
<b>Figure 4.</b> Arrow object.
</p>

### Properties

| Property | Description |
|----------|-------------|
| Position | Current position |
| Speed | Horizontal movement speed |
| Active | Arrow phase status |

### Responsibilities

- Move across the screen.
- Detect collision with the Bird.
- Trigger the next level after all Arrows are completed.

---

# Cloud

## Description

Clouds are decorative background objects. They slowly move across the screen to create a dynamic environment.

<p align="center">
<img src="images/cloud.png" width="180">
</p>

<p align="center">
<b>Figure 5.</b> Cloud object.
</p>

### Responsibilities

- Move slowly.
- Loop when leaving the screen.
- Provide background animation.

---

# Star

## Description

Stars are decorative background objects displayed in the sky. They do not affect gameplay.

<p align="center">
<img src="images/star.png" width="100">
</p>

<p align="center">
<b>Figure 6.</b> Star object.
</p>

### Responsibilities

- Decorative rendering.
- Background animation.

---

# Tree

## Description

Trees are decorative foreground objects placed near the ground to enrich the game scene.

<p align="center">
<img src="images/tree.png" width="140">
</p>

<p align="center">
<b>Figure 7.</b> Tree object.
</p>

### Responsibilities

- Decorative rendering.
- Continuous scrolling.
- Foreground animation.

---

# Game Controller

## Description

The Game Controller coordinates all gameplay objects and controls the overall game flow.

### Responsibilities

- Initialize objects.
- Update gameplay.
- Switch between Pipe Phase and Arrow Phase.
- Update score and level.
- Detect Game Over.
- Manage screen transitions.

---

# Object Interaction

<p align="center">
<img src="images/object-sequence.png" width="900">
</p>

<p align="center">
<b>Figure 8.</b> Interaction between gameplay objects.
</p>

The Game Controller updates every gameplay object during each timer tick. Objects update their internal states independently and report important events, such as collisions or score updates, back to the Game Controller.
