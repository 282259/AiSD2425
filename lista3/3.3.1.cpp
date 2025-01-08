#include <iostream>
#include <cstdlib>
#include <climits>
#include <chrono>
using namespace std;
using namespace std::chrono;

void S_RECURSIVE_ACTIVITY_SELECTOR(int s[], int f[], int k, int result[], int &q) {
    int m = k - 1;
    while (m > 0 && f[m] >= s[k]) {
        m--;
    }
    if (m > 0) {
        result[q++] = m;
        S_RECURSIVE_ACTIVITY_SELECTOR(s, f, m, result, q);
    }
}

void PRINT_R_A_S(int s[], int f[], int n) {
    int result[n];
    int q = 0;

    S_RECURSIVE_ACTIVITY_SELECTOR(s, f, n, result, q);

    cout << "Wybrane zajecia (rekurencyjnie): ";
    for (int i = q - 1; i >= 0; i--) {
        cout << "(" << s[result[i]] << ", " << f[result[i]] << ") ";
    }
    cout << endl;
}

void S_ACTIVITY_SELECTOR(int s[], int f[], int n, int result[], int &q) {
    result[q++] = n - 1;
    int k = n - 1;
    for (int m = n - 1; m >= 1; m--) {
        if (f[m] <= s[k]) {
            result[q++] = m;
            k = m;
        }
    }
}

void PRINT_A_S(int s[], int f[], int n) {
    int result[n];
    int q = 0;

    S_ACTIVITY_SELECTOR(s, f, n, result, q);

    cout << "Wybrane zajecia (iteracyjnie): ";
    for (int i = q - 1; i >= 0; i--) {
        cout << "(" << s[result[i]] << ", " << f[result[i]] << ") ";
    }
    cout << endl;
}



int last(int s[], int f[], int i) {
    for (int j = i - 1; j >= 0; j--) {
        if (f[j] <= s[i]) {
            return j;
        }
    }
    return -1;
}

void DYNAMIC_A_S(int s[], int f[], int n) {
    int dp[n];
    int prev[n];
    dp[0] = 1;
    prev[0] = 0;

    for (int i = 1; i < n; i++) {
        int k = last(s, f, i);
        if (k != -1 && dp[k] + 1 > dp[i - 1]) {
            dp[i] = dp[k] + 1;
            prev[i] = i;
        } else {
            dp[i] = dp[i - 1];
            prev[i] = prev[i - 1];
        }
    }

    cout << "Wybrane zajecia:\n";
    int i = n - 1;
    while (i > 0) {
        if (prev[i] == i) {
            cout << "(" << s[i] << ", " << f[i] << ") ";
            i = last(s, f, i);
        } else {
            i--;
        }
    }
}

void RANDOM(int s[], int f[], int n) {
    s[0] = 0;
    f[0] = INT_MIN;
    for (int i = 1; i <= n; i++) {
        s[i] = rand() % 100;
        f[i] = s[i] + rand() % 20 + 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (s[i] > s[j]) {
                swap(s[i], s[j]);
                swap(f[i], f[j]);
            }
        }
    }
}


int main() {
    srand(time(0));
    int wielkosci[] = {100, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (int n : wielkosci) {
        int s[n + 1];
        int f[n + 1];

        RANDOM(s,f, n);


        cout << "Rozmiar danych: " << n << endl;

        // Rekurencyjne z F
        int result1[n];
        int q1 = 0;
        auto start_rec_f = high_resolution_clock::now();
        S_RECURSIVE_ACTIVITY_SELECTOR(s, f, n, result1, q1);
        auto stop_rec_f = high_resolution_clock::now();
        auto duration_rec_f = duration_cast<microseconds>(stop_rec_f - start_rec_f);
        cout << "Czas rekursji (f[] posortowana): " << duration_rec_f.count() << " mikrosekund" << endl;

        // Iteracyjne z F
        int result2[n];
        int q2 = 0;
        auto start_iter_f = high_resolution_clock::now();
        S_ACTIVITY_SELECTOR(s, f, n, result2, q2);
        auto stop_iter_f = high_resolution_clock::now();
        auto duration_iter_f = duration_cast<microseconds>(stop_iter_f - start_iter_f);
        cout << "Czas iteracji (f[] posortowana): " << duration_iter_f.count() << " mikrosekund" << endl;



        cout << endl;
    }

    return 0;
}
