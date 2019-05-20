#include <iostream>
#include <vector>

void reverse_vector(std::vector<int>& vec) {
    int value;
    for (unsigned int i = 0; i < vec.size()/2; ++i) {
        value = vec[i];
        vec[i] = vec[vec.size() - 1 - i];
        vec[vec.size() - 1 - i] = value;
    }
}

void print_vector(const std::vector<int>& vec) {
    std::cout << "size: " << vec.size() << "; elements:";
    for (unsigned int i = 0; i < vec.size(); ++i) {
        std::cout << " " << vec[i];
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> a;
    std::cout << "Empty vector a:" << std::endl;
    print_vector(a);
    reverse_vector(a);
    std::cout << "After reverse, empty vector a:" << std::endl;
    print_vector(a);
    std::cout << std::endl;

    a.push_back(0);
    std::cout << "Vector a of size 1:" << std::endl;
    print_vector(a);
    reverse_vector(a);
    std::cout << "After reverse, vector a of size 1:" << std::endl;
    print_vector(a);
    std::cout << std::endl;

    a.push_back(1);
    std::cout << "Vector a of size 2:" << std::endl;
    print_vector(a);
    reverse_vector(a);
    std::cout << "After reverse, vector a of size 2:" << std::endl;
    print_vector(a);
    std::cout << std::endl;
    
    for (int i = a.size(); i < 20; ++i) {
        a.push_back(i);
    }
    std::cout << "Vector a of size 20:" << std::endl;
    print_vector(a);
    reverse_vector(a);
    std::cout << "After reverse, vector a of size 2:" << std::endl;
    print_vector(a);

    return 0;
}