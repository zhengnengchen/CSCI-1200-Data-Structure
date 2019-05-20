#include <fstream>
#include <cassert>
#include <cstdlib>

#include "ds_hashset.h"

// Hash function borrowed from lab
class hash_string_obj {
public:
    unsigned int operator() (const std::string& key) const {
        //  This implementation comes from
        //  http://www.partow.net/programming/hashfunctions/
        unsigned int hash = 1315423911;
        for (unsigned int i = 0; i < key.size(); ++i)
            hash ^= ((hash << 5) + key[i] + (hash >> 2));
        return hash;
    }
};

typedef ds_hashset<hash_string_obj> ds_hashset_type;

// Helper function to compute the difference of two string
int compare_key(const std::string& key1, const std::string& key2) {
    int count = 0;
    for (unsigned int i = 0; i < key1.size(); ++i) {
        if (key1[i] != key2[i]) ++count;
    }
    return count;
}

int main() {
    // Initialize a few variable
    ds_hashset_type hash_table;
    std::string data, tmp;
    int kmer;
    
    // Main part of main function. Used to process command line input. Hash
    // table is built when necessary information are acquired.
    while (std::cin >> tmp) {
        if (tmp == std::string("genome")) {
            // Open genome file to read in data
            std::cin >> tmp;
            std::ifstream in_str(tmp);
            if (!in_str.good()) {
                std::cerr << "Can't open " << tmp << " to read." << std::endl;
                exit(1);
            }
            
            // Connect each line into one string
            while (in_str >> tmp) data += tmp;
        } else if (tmp == std::string("table_size")) {
            // Optional parameter: size.
            std::cin >> tmp;
            unsigned int size = (unsigned int) atoi(tmp.c_str());
            assert(size > 0);
            hash_table.setSize(size);
        } else if (tmp == std::string("occupancy")) {
            // Optional parameter: occupancy ratio
            std::cin >> tmp;
            float occupancy = (float) atof(tmp.c_str());
            assert(occupancy > 0 && occupancy <= 1);
            hash_table.setOccupancy(occupancy);
        } else if (tmp == std::string("kmer")) {
            // Length of one k-mer.
            std::cin >> tmp;
            kmer = atoi(tmp.c_str());
            
            // Once kmer length is known, build the whole hash table.
            for (unsigned int i = 0; i <= data.size() - kmer; ++i) {
                std::string key = data.substr(i, kmer);
                hash_table.insert(key, i);
            }
        } else if (tmp == std::string("query")) {
            // Read in query's key
            std::cin >> tmp;
            int tolerance = atoi(tmp.c_str());
            std::cin >> tmp;
            std::cout << "Query: " << tmp << std::endl;
            
            // Using key string to find associating position list in hash table
            std::list<int> pos_list = hash_table.getPosition(tmp, kmer);
            if (pos_list.size() == 0) {
                std::cout << "No Match" << std::endl;
            } else {
                // We find position list using first-kmer of query string. Need
                // to check whole length string one by one
                std::vector<Result> results;
                unsigned int key_size = tmp.size();
                for (std::list<int>::const_iterator itr = pos_list.begin();
                     itr != pos_list.end() && *itr <= data.size() - key_size;
                     ++itr) {
                    std::string data_key = data.substr(*itr, key_size);
                    int error = compare_key(data_key, tmp);
                    if (error <= tolerance)
                        results.push_back(Result(*itr, error, data_key));
                }
                
                // Print out each validate result
                if (results.size() == 0) {
                    std::cout << "No Match" << std::endl;
                } else {
                    for (unsigned int i = 0; i < results.size(); ++i)
                        results[i].print(std::cout);
                }
            }
        } else {
            break;
        }
    }
    
    return 0;
}
