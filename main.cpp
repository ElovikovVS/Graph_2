//#define _WIN32_WINNT 0x0500
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
#include <wincon.h>
#define NMAX 100

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    int A[NMAX][NMAX];
    scanf ("%d",&n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf ("%d",&A[i][j]);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf (" %5d ",A[i][j]);
        printf("\n");
    }

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                if (A[i][j] > (A[i][k] + A[k][j])) A[i][j] = A[i][k] + A[k][j];
        }
    }

    printf("\n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf (" %5d ",A[i][j]);
        printf("\n");
    }

    int sum,result,mincolumn;
    for (int i = 0; i < n; ++i)
        result += A[0][i];

    for (int i = 1; i < n; ++i)
    {
        sum = 0;
        for (int j = 0; j < n; ++j)
            sum += A[i][j];
        if (result > sum)
        {
            result = sum;
            mincolumn = i;
        }
    }
    //
    //
    int **C;
    C = (int**)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        C[i] = (int*)malloc(2 * sizeof(int));
    }

    char str[3], str1[3]; //строка в которую поместим номер вершины
    int ox = 300, oy = 300; // координаты центра консоли
    int R = 270; // радиус описанной около многоугольника окружности

    for (int i = 0; i < n; i++)
    {
        C[i][0] = cos(i * 2 * 3.14 / n)*R + ox; //координата х
        C[i][1] = sin(i * 2 * 3.14 / n)*R + oy; //координата у
    }

    HDC hDC = GetDC(GetConsoleWindow());
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    HPEN Pen1 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

    printf("Нарисовать граф?(y/n)");
    char yes_or_no;
    scanf("%c", &yes_or_no);

    switch (yes_or_no)
    {
    case 'y':
    //Графика
    system("cls");
    system("mode con cols=125 lines=100");

    while (true)
    {
        SelectObject(hDC, Pen);
        for (int i = 0; i < n; i++)
            Ellipse(hDC, C[i][0] - 4, C[i][1] - 4, C[i][0] + 4, C[i][1] + 4);
        for (int i = 0; i < n; i++)
        {
            sprintf(str, "%d", i + 1);//переводим номер вер. i+1 типа int в str типа char[]
            SetTextColor(hDC, RGB(255, 255, 255)); //Цвет текста
            SetBkColor(hDC, RGB(1, 200, 100)); //Цвет фона
            TextOutA(hDC, C[i][0] - 4, C[i][1] - 22, str, strlen(str));
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (A[i][j] != 0)
                {
                    MoveToEx(hDC, C[i][0], C[i][1], NULL);
                    LineTo(hDC, C[j][0], C[j][1]);
                }
            }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (A[i][j] != 0)
                {
                    sprintf(str1, "%d", A[i][j]);
                    //Цвет текста
                    SetTextColor(hDC, RGB(255, 255, 255));
                    //Цвет фона
                    SetBkColor(hDC, RGB(0, 0, 0));
                    //Подписываем ребро примерно в середине
                    TextOutA(hDC, (C[i][0] + C[j][0]) / 2 - 3, (C[i][1] + C[j][1]) / 2 + 3, str1, strlen(str1));
                }
            }
    }
    break;

    default:
    break;
    }

    //
    //
    printf("\n mincolumn = %d\n",mincolumn);
    system ("pause");
    return 0;
}
