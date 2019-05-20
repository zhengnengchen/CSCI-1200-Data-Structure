#include <iostream>
#include <cmath>
#include <cstdint>

void compute_squares(uintptr_t *a, uintptr_t *b, const uintptr_t& n) {
    // Use ptr to iterate
    uintptr_t *s = a, *t = b;
    // b[i] = a[i]^2
    for (uintptr_t i = 0; i < n; ++i) {
        *t = pow(*s, 2);
        ++t;
        ++s;
    }
}

int main() {
    // Initialization
    uintptr_t n = 3;
    uintptr_t a[n], b[n];
    uintptr_t *p = a, *q = b;
    
    // Assign a with a[0] = 3, a[1] = 4, a[2] = 5 and print out
    for (uintptr_t i = 0; i < n; ++i) {
        *p = i + 3;
        std::cout << "a[" << i << "]: " << *p << std::endl;
        ++p;
    }
    
    // b[0] = 3^2 = 9, b[1] = 16, b[2] = 25
    compute_squares(a, b, n);
    
    // Print out b[i]
    std::cout << std::endl;
    for (uintptr_t i = 0; i < n; ++i) {
        std::cout << "b[" << i << "]: " << *q << std::endl;
        ++q;
    }
    
    return 0;
}
