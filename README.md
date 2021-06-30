README file for the CS F363 Compiler Construction Course Assignment conducted in the second semester of the academic year 2020-2021 at BITS Pilani KK Birla Goa Campus.

Author: Dhruv Nagpal
ID: 2018A7PS0095G
Date of submission: 16/04/2021

Included files:
1. game.cpp
2. game.h
3. lexer.l
4. readme.md
5. parser.y
6. Makefile

The following operations are supported:
1. <Operation> <Direction>.
2. ASSIGN <value> TO <x>,<y>.
3. VAR <variable> IS <x>,<y>.
4. VALUE IN <x>,<y>.

NOTE:
The subtract operation works like this:
SUBTRACT LEFT.
4 2 2 4 -> 4 4 0 0

COMPILATION AND RUNNING THE PROGRAM:
```
make
```   

Internally, the board is a 2D array of size 4x4, and base index (1,1)
Pessing Ctrl+D will exit the program.

Assumptions:
The automated tool will not push the code towards filling up all 16 blocks, since that behaviour was undefined.