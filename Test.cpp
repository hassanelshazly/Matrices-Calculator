#include <iostram>
#include <iomanip>
#include <random>
#include <chrono>

#include "matrix.h"


using namespace std;

int main()
{
    matrix<float> matrix1(5, 5) ;
    matrix<float> matrix2(5, 5) ;

    // Initializing the matrices with random numbers
    for(int i = 0; i < matrix1.getR() ; i++)
    {
        for(int j = 0; j < matrix1.getC() ; j++)
        {
            int randomNumber =  ;
            matrix1[i][j] = randomNumber ;
            int randomNumber =  ;
            matrix2[i][j] = randomNumber ;
        }
    }

    // Printing out the matrices
    cout << "Matrix 1" << endl << matrix1 << endl;
    cout << "Matrix 2" << endl << matrix2 << endl;
    
    matrix<float> result ; // for storing results 

    duration<double> time_taken ;

    auto start = chrono::high_resolution_clock::now();
    result = matrix1 + matrix2 ;
    auto end = chrono::high_resolution_clock::now();

    // Prining the result
    cout << "Result" << endl << result << endl;

    time_taken = end - start ;
    cout << "Time Taken = " << time_taken.count() << "  s\n";

}