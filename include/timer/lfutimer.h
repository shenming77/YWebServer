#ifndef LFUTIMER_H
#define LFUTIMER_H

#include <map>
#include <list>
#include <unordered_map>
#include "timer/timer.h"

class LFUTimer : public Timer {
public:
    explicit LFUTimer() = default;

    ~LFUTimer() { clear(); }
    
    void adjust(int id, int timeout) override;

    void add(int id, int timeout, const TimeoutCallBack& cb) override;

    void doWork(int id) override;

    void clear() override;

    void tick() override;

    void pop() override;

    int GetNextTick() override;

private:
    using List = std::list<TimerNode>;
    std::map<TimeStamp, List> time_;
    std::unordered_map<int, List::iterator> ref_;

};



#endif //LFUTIMER_H