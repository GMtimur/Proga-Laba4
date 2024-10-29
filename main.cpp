#include <iostream>
#include <vector>
#include <cstring> // для strcmp

using namespace std;

void inputMatrix(vector<vector<double> >& matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            cin >> matrix[i][j];
        }
    }
}

void printMatrix(const vector<vector<double> >& matrix) {
    for (const auto& row : matrix) {
        for (size_t j = 0; j < row.size(); ++j) {
            cout << row[j] << (j < row.size() - 1 ? " " : "");
        }
        cout << endl;
    }
}

bool multiplyMatrices(const vector<vector<double> >& A, const vector<vector<double> >& B, vector<vector<double> >& result) {
    if (A[0].size() != B.size()) {
        return false;
    }

    result.assign(A.size(), vector<double>(B[0].size(), 0));
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B[0].size(); ++j) {
            for (size_t k = 0; k < A[0].size(); ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return true;
}

bool powerMatrix(const vector<vector<double> >& A, int exp, vector<vector<double> >& result) {
    if (A.size() != A[0].size()) {
        return false;
    }

    result = A; // A_1
    for (int i = 1; i < exp; ++i) {
        vector<vector<double> > temp;
        if (!multiplyMatrices(result, A, temp)) {
            return false;
        }
        result = temp;
    }
    return true;
}

int main(int argc, char* argv[]) {
    setlocale(LC_CTYPE, "rus");
    bool isHuman = (argc <= 1 || strcmp(argv[1], "false") != 0);
    
    int N, M;
    if (isHuman) cout << "Введите числа N и М: " << endl;
    cin >> N >> M;

    vector<vector<double> > A1(N, vector<double>(M));
    inputMatrix(A1);

    while (true) {
        int command;
        if (isHuman) cout << "Введите номер команды (1, 2, 3): ";
        cin >> command;

        if (command == 0) {
            break;
        } else if (command == 1) {
            if (isHuman) cout << "Матрица А1: " << endl;
            printMatrix(A1);
        } else if (command == 2) {
            int K;
            if (isHuman) cout << "Введите число К: ";
            cin >> K;
            vector<vector<double> > A2(M, vector<double>(K));
            inputMatrix(A2);
            vector<vector<double> > result;
            if (!multiplyMatrices(A1, A2, result)) {
                cout << (isHuman ? "Матрицы нельзя перемножить!" : "NO") << endl;
            } else {
                A1 = result;
            }
        } else if (command == 3) {
            if (A1.size() != A1[0].size()) {
                cout << (isHuman ? "Матрицу нельзя возвести в степень!" : "NO") << endl;
                continue;
            }
            int x;
            if (isHuman) cout << "Введите степень: ";
            cin >> x;
            vector<vector<double> > result;
            if (!powerMatrix(A1, x, result)) {
                cout << (isHuman ? "Матрицу нельзя возвести в степень!" : "NO") << endl;
            } else {
                A1 = result;
            }
        } else {
            cout << (isHuman ? "Некорректная команда. Попробуйте снова." : "NO") << endl;
        }
    }

    return 0;
}
