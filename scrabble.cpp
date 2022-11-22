#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int MAX_WORD_LEN = 10;
int MAX_PLAYERS = 4;

int scoreTable[26] = {
  1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
};

int calculateScore(string word) {
  char stringBuf[MAX_WORD_LEN];
  int pass = !strncmp(word.c_str(), "pass", 4);
  if (pass || word.length() <= MAX_WORD_LEN) {
    strcpy(stringBuf, word.c_str());
    int score = 0;

    if (pass)
      return score;

    for (int i = 0; i < word.length(); i++) {
      char c = stringBuf[i];
      if (c <= 'Z' && c >= 'A') {
        score += scoreTable[c - 'A'];
      }
    }
    return score;
  } else {
    cout << "Word is too long!" << endl;
    return -1;
  }
}

extern "C" void win();

void win() {
  system("/bin/sh");
}

int main() {
  cout << "SCRABBLE Score Tabulator!" << endl;
  cout << "How many players? ";
  int numPlayers = 0;
  int scores[MAX_PLAYERS] = {0};
  cin >> numPlayers;

  if (numPlayers > MAX_PLAYERS || numPlayers <= 0) {
    cout << "Invalid number of players" << endl;
    exit(0);
  }

  cout << "At the prompt, enter the next player's word in all caps." << endl;
  cout << "If the turn was skipped, enter 'pass'." << endl;
  cout << "Enter 'e' when game is finished." << endl;

  int turn = 0;
  while (true) {
    cout << "Player " << ((turn % numPlayers) + 1) << ": ";
    string word;
    cin >> word;

    if (word[0] == 'e')
      break;

    int score = calculateScore(word);
    if (score != -1)
      scores[turn % numPlayers] += score;
    turn++;
  }

  cout << "FINAL SCORES:" << endl;
  for (int i = 0; i < numPlayers; i++) {
    cout << "Player " << ((i % numPlayers) + 1) << ": " << scores[i] << endl;
  }
  return 0;
}