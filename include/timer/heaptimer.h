
#ifndef HEAP_TIMER_H
#define HEAP_TIMER_H

#include "timer/timer.h"


class HeapTimer : public Timer {
public:
    HeapTimer() { heap_.reserve(64); }

    ~HeapTimer() { clear(); }
    
    void adjust(int id, int timeout) override;

    void add(int id, int timeout, const TimeoutCallBack& cb) override;

    void doWork(int id) override;

    void clear() override;

    void tick() override;

    void pop() override;

    int GetNextTick() override;

private:
    void del_(size_t i);
    
    void siftup_(size_t i);

    bool siftdown_(size_t index, size_t n);

    void SwapNode_(size_t i, size_t j);

    std::vector<TimerNode> heap_;

    std::unordered_map<int, size_t> ref_;
};

#endif //HEAP_TIMER_H