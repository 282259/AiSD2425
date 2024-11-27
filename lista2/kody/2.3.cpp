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

void LIST_DELETE(List& L, Node* x) {
    if (x->prev != nullptr) {
        x->prev->next = x->next;
    } else {
        L.head = x->next;
    }

    if (x->next != nullptr) {
        x->next->prev = x->prev;
    }

    delete x;
}
Node* LIST_SEARCH(List& L, double k) {
    Node* x = L.head;

    while (x != nullptr && x->key != k) {
        x = x->next;
    }

    return x;
}
void LIST_INSERT(List& L, Node* x) {
    x->next = L.head;
    x->prev = nullptr;
    if (L.head != nullptr) {
        L.head->prev = x;
        liczbaPorownan++;
    }
    L.head = x;
}
void PRINT_LIST(List& L) {
    Node* current = L.head;
    while (current != nullptr) {
        cout << current->key << " ";
        current = current->next;
    }
    cout << endl;
}

void INSERTION_SORT(List& L) {
    if (L.head == nullptr || L.head->next == nullptr) {
        return;
        liczbaPorownan++;
    }

    Node* current = L.head->next;

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




void RandomList(List& L, int n) {
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        double y = (rand() % 100);
        Node* x = new Node(y);
        LIST_INSERT(L, x);
    }
}


void Result(List& L) {

    INSERTION_SORT(L);
    cout << "Porownania: " << liczbaPorownan << "\nPrzypisania: " << liczbaPrzypisan << "\n";
    liczbaPorownan=0;
    liczbaPrzypisan=0;
    cout << endl;
}

int main() {

    List L;

    LIST_INSERT(L, new Node(-3.0));
    LIST_INSERT(L, new Node(1.3));
    LIST_INSERT(L, new Node(2.1));
    LIST_INSERT(L, new Node(3.0));

    cout << "Lista poczatkowa: ";
    PRINT_LIST(L);

    double key1 = 2.1;
    Node* foundNode = LIST_SEARCH(L, key1);
    if (foundNode) {
        cout << "Znaleziono element: " << foundNode->key << endl;
    } else {
        cout << "Nie znaleziono szukanego elementu"  << endl;
    }

    if (foundNode) {
        LIST_DELETE(L, foundNode);
    }
    cout << "Lista końcowa: ";
    PRINT_LIST(L);
    int sizes[] = {10, 100, 200, 400, 600, 800, 1000};

    for (int n : sizes) {

        List L;
        RandomList(L, n);
        Result(L);

        while (L.head != nullptr) {
            LIST_DELETE(L, L.head);
        }
    }



    return 0;
}
