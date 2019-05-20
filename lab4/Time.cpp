#include "Time.h"
#include <iostream>
#include <iomanip>

Time::Time() { // Default constructor
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond) { //constructor using arguments
    hour = aHour;
    minute = aMinute;
    second = aSecond;
}

const uintptr_t& Time::getHour() const {
    return hour;
}

const uintptr_t& Time::getMinute() const {
    return minute;
}

const uintptr_t& Time::getSecond() const {
    return second;
}

void Time::setHour(uintptr_t h) {
    hour = h;
}

void Time::setMinute(uintptr_t m) {
    minute = m;
}

void Time::setSecond(uintptr_t s) {
    second = s;
}

void Time::PrintAmPm() const {
    
    if (hour > 12) std::cout << hour - 12;
    else if (hour == 0) std::cout << hour + 12;
    else std::cout << hour;
    std::cout << ':' << std::setfill('0') << std::setw(2) << minute << ':' << std::setfill('0') << std::setw(2) << second;
    if (hour >= 12) std::cout << " PM" << std::endl;
    else std::cout << " AM" << std::endl;
}

bool IsEarlierThan(const Time& t1, const Time& t2) {
    if (t1.getHour() < t2.getHour()) return true;
    else if (t1.getHour() == t2.getHour() && t1.getMinute() < t2.getMinute()) return true;
    else if (t1.getHour() == t2.getHour() && t1.getMinute() == t2.getMinute() && t1.getSecond() < t2.getSecond()) return true;
    else return false;
}
