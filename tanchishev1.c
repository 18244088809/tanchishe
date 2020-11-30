#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>

#define High 15
#define Width 25
#define canvasBorder -1//�����߿�
#define snakeHead 1//��ͷ
#define snakeBodySize 4
#define Food -2//ʳ��
#define canvasBlank 0 //�����հ�
//�ƶ�����
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int canvas[High][Width] = {0};
int moveDirection;
int food_x, food_y;

void gotoxy(int x, int y)                            //������ƶ���xy
{                                                    //�������
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //GetStdHandle:��ȡָ���ı�׼�豸�ľ��
    COORD pos;                                       //COORD:һ���ַ��ڿ���̨��Ļ�ϵ�����
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void startup()
{
    int i, j;
    for (i = 0; i < High; i++)
    {
        canvas[i][0] = canvasBorder;
        canvas[i][Width - 1] = canvasBorder;
    }
    for (j = 0; j < Width; j++)
    {
        canvas[0][j] = canvasBorder;
        canvas[High - 1][j] = canvasBorder;
    }
    canvas[High / 2][Width / 2] = snakeHead;
    for (i = 1; i <= snakeBodySize; i++)
    {
        canvas[High / 2][Width / 2 - i] = i + snakeHead;
    }
    moveDirection = RIGHT;//�ƶ������ʼ������
    food_x = rand() % (High - 5) + 2;
    food_y = rand() % (Width - 5) + 2;
    canvas[food_x][food_y] = Food;
}

void show()
{
    gotoxy(0, 0);
    int i, j;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (canvas[i][j] == canvasBorder)
            {
                printf("#");
            }
            if (canvas[i][j] == canvasBlank)
            {
                printf(" ");
            }
            if (canvas[i][j] == snakeHead)
            {
                printf("@");
            }
            if (canvas[i][j] > snakeHead)
            {
                printf("*");
            }
            if (canvas[i][j] == Food)
            {
                printf("F");
            }
        }
        printf("\n");
    }
    Sleep(100);
}

void moveSnakeByDirection()
{
    int i, j;
    int max = 0;
    int oldTail_i, oldTail_j;
    int oldHead_i, oldHead_j;
    int newHead_i, newHead_j;
    for (i = 1; i < High - 1; i++)
    {
        for (j = 1; j < Width - 1; j++)
        {
            if (canvas[i][j] >= snakeHead)
            {
                canvas[i][j]++;
            }
            if (canvas[i][j] > max)
            {
                max = canvas[i][j];
                oldTail_i = i;
                oldTail_j = j;
            }
            if (canvas[i][j] == snakeHead+1)
            {
                oldHead_i = i;
                oldHead_j = j;
            }
        }
    }

    if (moveDirection == UP)
    {
        newHead_i = oldHead_i - 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == DOWN)
    {
        newHead_i = oldHead_i + 1;
        newHead_j = oldHead_j;
    }
    if (moveDirection == LEFT)
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j - 1;
    }
    if (moveDirection == RIGHT)
    {
        newHead_i = oldHead_i;
        newHead_j = oldHead_j + 1;
    }
    if (canvas[newHead_i][newHead_j] == Food)
    { //����ͷ�Ե�ʳ��
        food_x = rand() % (High - 5) + 2;
        food_y = rand() % (Width - 5) + 2;
        canvas[food_x][food_y] = Food;
    }
    else
    { //���� β�ͱ���
        canvas[oldTail_i][oldTail_j] = canvasBlank;
    }

    if (canvas[newHead_i][newHead_j] == canvasBorder || canvas[newHead_i][newHead_j] > snakeHead)
    {
        printf("ʧ��\n");
        exit(0);
    }
    else
    {
        canvas[newHead_i][newHead_j] = snakeHead;
    }
}

void updateWithoutInput()
{
    moveSnakeByDirection();
}

void updateWithInput()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if (input == 'w')
        {
            moveDirection = UP;
        }
        if (input == 's')
        {
            moveDirection = DOWN;
        }
        if (input == 'a')
        {
            moveDirection = LEFT;
        }
        if (input == 'd')
        {
            moveDirection = RIGHT;
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