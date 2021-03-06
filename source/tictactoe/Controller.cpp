#include "Controller.h"

Controller::Controller(void (*isSet)(int))
{
  this->isSet = isSet;
  reset();
}

void Controller::setMark(int pos)
{
  if (!gameOver) {
    if (grid[pos] == NOT_SET) {
      grid[pos] = currentPlayer;
      checkGameOver();
      nextPlayer();
      turnCount++;
      isSet(pos);
    }
  }
}

void Controller::nextPlayer()
{
  currentPlayer = (currentPlayer + 1) % 2;
}

void Controller::checkGameOver()
{
  // vertical
  if (gameOver == false && grid[0] != NOT_SET && grid[0] == grid[3] && grid[3] == grid[6]) { gameOver = true; }
  if (gameOver == false && grid[1] != NOT_SET && grid[1] == grid[4] && grid[4] == grid[7]) { gameOver = true; }
  if (gameOver == false && grid[2] != NOT_SET && grid[2] == grid[5] && grid[5] == grid[8]) { gameOver = true; }
  
  // horizontal
  if (gameOver == false && grid[0] != NOT_SET && grid[0] == grid[1] && grid[1] == grid[2]) { gameOver = true; }
  if (gameOver == false && grid[3] != NOT_SET && grid[3] == grid[4] && grid[4] == grid[5]) { gameOver = true; }
  if (gameOver == false && grid[6] != NOT_SET && grid[6] == grid[7] && grid[7] == grid[8]) { gameOver = true; }
  
  // diagonal
  if (gameOver == false && grid[0] != NOT_SET && grid[0] == grid[4] && grid[4] == grid[8]) { gameOver = true; }
  if (gameOver == false && grid[2] != NOT_SET && grid[2] == grid[4] && grid[4] == grid[6]) { gameOver = true; }
  
  if (gameOver) {
    winner = currentPlayer;
    return;
  }
  
  if (turnCount >= GRID_SIZE-1) {
    gameOver = true;
  }
}

bool Controller::isGameOver()
{
  return gameOver;
}

int Controller::getWinner()
{
  return winner;
}

int Controller::getCurrentPlayer()
{
  return currentPlayer;
}

void Controller::reset()
{
  currentPlayer = O_PLAYER;
  winner = NOT_SET;
  gameOver = false;
  turnCount = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    grid[i] = NOT_SET;
  }
}

