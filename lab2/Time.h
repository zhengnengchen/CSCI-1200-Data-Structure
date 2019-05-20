class Time {
public:
    Time();
    Time(int aHour, int aMinute, int aSecond);
    
    // ACCESSORS
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    
    //MODIFIERS
    void setHour(int h);
    void setMinute(int m);
    void setSecond(int s);
    
    // other member functions
    void PrintAmPm() const;
    
private: // Member variables
    int hour, minute, second;
};

bool IsEarlierThan(const Time& t1, const Time& t2);
