// Example input for the preprocessor
#define PI 3.14
#define SQUARE(x) ((x) * (x))
#include "myheader.h"

/* This comment should be removed. */
int main(void)
{
    int a = 10;
    int b = 5;

    int sum = a + b;
    int difference = a - b;
    int product = a * b;

    int value = DOUBLE(7);

    return (sum == 15 && difference == 5 &&
            product == 50 && value == 14) ? 0 : 1;
}
