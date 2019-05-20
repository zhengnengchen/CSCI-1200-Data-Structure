#include <cstdint>

class Time {
public:
    Time();
    Time(uintptr_t aHour, uintptr_t aMinute, uintptr_t aSecond);
    
    // ACCESSORS
    const uintptr_t& getHour() const;
    const uintptr_t& getMinute() const;
    const uintptr_t& getSecond() const;
    
    //MODIFIERS
    void setHour(uintptr_t h);
    void setMinute(uintptr_t m);
    void setSecond(uintptr_t s);
    
    // other member functions
    void PrintAmPm() const;
    
private: // Member variables
    uintptr_t hour, minute, second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);
