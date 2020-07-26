/******************************************************************************
 * Copyright (C) 2020 by Hassan El-shazly
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright.
 *
 *****************************************************************************/
/**
 * @file parsing.h
 * @brief 
 * 
 * This file exports helper funtions to parse matrices in C++
 *
 * @author Hassan El-shazly
 * @date Last Edit Jul-2020
 *
 */
#ifndef _PARSING_H_
#define _PARSING_H_

#include <vector>
#include <utility>
#include <cstdlib>
#include <complex>
#include <string>
#include <algorithm>

using std::vector;
using std::string;
using std::complex;
using std::ostream;
using std::ostringstream;


/**
 * remove leading and laging spaces a given string
 */
string strip(const string& input);

/**
 * remove leading and laging spaces from vector of strings
 */
vector<string> strip(const vector<string>& input);

/**
 * split string based on a given char
 */
vector<string> split(const string& s, char b);

/**
 * reomove repeated spaces in a given string
 */
string clear_spaces(const string& s);

/**
 * transform vector of strings to vector of floats
 */
vector<float> to_float(const vector<string>& input);

/**
 * transform vector of strings to vector of complex numbers
 */
vector<complex<float>> to_complex(const vector<string>& input);

/**
 * transform string input into float matrix
 */
vector<vector<float>> parse_float_input(string& input);

/**
 * transform string input into complex matrix
 */
vector<vector<complex<float>>> parse_complex_input(string& input);


/**
 * overload << operator to print complex numbers
 */
ostream& operator<<(ostream& os, complex<float> c);

#endif // End of the file