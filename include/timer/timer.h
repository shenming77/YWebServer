
#ifndef TIMER_H
#define TIMER_H

#include <queue>
#include <unordered_map>
#include <time.h>
#include <algorithm>
#include <arpa/inet.h> 
#include <functional> 
#include <assert.h> 
#include <chrono>
#include "log/log.h"

typedef std::function<void()> TimeoutCallBack;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds MS;
typedef Clock::time_point TimeStamp;

struct TimerNode {
    int id;
    TimeStamp expires;
    TimeoutCallBack cb;
    explicit TimerNode(const int& id, const TimeStamp& expires,const TimeoutCallBack& cb): id(id), expires(expires), cb(cb) {}
    explicit TimerNode() = default;
    bool operator<(const TimerNode& t) {
        return expires < t.expires;
    }
    bool operator>(const TimerNode& t) const {
        return expires > t.expires;
    }
};

class Timer {
public:
    Timer() = default;

    virtual ~Timer() = default;
    
    virtual void adjust(int id, int timeout) = 0; //调整指定id的结点

    virtual void add(int id, int timeout, const TimeoutCallBack& cb) = 0;

    virtual void doWork(int id) = 0; // 删除指定id结点，并触发回调函数 

    virtual void clear() = 0;

    virtual void tick() = 0; //清除超时结点 

    virtual void pop() = 0;

    virtual int GetNextTick() = 0; //获取一个最近时间

};

using TimePtr = std::unique_ptr<Timer>;

#endif //TIMER_H