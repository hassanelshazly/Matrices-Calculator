#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <complex>
#include <algorithm>

#include "matrix.h"

using namespace std;

vector<string> strip(const vector<string>& input);
string strip(const string& input);
vector<string> split(const string& s, char b);
string clearSpaces(const string& s);

vector<float> tofloat(const vector<string>& input);
ostream& operator<<(ostream& os, complex<float> c);
vector<vector<float>> parse_floatInput(string& input);
vector<vector<complex<float>>> parse_complexInput(string& input);


int main()
{
    matrix<complex<float>> matrix1, matrix2;
    string s; getline(cin, s);
    try
    {
        matrix1 = parse_complexInput(s);
        string op; getline(cin, op);
        if(op == "+")
        {
            getline(cin, s);
            matrix2 = parse_complexInput(s) ;
            (matrix1 += matrix2).print_l() ;
        }
        else if(op == "-")
        {
            getline(cin, s);
            matrix2 = parse_complexInput(s) ;
            (matrix1 -= matrix2).print_l() ;
        }
        else if(op == "*")
        {
            getline(cin, s);
            matrix2 = parse_complexInput(s) ;
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
         if(op == "D")
        {
            cout << determinant(matrix1);
        }
        else if(op == "I")
        {
            matrix1.invert().print_l();
        }
        else if(op == "/")
        {
            getline(cin, s);
            matrix2 = parse_complexInput(s);
            matrix2 = matrix2.invert();
            matrix1.multiply(matrix2).print_l();
        }
    }
    catch(...)
    {
        cout << "ERROR" ;
        return 0 ;
    }
     
}

vector<string> strip(const vector<string>& input)
{   
    vector<string> v = input;
    for(string& s : v) 
    {
        while(s[0] == ' ') 
            s.erase(0, 1) ;
        while(s[s.length()-1] == ' ') 
            s.erase(s.length()-1, 1);
    }
    return v; 
}

string strip(const string& input)
{   
    string s = input;
    while(s[0] == ' ') 
        s.erase(0, 1) ;
    while(s[s.length()-1] == ' ') 
        s.erase(s.length()-1, 1);

    return s; 
}

vector<string> split(const string& s, char b)
{
    vector<string> v ;
    int j = 0 ;
    int n = s.length() ;
    string m ;
    for(int i = 0 ; i < n ; i++)
    {
        if (s[i] == b)
        {
            m = s.substr(j,i-j) ;
            if(m != "") v.push_back(m);
            j = i+1 ;
        }
    }
    v.push_back(s.substr(j,n-j));
    return v ;
}

string clearSpaces(const string& s)
{
    string input = s;
    string::iterator new_end = unique(input.begin(), input.end(), [] (const char &x, const char &y) {
       return x == y and x == ' ';
    });
    input.erase(new_end, input.end());
    return input;
}

vector<float> tofloat(const vector<string>& input)
{
    vector<float> vec;
    for(const auto& s: input)
        vec.push_back(atof(s.c_str()));
    return vec;
}

ostream& operator<<(ostream& os, complex<float> c)
{
    if(real(c) != 0) os << real(c) ;
    if(imag(c) == 1 && real(c) == 0) os << "i" ;
    else if(imag(c) == 1 && real(c) != 0) os << "+i" ;
    else if(imag(c) == -1) os << "-i" ;
    else if(imag(c) > 0)
        if(real(c) != 0)
            os << "+" << imag(c) << "i" ;
        else
            os << imag(c) << "i" ;
    else if(imag(c) < 0)
        os << imag(c) << "i" ;
    if(real(c) == 0 && imag(c) == 0) os << "0" ;
    return os;
}
vector<complex<float>> toComplex(const vector<string>& input)
{
    vector<complex<float>> vec;
    for(string s: input)
        if(s.find("i") != string::npos)
            if(s.find("+") != string::npos || s.find("-",1) != string::npos)
            {
                float r = atof(s.c_str()) ;
                ostringstream os ; os << r ;
                s.replace(0, os.str().length() ,"");
                float i = atof(s.c_str()) ;
                if(i == 0 && s.find("+") != string::npos) i = 1 ;
                if(i == 0 && s.find("-") != string::npos) i = -1 ;
                vec.push_back(complex<float>(r, i));
            }
            else
            {
                float i = atof(s.c_str()) ;
                if(i == 0 && s.length() == 1) i = 1 ;
                if(i == 0 && s.length() == 2) i = -1 ;
                vec.push_back(complex<float>(0, i));
            }
        else
            vec.push_back(complex<float>(atof(s.c_str()), 0));
    return vec;
}


vector<vector<float>> parse_floatInput(string& input)
{   
    vector<vector<float>> vec;
    if(input.size() < 2)
        return vec;
    input.erase(input.begin()) ; 
    input.erase(input.end()-1) ;
    input = clearSpaces(input); 
    vector<string> rows = split(input, ';');
    for(const auto& row : rows)
        vec.push_back(tofloat(split(strip(row), ' ')));
    return vec;
}

vector<vector<complex<float>>> parse_complexInput(string& input)
{
    vector<vector<complex<float>>> vec;
    if(input.size() < 2)
        return vec;
    input.erase(input.begin()) ; 
    input.erase(input.end()-1) ;
    input = clearSpaces(input); 
    vector<string> rows = split(input, ';');
    for(const auto& row : rows)
        vec.push_back(toComplex(split(strip(row), ' ')));
    return vec;
}