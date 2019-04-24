/**
 * this was supposed to be compiled with std=c++11
 * but it is edited to support older versions of c++
 */


/**
 * author: Hassan El-shazly
 * section: 4
 * B.N: 32
 */

/* matrix.h file */

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>

using std::vector ;

template <typename ValueType>
class matrix
{
public:

    matrix();
    matrix(int row, int col);
    matrix(const matrix<ValueType>& m);
    // matrix(matrix<ValueType>&& m);
    matrix(const vector<vector<ValueType> >& vec);

    matrix<ValueType>& operator=(const matrix<ValueType>& m);
    // matrix<ValueType>& operator=(matrix<ValueType>&& m);
    bool operator==(const matrix<ValueType>& m);
    bool operator!=(const matrix<ValueType>& m);

    matrix<ValueType>& operator+=(const matrix<ValueType>& m);
    matrix<ValueType>& operator-=(const matrix<ValueType>& m);
    matrix<ValueType>& operator*=(const matrix<ValueType>& m); // scaler multiplication
    matrix<ValueType>& operator/=(const matrix<ValueType>& m); // scaler division
    matrix<ValueType>& operator+=(const ValueType& val);
    matrix<ValueType>& operator-=(const ValueType& val);
    matrix<ValueType>& operator*=(const ValueType& val);
    matrix<ValueType>& operator/=(const ValueType& val); 
    vector<ValueType>& operator[](int rowIndex);
    
    matrix<ValueType> multiply(matrix<ValueType>& m); // matrices multiplication
    matrix<ValueType>& invert();
    matrix<ValueType> transpose();
    matrix<ValueType> power(int n);

    matrix<ValueType>& print_r();
    matrix<ValueType>& print_r(std::ostream& os);
    matrix<ValueType>& print_l(); // matlab format
    matrix<ValueType>& print_l(std::ostream& os);

    matrix<ValueType>& setDim(int row, int col); // This doesn't guarantee the matrix data still valid
    std::pair<int, int> getDim();
    int getR();
    int getC();
    static std::pair<int, int> check_dim(const vector<vector<ValueType> >& vec);

    template <typename T> friend 
    std::ostream& operator<<(std::ostream& os,const matrix<T>& m);
    template <typename T> friend 
    matrix<T> subMatrix(matrix<T> m, int row, int col);
private:
    int rows ; int cols ;
    vector<vector<ValueType> > elements;
};

template <typename ValueType>
matrix<ValueType>::matrix()
    : rows(0), cols(0) {}

template <typename ValueType>
matrix<ValueType>::matrix(int row, int col)
    : rows(row), cols(col)
{
    elements.resize(row);
    for(int i = 0; i < row; i++)
        elements[i].resize(col);
}

template <typename ValueType>
matrix<ValueType>::matrix(const matrix<ValueType>& m)
    : rows(m.rows), cols(m.cols), elements(m.elements) {}

// template <typename ValueType>
// matrix<ValueType>::matrix(matrix<ValueType>&& m)
//     : rows(m.rows), cols(m.cols), elements(std::move(m.elements)) {}

template <typename ValueType>
matrix<ValueType>::matrix(const vector<vector<ValueType> >& vec)
{
    std::pair<int, int> p = check_dim(vec);
    if(p.first < 0)
        throw std::length_error("Dimentions error");
    rows = p.first;
    cols = p.second;
    elements = vec ;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::print_r()
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            std::cout << elements[i][j] << " " ;
        std::cout << std::endl ;
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::print_r(std::ostream& os)
{
   for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            os << elements[i][j] << " " ;
        os << std::endl ;
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::print_l()
{
    std::cout << "[" ;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++) {
            std::cout << elements[i][j] ;
            if(j<(cols-1)) std::cout << " " ;
        }
        if(i<(rows-1)) std::cout << ";" ;
    }
    std::cout << "]" ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::print_l(std::ostream& os)
{
    os << "[" ;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++) {
            os << elements[i][j] ;
            if(j<(cols-1)) os << " " ;
        }
        if(i<(rows-1)) os << ";" ;
    }
    os << "]" ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::setDim(int row, int col)
{
    rows = row; cols = col;
    elements.resize(row);
    for(int i = 0; i < row; i++)
        elements[i].resize(col);
    return *this;
}

template <typename ValueType>
inline std::pair<int, int> matrix<ValueType>::getDim()
{
    return std::make_pair(rows, cols);
}

template <typename ValueType>
inline int matrix<ValueType>::getR()
{
    return rows;
}

template <typename ValueType>
inline int matrix<ValueType>::getC()
{
    return cols;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator=(const matrix<ValueType>& m)
{
    rows = m.rows; cols = m.cols;
    elements = m.elements;
    return *this;
}

// template <typename ValueType>
// matrix<ValueType>& matrix<ValueType>::operator=(matrix<ValueType>&& m)
// {
//     rows = m.rows; cols = m.cols;
//     elements = std::move(m.elements);
//     return *this;
// }

template <typename ValueType>
bool matrix<ValueType>::operator==(const matrix<ValueType>& m)
{
    return  elements == m.elements ;
}

template <typename ValueType>
bool matrix<ValueType>::operator!=(const matrix<ValueType>& m)
{
    return elements != m.elements ;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator+=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("Error: Matrices dimentions must be the same") ;
    // auto itm = m.elements.begin();
    // std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
    //     auto iitm = itm->begin();
    //     std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
    //         iite += *iitm ;
    //         iitm++;
    //     });
    //     itm++;
    // });
    /* another simple way, use one only */
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            elements[i][j] += m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator-=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("Error: Matrices dimentions must be the same") ;
    // auto itm = m.elements.begin();
    // std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
    //     auto iitm = itm->begin();
    //     std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
    //         iite -= *iitm ;
    //         iitm++;
    //     });
    //     itm++;
    // });
    /* another simple way, use one only */
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            elements[i][j] -= m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator*=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("Error: Matrices dimentions must be the same") ;
    // auto itm = m.elements.begin();
    // std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
    //     auto iitm = itm->begin();
    //     std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
    //         iite *= *iitm ;
    //         iitm++;
    //     });
    //     itm++;
    // });
    /* another simple way, use one only */
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            elements[i][j] *= m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator/=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("Error: Matrices dimentions must be the same") ;
    // auto itm = m.elements.begin();
    // std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
    //     auto iitm = itm->begin();
    //     std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
    //         iite /= *iitm ;
    //         iitm++;
    //     });
    //     itm++;
    // });
    /* another simple way, use one only */
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            elements[i][j] /= m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator+=(const ValueType& val)
{
    // for(auto& row : elements)
    //     for(auto& col : row)
    //         col += val;
    for(int i = 0; i < elements.size(); i++)
        for(int j = 0; j < elements[i].size(); j++)
            elements[i][j] += val;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator-=(const ValueType& val)
{
    // for(auto& row : elements)
    //     for(auto& col : row)
    //         col -= val;
    for(int i = 0; i < elements.size(); i++)
        for(int j = 0; j < elements[i].size(); j++)
            elements[i][j] -= val;
    
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator*=(const ValueType& val)
{
    // for(auto& row : elements)
    //     for(auto& col : row)
    //         col *= val;
    for(int i = 0; i < elements.size(); i++)
        for(int j = 0; j < elements[i].size(); j++)
            elements[i][j] *= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator/=(const ValueType& val)
{
    // for(auto& row : elements)
    //     for(auto& col : row)
    //         col /= val;
    for(int i = 0; i < elements.size(); i++)
        for(int j = 0; j < elements[i].size(); j++)
            elements[i][j] /= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType> matrix<ValueType>::multiply(matrix<ValueType>& m)
{
    if(cols != m.rows)
        throw std::length_error("Error: check matrices dimentions");
    matrix<ValueType> res(rows, m.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < m.cols; j++)
            for (int k = 0 ; k < m.rows ; k++ )
                res[i][j] += elements[i][k] * m[k][j];
    return res;
}

template <typename ValueType>
matrix<ValueType> matrix<ValueType>::power(int n)
{
    if(rows != cols)
        throw std::length_error("Error: check matrix dimentions");
    matrix<ValueType> res = *this;
    for(int i = 0; i < n-1; i++)
        res = res.multiply(*this);
    return res;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::invert()
{
    if(rows != cols)
        throw std::length_error("Error: check matrix dimentions");
    matrix<ValueType> adj (rows, cols);
    ValueType signRow = 1 ;
    ValueType signCol = signRow ;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++) 
        {
            adj[i][j] = determinant(subMatrix(*this, i, j)) * signCol;
            signCol = -signCol;
        }
        signRow = -signRow;
        signCol = signRow;
    }
    ValueType det = determinant(*this);
    if(det == static_cast<ValueType>(0))
        throw std::out_of_range("Error: Determinant equal zero");
    *this = adj.transpose() / det;    
    return *this;
}
 
template <typename ValueType>
matrix<ValueType> matrix<ValueType>::transpose()
{
    matrix<ValueType> res(cols, rows);
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            res[j][i] = elements[i][j];
    return res;
}

template <typename ValueType> 
std::pair<int, int> matrix<ValueType>::check_dim(const vector<vector<ValueType> >& vec)
{
    int rows = vec.size();
    int cols = vec[0].size();
    for(int i=0; i<vec.size();i++)
        if(vec[i].size() != cols)
            return std::make_pair(-1,-1);
    return std::make_pair(rows, cols);
}

template <typename ValueType>
vector<ValueType>& matrix<ValueType>::operator[](int rowIndex)
{
    return elements[rowIndex];
}

template <typename ValueType>
std::ostream& operator<<(std::ostream& os, const matrix<ValueType>& m)
{
    for(int i=0; i<m.getR();i++)
    {
        for(int j=0; j<m.getC(); j++)
            os << m[i][j] << " " ;
        os << std::endl ;
    }
    return os ;
}

template <typename ValueType>
matrix<ValueType> subMatrix(matrix<ValueType> m, int row, int col)
{
    for(int i = 0; i<m.getR(); i++)
        m[i].erase(m[i].begin() + col);
    m.elements.erase(m.elements.begin() + row);
    return matrix<ValueType>(m.elements);
}

template <typename ValueType>
ValueType determinant(matrix<ValueType> m)
{
    if(m.getR() != m.getC())
        throw std::length_error("Error: check matrix dimentions");
    if(m.getR() == 1) return m[0][0] ;
    ValueType det = ValueType();
    ValueType sign = 1 ;
    for(int i = 0; i<m.getC(); i++)
    {
        det += m[0][i] * determinant(subMatrix(m, 0, i)) * sign;
        sign = -sign ;
    }
    return det;
}

template <typename ValueType>
matrix<ValueType> operator+(matrix<ValueType> m1, matrix<ValueType> m2)
{
    return m1 += m2;
}

template <typename ValueType>
matrix<ValueType> operator-(matrix<ValueType> m1, matrix<ValueType> m2)
{
    return m1 -= m2;
}

template <typename ValueType>
matrix<ValueType> operator*(matrix<ValueType> m1, matrix<ValueType> m2)
{
    return m1 *= m2;
}

template <typename ValueType>
matrix<ValueType> operator/(matrix<ValueType> m1, matrix<ValueType> m2)
{
    return m1 /= m2;
}

template <typename ValueType>
matrix<ValueType> operator+(matrix<ValueType> m1, const ValueType& val)
{
    return m1 += val;
}

template <typename ValueType>
matrix<ValueType> operator-(matrix<ValueType> m1, const ValueType& val)
{
    return m1 -= val;
}

template <typename ValueType>
matrix<ValueType> operator*(matrix<ValueType> m1, const ValueType& val)
{
    return m1 *= val;
}

template <typename ValueType>
matrix<ValueType> operator/(matrix<ValueType> m1, const ValueType& val)
{
    return m1 /= val;
}

/* end matrix.h file */

/* main.cpp file */

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <complex>
// #include "matrix.h"

using namespace std;

vector<string>& strip(vector<string>& v)
{   
    for(int i=0; i<v.size();i++) 
    {
        string s = v[i];
        while(s[0] == ' ') 
            s.erase(0, 1) ;
        while(s[s.length()-1] == ' ') 
            s.erase(s.length()-1, 1);
    }
    return v; 
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

vector<float> tofloat(const vector<string>& input)
{
    vector<float> vec;
    for(int i=0; i<input.size(); i++) 
        vec.push_back(atof(input[i].c_str()));
    return vec;
}

/* use this in all cases */
// ostream& operator<<(ostream& os, complex<float> c)
// {
//     if(real(c) != 0) os << real(c) ;
//     if(imag(c) == 1 && real(c) == 0) os << "i" ;
//     else if(imag(c) == 1 && real(c) != 0) os << "+i" ;
//     else if(imag(c) == -1) os << "-i" ;
//     else if(imag(c) > 0)
//         if(real(c) != 0)
//             os << "+" << imag(c) << "i" ;
//         else
//             os << imag(c) << "i" ;
//     else if(imag(c) < 0)
//         os << imag(c) << "i" ;
//     if(real(c) == 0 && imag(c) == 0) os << "0" ;
//     return os;
// }

/* use this in project submision for bouns level only */
ostream& operator<<(ostream& os, complex<float> c)
{
    os << real(c) ;
    if(imag(c) == 0) os << "+0i" ;
    else if (imag(c) > 0) os << "+" << imag(c) <<"i" ;
    else if (imag(c) < 0) os << imag(c) <<"i" ;
    return os;
}
vector<complex<float> > toComplex(const vector<string>& input)
{
    vector<complex<float> > vec;
    for(int i=0; i<input.size(); i++) 
    {
        string s = input[i];
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
                /** comment the two following in project submision for bouns level
                 *  uncomment in all other cases */
                // if(i == 0 && s.length() == 1) i = 1 ;
                // if(i == 0 && s.length() == 2) i = -1 ;
                vec.push_back(complex<float>(0, i));
            }
        else
            vec.push_back(complex<float>(atof(s.c_str()), 0));
    }
    return vec;
}

vector<vector<float> > parse_floatInput(string& input)
{   
    vector<vector<float> > vec;
    if(input.size() < 2)
        return vec;
    input.erase(input.begin()) ; 
    input.erase(input.end()-1) ; 
    vector<string> rows = split(input, ';');
    for(int i =0; i<rows.size(); i++)
        vec.push_back(tofloat(split(rows[i], ' ')));
    return vec;
}

vector<vector<complex<float> > > parse_complexInput(string& input)
{
    vector<vector<complex<float> > > vec;
    if(input.size() < 2)
        return vec;
    input.erase(input.begin()) ; 
    input.erase(input.end()-1) ; 
    vector<string> rows = split(input, ';');
    for(int i =0; i<rows.size(); i++)
        vec.push_back(toComplex(split(rows[i], ' ')));
    return vec;
}


int main()
{
    matrix<complex<float> > matrix1, matrix2;
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
            matrix1.multiply(matrix2.invert()).print_l();
        }
    }
    catch(...)
    {
        cout << "ERROR" ;
        return 0 ;
    }
     
}

/* end main.cpp file */