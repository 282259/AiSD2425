
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;
int liczbaPrzypisan = 0;
int liczbaPorownan = 0;


struct Node {
    double key;
    Node* prev;
    Node* next;
    Node(double value) : key(value), prev(nullptr), next(nullptr) {}
};

struct List {
    Node* head;
    List() : head(nullptr) {}
};


void LIST_INSERT(List& L, Node* x) {
    x->next = L.head;
    x->prev = nullptr;
    if (L.head != nullptr) {
        L.head->prev = x;
        liczbaPorownan++;
    }
    L.head = x;
}


void INSERTION_SORT(List& L) {
    if (L.head == nullptr || L.head->next == nullptr) {
        return;
        liczbaPorownan++;
    }

    Node* current = L.head->next;
    liczbaPrzypisan++;

    while (current != nullptr) {
        Node* keyNode = current;
        Node* prevNode = current->prev;
        liczbaPrzypisan++;

        liczbaPorownan++;

        while (prevNode != nullptr && prevNode->key > keyNode->key) {
            swap(prevNode->key, keyNode->key);
            liczbaPrzypisan+=2;
            keyNode = prevNode;
            prevNode = prevNode->prev;
            liczbaPorownan++;
        }

        current = current->next;
        liczbaPrzypisan++;
    }
}


void BUCKET_SORT(double A[], int n) {
    List B[n];
    for (int j = 0; j < n; j++) {
        B[j] = List();
        liczbaPrzypisan++;
    }
    for (int i = 0; i < n; ++i) {
        int index = static_cast<int>((n) * A[i]);
        Node* newNode = new Node(A[i]);
        LIST_INSERT(B[index], newNode);
        liczbaPrzypisan+=2;
    }

    for (int i = 0; i < n; ++i) {
        INSERTION_SORT(B[i]);
    }

    int index = 0;
    for (int i = 0; i < n; ++i) {
        Node* current = B[i].head;
        liczbaPrzypisan++;
        while (current != nullptr) {
            A[index++] = current->key;
            current = current->next;
            liczbaPrzypisan+=2;
            liczbaPorownan++;
        }
    }

}



void BUCKET_SORT2(double A[], int n) {
    double minValue = A[0];
    double maxValue = A[0];
    liczbaPrzypisan+=2;
   for (int i = 1; i < n; i++) {
    if (A[i] < minValue) {
        liczbaPorownan++;
        liczbaPrzypisan++;
        minValue = A[i];
    }

    if (A[i] > maxValue) {
        liczbaPorownan++;
        liczbaPrzypisan++;
        maxValue = A[i];
    }
}

    double range = maxValue - minValue;
    List B[n];
    for (int j = 0; j < n; j++) {
        B[j] = List();
        liczbaPrzypisan++;
    }



    for (int i = 0; i < n; ++i) {
        int bucketIndex = static_cast<int>(((A[i] - minValue) / range) * n);
        if (bucketIndex == n) bucketIndex--;
        LIST_INSERT(B[bucketIndex], new Node(A[i]));
        liczbaPorownan++;
        liczbaPrzypisan++;
    }

    for (int j = 0; j < n; ++j) {
        INSERTION_SORT(B[j]);
    }
    int idx = 0;
    for (int j = 0; j < n; ++j) {
        Node* current = B[j].head;
        liczbaPrzypisan++;
        while (current != nullptr) {
            A[idx++] = current->key;
            Node* temp = current;
            current = current->next;
            liczbaPorownan++;
            liczbaPrzypisan+=2;

        }
    }

}




void RandomArrayBucket1(double arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = static_cast<double>(rand()) / RAND_MAX;
    }
}

void RandomArrayBucket2(double arr[], int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = (rand() % 20000 - 10000) / 100.0; /
    }
}

void BucketSort1(int size) {
    double* arr = new double[size];
    RandomArrayBucket1(arr, size);

    liczbaPorownan = 0;
    liczbaPrzypisan = 0;

    BUCKET_SORT(arr, size);

    cout << "BUCKET_SORT - Rozmiar tablicy: " << size << endl;
    cout << "Liczba przypisan: " << liczbaPrzypisan << endl;
    cout << "Liczba por0wnan: " << liczbaPorownan << endl;


    delete[] arr;
}

void BucketSort2(int size) {
    double* arr = new double[size];
    RandomArrayBucket2(arr, size);

    liczbaPorownan = 0;
    liczbaPrzypisan = 0;

    BUCKET_SORT2(arr, size);

    cout << "BUCKET_SORT2 - Rozmiar tablicy: " << size << endl;
    cout << "Liczba przypisan: " << liczbaPrzypisan << endl;
    cout << "Liczba porownan: " << liczbaPorownan << endl;


    delete[] arr;
}

int main() {
    srand(time(nullptr));

    int sizes[] = {10, 100, 200, 400, 600, 800, 1000};

    for (int s = 0; s < 7; ++s) {
        int size = sizes[s];
        BucketSort1(size);
    }


    return 0;
}

