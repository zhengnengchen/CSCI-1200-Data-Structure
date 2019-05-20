#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main(int argc, char* argv[]) {
    std::ifstream input(argv[1]);
    if (!input.good()) {
        std::cerr << "Cannot open " << argv[1] << " to read" << std::endl;
        return 1;
    }
    
    std::map<std::string, unsigned int> freq;
    std::string tmp;
    std::map<std::string, unsigned int>::iterator it;
    while (input >> tmp) {
        // Check 1
//        freq[tmp] += 1;
        
        // Check2
        it = freq.find(tmp);
        if (it == freq.end()) freq.insert(std::pair<std::string, unsigned int>(tmp, 1));
        else it->second += 1;
    }
    
    unsigned int max_freq = 0;
    for (std::map<std::string, unsigned int>::iterator itr = freq.begin();
         itr != freq.end();
         ++itr) {
        if (itr->second > max_freq) max_freq = itr->second;
    }
    for (std::map<std::string, unsigned int>::iterator itr = freq.begin();
         itr != freq.end();
         ++itr) {
        if (itr->second == max_freq) std::cout << itr->first << " ";
    }
    std::cout << std::endl;
}
