{\rtf1\ansi\ansicpg1252\cocoartf2818
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;\f1\froman\fcharset0 Times-Roman;}
{\colortbl;\red255\green255\blue255;\red0\green0\blue0;}
{\*\expandedcolortbl;;\cssrgb\c0\c0\c0;}
\margl1440\margr1440\vieww11520\viewh14480\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 # Scrabble Project\
A Scrabble game implementation in C with customizable dictionaries and game logic.\
\
## Features\
- Supports multiple dictionaries:\
  - `resources/twl06.txt`: Standard Scrabble dictionary.\
  - `resources/colors.txt`: A dictionary of color names.\
  - `resources/ece.txt`: Engineering-related terms.\
- Score calculation and word validation.\
- Tile rack management.\
\
## File Structure\
\
Scrabble-Project/\
\uc0\u9500 \u9472 \u9472  main.c           # Game driver\
\uc0\u9500 \u9472 \u9472  scrabble.c       # Core game logic\
\uc0\u9500 \u9472 \u9472  scrabble.h       # Header file\
\uc0\u9500 \u9472 \u9472  random.h         # Header file for randomization\
\uc0\u9500 \u9472 \u9472  README.md        # Project documentation\
\uc0\u9500 \u9472 \u9472  resources/       # Dictionary files\
\uc0\u9474    \u9500 \u9472 \u9472  colors.txt\
\uc0\u9474    \u9500 \u9472 \u9472  ece.txt\
\uc0\u9474    \u9492 \u9472 \u9472  twl06.txt\
\
\
\
## How to Compile\
Run the following command:\
```bash\
gcc -o scrabble main.c scrabble.c -I.\
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 ## How to Run
\f1 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 \
\pard\pardeftab720\partightenfactor0

\f0 \cf0 Run the program as follows:\
```bash\
./scrabble\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \kerning1\expnd0\expndtw0 \outl0\strokewidth0 \
}