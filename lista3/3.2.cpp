#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;


int REC_LCS(const string &s1, const string &s2, int m, int n, int **b) {
    if (m == 0 || n == 0)
        return 0;

    if (b[m][n] != -1)
        return b[m][n];

    if (s1[m - 1] == s2[n - 1])
        return b[m][n] = 1 + REC_LCS(s1, s2, m - 1, n - 1, b);
    return b[m][n] = max(REC_LCS(s1, s2, m, n - 1, b), REC_LCS(s1, s2, m - 1, n, b));
}


void ROZWIAZANIE(const string &s1, const string &s2) {
    int m = s1.length();
    int n = s2.length();

    int **b = new int*[m + 1];
    for (int i = 0; i <= m; ++i) {
        b[i] = new int[n + 1];
        for (int j = 0; j <= n; ++j) {
            b[i][j] = -1;
        }
    }

    int l = REC_LCS(s1, s2, m, n, b);
    string podciag = "";
    while (m > 0 && n > 0) {
        if (s1[m - 1] == s2[n - 1]) {
            podciag = s1[m - 1] + podciag;
            m--;
            n--;
        } else if (b[m - 1][n] > b[m][n - 1]) {
            m--;
        } else {
            n--;
        }
    }


    for (int i = 0; i <= m; ++i) {
        delete[] b[i];
    }
    delete[] b;
}


pair<int, char **> IT_LCS(const string &X, const string &Y) {
    int m = X.size();
    int n = Y.size();

    // Alokacja pamięci dla tablic c i b
    int **c = new int *[m + 1];
    char **b = new char *[m + 1];
    for (int i = 0; i <= m; i++) {
        c[i] = new int[n + 1];
        b[i] = new char[n + 1];
    }

    // Inicjalizacja brzegów tablicy c
    for (int i = 0; i <= m; i++) c[i][0] = 0;
    for (int j = 0; j <= n; j++) c[0][j] = 0;

    // Obliczanie długości LCS
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '\\'; // "skos" oznacza dopasowanie
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = '|'; // "góra"
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '-'; // "lewo"
            }
        }
    }

    int length = c[m][n]; // Długość LCS
    for (int i = 0; i <= m; i++) {
        delete[] c[i];
    }
    delete[] c;

    // Zwracamy długość LCS oraz wskaźnik do tablicy b
    return {length, b};
}

// Funkcja do wypisywania LCS na podstawie tablicy b
void PrintLCS(char **b, const string &X, int i, int j) {
    if (i == 0 || j == 0) return;
    if (b[i][j] == '\\') {
        PrintLCS(b, X, i - 1, j - 1);
        cout << X[i - 1];
    } else if (b[i][j] == '|') {
        PrintLCS(b, X, i - 1, j);
    } else {
        PrintLCS(b, X, i, j - 1);
    }
}
string RANDOM_STRING(int l) {
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string napis;
    for (int i = 0; i < l; i++) {
        napis += abc[rand() % abc.length()];
    }
    return napis;
}


int main() {

   cout << "\nTesty wydajności (porównanie rekurencyjnego i iteracyjnego LCS):" << endl;
int dlugosciKrotkie[] = {1,5,10,15,20,25,30,35,40,45,50,55,60};
for (int l : dlugosciKrotkie) {
    string s1 = RANDOM_STRING(l);
    string s2 = RANDOM_STRING(l);
    int m = s1.length();
    int n = s2.length();
     int **b = new int*[m + 1];
        for (int i = 0; i <= m; ++i) {
            b[i] = new int[n + 1];
            for (int j = 0; j <= n; ++j) {
                b[i][j] = -1;
            }
        }
    // Rekurencyjny LCS
    auto startRek = high_resolution_clock::now();
    int lcsLengthRecursive = REC_LCS(s1, s2, s1.length(), s2.length(), b);
    auto stopRek = high_resolution_clock::now();
    auto durationRek = duration_cast<microseconds>(stopRek - startRek);

    // Iteracyjny LCS
    auto startIter = high_resolution_clock::now();
    auto [lengthIter, c] = IT_LCS(s1, s2);
    auto stopIter = high_resolution_clock::now();
    auto durationIter = duration_cast<microseconds>(stopIter - startIter);

    cout << "Dlugosc ciagow: " << l
         << ", Rekurencyjny LCS: " << lcsLengthRecursive
         << ", Czas: " << durationRek.count() << " mikrosekund"
         << ", Iteracyjny LCS: " << lengthIter
         << ", Czas: " << durationIter.count() << " mikrosekund" << endl;

    // Czyszczenie pamięci dla iteracyjnego LCS
    for (int i = 0; i <= s1.length(); i++) {
        delete[] b[i];
    }
    delete[] b;
}

    return 0;
}

