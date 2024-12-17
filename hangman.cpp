#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <set>

using namespace std;

const vector<string> EASY = {"apple", "beach", "chair", "dance", "eagle"};
const vector<string> MEDIUM = {"dishwasher", "automobile", "refrigerator", "xylophone"};
const vector<string> HARD = {"supercalafajalistickespeealadojus", "pneumonoultramicroscopicsilicovolcanoconiosis"};
const int MAX_TRIES = 6;

enum Difficulty {EASY_MODE = 1, MEDIUM_MODE = 2, HARD_MODE = 3};

string getRandomWord(const vector<string>& wordList) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, wordList.size() - 1);
    return wordList[dis(gen)];
}

string toLowerCase(string input) {
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

// Displays guessed letters and remaining letters as _
void displayWord(const string& targetWord, const set<char>& guessedLetters) {
    for (char c : targetWord) {
        if (guessedLetters.find(c) != guessedLetters.end()) {
            cout << c << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// A check if the word has been guessed
bool isWordComplete(const string& targetWord, const set<char>& guessedLetters) {
    for (char c : targetWord) {
        if (guessedLetters.find(c) == guessedLetters.end()) {
            return false;
        }
    }
    return true;
}

// Choose difficulty between 1 and 3
Difficulty chooseDifficulty() {
    int choice;
    cout << "\nChoose difficulty level:" << endl;
    cout << "1. Easy (5-letter words)" << endl;
    cout << "2. Medium (8-10 letter words)" << endl;
    cout << "3. Hard (very long words)" << endl;
    cout << "Enter your choice (1-3): ";
    // Checks the input
    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Invalid input. Please enter 1, 2, or 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Changes the type to Type Difficulty
    return static_cast<Difficulty>(choice);
}

int main() {
    cout << "Welcome to Hangman!" << endl;
    // Game continuation loop
    bool playAgain = true;
    while (playAgain) {
        Difficulty difficulty = chooseDifficulty();
        string targetWord;
        
        switch (difficulty) {
            case EASY_MODE:
                targetWord = getRandomWord(EASY);
                break;
            case MEDIUM_MODE:
                targetWord = getRandomWord(MEDIUM);
                break;
            case HARD_MODE:
                targetWord = getRandomWord(HARD);
                break;
        }

        set<char> guessedLetters;
        set<char> wrongLetters;
        int tries = 0;
        bool won = false;

        cout << "\nTry to guess the " << targetWord.length() << "-letter word." << endl;
        cout << "You have " << MAX_TRIES << " attempts." << endl;

        while (tries < MAX_TRIES && !won) {
            cout << "\nAttempt " << tries + 1 << "/" << MAX_TRIES << endl;
            cout << "Word: ";
            displayWord(targetWord, guessedLetters);
            
            if (!wrongLetters.empty()) {
                cout << "Wrong letters: ";
                for (char c : wrongLetters) {
                    cout << c << " ";
                }
                cout << endl;
            }

            char guess;
            cout << "Enter a letter: ";
            cin >> guess;
            guess = tolower(guess);

            if (guessedLetters.find(guess) != guessedLetters.end()) {
                cout << "You already guessed that letter!" << endl;
                continue;
            }

            guessedLetters.insert(guess);

            if (targetWord.find(guess) != string::npos) {
                cout << "Correct guess!" << endl;
            } else {
                cout << "Wrong guess!" << endl;
                wrongLetters.insert(guess);
                tries++;
            }

            won = isWordComplete(targetWord, guessedLetters);
        }

        if (won) {
            cout << "\nCongratulations! You've won! The word was: " << targetWord << endl;
        } else {
            cout << "\nGame Over! The word was: " << targetWord << endl;
        }

        char playChoice;
        cout << "\nWould you like to play again? (y/n): ";
        cin >> playChoice;
        playAgain = (toLowerCase(string(1, playChoice)) == "y");
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}