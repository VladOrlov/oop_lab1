#include <iostream>
#include <ctime>
#include <math.h>

#include "TextTable.h"

using namespace std;

struct function_parametrs {
    float a = 2;
    float b = 12;
    float x1 = -5;
    float x2 = 5;
    float dx = 0.5;
} params;

void Tab();
void Print();
float function(function_parametrs params, float x);
void random_array();
void fx_to_integer();

const int A = 65;
const float delta = 0.035f;
int *fx_integer;
float *rnd;
float *fx;
float Smin, Smax;
int N;

int main() {
    Tab();
    cout << endl;
    random_array();
    cout << endl;
    Print();
    cout << endl;

    return 0;
}

void Print() {
    fx_to_integer();
    cout << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < fx_integer[i]; j++) {
            cout << "\u0333";
        }
        cout << endl;
    }
    cout << endl;
}


void fx_to_integer() {
    fx_integer = new int[N];
    for (int i = 0; i < N; i++) {
        int y = round(fx[i]);
        if (y < 0)
            y = 0;
        else if (y > 65)
            y = 65;
        fx_integer[i] = y;
    }
}

void random_array() {
    printf("\nSmax = %.3f\tSmin = %.3f\n", Smax, Smin);
    srand((unsigned) time(0));
    rnd = new float[N];
    float step = Smax * delta;
    int n = (int) ((Smax - Smin) / step);

    TextTable textTable( '-', '|', '+' );
    textTable.add( "N" );
    textTable.add( "f(x)" );
    textTable.endOfRow();

    for (int i = 0; i < N; i++) {
        rnd[i] = ((rand() % (n + 1)) * step) + Smin;
        textTable.add(to_string(i + 1));
        textTable.add(to_string(rnd[i]));
        textTable.endOfRow();
    }
    textTable.setAlignment(2, TextTable::Alignment::RIGHT);
    std::cout << textTable;
}

void Tab() {
    N = (int) ((params.x2 - params.x1) / params.dx) + 1;
    fx = new float[N];

    float x = params.x1;
    float S1, S2;
    S1 = S2 = 0;

    TextTable textTable('-', '|', '+');
    textTable.add("x");
    textTable.add("N");
    textTable.add("f(x)");
    textTable.endOfRow();

    for (int i = 0; i < N; i++) {

        float y = function(params, x);
        fx[i] = y;
        textTable.add(to_string(x));
        textTable.add(to_string(i+1));
        textTable.add(to_string(y));
        textTable.endOfRow();

        x += params.dx;
        if (y > 0) {
            S1 += y;
        }
        if ((i + 1) % 2 == 1) {
            S2 += y;
        }
    }

    textTable.setAlignment(2, TextTable::Alignment::RIGHT);
    std::cout << textTable;

    if (S1 > S2) {
        Smax = S1;
        Smin = S2;
    } else {
        Smin = S1;
        Smax = S2;
    }
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