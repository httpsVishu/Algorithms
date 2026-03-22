#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

long long addCount = 0;
long long mulCount = 0;

bool isPowerOfTwo(int n){
    if (n <= 0) return false;
    while (n > 1){
        if (n % 2 != 0) return false;
        n = n/2 ;
    }
    return true;
}

vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> M(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = rand() % 50 + 1;
    return M;
}


vector<vector<int>> add(vector<vector<int>> A, vector<vector<int>> B, int n){
    vector<vector<int>> C(n, vector<int> (n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            C[i][j] = A[i][j] + B[i][j];
            addCount++;
        }
    }
    return C;
}

vector<vector<int>> subtract(vector<vector<int>> A, vector<vector<int>> B, int n){
    vector<vector<int>> C(n, vector<int> (n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            C[i][j] = A[i][j] - B[i][j];
            addCount++;
        }
    }
    return C;
}

vector<vector<int>> strassen(vector<vector<int>> A, vector<vector<int>> B, int n) {
    vector<vector<int>> C(n, vector<int>(n));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        mulCount++;
        return C;
    }

    int k = n / 2;

    vector<vector<int>> A11(k, vector<int>(k)), A12(k, vector<int>(k)),
                        A21(k, vector<int>(k)), A22(k, vector<int>(k));
    vector<vector<int>> B11(k, vector<int>(k)), B12(k, vector<int>(k)),
                        B21(k, vector<int>(k)), B22(k, vector<int>(k));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    auto P = strassen(A11, subtract(B12, B22, k), k);
    auto Q = strassen(add(A11, A12, k), B22, k);
    auto R = strassen(add(A21, A22, k), B11, k);
    auto S = strassen(A22, subtract(B21, B11, k), k);
    auto T = strassen(add(A11, A22, k), add(B11, B22, k), k);
    auto U = strassen(subtract(A12, A22, k), add(B21, B22, k), k);
    auto V = strassen(subtract(A11, A21, k), add(B11, B12, k), k);

    auto C11 = add(subtract(add(T, S, k), Q, k), U, k);
    auto C12 = add(P, Q, k);
    auto C21 = add(R, S, k);
    auto C22 = add(subtract(add(T, P, k), R, k), V, k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}

void printMatrix(const vector<vector<int>> &M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }
}

int main(){
    srand(time(0));
    int n;
    cout<< "Enter order of matrix (power of 2 only): ";
    cin>> n;

    if (!isPowerOfTwo(n)){
        cout<< "Error: Enter size in power of 2 (1,2,4,8,...) :/"<<endl;
        return 0;
    }

    auto A = generateMatrix(n);
    auto B = generateMatrix(n);
    cout<< "\n Matrix A: \n";
    printMatrix(A, n);
    cout<< "\n Matrix B: \n";
    printMatrix(B, n);

    auto C = strassen(A, B, n);
    cout<< "\n Result Matrix: \n";
    printMatrix(C, n);

    cout << "\n Additions/Subtractions: " << addCount;
    cout << "\n Multiplications: " << mulCount;
    cout << "\n Total Operations: " << addCount + mulCount << endl;

    return 0;
    
}








