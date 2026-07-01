# Words of Wonders: Terminal Edition 🧩

A console-based 2D word puzzle game written in C, inspired by the popular "Words of Wonders" mobile game. 

This project was developed as part of the **"Problem Set 6: Curses"** assignment for the Faculty of Electrical Engineering and Informatics (FEI) at the Technical University of Košice (TUKE). It demonstrates practical experience with the C programming language, terminal environments, and text-based interactive application design.

## 🌟 Key Features

The game leverages the `ncurses` library to create a fully interactive Text-Based User Interface (TUI) without the need for a graphical desktop environment. 

* **Color Integration:** Uses `ncurses` color pairs to highlight correctly guessed letters (green) and dynamically display the timer (yellow).
* **Real-Time Keyboard Control:** Continuous input handling using `ncurses` without needing to press the `Enter` key for every character.
* **3 Difficulty Levels:** Choose from Easy (6x6 grid), Medium (12x12 grid), or Hard (17x17 grid). Each level has a unique set of words and its own strict time limit.
* **Dynamic Time Management:** A built-in countdown timer actively updates on the screen and dictates the win/loss state of the session.
* **Modular Architecture:** The underlying code is broken down into 10 custom functions (e.g., `initialize_board()`, `let_the_game_begin()`) to handle state, input validation, and rendering efficiently.

## 🛠 Prerequisites & Installation

To compile and run this game, you need a C compiler (`gcc`), `make`, and the `ncurses` development library installed on your Linux or macOS system.

**Ubuntu / Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential libncurses5-dev libncursesw5-dev
```
macOS (via Homebrew):


```bash
brew install ncurses make
🚀 Compilation & Running
The project includes a Makefile configured with strict compilation flags (-Wall -Wextra -std=c11) to ensure high code quality.

1. Clone this repository to your local machine.

2. Open your terminal and navigate to the project directory.

3. Compile the game using the provided Makefile:

```bash
make
4. Run the executable:

```bash
./program
Note: To clean up the compiled executable later, simply run make clean.

🕹️ How to Play
1. Select Difficulty: Upon launching, enter 1 (Easy), 2 (Medium), or 3 (Hard) in the main menu[cite: 1].

2. Make Words: Look at the AVAILABLE LETTERS displayed at the bottom of the screen[cite: 1]. Type a valid word using only those letters.
(Note: Input is automatically converted to uppercase)[cite: 1].

3. Fill the Grid: If your word is correct, the empty brackets | | on the board will be filled with the highlighted green letters[cite: 1].

4. Win or Lose:

Win: Guess all the hidden words before the timer hits 00:00[cite: 1].

Lose: The game ends automatically if the time runs out[cite: 1].

5. Quit: Type EXIT at any time to immediately close the game[cite: 1].

📄 Documentation
For a detailed technical breakdown of the ncurses functions used, the logic behind the grid rendering, and the overall project architecture, please refer to the attached documentation.pdf (written in Slovak)[cite: 1].
