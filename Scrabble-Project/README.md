# Scrabble Project
A Scrabble game implementation in C with customizable dictionaries and game logic.

## Features
- Supports multiple dictionaries:
  - `resources/twl06.txt`: Standard Scrabble dictionary.
  - `resources/colors.txt`: A dictionary of color names.
  - `resources/ece.txt`: Engineering-related terms.
- Score calculation and word validation.
- Tile rack management.

## File Structure

Scrabble-Project/
├── main.c           # Game driver
├── scrabble.c       # Core game logic
├── scrabble.h       # Header file
├── random.h         # Header file for randomization
├── README.md        # Project documentation
├── resources/       # Dictionary files
│   ├── colors.txt
│   ├── ece.txt
│   └── twl06.txt



## How to Compile
Run the following command:
```bash
gcc -o scrabble main.c scrabble.c -I.

## How to Run
Run the program as follows:
```bash
./scrabble

