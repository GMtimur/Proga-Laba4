#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 100;
const int MAX_M = 100;

void inputMatrix(double matrix[MAX_N][MAX_M], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }
}

void printMatrix(double matrix[MAX_N][MAX_M], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << (j < cols - 1 ? " " : "");
        }
        cout << endl;
    }
}

bool multiplyMatrices(double A[MAX_N][MAX_M], int A_rows, int A_cols, 
                      double B[MAX_N][MAX_M], int B_rows, int B_cols, 
                      double result[MAX_N][MAX_M], int &result_rows, int &result_cols) {
    if (A_cols != B_rows) {
        return false;
    }
    for (int i = 0; i < A_rows; ++i) {
        for (int j = 0; j < B_cols; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < A_cols; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    result_rows = A_rows;
    result_cols = B_cols;
    return true;
}

bool powerMatrix(double A[MAX_N][MAX_M], int N, int exp, double result[MAX_N][MAX_M]) {
    if (N <= 0 || exp < 1) {
        return false;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = A[i][j];
        }
    }
    double temp[MAX_N][MAX_M];
    for (int i = 1; i < exp; ++i) {
        if (!multiplyMatrices(result, N, N, A, N, N, temp, N, N)) {
            return false;
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result[i][j] = temp[i][j];
            }
        }
    }
    return true;
}


int main(int argc, char* argv[]) {
    setlocale(LC_CTYPE, "rus");
    bool isHuman = (argc <= 1 || strcmp(argv[1], "false") != 0);
    int N, M;
    if (isHuman) cout << "Введите числа N и М: " << endl;
    cin >> N >> M;
    double A1[MAX_N][MAX_M];
    inputMatrix(A1, N, M);
    while (true) {
        int command;
        if (isHuman) cout << "Введите номер команды (1, 2, 3): ";
        cin >> command;
        if (command == 0) {
            break;
        } else if (command == 1) {
            if (isHuman) cout << "Матрица А1: " << endl;
            printMatrix(A1, N, M);
        } else if (command == 2) {
            int K;
            if (isHuman) cout << "Введите число К: ";
            cin >> K;
            double A2[MAX_N][MAX_M];
            inputMatrix(A2, M, K);
            double result[MAX_N][MAX_M];
            int result_rows, result_cols;
            if (!multiplyMatrices(A1, N, M, A2, M, K, result, result_rows, result_cols)) {
                cout << (isHuman ? "Матрицы нельзя перемножить!" : "NO") << endl;
            } else {
                N = result_rows;
                M = result_cols;
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < M; ++j) {
                        A1[i][j] = result[i][j];
                    }
                }
            }
        } else if (command == 3) {
            if (N != M) {
                cout << (isHuman ? "Матрицу нельзя возвести в степень!" : "NO") << endl;
                continue;
            }

            int x;
            if (isHuman) cout << "Введите степень: ";
            cin >> x;

            double result[MAX_N][MAX_M];
            if (!powerMatrix(A1, N, x, result)) {
                cout << (isHuman ? "Матрицу нельзя возвести в степень!" : "NO") << endl;
            } else {
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        A1[i][j] = result[i][j];
                    }
                }
            }
        } else {
            cout << (isHuman ? "Некорректная команда. Попробуйте снова." : "NO") << endl;
        }
    }

    return 0;
}
