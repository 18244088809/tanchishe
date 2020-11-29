#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define High_i 15
#define Width_j 25
#define snakeBody 4

int canvas[High_i][Width_j] = {0};
int moveDirection;
int food_x, food_y;

void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}
void startup()
{
    int i, j;
    for (i = 0; i < High_i; i++)
    {
        canvas[i][0] = -1;
        canvas[i][Width_j - 1] = -1;
    }
    for (j = 0; j < Width_j; j++)
    {
        canvas[0][j] = -1;
        canvas[High_i - 1][j] = -1;
    }
    canvas[High_i / 2][Width_j / 2] = 1;
    for (i = 1; i <= snakeBody; i++)
    {
        canvas[High_i / 2][Width_j / 2 - i] = i + 1;
    }
    food_x = rand() % (High_i - 5) + 2;
    food_y = rand() % (Width_j - 5) + 2;
    canvas[food_x][food_y] = -2;
    moveDirection = 4;
}

void show()
{
    gotoxy(0, 0);
    int i, j;
    for (i = 0; i < High_i; i++)
    {
        for (j = 0; j < Width_j; j++)
        {
            if (canvas[i][j] == -1)
            {
                printf("#");
            }
            if (canvas[i][j] == 0)
            {
                printf(" ");
            }
            if (canvas[i][j] == 1)
            {
                printf("@");
            }
            if (canvas[i][j] > 1)
            {
                printf("*");
            }
            if (canvas[i][j] == -2)
            {
                printf("F");
            }
        }
        printf("\n");
    }
    Sleep(100);
}
void moveSnakeBySnake()
{
    int i, j;
    int max = 0;
    int oldHead_i, oldHead_j;
    int oldTail_i, oldTail_j;
    int newHead_i, newHead_j;
    for (i = 1; i < High_i - 1; i++)
    {
        for (j = 1; j < Width_j - 1; j++)
        {
            if (canvas[i][j] > 0)
            {
                canvas[i][j]++;
            }
            if (canvas[i][j] == 2)
            {
                oldHead_i = i;
                oldHead_j = j;
            }
            if (canvas[i][j] > max)
            {
                max = canvas[i][j];
                oldTail_i = i;
                oldTail_j = j;
            }
        }
    }

    if (moveDirection == 1)
    {
        newHead_i = oldHead_i - 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == 2)
    {
        newHead_i = oldHead_i + 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == 3)
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j - 1;
    }
    if (moveDirection == 4)
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j + 1;
    }
    if (canvas[newHead_i][newHead_j] == -2)
    {
        food_x = rand() % (High_i - 5) + 2;  //[2,12)
        food_y = rand() % (Width_j - 5) + 2; // [2,22)
        canvas[food_x][food_y] = -2;
    }
    else
    { //没食物 尾巴变0
        canvas[oldTail_i][oldTail_j] = 0;
    }
    if (canvas[newHead_i][newHead_j] == -1 || canvas[newHead_i][newHead_j] > 0)
    {
        printf("游戏失败！\n");
        exit(0);
    }
    else
    {
        canvas[newHead_i][newHead_j] = 1;
    }
}
void updateWithoutInput()
{
    moveSnakeBySnake();
}

void updateWithInput()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if (input == 'w')
        {
            moveDirection = 1;
        }
        if (input == 's')
        {
            moveDirection = 2;
        }
        if (input == 'a')
        {
            moveDirection = 3;
        }
        if (input == 'd')
        {
            moveDirection = 4;
        }
    }
}

int main()
{
    startup();
    while (1)
    {
        show();
        updateWithoutInput();
        updateWithInput();
    }

    return 0;
}