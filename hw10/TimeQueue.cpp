#include "TimeQueue.h"
#include "Job.h"
#include <utility> // std::swap
#include <cassert> // assert()

// push() append the pointer to the last leaf of queue. Then newly added pointer
// is percolated up to a suitable position. time_ptr and time_hook need to be
// updated
void TimeQueue::push(Job* job) {
    // First, put job ptr into vector and point time pointer to this queue
    queue.push_back(job);
    queue.back()->time_ptr = this;
    queue.back()->time_hook = queue.size() - 1;
    
    // Then using percolate_up() to move newly added job to a suitable position
    unsigned int size = queue.size();
    unsigned int current = size - 1;
    while (current != 0) {
        unsigned int parent = (current - 1) / 2;
        // Older(smaller) timestamp is on the top of heap.
        if (queue[current]->timestamp < queue[parent]->timestamp) {
            // Swapping two elements
            std::swap(queue[current]->time_hook, queue[parent]->time_hook);
            std::swap(queue[current], queue[parent]);
            
            // Moving one level up
            current = parent;
        } else break;
    }
}

// First element in queue is returned and deleted from queue. time_ptr and
// time_hook need to be updated
Job* TimeQueue::pop() {
    // Make sure we do not pop element from empty queue
    assert(!queue.empty());
    
    // Replace root with the value of last leaf and remove last leaf
    Job* root = queue[0];
    queue[0] = queue[queue.size() - 1];
    queue.pop_back();
    
    // percolate_down()
    const unsigned int size = queue.size();
    unsigned int current = 0;
    while (current * 2 + 1 < size) {
        // Pointing to child with smaller timestamp
        unsigned int child;
        if (current * 2 + 2 < size &&
            queue[current*2+2]->timestamp < queue[current*2+1]->timestamp)
            child = current * 2 + 2;
        else child = current * 2 + 1;
        
        // Older(smaller) timestamp is on the top of heap.
        if (queue[child]->timestamp < queue[current]->timestamp) {
            // Swapping elements in heap
            std::swap(queue[current]->time_hook, queue[child]->time_hook);
            std::swap(queue[current], queue[child]);
            
            // Moving one level down
            current = child;
        } else break;
    }
    
    // Root, or oldest job, is returned
    return root;
}

// remove_from_index() remove a element using hook index and processing the
// remaining of vector by moving children up to parent's position to fill
// queue vector.
void TimeQueue::remove_from_index(tq_hook index) {
    assert(0 <= index && index < queue.size());
    
    // Processing children
    const unsigned int size = queue.size();
    unsigned int current = index;
    while (current * 2 + 1 < size) {
        // Find the index of child with older(smaller) timestamp
        unsigned int smaller_child;
        if (current * 2 + 2 < size &&
            queue[current*2+2]->timestamp < queue[current*2+1]->timestamp)
            smaller_child = current * 2 + 2;
        else smaller_child = current * 2 + 1;
        
        // Move child up to current position
        queue[smaller_child]->time_hook = current;
        queue[current] = queue[smaller_child];
        
        // Go to one level deeper
        current = smaller_child;
    }
    
    // Finally, a leaf is empty. Hence we remove this empty slot from vector by
    // move each element after the position pointed by 'current' one position
    // ahead and pop_back last position
    while (current + 1 < size) {
        queue[current + 1]->time_hook = current;
        queue[current] = queue[current + 1];
        current += 1;
    }
    queue.pop_back();
}

void TimeQueue::printHeap(std::ostream& ostr) const {
    ostr << "TQ " << queue;
}
