#ifndef ds_hashset_h_
#define ds_hashset_h_

// Main structure is borrowed from lab's hash set file
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

// A help class used to represent the data structure of query result
class Result {
public:
    // Constructor
    Result(const unsigned int& p, const int& e, const std::string& k)
    : position(p), error(e), key(k) {}
    
    // Helper function for printing result
    void print(std::ostream& ostr) {
        ostr << position << " " << error << " " << key << std::endl;
    }
    
private:
    // Representation
    unsigned int position;
    int error;
    std::string key;
};

// The ds_hashset is templated over both the type of key and the type
// of the hash function, a function object.
template <typename HashFunc>
class ds_hashset {
public:
    // =================================================================
    // HASH SET IMPLEMENTATION
    
    // Constructor for the table accepts the size of the table.  Default
    // constructor for the hash function object is implicitly used.
    ds_hashset(unsigned int init_size = 100, float init_occupancy = 0.5)
    : m_table(init_size), m_size(0), m_occupancy(init_occupancy) {}
    
    // Copy constructor just uses the member function copy constructors.
    ds_hashset(const ds_hashset<HashFunc>& old)
    : m_table(old.m_table), m_size(old.m_size), m_occupancy(old.m_occupancy) {}
    
    ~ds_hashset() {}
    
    // Copy constructor
    ds_hashset& operator=(const ds_hashset<HashFunc>& old) {
        if (&old != this) {
            this->m_table = old.m_table;
            this->m_size = old.m_size;
            this->m_hash = old.m_hash;
            this->m_occupancy = old.m_occupancy;
        }
        return *this;
    }
    
    // Modifiers. Used when optional parameter is specified
    void setSize(unsigned int s) { m_size = s; resize_table(s); }
    void setOccupancy(float o) { m_occupancy = o; }
    
    // Insert the key and position into hash table
    void insert(const std::string& key, const int position) {
        // Check if table is too crowded
        unsigned int threshold = (unsigned int)floor(m_occupancy*m_table.size());
        if (m_size >= threshold) this->resize_table(2 * m_table.size());
        
        // Compute the hash value and then the table index
        unsigned int index = m_hash(key) % m_table.size();
        
        // Find appropriate position
        if (m_table[index].first.size() == 0) {
            // If we happen to find a space for key
            m_table[index] = std::make_pair(key, std::list<int>());
            m_size += 1;
        } else {
            // While there is collision, using linear probe to find available
            // slot
            while (m_table[index].first != key &&
                   m_table[index].first.size() != 0) {
                index += 1;
                
                // If we arrive at the end of table
                if (index == m_table.size()) index = 0;
            }
            
            // No collision found. Key is not in table. Find a empty slot.
            if (m_table[index].first.size() == 0) {
                m_table[index] = std::make_pair(key, std::list<int>());
                m_size += 1;
            }
        }
        
        // Previous work just found position but do not do anything to list.
        // Append here
        m_table[index].second.push_back(position);
    }
    
    // Find key's position list and return
    const std::list<int> getPosition(const std::string& key,
                                     const int& kmer) const {
        std::string key_part = key.substr(0, kmer);
        unsigned int hash_value = m_hash(key);
        unsigned int index = hash_value % m_table.size();
        const unsigned int const_index = index;
        
        // Find using linear probing
        while (m_table[index].first != key_part) {
            index += 1;
            if (index == m_table.size()) index = 0;
            
            // Returning to start position means that we found nothing
            if (index == const_index) return std::list<int>();
        }
        
        // A index is found. Returning associating list no matther if it belongs
        // to key or is empty
        return m_table[index].second;
    }
    
private:
    // =================================================================
    // HASH SET REPRESENTATION
    std::vector<std::pair<std::string, std::list<int> > > m_table;
    HashFunc m_hash;
    unsigned int m_size;
    float m_occupancy;
    
    // =================================================================
    // Private helper functions
    void resize_table(unsigned int new_size) {
        // Initialize a new table
        std::vector<std::pair<std::string, std::list<int> > > new_table(new_size);
        
        // For each entry in old table
        for (unsigned int i = 0; i < m_table.size(); ++i) {
            if (m_table[i].first.size() != 0) {
                // Extract key
                std::string key = m_table[i].first;
                
                // Rehash
                unsigned int hash_value = m_hash(key);
                unsigned int index = hash_value % new_size;
                
                // Insert into new position of new hash table
                while (new_table[index].first.size() != 0) {
                    index += 1;
                    if (index == new_table.size()) index = 0;
                }
                new_table[index] = m_table[i];
            }
        }
        
        // Update m_table to new_table
        this->m_table = new_table;
    }
};
#endif
