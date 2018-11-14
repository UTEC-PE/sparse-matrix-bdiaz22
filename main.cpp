#include <iostream>

#include "matrix.h"

#define EXIT_SUCCESS 0
using namespace std;

int main(int argc, char *argv[]) {
	Matrix<int> matrix1(5,5);

    matrix1.set(0,0,1);
    matrix1.set(1,1,2);
    matrix1.set(2,1,3);
    matrix1.set(1,1,4);
    matrix1.set(1,3,5);
    matrix1.set(2,3,6);
    matrix1.set(2,2,7);
    matrix1.set(0,2,8);
    matrix1.set(1,2,9);
    matrix1.set(0,1,10);           

    cout << matrix1(0,0) << endl;
    cout << matrix1(1,1) << endl;
    cout << matrix1(2,1) << endl;
    cout << matrix1(1,1) << endl;
    cout << matrix1(1,3) << endl;
    cout << matrix1(2,3) << endl;
    cout << matrix1(2,2) << endl;
    cout << matrix1(0,2) << endl;
    cout << matrix1(0,1) << endl;
    cout << (matrix1*2)(0,1) << endl;
    cout << matrix1.transposed()(1,0) << endl;

    cout << "\n";

    Matrix<int> matrix2 =  matrix1;
    cout << matrix2(0,0) << endl;
    cout << matrix2(1,1) << endl;
    cout << matrix2(2,1) << endl;
    cout << matrix2(1,1) << endl;
    cout << matrix2(1,3) << endl;
    cout << matrix2(2,3) << endl;
    cout << matrix2(2,2) << endl;
    cout << matrix2(0,2) << endl;
    cout << matrix2(0,1) << endl;
    cout << (matrix2*4)(0,1) << endl;
    cout << matrix2.transposed()(3,2) << endl;

    cout << endl;

    Matrix<int> matrix3(5,5);
    matrix3 = matrix1 + matrix2;
    cout << matrix3(0,0) << endl;
    cout << matrix3(1,1) << endl;
    cout << matrix3(2,1) << endl;
    cout << matrix3(1,1) << endl;
    cout << matrix3(1,3) << endl;
    cout << matrix3(2,3) << endl;
    cout << matrix3(2,2) << endl;
    cout << matrix3(0,2) << endl;
    cout << matrix3(0,1) << endl;
    cout << (matrix3*4)(0,1) << endl;
    cout << matrix3.transposed()(3,2) << endl;
    system("PAUSE");

    Matrix<int> matrix4(2,1);
    Matrix<int> matrix5(1,2);

    matrix4.set(0,0,1);
    matrix4.set(1,0,2);

    matrix5.set(0,0,1);
    matrix5.set(0,1,2);

    Matrix<int> resultante(2,2);
    resultante = matrix4*matrix5;
    cout << resultante(0,0) << endl;
    cout << resultante(0,1) << endl;
    cout << resultante(1,0) << endl;   
    cout << resultante(1,1) << endl;


    return EXIT_SUCCESS;
}