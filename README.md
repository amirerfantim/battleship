# Battleship Game


## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)

## Introduction

This project is a command-line implementation of the classic game Battleship. The objective of the game is to strategically place your ships on a grid and take turns guessing the locations of your opponent's ships. The first player to sink all of the opponent's ships wins the game.

## Installation

To run this Battleship game, follow these steps:

1. Clone the repository to your local machine.
2. Compile the source code using a C compiler.
3. Execute the compiled binary.

Here's an example of how to compile the project using `gcc`:

```shell
gcc -o battleship main.c functions.c
```

## Usage

After successfully installing the game, you can use the following command to run it:

```shell
./battleship
```

The game will start and display a grid for each player. Each player will take turns guessing the coordinates to attack their opponent's ships. The game will indicate whether the attack was a hit or a miss. The players continue taking turns until one of them sinks all of their opponent's ships.

Enjoy the strategic challenge of Battleship!


## License

This project is licensed under the [MIT License](LICENSE). You are free to use, modify, and distribute this software. See the [LICENSE](LICENSE) file for more details.

![Demo GIF](demo.gif)
