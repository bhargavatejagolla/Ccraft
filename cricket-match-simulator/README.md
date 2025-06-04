# Cricket Match Simulation

## Overview
A C program that simulates a cricket match between two teams, tracking batting and bowling statistics. The simulation includes player performances, scoreboards, and match results.

## Features
- Team creation with customizable player names
- Innings simulation with ball-by-ball input
- Scoreboard display with detailed player statistics
- Automatic target calculation for second innings
- Match result declaration
- Memory management for player data

## Difficulty Level
- **Intermediate C Programming** (uses structures, pointers, dynamic memory allocation, and file I/O)

## Requirements
- C compiler (GCC recommended)
- Standard C libraries (stdio.h, stdlib.h, string.h, stdbool.h)

## Installation & Usage

### Compilation
```bash
gcc cricket_simulation.c -o cricket
```
## Game Flow
- Enter team names and player details

- First innings (Team 1 bats)

- Second innings (Team 2 chases target)

- Match result declaration
## Code Structure
### Key Data Structures
``` c
struct Player {
    char name[50];
    int runs;
    int balls;
    int fours;
    int sixes;
    int isOut;
    struct Player *prev;
    struct Player *next;
};

struct Team {
    char name[50];
    struct Player *head;
    int playerCount;
    int totalRuns;
    int wickets;
    float overs;
};
```
## Main Functions
- inputTeam() - Collects team information

- playInnings() - Simulates an innings

- printScoreboard() - Displays team statistics

- declareResult() - Determines match winner
## Sample Output
  ```bash
  ========= Cricket Match Simulation =========

Enter team name: India
Enter number of players in India: 3
Enter player 1 name: Kohli
Enter player 2 name: Rohit
Enter player 3 name: Dhoni

Enter team name: Australia
Enter number of players in Australia: 3
Enter player 1 name: Smith
Enter player 2 name: Warner
Enter player 3 name: Cummins

--- First Innings (India Batting) ---
Over 1
Enter bowler name: Cummins
Ball 1: Enter runs (0-6), -1 for out, W for wide, NB for no-ball: 4
Ball 2: Enter runs (0-6), -1 for out, W for wide, NB for no-ball: 1
...

--- India Scoreboard ---
-------------------------------------------------------------
| Player       | Runs | Balls | 4s | 6s | Status    |
-------------------------------------------------------------
| Kohli        | 45   | 30    | 4  | 2  | Not Out   |
| Rohit        | 32   | 28    | 3  | 1  | Out       |
| Dhoni        | 12   | 14    | 1  | 0  | Not Out   |
-------------------------------------------------------------
| TOTAL: 89/1 in 2.0 overs                        |
-------------------------------------------------------------

Target for Australia: 90 runs

--- Second Innings (Australia Batting) ---
...

*\\O/* India won the match! *\\O/*
```
## Game Rules
- Maximum 2 overs per innings (configurable)

- Standard cricket scoring (0-6 runs per ball)

- Special inputs:

  - -1: Wicket

  - W: Wide ball

  - NB: No ball
## Future Enhancements   
- Add graphical interface

- Implement player skill ratings

- Add tournament mode

- Include more detailed bowling statistics

- Save match history to file



## 👤 Author

**Golla Bhargava Teja**  
🌐 [https://github.com/vhargavatejagolla](https://github.com/bhargavatejagolla)

---

## 📄 License

This project is licensed under the **MIT License** – see the [LICENSE](LICENSE) file for details.

