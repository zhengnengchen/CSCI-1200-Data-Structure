#include <iostream>

int main() {
    float input[100];
    std::cout << "Input an array of floats: " << std::endl;
    int length;
    std::cin >> length;
    float total = 0;
    for (int i = 0; i < length; ++i) {
        std::cin >> input[i];
        total += input[i];
    }
    float average = total/length;
    std::cout << "Average: " << average << "; Numbers that smaller than average:";
    for (int i = 0; i < length; ++i) {
        if (input[i] < average) {
            std::cout << input[i] << " ";
        }
    }
    std::cout << std::endl;
}
