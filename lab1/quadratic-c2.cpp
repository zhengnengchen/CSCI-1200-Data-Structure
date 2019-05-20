#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function


// Returns true if the candidate root is indeed a root of the polynomial a*x*x + b*x + c = 0 
bool check_root(int a, int b, int c, float root) {  
    // plug the value into the formula
    float check = a * root * root + b * root + c;
    // see if the absolute value is zero (within a small tolerance)
    if (fabs(check) > 0.0001) {
        std::cerr << "ERROR:  " << root << " is not a root of this formula." << std::endl;
        return false;
    } else {
        return true;
    }
}

/* Use the quadratic formula to find the two real roots of polynomial.   Returns 
true if the roots are real, returns false if the roots are imaginary.  If the roots 
are real, they are returned through the reference parameters root_pos and root_neg. */ 
bool find_roots(int a, int b, int c, float &root_pos, float &root_neg) {
    // compute the quantity under the radical of the quadratic formula
    int radical = b*b - 4*a*c;
    // if the radical is negative, the roots are imaginary
    if (radical < 0) {
        std::cerr << "ERROR:  Imaginary roots" << std::endl;
        return false;
    }
    float sqrt_radical = sqrt(radical);
    // compute the two rootsl
    root_pos = (-b + sqrt_radical) / (2*a);
    root_neg = (-b - sqrt_radical) / (2*a);
    return true;
}

int main() {
  int b_array[5], c_array[5], smaller_root[5];
  // We will loop until we are five pairs of coefficients
  for (int i = 0; i < 5; ++i) {
      std::cout << "Enter 2 integer coefficients to a quadratic function: a*x*x + b*x + c = 0" << std::endl;
      int my_b, my_c;
      std::cin >> my_b >> my_c;
      // create a place to store the roots
      b_array[i] = my_b;
      c_array[i] = my_c;
  }

  // Another loop to calculate smaller root
  std::cout <<  "The smaller root is: ";
  for (int i = 0; i < 5; ++i) {
      float root_1, root_2;
      bool success = find_roots(1, b_array[i], c_array[i], root_1, root_2);
      // If the polynomial has imaginary roots, skip the rest of this loop and start over
      if (!success) {
          std::cout << "Skip a imaginary result." << std::endl;
          continue;
      }
      smaller_root[i] = root_2;
      std::cout << smaller_root[i] << " ";
      // Check our work...
      if (!check_root(1, b_array[i], c_array[i], root_1) || !check_root(1, b_array[i], c_array[i], root_2)) {
          std::cerr << "ERROR:  Unable to verify one or both roots." << std::endl;
          // if the program has an error, we choose to exit with a
          // non-zero error code
          exit(1);
      }
  }
  std::cout << std::endl;
  // by convention, main should return zero when the program finishes normally
  return 0; 
}
