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
    matrix(matrix<ValueType>&& m);
    matrix(const vector<vector<ValueType>>& vec);

    matrix<ValueType>& operator=(const matrix<ValueType>& m);
    matrix<ValueType>& operator=(matrix<ValueType>&& m);
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
    static std::pair<int, int> check_dim(const vector<vector<ValueType>>& vec);

    template <typename T> friend 
    std::ostream& operator<<(std::ostream& os,const matrix<T>& m);
    template <typename T> friend 
    matrix<T> subMatrix(matrix<T> m, int row, int col);
private:
    int rows ; int cols ;
    vector<vector<ValueType>> elements;
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

template <typename ValueType>
matrix<ValueType>::matrix(matrix<ValueType>&& m)
    : rows(m.rows), cols(m.cols), elements(std::move(m.elements)) {}

template <typename ValueType>
matrix<ValueType>::matrix(const vector<vector<ValueType>>& vec)
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
    for(const auto& items : elements)
    {
        for(const auto& element : items)
            std::cout << element << " " ;
        std::cout << std::endl ;
    }
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::print_r(std::ostream& os)
{
    for(const auto& items : elements)
    {
        for(const auto& element : items)
            os << element << " " ;
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

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator=(matrix<ValueType>&& m)
{
    rows = m.rows; cols = m.cols;
    elements = std::move(m.elements);
    return *this;
}

template <typename ValueType>
bool matrix<ValueType>::operator==(const matrix<ValueType>& m)
{
    return elements == m.elements ;
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
    auto itm = m.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
            iite += *iitm ;
            iitm++;
        });
        itm++;
    });
    /* another simple way, use one only */
    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] += m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator-=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("Error: Matrices dimentions must be the same") ;
    auto itm = m.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
            iite -= *iitm ;
            iitm++;
        });
        itm++;
    });
    /* another simple way, use one only */
    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] -= m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator*=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("Error: Matrices dimentions must be the same") ;
    auto itm = m.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
            iite *= *iitm ;
            iitm++;
        });
        itm++;
    });
    /* another simple way, use one only */
    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] *= m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator/=(const matrix<ValueType>& m)
{
    if(rows != m.rows || cols != m.cols)
        throw std::length_error("Error: Matrices dimentions must be the same") ;
    auto itm = m.elements.begin();
    std::for_each(elements.begin(), elements.end(), [&itm](auto& ite) {
        auto iitm = itm->begin();
        std::for_each(ite.begin(), ite.end(), [&iitm](auto& iite) {
            iite /= *iitm ;
            iitm++;
        });
        itm++;
    });
    /* another simple way, use one only */
    // for(int i=0; i<rows; i++)
    //     for(int j=0; j<cols; j++)
    //         elements[i][j] /= m.elements[i][j] ;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator+=(const ValueType& val)
{
    for(auto& row : elements)
        for(auto& col : row)
            col += val;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator-=(const ValueType& val)
{
    for(auto& row : elements)
        for(auto& col : row)
            col -= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator*=(const ValueType& val)
{
    for(auto& row : elements)
        for(auto& col : row)
            col *= val;
    return *this;
}

template <typename ValueType>
matrix<ValueType>& matrix<ValueType>::operator/=(const ValueType& val)
{
    for(auto& row : elements)
        for(auto& col : row)
            col /= val;
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
std::pair<int, int> matrix<ValueType>::check_dim(const vector<vector<ValueType>>& vec)
{
    int rows = vec.size();
    int cols = vec[0].size();
    for(const auto& row : vec)
        if(row.size() != cols)
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
    for(const auto& items : m.elements)
    {
        for(const auto& element : items)
            os << element << " " ;
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