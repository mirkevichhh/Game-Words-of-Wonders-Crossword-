# Words of Wonders: Terminal Edition 🎮

A console-based word puzzle game written in C, inspired by the popular "Words of Wonders" mobile game. It uses the `ncurses` library to provide an interactive Text-based User Interface (TUI) directly in your terminal.

## 🌟 Features

* **3 Difficulty Modes:** Choose between Easy, Medium, and Hard. Each mode features a unique set of words, a different grid size, and specific time limits.
* **Real-Time Timer:** A built-in countdown timer creates a challenging atmosphere. 
* **Dynamic Grid Rendering:** The crossword board updates dynamically in real-time as you guess the correct words. Correctly guessed letters are highlighted in green.
* **Input Validation:** The game automatically checks your input against the solution list and prevents duplicate guesses.

## 🛠 Prerequisites

To compile and run this game, you need a C compiler (like GCC) and the `ncurses` library installed on your system.

* **Linux (Debian/Ubuntu):**
  ```bash
  sudo apt-get install libncurses5-dev libncursesw5-dev
macOS:
(ncurses is usually pre-installed, or you can get it via Homebrew)

Bash
brew install ncurses
🚀 Compilation & Running
1. Clone this repository to your local machine.

2. Open your terminal and navigate to the folder containing the code.

3. Compile the source code using the -lncurses flag:

Bash
gcc main.c -o wow_game -lncurses
Run the executable:

Bash
./wow_game
🕹️ How to Play
1. Launch the game and select your preferred difficulty mode (1-3).

2. Look at the AVAILABLE LETTERS displayed at the bottom of the screen.

3. Type a valid word using those letters and press Enter.

4. If correct, the word will appear on the crossword board!

5. Find all the hidden words before the timer runs out to win.

6. Type EXIT at any time to quit the game.
