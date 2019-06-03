#include <iostream>
#include <ctime>
#include <math.h>

using namespace std;

struct function_parametrs {
    float a = 2;
    float b = 12;
    float x1 = -5;
    float x2 = 5;
    float dx = 0.5;
} params;

char *DrawLine(int N);

float function(function_parametrs params, float x);

void Print_row(float x, int N, float y);

void Tab();

void RandomArray();

void FxToDecimal();

void Print();

const int A = 65;
const float delta = 0.035f;
int *fx_decimal;
float *rnd;
float *fx;
float Smin, Smax;
int N;


int main() {
    Tab();
    cout << endl;
//    system("pause");
    RandomArray();
    cout << endl;
//    system("pause");
    Print();

    cout << endl;
//    system("pause");
    return 0;
}

void Print() {
    FxToDecimal();
    cout << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < fx_decimal[i]; j++)
            cout << char(0xDB);
        cout << endl;
    }
    cout << endl;
}


void FxToDecimal() {
    fx_decimal = new int[N];
    for (int i = 0; i < N; i++) {
        int y = round(fx[i]);
        if (y < 0)
            y = 0;
        else if (y > 65)
            y = 65;
        fx_decimal[i] = y;
    }
}

void RandomArray() {
    printf("\nSmax = %.3f\tSmin = %.3f\n", Smax, Smin);
    srand((unsigned) time(0));
    rnd = new float[N];
    float step = Smax * delta;
    int n = (int) ((Smax - Smin) / step);
    printf("\n%c%.7s%c%.12s%c", 218, DrawLine(7), 194, DrawLine(12), 191);
    printf("\n%c %-5s %c %-10s %c", 179, "N", 179, "f(x)", 179);

    for (int i = 0; i < N; i++) {
        printf("\n%c%.7s%c%.12s%c", 195, DrawLine(7), 197, DrawLine(12), 180);
        rnd[i] = ((rand() % (n + 1)) * step) + Smin;
        printf("\n%c %5d %c %10.5f %c", 179, i + 1, 179, rnd[i], 179);
    }

    printf("\n%c%.7s%c%.12s%c", 192, DrawLine(7), 193, DrawLine(12), 217);
}

char *DrawLine(int N) {
    char *line = new char[N];
    for (int i = 0; i < N; i++)
        line[i] = char(196);
    return line;
}

void Tab() {
    N = (int) ((params.x2 - params.x1) / params.dx) + 1;
    fx = new float[N];

    printf("\n%c%.7s%c%.7s%c%.12s%c", 218, DrawLine(7), 194, DrawLine(7), 194, DrawLine(12), 191);
    printf("\n%c %-5s %c %-5s %c %-10s %c", 179, "x", 179, "N", 179, "f(x)", 179);
    float x = params.x1;
    float S1, S2;
    S1 = S2 = 0;

    for (int i = 0; i < N; i++) {
        printf("\n%c%.7s%c%.7s%c%.12s%c", 195, DrawLine(7), 197, DrawLine(7), 197, DrawLine(12), 180);
        float y = function(params, x);
        fx[i] = y;
        Print_row(x, i + 1, y);
        x += params.dx;
        if (y > 0)
            S1 += y;
        if ((i + 1) % 2 == 1)
            S2 += y;
    }

    printf("\n%c%.7s%c%.7s%c%.12s%c\n", 192, DrawLine(7), 193, DrawLine(7), 193, DrawLine(12), 217);
    if (S1 > S2) {
        Smax = S1;
        Smin = S2;
    } else {
        Smin = S1;
        Smax = S2;
    }
}

void Print_row(float x, int N, float y) {
    printf("\n%c %5.1f %c %5d %c %10.5f %c", 179, x, 179, N, 179, y, 179);
}

float function(function_parametrs params, float x) {
    float y;
    if (x <= 1) {
        y = params.a * pow(x, 2.0) + params.b;
    } else {
        y = (params.b - 2) / x;
    }
    return y;
}