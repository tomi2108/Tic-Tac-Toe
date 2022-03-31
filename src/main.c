#include <stdio.h>

void renderBoard(int[3][3]);
void printCell(int);
void convertMovesToBoard(int[3][3], int[5][2], int[5][2], int, int);
void convertToMoves(int[2], int);
int isWinnerBoard(int[3][3]);
int isValidMove(int, int[9]);

int main()
{
  int turn = 0;
  int input = 0;
  int occupiedSpaces[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  int p1Length = 0;
  int p2Length = 0;

  int player1Moves[5][2];
  int player2Moves[5][2];

  int board[3][3] = {{0, 0, 0},
                     {0, 0, 0},
                     {0, 0, 0}};

  printf("Welcome To tic tac toe \n");
  renderBoard(board);

  while (!isWinnerBoard(board))
  {
    int totalMoves = p1Length + p2Length;
    int moves[2] = {0, 0};

    printf("Player %d turn: ", turn + 1);
    scanf("%d", &input);

    if (isValidMove(input, occupiedSpaces))
    {

      occupiedSpaces[totalMoves] = input;

      convertToMoves(moves, input);

      if (turn == 0)
      {
        player1Moves[p1Length][0] = moves[0];
        player1Moves[p1Length][1] = moves[1];
        p1Length++;
      }
      else if (turn == 1)
      {
        player2Moves[p2Length][0] = moves[0];
        player2Moves[p2Length][1] = moves[1];
        p2Length++;
      }

      convertMovesToBoard(board, player1Moves, player2Moves, p1Length, p2Length);
      renderBoard(board);
      turn = (turn + 1) % 2;
    }
    else
    {
      printf("Invalid move, try again! \n");
    }
  }
  if (turn == 0)
  {
    turn = 2;
  }
  printf("Player %d won, congrats!!!  ", (turn));

  return 0;
}

int isValidMove(int move, int occupied[9])
{
  for (int i = 0; i < 9; i++)
  {
    if (move != i)
    {
      return 0;
    }
  }

  for (int i = 0; i < 9; i++)
  {
    if (occupied[i] == move)
    {
      return 0;
    }
  }

  return 1;
}

int checkRow(int board[3][3], int row)
{
  int p1Check = 0;
  int p2Check = 0;

  for (int i = 0; i < 3; i++)
  {
    if (board[row][i] == 1)
    {
      p1Check++;
    }
    if (board[row][i] == 2)
    {
      p2Check++;
    }
  }

  if (p1Check == 3)
  {
    return 1;
  }
  if (p2Check == 3)
  {
    return 2;
  }
  return 0;
}

int checkColumn(int board[3][3], int column)
{
  int p1Check = 0;
  int p2Check = 0;

  for (int i = 0; i < 3; i++)
  {
    if (board[i][column] == 1)
    {
      p1Check++;
    }
    if (board[i][column] == 2)
    {
      p2Check++;
    }
  }

  if (p1Check == 3)
  {
    return 1;
  }
  if (p2Check == 3)
  {
    return 2;
  }
  return 0;
}

int checkDiagonal(int board[3][3], int diag)
{

  if (diag == 0)
  {
    int p1Check = 0;
    int p2Check = 0;

    for (int i = 0; i < 3; i++)
    {
      if (board[i][i] == 1)
      {
        p1Check++;
      }
      if (board[i][i] == 2)
      {
        p2Check++;
      }
    }

    if (p1Check == 3)
    {
      return 1;
    }
    if (p2Check == 3)
    {
      return 2;
    }

    if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1)
    {
      return 1;
    }
    if (board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2)
    {
      return 2;
    }
  }
  else if (diag == 1)
  {
    int p1Check = 0;
    int p2Check = 0;

    for (int i = 0, j = 2; i < 3; i++)
    {
      if (board[i][j] == 1)
      {
        p1Check++;
      }
      if (board[i][j] == 2)
      {
        p2Check++;
      }
      j--;
    }

    if (p1Check == 3)
    {
      return 1;
    }
    if (p2Check == 3)
    {
      return 2;
    }
  }
  return 0;
}

int isWinnerBoard(int board[3][3])
{
  for (int i = 0; i < 3; i++)
  {
    int rowWin = checkRow(board, i);
    int columnWin = checkColumn(board, i);
    if (rowWin || columnWin)
    {
      return 1;
    };
  }
  for (int i = 0; i < 2; i++)
  {
    int diagonalWin = checkDiagonal(board, i);
    if (diagonalWin)
    {
      return 1;
    }
  }

  return 0;
}

void copyArr(int arr[], int arrToCopy[])
{
  for (int i = 0; i < 2; i++)
  {
    arr[i] = arrToCopy[i];
  }
}

void convertMovesToBoard(int board[3][3], int player1Moves[5][2], int player2Moves[5][2], int p1Length, int p2Length)
{
  for (int k = 0; k < p1Length; k++)
  {
    int p1Move[2];
    copyArr(p1Move, player1Moves[k]);
    board[p1Move[0]][p1Move[1]] = 1;
  }
  for (int k = 0; k < p2Length; k++)
  {
    int p2Move[2];
    copyArr(p2Move, player2Moves[k]);
    board[p2Move[0]][p2Move[1]] = 2;
  }
}

void convertToMoves(int arr[2], int m)
{
  switch (m)
  {
  case 1:
    arr[0] = 0;
    arr[1] = 0;
    break;
  case 2:
    arr[0] = 0;
    arr[1] = 1;
    break;
  case 3:
    arr[0] = 0;
    arr[1] = 2;
    break;
  case 4:
    arr[0] = 1;
    arr[1] = 0;
    break;
  case 5:
    arr[0] = 1;
    arr[1] = 1;
    break;
  case 6:
    arr[0] = 1;
    arr[1] = 2;
    break;
  case 7:
    arr[0] = 2;
    arr[1] = 0;
    break;
  case 8:
    arr[0] = 2;
    arr[1] = 1;
    break;
  case 9:
    arr[0] = 2;
    arr[1] = 2;
    break;

  default:
    break;
  }
};

void printCell(int c)
{
  if (c == 0)
  {
    printf(" ");
  };
  if (c == 1)
  {
    printf("X");
  };
  if (c == 2)
  {
    printf("O");
  };
}

void renderBoard(int board[3][3])
{

  for (int i = 0; i < 3; i++)
  {
    printf("--------------\n");
    for (int j = 0; j < 3; j++)
    {
      if (j == 0)
      {
        printf("| ");
        printCell(board[i][j]);
        printf(" | ");
      }
      if (j == 1)
      {
        printCell(board[i][j]);
        printf(" | ");
      };
      if (j == 2)
      {
        printCell(board[i][j]);
        printf(" |\n");
      }
    }
  };
  printf("--------------\n");
}
