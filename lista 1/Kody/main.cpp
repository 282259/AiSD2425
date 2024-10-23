#include <iostream>
#include <climits>
using namespace std;
int liczbaPrzypisan = 0;
int liczbaPorownan = 0;
//zad.1
void INSERTION_SORT(int A[], int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        liczbaPrzypisan++;
        int j = i - 1;

        while (j >= 0 && A[j] > key) {
            liczbaPorownan++;
            A[j + 1] = A[j];
            liczbaPrzypisan++;
            j--;
        }
        A[j + 1] = key;
        liczbaPrzypisan++;
    }
}

void MODIFIED_INSERTION_SORT(int A[], int n) {
    for (int i = 1; i < n-1; i += 2) {
        int pierwszy = A[i];
        int drugi = A[i+1];
        liczbaPrzypisan +=2;
        if (pierwszy > drugi) {
            liczbaPorownan++;
            swap(pierwszy, drugi);
            liczbaPrzypisan += 2;
        }

        int j = i - 1;
        while (j >= 0 && A[j] > pierwszy) {
            liczbaPorownan++;
            A[j+1] = A[j];
            liczbaPrzypisan++;
            j--;
        }
        A[j+1] = pierwszy;
        liczbaPrzypisan++;

        j = i;
        while (j >= 0 && A[j] > drugi) {
            liczbaPorownan++;
            A[j+1] = A[j];
            liczbaPrzypisan++;
            j--;
        }
        A[j+1] = drugi;
        liczbaPrzypisan++;
    }

    if (n % 2 == 0) {
        liczbaPorownan++;
        int ostatni = A[n - 1];
        liczbaPrzypisan++;
        int j = n - 2;
        while (j >= 0 && A[j] > ostatni) {
            liczbaPorownan++;
            A[j + 1] = A[j];
            liczbaPrzypisan++;
            j--;
        }
        A[j + 1] = ostatni;
        liczbaPrzypisan++;
    }
}
//zad.2
void MERGE(int A[], int p, int s, int k) {
    int n1 = s - p + 1;
    int n2 = k - s;
    int L[n1 + 1];
    int P[n2 + 1];

    for (int i = 0; i < n1; i++) {
        L[i] = A[i+p];
        liczbaPrzypisan++;
    }
    for (int j = 0 ; j < n2; j++) {
        P[j] = A[s+1+j];
        liczbaPrzypisan++;
    }

    L[n1] = INT_MAX;
    P[n2] = INT_MAX;
    liczbaPrzypisan += 2;

    int i = 0;
    int j = 0;

    for (int l = p; l <= k; l++) {

        if (P[j] <= L[i]) {
            A[l] = P[j];
            liczbaPorownan++;
            liczbaPrzypisan++;
            j++;
        }
        else {
            A[l] = L[i];
            liczbaPorownan++;
            liczbaPrzypisan++;
            i++;
        }
    }

}
void MERGE_SORT(int A[], int p, int k){
    if (p < k){
        liczbaPorownan++;
        int s = (p+k)/ 2;
        MERGE_SORT(A, p, s);
        MERGE_SORT(A, s + 1, k);
        MERGE(A, p, s, k);


    }
}
void MODIFIED_MERGE( int A[], int p, int s1, int s2,int k ){
    int n1 = s1 - p + 1;
    int n2 = s2 - s1;
    int n3 = k - s2;

    int L[n1 + 1], M[n2 + 1], P[n3 + 1];

    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
        liczbaPrzypisan++;
    }
    for (int i = 0; i < n2; i++) {
        M[i] = A[s1 + 1 + i];
        liczbaPrzypisan++;
    }
    for (int i = 0; i < n3; i++) {
        P[i] = A[s2 + 1 + i];
        liczbaPrzypisan++;
    }

    L[n1] = INT_MAX;
    M[n2] = INT_MAX;
    P[n3] = INT_MAX;
    liczbaPrzypisan += 3;

    int i = 0, j = 0, l = 0;

    for (int x = p; x <= k; x++) {
        if (L[i] <= M[j] && L[i] <= P[l]) {
            liczbaPorownan++;
            A[x] = L[i];
            liczbaPrzypisan++;
            i++;
        } else if (M[j] <= L[i] && M[j] <= P[l]) {
            liczbaPorownan++;
            A[x] = M[j];
            liczbaPrzypisan++;
            j++;
        } else {
            liczbaPorownan++;
            A[x] = P[l];
            liczbaPrzypisan++;
            l++;
        }
    }

}
void MODIFIED_MERGE_SORT(int A[], int p, int k) {
    if (p < k) {
        liczbaPorownan++;
        int s1 = p + (k - p) / 3;
        int s2 = p + 2 * (k - p) / 3;

        MODIFIED_MERGE_SORT(A, p, s1);
        MODIFIED_MERGE_SORT(A, s1 + 1, s2);
        MODIFIED_MERGE_SORT(A, s2 + 1, k);
        MODIFIED_MERGE(A, p, s1, s2, k);
    }
}

//zad.3
int LEFT(int i) {
    return 2 * i+ 1;
}

int RIGHT(int i) {
    return 2 * i + 2;
}


void HEAPIFY(int A[], int n, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = i;

    if (l < n && A[l] > A[largest]) {
        liczbaPorownan++;
        liczbaPrzypisan++;
        largest = l;
    }

    if (r < n && A[r]> A[largest]){
        liczbaPorownan++;
        liczbaPrzypisan++;
        largest = r;
    }

    if (largest != i) {
        liczbaPorownan++;
        swap(A[i], A[largest]);
        liczbaPrzypisan += 2;
        HEAPIFY(A, n, largest);
    }
}

void BUILD_HEAP(int A[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--){
        HEAPIFY(A, n, i);
    }
}

void HEAP_SORT(int A[], int n) {
    BUILD_HEAP(A, n);
    for (int i = n - 1; i > 0; i--) {
        swap(A[0], A[i]);
        liczbaPrzypisan += 2;
        HEAPIFY(A, i, 0);
    }
}


int LEFT1(int i) {
    return 3 * i +1;
}

int MIDDLE1(int i) {
    return 3 * i + 2;
}

int RIGHT1(int i) {
    return 3 * i + 3;
}

void MODIFIED_HEAPIFY(int A[], int n, int i) {
    int l = LEFT1(i);
    int m = MIDDLE1(i);
    int r = RIGHT1(i);
    int largest = i;

    if (l < n && A[l] > A[largest])  {
        liczbaPorownan++;
        liczbaPrzypisan++;
        largest = l;

    }

    if (m < n && A[m] > A[largest]) {
        liczbaPorownan++;
        liczbaPrzypisan++;
        largest = m;

    }

    if (r < n && A[r] > A[largest]) {
        liczbaPorownan++;
        liczbaPrzypisan++;
        largest = r;
    }

    if (largest != i) {
        swap(A[i], A[largest]);
        liczbaPorownan++;
        liczbaPrzypisan += 2;
        MODIFIED_HEAPIFY(A, n, largest);
    }
}

void MODIFIED_BUILD_HEAP(int A[], int n) {
    for (int i = n / 3 - 1; i >= 0; i--){
        MODIFIED_HEAPIFY(A, n, i);
    }
}

void MODIFIED_HEAP_SORT(int A[], int n) {
    MODIFIED_BUILD_HEAP(A, n);

    for (int i = n - 1; i > 0; i--) {
        swap(A[0], A[i]);
        liczbaPrzypisan += 2;
        MODIFIED_HEAPIFY(A, i, 0);
    }
}


// Funkcja do generowania losowych tablic
void RandomArray(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 1000;
    }
}

void printResults(int n) {
    int A[n], B[n], C[n], D[n], E[n], F[n], G[n], H[n];
    RandomArray(A, n);


    for (int i = 0; i < n; i++) {
        B[i] = C[i] = D[i] = E[i] = F[i] = G[i] = H[i] = A[i];
    }

    // INSERTION_SORT
    liczbaPorownan = 0;
    liczbaPrzypisan = 0;
    INSERTION_SORT(A, n);
    cout << "INSERTION_SORT - Dlugosc tablicy: " << n << endl;
    cout << "Liczba porównañ: " << liczbaPorownan << endl;
    cout << "Liczba przypisañ: " << liczbaPrzypisan << endl;

    // MODIFIED_INSERTION_SORT
    liczbaPorownan = 0;
    liczbaPrzypisan = 0;
    MODIFIED_INSERTION_SORT(B, n);
    cout << "MODIFIED_INSERTION_SORT - Dlugosc tablicy: " << n << endl;
    cout << "Liczba porównañ: " << liczbaPorownan << endl;
    cout << "Liczba przypisañ: " << liczbaPrzypisan << endl;

    // MERGE_SORT
    liczbaPorownan = 0;
    liczbaPrzypisan = 0;
    MERGE_SORT(C, 0, n - 1);
    cout << "MERGE_SORT - Dlugosc tablicy: " << n << endl;
    cout << "Liczba porównañ: " << liczbaPorownan << endl;
    cout << "Liczba przypisañ: " << liczbaPrzypisan << endl;

    // MODIFIED_MERGE_SORT
    liczbaPorownan = 0;
    liczbaPrzypisan = 0;
    MODIFIED_MERGE_SORT(D, 0, n - 1);
    cout << "MODIFIED_MERGE_SORT - Dlugosc tablicy: " << n << endl;
    cout << "Liczba porównañ: " << liczbaPorownan << endl;
    cout << "Liczba przypisañ: " << liczbaPrzypisan << endl;

    // HEAP_SORT
    liczbaPorownan = 0;
    liczbaPrzypisan = 0;
    HEAP_SORT(E, n);
    cout << "HEAP_SORT - Dlugosc tablicy: " << n << endl;
    cout << "Liczba porównañ: " << liczbaPorownan << endl;
    cout << "Liczba przypisañ: " << liczbaPrzypisan << endl;

    // MODIFIED_HEAP_SORT
    liczbaPorownan = 0;
    liczbaPrzypisan = 0;
    MODIFIED_HEAP_SORT(F, n);
    cout << "MODIFIED_HEAP_SORT - Dlugosc tablicy: " << n << endl;
    cout << "Liczba porównañ: " << liczbaPorownan << endl;
    cout << "Liczba przypisañ: " << liczbaPrzypisan << endl;

    cout << "------------------------------------" << endl;
}

int main() {


    int sizes[] = {5, 10, 100, 200, 400, 600, 800, 1000};

    for (int i = 0; i < 8; i++) {
        printResults(sizes[i]);
    }

    return 0;
}
