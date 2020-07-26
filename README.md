# Matrices Calculator
An efficient, safe, convenient matrix type in C++ optimized to be used in mathematical computations and provides the following operations:

All the scalar operations with overloaded operators ``` + ``` ``` - ``` ``` * ``` ``` / ``` ``` += ``` ``` -= ``` ``` *= ``` ``` /= ```

Multiplication ```multiply()```,  power ```power()```, inverse ```invert()```, and transpose ```transpose()```  

Row and Column opeartions ```get_row()``` ``` get_col()``` ``` push_row()``` ``` push_col() ``` ```replace_row()``` ``` replace_col()``` ```erase_row()``` ```erase_col()``` ```swap_rows()``` ```swap_cols()```

Determinant ```det()``` ```determinant()``` ```det_recursive()``` ```determinant_recursive()``` 

Back Substitution (Gaussian Elimination) ```back_sub()``` ```back_substitution()```   

# Getting Started
```
1. git clone https://github.com/hassanelshazly/Matrices-Calculator

2. add matrix folder to your include path

3. #include "matrtix.h" in your files
```

##

## Usage
```
$ make

$ ./main.out test/test1.txt

$ ./main.out test/test2.txt
```

* It's an traditional templete class in c++, to define it ``` matrix<type> new_matrix ```

* The documntation and defintion in ```matrix/matrix_def.h```

* The implemention in ```matrix/matrix_impl.h```

* A simple example for complex matrices calculator is provided in ```src/main.cpp```

* Helper functions for parsing input are provided in ```include/parsing.h``` && ```src/parsing.cpp```


## License

This project is licensed under GNU General Public License v3.0
