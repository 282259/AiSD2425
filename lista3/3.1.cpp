#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int CUT_ROD(int p[], int n) {
    if (n == 0) {
        return 0;
    }
    int q = INT_MIN;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i-1] + CUT_ROD(p, n - i));
    }
    return q;
}

int MEMORIZED_CUT_ROD(int p[], int r[], int n) {
    if (r[n] >= 0) {
        return r[n];
    }
    if (n == 0) {
        r[n] = 0;
    } else {
        int q = INT_MIN;
        for (int i = 1; i <= n; i++) {
            q = max(q, p[i-1] + MEMORIZED_CUT_ROD(p, r, n - i));
        }
        r[n] = q;
    }
    return r[n];
}

int EXT_BOT_UP_CUT_ROD(int p[], int r[], int s[], int n) {
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++) {
            if (q < p[i-1] + r[j - i]) {
                q = p[i-1] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    return r[n];
}

void PRINT_MEMORIZED_SOLUTION(int p[], int n) {
    int* r = new int[n + 1];
    fill(r, r + n + 1, -1);

    int maxProfit = MEMORIZED_CUT_ROD(p, r, n);
    cout << "Maksymalny zysk: " << maxProfit << endl;

    cout << "Podzial: ";
    while (n > 0) {
        for (int i = 1; i <= n; i++) {
            if (r[n] == p[i-1] + r[n - i]) {
                cout << i << " ";
                n -= i;
                break;
            }
        }
    }
    cout << endl;

    delete[] r;
}

void PRINT_EXT_SOLUTION(int p[], int n) {
    int* r = new int[n + 1];
    int* s = new int[n + 1];

    EXT_BOT_UP_CUT_ROD(p, r, s, n);

    cout << "Maksymalny zysk: " << r[n] << endl;

    cout << "Podzial: ";
    while (n > 0) {
        cout << s[n] << " ";
        n -= s[n];
    }
    cout << endl;

    delete[] r;
    delete[] s;
}

int main() {
    const int n = 5;
    int p[n] = { 9, 10, 10, 10, 12};

    int rodLength = 3;
    cout << "Maksymalny zysk (CUT_ROD): " << CUT_ROD(p, rodLength) << endl;
    cout << "Dla dlugosci: " << rodLength << endl;
    PRINT_MEMORIZED_SOLUTION(p, rodLength);

    PRINT_EXT_SOLUTION(p, rodLength);

    return 0;
}

