#include "UrgentQueue.h"
#include "Job.h"
#include <utility> // std::swap
#include <cassert> // assert()

// push() append the pointer to the last leaf of queue. Then newly added pointer
// is percolated up to a suitable position. priority_ptr and urgent_hook need to
// be updated
void UrgentQueue::push(Job* job) {
    // First, put job ptr into vector and point priority pointer to this queue
    queue.push_back(job);
    queue.back()->priority_ptr = this;
    queue.back()->urgent_hook = queue.size() - 1;
    
    // Then using percolate_up() to move newly added job to a suitable position
    unsigned int size = queue.size();
    unsigned int current = size - 1;
    while (current != 0) {
        unsigned int parent = (current - 1) / 2;
        if (queue[current]->priority > queue[parent]->priority) {
            // Swapping two elements
            std::swap(queue[current]->urgent_hook, queue[parent]->urgent_hook);
            std::swap(queue[current], queue[parent]);
            
            // Moving one level up
            current = parent;
        } else break;
    }
}

// First element in queue is returned and deleted from queue. priority_ptr and
// urgent_hook need to be updated
Job* UrgentQueue::pop() {
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
        // Pointing child to right child if right child exists and has greater
        // priority. Otherwise, pointing to left child.
        unsigned int child;
        if (current * 2 + 2 < size &&
            queue[current*2+2]->priority > queue[current*2+1]->priority)
            child = current * 2 + 2;
        else child = current * 2 + 1;
        
        if (queue[child]->priority > queue[current]->priority) {
            // Swapping elements in heap
            std::swap(queue[current]->urgent_hook, queue[child]->urgent_hook);
            std::swap(queue[current], queue[child]);
            
            // Moving one level down
            current = child;
        } else break;
    }
    
    // Root, or heighest priority job, is returned
    return root;
}

// remove_from_index() remove a element using hook index and processing the
// remaining of vector by moving children up to parent's position to fill
// queue vector.
void UrgentQueue::remove_from_index(uq_hook index) {
    asserr(0 < index && index < queue.size());
    
    // Processing children
    const unsigned int size = queue.size();
    unsigned int current = index;
    while (current * 2 + 1 < size) {
        // Find the index of child with larger priority
        unsigned int larger_child;
        if (current * 2 + 2 < size &&
            queue[current*2+2]->priority > queue[current*2+1]->priority)
            larger_child = current * 2 + 2;
        else larger_child = current * 2 + 1;
        
        // Move child up to current position
        queue[larger_child]->urgent_hook = current;
        queue[current] = queue[larger_child];
        
        // Go to one level deeper
        current = larger_child;
    }
    
    // Finally, a leaf is empty. Hence we remove this empty slot from vector by
    // move each element after the position pointed by 'current' one position
    // ahead and pop_back last position
    while (current + 1 < size) {
        queue[current + 1]->urgent_hook = current;
        queue[current] = queue[current + 1];
        current += 1;
    }
    queue.pop_back();
}

void UrgentQueue::printHeap(std::ostream& ostr) const {
    ostr << "UQ " << queue;
}
