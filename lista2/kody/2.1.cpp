#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;
int liczbaPrzypisan = 0;
int liczbaPorownan = 0;

int PARTITION(double A[], int p , int k){
    double x = A[k];
    liczbaPrzypisan++;
    int i = p - 1;
    for ( int j= p; j<= k-1; j++){
        liczbaPorownan++;
        if (A[j] <= x){
            i ++;
            swap(A[i], A[j]);
            liczbaPrzypisan+=2;
        }
    }
    swap(A[k],A[i+1]);
    liczbaPrzypisan+=2;

    return i + 1;
    }
void QUICKSORT( double A[], int p, int k){
    liczbaPorownan++;
    if (p<k){
        double q = PARTITION(A,p,k);
        QUICKSORT(A,p,q-1);
        QUICKSORT(A,q+1, k);
    }
}
pair<int, int> PARTITION2(double A[], int p, int k) {

    int i = p + 1;
    int x22 = k - 1;
    int x11 = p + 1;
    liczbaPorownan++;
    if (A[p] > A[k]) {
        liczbaPrzypisan+=2;
        swap(A[p], A[k]);
    }
    double x1 = A[p];
    double x2 = A[k];
    liczbaPrzypisan+=2;


    for (i = p+1; i <= x22; i++) {
        if (A[i] < x1) {
            liczbaPorownan++;
            swap(A[i], A[x11]);
            liczbaPrzypisan+=2;
            x11++;
        } else if (A[i] > x2) {
            swap(A[i], A[x22]);
            liczbaPorownan++;
            liczbaPrzypisan+=2;
            x22--;
            i--;
        }
    }

    swap(A[p], A[x11 - 1]);
    swap(A[k], A[x22 + 1]);
    liczbaPrzypisan+=4;
    return {x11 - 1, x22 + 1};
}
void QUICKSORT2(double A[], int p, int k) {
    liczbaPorownan++;
    if (p < k) {
        pair<int, int> x = PARTITION2(A, p, k);
        int q1 = x.first;
        int q2 = x.second;

        QUICKSORT2(A, p, q1 - 1);
        QUICKSORT2(A, q1 + 1, q2 - 1);
        QUICKSORT2(A, q2 + 1, k);
    }
}



void RandomArray(double arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = static_cast<double>(rand()) / RAND_MAX;
    }
}



void printResults(int n) {
    double A[n], B[n], C[n];
    RandomArray(A, n);


    for (int i = 0; i < n; i++) {
        B[i] = C[i]= A[i];
    }
    liczbaPorownan = 0;
    liczbaPrzypisan = 0;
    QUICKSORT(A, 0, n-1);
    cout << "QUICK_SORT - Dlugosc tablicy: " << n << endl;
    cout << "Liczba porównañ: " << liczbaPorownan << endl;
    cout << "Liczba przypisañ: " << liczbaPrzypisan << endl;

    liczbaPorownan = 0;
    liczbaPrzypisan = 0;
    QUICKSORT2(B, 0, n-1);

    cout << "QUICK_SORT2 - Dlugosc tablicy: " << n << endl;
    cout << "Liczba porównañ: " << liczbaPorownan << endl;
    cout << "Liczba przypisañ: " << liczbaPrzypisan << endl;
}


int main() {
    int sizes[] = {10, 100, 200, 400, 600, 800, 1000};

    for (int i = 0; i < 7; i++) {
        printResults(sizes[i]);
    }

    cout << endl;
    return 0;
}

