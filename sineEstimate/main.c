#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265

double sineEstimate(double theta, int n);
double cosineEstimate(double theta, int n);
long int factorial(int n);
//int pow(int base, int exponent);
//double fmod(double a, double b);

// Maclaurin series: f(x) = f(0) + f'(0)x + f''(0)x^2 / 2! + f'''(0)x^3 / 3! + ...


int main(void) {
    int trueCount = 0;
    int falseCount = 0;
    for (int i = 0; i < 360; i++) {
        if (sineEstimate(i, 10) >= sin(i) - 0.0001 && sineEstimate(i, 10) <= sin(i) + 0.0001 ? 1 : 0) {
            //printf("%d: true (sin: %f, est: %f)\n", i, sin(i), sineEstimate(i, 10));
            trueCount++;
        } else {
            //printf("%d: false (sin: %f, est: %f)\n", i, sin(i), sineEstimate(i, 10));
            falseCount++;
        }
    }
    printf("%d%% correct\n", (trueCount * 100) / (trueCount + falseCount));

    trueCount = 0;
    falseCount = 0;
    for (int i = 0; i < 360; i++) {
        if (cosineEstimate(i, 10) >= cos(i) - 0.0001 && cosineEstimate(i, 10) <= cos(i) + 0.0001 ? 1 : 0) {
            //printf("%d: true (cos: %f, est: %f)\n", i, cos(i), cosineEstimate(i, 10));
            trueCount++;
        } else {
            //printf("%d: false (cos: %f, est: %f)\n", i, cos(i), cosineEstimate(i, 10));
            falseCount++;
        }
    }
    printf("%d%% correct\n", (trueCount * 100) / (trueCount + falseCount));
    /*double theta = 183;
    printf("sineEstimate(0, 10) = %lf\n", sineEstimate(theta, 10));
    printf("sin(0) = %f\n", sin(theta));

    printf("cosineEstimate(0, 10) = %lf\n", cosineEstimate(theta, 10));
    printf("cos(0) = %f\n", cos(theta));*/

    return 0;
}

// gcc main.c -o main && ./main

// theta: angle in degrees
// n: number of terms or granularity of function
// returns: the estimated value of sine
//
// This function estimates the value of sine using the Maclaurin series (can also use Taylor series).
// The Maclaurin series for sine is given by the following formula:
// sin(x) = x - x^3 / 3! + x^5 / 5! - x^7 / 7! + ...
double sineEstimate(double theta, int n) {
    // Reduce the angle to the range [-pi, pi]
    while (theta > PI) {
        theta -= 2 * PI;
    }
    while (theta < -PI) {
        theta += 2 * PI;
    }

    double sum = 0.0;
    double term = theta;
    double thetaSquared = theta * theta;
    double sign = 1.0;

    // Use the Taylor series expansion of sine function
    for (int i = 1; i <= n; i++) {
        sum += sign * term;
        sign *= -1.0;
        // instead of calculating a factorial (x^(2n+1) / (2n+1)!), we can multiply the previous term by x^2 / ((2 * i) * (2 * i + 1))
        // this is more efficient than calculating the factorial
        // eg:
        // 3! = 3 * 2 * 1 = 3 * 2
        // x^3 / 3! = x^3 / (3 * 2)
        // x^3 / (3 * 2) = x * x^2 / (3 * 2)
        //
        // x * x^2 / (3 * 2) = x^3 / 3!
        //
        // so, we can now replace x * x^2 / (3 * 2) with theta * thetaSquared / ((2 * i) * (2 * i + 1))
        term *= thetaSquared / ((2 * i) * (2 * i + 1));
    }

    return sum;
}

// theta: angle in degrees
// n: number of terms or granularity of function
// returns: the estimated value of cosine
//
// This function estimates the value of cosine using the Maclaurin series (can also use Taylor series).
// The Maclaurin series for cosine is given by the following formula:
// cos(x) = 1 - x^2 / 2! + x^4 / 4! - x^6 / 6! + ...
double cosineEstimate(double theta, int n) {
    // Reduce the angle to the range [-pi, pi]
    while (theta > PI) {
        theta -= 2 * PI;
    }
    while (theta < -PI) {
        theta += 2 * PI;
    }

    double sum = 0.0;
    double term = 1.0;
    double thetaSquared = theta * theta;
    double sign = 1.0;

    // Use the Taylor series expansion of cosine function
    for (int i = 1; i <= n; i++) {
        sum += sign * term;
        sign *= -1.0;
        // this is basically the same as the sine function, but we start at 1 instead of 0
        // we also multiply the previous term by x^2 / ((2 * i - 1) * (2 * i)) instead of x^2 / ((2 * i) * (2 * i + 1))
        // this is because the cosine is the derivative of the sine function
        term *= thetaSquared / ((2 * i - 1) * (2 * i));
    }

    return sum;
}

// n: the number to find the factorial of
// returns: the factorial of n
// idk what the function for factorials are for math.h
long int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// base: the base number
// exponent: the exponent
// returns: base raised to the power of exponent
/*int pow(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

// a: the dividend
// b: the divisor
double fmod(double a, double b) {
    double frac = a / b;
    int floor = frac > 0 ? (int)frac : (int)(frac - 0.9999999999999999);
    return (a - b * floor);
}*/