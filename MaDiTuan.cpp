#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cstring>
#include "graphics.h"   //Sử dụng để biểu diện bàn cờ
#define MAX 10
#pragma comment(lib, "graphics.lib")
using namespace std;

//Biến dùng cho thuật toán
int A[MAX][MAX] = { 0 };
int X[8] = { -2,-2,-1,-1, 1, 1, 2, 2 };   //1 quân ngựa có nhiêu nhất 8 cách đi 
int Y[8] = { -1, 1,-2, 2,-2, 2,-1, 1 };
int step = 0;//thứ tự bước đi
int n; //kích thước bàn cờ (boardsize)

int squareSize = 50;

void Output() { //Xuất từng tọa độ đường đi
    for (int k = 1; k <= n * n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
            {
                if (A[i][j] == k)
                {
                    cout << "A(" << i << ", " << j << ")," << "  ";
                }
            }
        }
    }
    cout << endl;
}

void GiaoDien() {      //Giao Diện Bàn Cờ

    //Bàn cờ n*n
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = j * squareSize;
            int y = i * squareSize;
            if ((i + j) % 2 == 0) {
                setfillstyle(SOLID_FILL, BROWN);
            }
            else {
                setfillstyle(SOLID_FILL, BLACK);
            }
            bar(x, y, x + squareSize, y + squareSize);
        }
    }
    for (int k = 1; k <= n * n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
            {
                if (A[i][j] == k)
                {
                    // Vẽ quân mã tại vị trí (i, j)
                    setfillstyle(SOLID_FILL, RED);   //Màu đỏ là đang xét
                    int knightX = i * squareSize + squareSize / 2;
                    int knightY = j * squareSize + squareSize / 2;
                    fillellipse(knightX, knightY, squareSize / 4, squareSize / 4);
                    Sleep(800);
                    setfillstyle(SOLID_FILL, WHITE); //Màu trắng là xét xong vị trí hiện tại
                    fillellipse(knightX, knightY, squareSize / 4, squareSize / 4);

                    //Đánh dấu thứ tự vào ô đã xét
                    stringstream ss;
                    ss << A[i][j];
                    string strNumber = ss.str();
                    char charNumber[100];
                    strcpy_s(charNumber, sizeof(charNumber), strNumber.c_str()); // Sao chép chuỗi từ strNumber vào charNumber
                    outtextxy(i * squareSize + squareSize / 9, j * squareSize + squareSize / 9, charNumber);
                }
            }
        }
    }
    getch();
    closegraph();
}

void Move(int x, int y) {
    ++step;   //Tăng bước đi
    A[x][y] = step;    //Đánh dấu đã đi vào ô này
    for (int i = 0; i < 8; i++) {
        if (step == n * n) {   //Kiểm tra quân mã đã đi hết bàn cờ chưa
            cout << "\nToa do cac diem lan luot la: " << endl;
            Output();
            GiaoDien();
            exit(0);
        }
        int u = x + X[i];
        int v = y + Y[i];
        if (u >= 0 && u < n && v >= 0 && v < n && A[u][v] == 0)   //Ràng buộc
            Move(u, v);
    }
    --step;   //Trả lại bước đi trước đó
    A[x][y] = 0;  //Trả lại trạng thái ô trước đó
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    cout << "Nhap kich thuoc ban co (boardsize) = ";
    cin >> n;
    int a, b;
    cout << "Nhap vi tri ban dau (x, y): " << endl;
    cout << "x: ";
    cin >> a;
    cout << "y: ";
    cin >> b;
    cout << "Vi tri ban dau (" << a << ", " << b << "): " << endl;
    Move(a, b);

    //Nếu không có đường đi thỏa 
    cout << "Quan Ma khong the di chuyen het ban co voi vi tri ban dau: x = " << a << ", y = " << b << endl;

    return 0;
}