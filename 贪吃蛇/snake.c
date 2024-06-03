#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>
#include <conio.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define KEY_PRESS(VK) ((GetAsyncKeyState(VK) & 0x1) ? 1 : 0)
#define Normal 1000
#define Hard 500

int Snake_x = 3;
int Snake_y = 3;
int Food_x = 1;
int Food_y = 1;
int Direction = LEFT;
char ch1 = 'O';
wchar_t ch2 = L'●';
char ch3 = 'C';
int Num = 0;
int Speed = Normal;

void SetPos(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(handle, pos);
}

void Start()
{
    system("cls");
    system("title 贪吃蛇");
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo);
    Snake_x = 3;
    Snake_y = 3;
    Num = 0;
}

void Hello()
{
    do
    {
        system("cls");
        SetPos(1, 1);
        wprintf(L"欢迎来到《潦草的吃豆人1.0》");
        SetPos(1, 2);
        wprintf(L"请选择难度：1.Normal；2.Hard");
        Speed = getch();
        Speed = Speed - 48;
    } while (!((Speed == 1) || (Speed == 2)));
}

void Map()
{
    system("cls");
    for (int i = 1; i < 6; i++)
    {
        for (int n = 1; n < 6; n++)
        {
            SetPos(i, n);
            printf("%c", ch1);
        }
        printf("\n");
    }
}

void Snake()
{
    SetPos(Snake_x, Snake_y);
    wprintf(L"%lc", ch2);
}

void Food()
{
    do
    {
        Food_x = 1 + rand() % (5 - 1 + 1);
        Food_y = 1 + rand() % (5 - 1 + 1);
    } while ((Food_x == Snake_x) && (Food_y == Snake_y));
    SetPos(Food_x, Food_y);
    printf("%c", ch3);
}

void Mark()
{
    SetPos(7, 3);
    printf("%d", Num);
}

int Wall()
{
    if ((Snake_x == 0) || (Snake_x == 6) || (Snake_y == 0) || (Snake_y == 6))
    {
        return 0;
    }
    return 1;
}

void EatFood()
{
    if ((Food_x == Snake_x) && (Food_y == Snake_y))
    {
        Num++;
        Food();
        Mark();
    }
}

void Pause()
{
    if (Speed == 1)
    {
        Sleep(1000);
        return;
    }
    Sleep(500);
}

void GameRun()
{
    while (1)
    {
        Pause();
        if (KEY_PRESS(VK_LEFT) == 1)
            Direction = LEFT;
        else if (KEY_PRESS(VK_RIGHT) == 1)
            Direction = RIGHT;
        else if (KEY_PRESS(VK_UP) == 1)
            Direction = UP;
        else if (KEY_PRESS(VK_DOWN) == 1)
            Direction = DOWN;
        if (Direction == LEFT)
        {
            SetPos(Snake_x, Snake_y);
            printf("%c", ch1);
            SetPos(Snake_x - 1, Snake_y);
            wprintf(L"%lc", ch2);
            Snake_x--;
        }
        else if (Direction == RIGHT)
        {
            SetPos(Snake_x, Snake_y);
            printf("%c", ch1);
            SetPos(Snake_x + 1, Snake_y);
            wprintf(L"%lc", ch2);
            Snake_x++;
        }
        else if (Direction == UP)
        {
            SetPos(Snake_x, Snake_y);
            printf("%c", ch1);
            SetPos(Snake_x, Snake_y - 1);
            wprintf(L"%lc", ch2);
            Snake_y--;
        }
        else if (Direction == DOWN)
        {
            SetPos(Snake_x, Snake_y);
            printf("%c", ch1);
            SetPos(Snake_x, Snake_y + 1);
            wprintf(L"%lc", ch2);
            Snake_y++;
        }
        EatFood();
        if (Wall() == 0)
            return;
    }
}

void Die()
{
    system("cls");
    SetPos(1, 1);
    wprintf(L"你死了");
    SetPos(1, 2);
    wprintf(L"你的分数是%d", Num);
    SetPos(1, 3);
    system("pause");
}

int main()
{
    setlocale(LC_ALL, "");
    while (1)
    {
        Start();
        Hello();
        Map();
        Snake();
        Food();
        Mark();
        GameRun();
        Die();
    }
    return 0;
}