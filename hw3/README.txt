HOMEWORK 3: MATRIX CLASS


NAME:  Zhengneng Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None. Lecture notes. cplusplusreference.com.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get: O(1)

set: O(1)

num_rows: O(1)

get_column: O(m)

operator<<: O(mn)

quarter: O(mn)

operator==: O(mn)

operator!=: O(mn)

swap_rows: O(n)

rref (provided in matrix_main.cpp): O(mmn) = O(m^2 n)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

I used Dr. Memory and printf(). The most significant corner cases happen due to
the strange behavior of matrix when either dimension becomes zero. Hence,
besides test cases provided in simple_test(), I implement myself test cases to
cover those functions that were not fully tested in simple_test():

multiply_by_coefficient()
get_col()
transpose()
quarter()
subtract()

Hence, like what I did in extra credit test that I fully test for all possible
matrix dimension and its changes, I test these 4 functions for matrices of
different dimensions. Also, multiply_by_coefficient() should be considered when
multiply zero or negative number.



EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.

I implemented resize() for extra credit. Suppose p = the number of rows of new
matrix and q = the number of columns of new matrix.The order notation is
resize(): O(pq)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

