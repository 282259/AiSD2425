#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

int liczbaPrzypisan = 0;
int liczbaPorownan = 0;

void COUNTING_SORT(int A[], int n, int k, int d) {
    int C[d] = {0};
    int B[n];

    for (int i = 0; i < n; i++) {
        int digit = (A[i] / k) % d;
        liczbaPrzypisan++; /
        C[digit]++;
    }

    for (int i = 1; i < d; i++) {
        C[i] += C[i - 1];
        liczbaPrzypisan++;
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (A[i] / k) % d;
        B[C[digit] - 1] = A[i];
        C[digit]--;
        liczbaPrzypisan += 2;
    }

    for (int i = 0; i < n; i++) {
        A[i] = B[i];
        liczbaPrzypisan++;
    }
}

void RADIX_SORT(int A[], int n, int d) {
    int maxVal = *max_element(A, A + n);
    for (int k = 1; maxVal / k > 0; k *= d) {
        COUNTING_SORT(A, n, k, d);
    }
}

void RADIX_SORT_WITH_NEGATIVES(int A[], int n, int d) {
    int negative_count = 0, positive_count = 0;

    for (int i = 0; i < n; i++) {
        if (A[i] < 0) {
            negative_count++;
        } else if (A[i] > 0) {
            positive_count++;
        }
        liczbaPorownan++;
    }

    int negatives[negative_count], positives[positive_count];
    int neg_index = 0, pos_index = 0;


    for (int i = 0; i < n; i++) {
        if (A[i] < 0) {
            negatives[neg_index++] = -A[i];
            liczbaPrzypisan++;
        } else {
            positives[pos_index++] = A[i];
            liczbaPrzypisan++;
        }
        liczbaPorownan++;
    }


    if (positive_count > 0) {
        RADIX_SORT(positives, positive_count, d);
        liczbaPorownan++;
    }
    if (negative_count > 0) {
        RADIX_SORT(negatives, negative_count, d);
        liczbaPorownan++;
    }


    int index = 0;
    for (int i = negative_count - 1; i >= 0; i--) {
        A[index++] = -negatives[i];
        liczbaPrzypisan++;
    }

    for (int i = 0; i < positive_count; i++) {
        A[index++] = positives[i];
        liczbaPrzypisan++;
    }
}

int* tablica(int n) {
    srand(time(0));
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        A[i] = (rand() % 100);
    }
    return A;
}

int main() {
    int dlugosci[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};


    for (int n : dlugosci) {
        int* A = tablica(n);

        liczbaPrzypisan = 0;
        liczbaPorownan = 0;


        RADIX_SORT(A, n, 8); // Sortowanie przy u¿yciu Radix Sort z podstaw¹ 8


        cout << "Dlugosc tablicy: " << n << endl;
        cout << "Przypisania: " << liczbaPrzypisan << endl;
        cout << "Porownania: " << liczbaPorownan << endl;

        delete[] A;
    }

    return 0;
}
