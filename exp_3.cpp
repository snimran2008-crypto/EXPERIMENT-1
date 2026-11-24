#include <iostream>
using namespace std;

class Matrix {
private:
    int data[2][2];

public:
    Matrix(int a = 0, int b = 0, int c = 0, int d = 0) {
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
    }

    // Operator +
    Matrix operator+(const Matrix &m) {
        Matrix result;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] + m.data[i][j];
        return result;
    }

    // Operator *
    Matrix operator*(const Matrix &m) {
        Matrix result;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < 2; k++)
                    result.data[i][j] += data[i][k] * m.data[k][j];
            }
        }
        return result;
    }

    // Operator []
    int* operator[](int index) {
        return data[index];
    }

    // Operator >> for user input
    friend istream& operator>>(istream &in, Matrix &m) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                in >> m.data[i][j];
            }
        }
        return in;
    }

    // Operator << for output
    friend ostream& operator<<(ostream &out, const Matrix &m) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                out << m.data[i][j] << " ";
            out << endl;
        }
        return out;
    }
};

int main() {
    Matrix A, B;

    cout << "Enter 4 integers for Matrix A (row by row):" << endl;
    cin >> A;

    cout << "Enter 4 integers for Matrix B (row by row):" << endl;
    cin >> B;

    Matrix sum = A + B;
    Matrix product = A * B;

    cout << "\nMatrix A:" << endl;
    cout << A;
    cout << "Matrix B:" << endl;
    cout << B;
    cout << "Addition of Matrices:" << endl;
    cout << sum;
    cout << "Multiplication of Matrices:" << endl;
    cout << product;

    return 0;
}
