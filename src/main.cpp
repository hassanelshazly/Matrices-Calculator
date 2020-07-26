/******************************************************************************
 * Copyright (C) 2020 by Hassan El-shazly
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright.
 *
 *****************************************************************************/
/**
 * @file main.cpp
 * @brief 
 * 
 * This file implements complex matrix calculator using <code>matrix</code> class
 * the input must start with "start" line and ends with "end" line
 * the input can be from a file of the standard input
 * the output is to the standard output
 *
 * @author Hassan El-shazly
 * @date Last Edit Jul-2020
 *
 */

#include <iostream>
#include <vector>

#include "matrix.h"
#include "parsing.h"

using namespace std;


int main(int argc, char ** argv)
{
    if(argc > 1) 
    {
        freopen(argv[1], "r", stdin);
    }
    try
    {
        matrix<complex<float>> matrix1, matrix2;
        string s = ""; 
        
        while(s != "start") {
            getline(cin, s);
        }
        while(true) {
            getline(cin, s);
            if(s == "end") {
                break;
            }
            if(s == "") {
                continue;
            }
            matrix1 = parse_complex_input(s);
            string op; getline(cin, op);
            
            if(op == "+")
            {
                getline(cin, s);
                matrix2 = parse_complex_input(s) ;
                (matrix1 += matrix2).print_l() ;
            }
            else if(op == "-")
            {
                getline(cin, s);
                matrix2 = parse_complex_input(s) ;
                (matrix1 -= matrix2).print_l() ;
            }
            else if(op == "*")
            {
                getline(cin, s);
                matrix2 = parse_complex_input(s) ;
                matrix1.multiply(matrix2).print_l() ;
            }
            else if(op == "^")
            {
                int n; cin >> n ;
                matrix1.power(n).print_l();
            }
            else if(op == "T")
            {
                matrix1.transpose().print_l();
            }
            else if(op == "D")
            {
                cout << determinant_recursive(matrix1);
            }
            else if(op == "I")
            {
                matrix1.invert().print_l();
            }
            else if(op == "/")
            {
                getline(cin, s);
                matrix2 = parse_complex_input(s);
                matrix2 = matrix2.invert();
                matrix1.multiply(matrix2).print_l();
            }
            else 
            {
                cout << "\nInvalid opeartor\n";
                return 0;
            }
            cout << std::endl;
        }
    }
    catch(...)
    {
        cout << "ERROR" ;
        return 0 ;
    }
     
}

