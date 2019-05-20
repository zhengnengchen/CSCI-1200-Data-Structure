#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
    std::vector<T> m_heap;
    
public:
    priority_queue() {}
    
    priority_queue( std::vector<T> const& values )
    {
        for (unsigned int i = 0; i < values.size(); ++i) push(values[i]);
    }
    
    const T& top() const
    {
        assert( !m_heap.empty() );
        return m_heap[0];
    }
    
    void push( const T& entry )
    {
        // Add the the end of vector which is also after last leaf.
        m_heap.push_back(entry);
        
        // percolate_up()
        const unsigned int size = m_heap.size();
        unsigned int current = size - 1;
        while (current != 0) { // while(p->parent)
            unsigned int parent = (current - 1) / 2;
            if (m_heap[current] < m_heap[parent]) { // if (p->value < p->parent->value)
                std::swap(m_heap[current], m_heap[parent]); // swap(p, parent);
                current = parent; // p = p->parent;
            } else break;
        }
    }
    
    void pop()
    {
        assert( !m_heap.empty() );
        // Replace root with the value of last leaf and remove last leaf
        m_heap[0] = m_heap[m_heap.size() - 1];
        m_heap.pop_back();
        
        // percolate_down()
        const unsigned int size = m_heap.size();
        unsigned int current = 0;
        while (current * 2 + 1 < size) { // while(p->left)
            unsigned int child; // TreeNode<T>* child;
            if (current * 2 + 2 < size &&
                m_heap[current * 2 + 2] < m_heap[current * 2 + 1]) {
                // if (p->right && p->right->value < p->left->value)
                child = current * 2 + 2; // child = p->right;
            } else child = current * 2 + 1; // child = p->left;
            if (m_heap[child] < m_heap[current]) { // if (child->value < p->value)
                std::swap(m_heap[child], m_heap[current]); // swap(child, p);
                current = child; // p = child;
            } else break;
        }
    }
    
    const unsigned int size() const { return m_heap.size(); }
    bool empty() const { return m_heap.empty(); }
    
    
    //  The following three functions are used for debugging.
    
    //  Check to see that internally the heap property is realized.
    bool check_heap( )
    {
        return this->check_heap( this->m_heap );
    }
    
    //  Check an external vector to see that the heap property is realized.
    bool check_heap( const std::vector<T>& heap )
    {
        const unsigned int size = heap.size();
        for (unsigned int i = 0; i < size; ++i) {
            unsigned int left = i * 2 + 1;
            unsigned int right = i * 2 + 2;
            // if (p->left && p->value > p->left->value)
            if (left < size && heap[i] > heap[left]) return false;
            // if (p->right && p->value > p->right->value)
            if (right < size && heap[i] > heap[right]) return false;
        }
        return true;
    }
    
    //  A utility to print the contents of the heap.  Use it for debugging.
    void print_heap( std::ostream & ostr )
    {
        for ( unsigned int i=0; i<m_heap.size(); ++i )
            ostr << i << ": " << m_heap[i] << std::endl;
    }
    
};


template <class T>
void heap_sort( std::vector<T> & v )
{
    // Empty or just 1 element
    if (v.size() == 0 || v.size() == 1) return;
    
    // build a binary heap
    const unsigned int size = v.size();
    for (int i = size / 2 - 1; i >= 0; --i) {
        unsigned int parent = i;
        unsigned int child = parent * 2 + 1;
        while (child < size) {
            if (child + 1 < size && v[child] < v[child + 1]) child += 1;
            if (v[parent] < v[child]) {
                std::swap(v[parent], v[child]);
                parent = child;
                child = parent * 2 + 1;
            } else break;
        }
    }
    
    for (unsigned int i = size - 1; i > 0; --i) {
        std::swap(v[0], v[i]);
        
        unsigned int parent = 0;
        unsigned int child = parent * 2 + 1;
        while (child < i) {
            if (child + 1 < i && v[child] < v[child + 1]) child += 1;
            if (v[parent] < v[child]) {
                std::swap(v[parent], v[child]);
                parent = child;
                child = parent * 2 + 1;
            } else break;
        }
    }
}

#endif
