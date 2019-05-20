#include "Time.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    Time t1(5, 30, 59);
    Time t2;
    
    t2.setHour(14);
    t2.setMinute(5);
    t2.setSecond(4);
    
    Time t3(12, 0, 0);
    Time t4(0, 0, 0);
    
    t1.PrintAmPm();
    t2.PrintAmPm();
    t3.PrintAmPm();
    t4.PrintAmPm();
    
    std::vector<Time> times;
    
    times.push_back(t1);
    times.push_back(t2);
    times.push_back(t3);
    times.push_back(t4);
    sort(times.begin(), times.end(), IsEarlierThan);
    std::cout << "After sorting:" << std::endl;
    for (int i = 0; i < times.size(); ++i) {
        times[i].PrintAmPm();
    }
    return 0;
}
