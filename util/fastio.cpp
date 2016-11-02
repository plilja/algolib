#include "stdio.h"

/**
 * Marginally faster way to read integers than scanf. Usable 
 * on problems with really big input. Should probably not be
 * used for anything but programming puzzles.
 */
int readInt() {
    int c = getchar_unlocked();
    int x = 0;
    // look for minus sign
    for (; (c < '0' || c > '9') && c != '-'; c = getchar_unlocked()) {
    }

    bool neg = false;
    if (c == '-') {
        neg = true;
        c = getchar_unlocked();
    }

    // read digits part
    for (; c >= '0' && c <= '9'; c = getchar_unlocked()) { 
        x = 10 * x + c - 48; 
    }

    if (neg) {
        x = -x;
    }

    return x;
}

/**
 * Marginally faster way to print integers than printf. Usable 
 * on problems that require lots of output. Should probably not be
 * used for anything but programming puzzles.
 */
inline void printInt(int x) {
    if (x == 0) {
        putchar_unlocked('0');
        return;
    }
    long long x_ = x; // avoid overflow for min int
    if (x_ < 0) {
        putchar_unlocked('-');
        x_ = -x_;
    }
    long long rev = x_;

    // calculate how many zeroes that end the number
    int zeros = 0;
    while (rev % 10 == 0) {
        rev /= 10;
        ++zeros;
    }

    // Reverse number and put result in rev
    rev = 0;
    while (x_) {
        rev = 10 * rev + x_ % 10;
        x_ /= 10;
    }

    while (rev) {
        putchar_unlocked('0' + rev % 10);
        rev /= 10;
    }
    while(zeros--) {
        putchar_unlocked('0');
    }
}

inline void printSpace() {
    putchar_unlocked(' ');
}

inline void printNewLine() {
    putchar_unlocked('\n');
}
