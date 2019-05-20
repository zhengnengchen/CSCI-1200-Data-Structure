#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>
#include <iostream>    //Needed for std::ostream

typedef unsigned int tq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class TimeQueue {
public:
    // Constructor
    TimeQueue() {};
    
    // Accessor
    const Job* top() const { return queue.front(); };
    
    // Modifiers
    void push(Job* j);
    Job* pop();
    void remove_from_index(tq_hook index);
    
    // print. Using overloaded operator.
    void printHeap(std::ostream& ostr) const;
private:
    // Representation
    std::vector<Job*> queue;
};

#endif
