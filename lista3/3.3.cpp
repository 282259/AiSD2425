#include <iostream>
#include <cstdlib>
#include <climits>
#include <chrono>
using namespace std;
using namespace std::chrono;

void F_RECURSIVE_ACTIVITY_SELECTOR(int s[],int f[], int n, int k, int result[], int& q) {
    int m = k + 1;
    while (m <= n && s[m] < f[k]) {
        m++;
    }
    if (m <= n) {
        result[q++] = m;
        F_RECURSIVE_ACTIVITY_SELECTOR(s, f, n, m, result, q);
    }
}
void PRINT_F_A_R(int s[], int f[], int n) {
    int result[n];
    int q = 0;

    F_RECURSIVE_ACTIVITY_SELECTOR(s, f, n, 0, result, q);

    cout << "Wybrane zajecia (rekurencyjnie z F): ";
    for (int i = 0; i < q; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}
void F_ACTIVITY_SELECTOR(int s[], int f[], int n, int result[], int& q) {
    result[q++] = 1;
    int k = 1;

    for (int m = 2; m <= n; ++m) {
        if (s[m] >= f[k]) {
            result[q++] = m;
            k = m;
        }
    }
}
void PRINT_F_A_I(int s[], int f[], int n) {
    int result[n];
    int q = 0;

    F_ACTIVITY_SELECTOR(s, f, n, result, q);

    cout << "Wybrane zajecia (iteracyjnie z F): ";
    for (int i = 0; i < q; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}


void RANDOM_S(int s[], int n) {
    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        s[i] = rand() % (n * 2);
    }
}
void SORTED_F(int s[], int f[], int n) {
    f[0] = INT_MIN;
    for (int i = 1; i <= n; i++) {
        f[i] = s[i] + rand() % 100 + 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (f[i] > f[j]) {
                swap(f[i], f[j]);
                swap(s[i], s[j]);
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

        RANDOM_S(s, n);
        SORTED_F(s, f, n);

        cout << "Rozmiar danych: " << n << endl;

        // Rekurencyjne z F
        int result1[n];
        int q1 = 0;
        auto start_rec_f = high_resolution_clock::now();
        F_RECURSIVE_ACTIVITY_SELECTOR(s, f, n, 0, result1, q1);
        auto stop_rec_f = high_resolution_clock::now();
        auto duration_rec_f = duration_cast<microseconds>(stop_rec_f - start_rec_f);
        cout << "Czas rekursji (f[] posortowana): " << duration_rec_f.count() << " mikrosekund" << endl;

        // Iteracyjne z F
        int result2[n];
        int q2 = 0;
        auto start_iter_f = high_resolution_clock::now();
        F_ACTIVITY_SELECTOR(s, f, n, result2, q2);
        auto stop_iter_f = high_resolution_clock::now();
        auto duration_iter_f = duration_cast<microseconds>(stop_iter_f - start_iter_f);
        cout << "Czas iteracji (f[] posortowana): " << duration_iter_f.count() << " mikrosekund" << endl;


        cout << endl;
    }

    return 0;
}


