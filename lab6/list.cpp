#include <iostream>
#include <list>

void reverse_list(std::list<int>& lst) {
    int value;
    std::list<int>::iterator itr = lst.begin();
    std::list<int>::reverse_iterator r_itr = lst.rbegin();
    for (unsigned int i = 0; i < lst.size()/2; ++i, ++itr, ++r_itr) {
        value = *itr;
        *itr = *r_itr;
        *r_itr = value;
    }
}

void print_list(const std::list<int>& lst) {
    std::cout << "size: " << lst.size() << "; elements:";
    for (std::list<int>::const_iterator itr = lst.begin(); itr != lst.end(); ++itr) {
        std::cout << " " << *itr;
    }
    std::cout << std::endl;
}

int main() {
    std::list<int> a;
    std::cout << "Empty list a:" << std::endl;
    print_list(a);
    reverse_list(a);
    std::cout << "After reverse, empty list a:" << std::endl;
    print_list(a);
    std::cout << std::endl;

    a.push_back(0);
    std::cout << "list a of size 1:" << std::endl;
    print_list(a);
    reverse_list(a);
    std::cout << "After reverse, list a of size 1:" << std::endl;
    print_list(a);
    std::cout << std::endl;

    a.push_front(1);
    std::cout << "list a of size 2:" << std::endl;
    print_list(a);
    reverse_list(a);
    std::cout << "After reverse, list a of size 2:" << std::endl;
    print_list(a);
    std::cout << std::endl;
    
    for (int i = a.size(); i < 20; ++i) {
        a.push_back(i);
    }
    std::cout << "list a of size 20:" << std::endl;
    print_list(a);
    reverse_list(a);
    std::cout << "After reverse, list a of size 2:" << std::endl;
    print_list(a);

    return 0;
}