#include "timer/lfutimer.h"

void LFUTimer::adjust(int id, int timeout) {
    //调整指定id的结点 
    assert(!time_.empty() && ref_.count(id) > 0);
    auto Timeout = Clock::now() + MS(timeout);
    auto& node = *ref_[id];
    time_[Timeout].splice(time_[Timeout].end(),time_[node.expires],ref_[id]);
    if(time_[node.expires].empty())time_.erase(node.expires);
    node.expires = Timeout;
}

void LFUTimer::add(int id, int timeout, const TimeoutCallBack& cb) {
    assert(id >= 0);
    auto Timeout = Clock::now() + MS(timeout);
    if(!ref_.count(id)) {
        ref_[id] = time_[Timeout].emplace(time_[Timeout].end(),id,Timeout,cb);
    }else {
        auto& node = *ref_[id];
        time_[Timeout].splice(time_[Timeout].end(),time_[node.expires],ref_[id]);
        if(time_[node.expires].empty())time_.erase(node.expires);
        node.expires = Timeout;
        node.cb = cb;
    }
}

void LFUTimer::doWork(int id) {
    //删除指定id结点，并触发回调函数
    if(time_.empty() || ref_.count(id) == 0) {
        return;
    }
    auto node = *ref_[id];
    node.cb();
    time_[node.expires].erase(ref_[node.id]);
    ref_.erase(node.id);
    if(time_[node.expires].empty())time_.erase(node.expires);
}

void LFUTimer::clear() {
    while (!time_.empty()) {
        pop();
    };
}

void LFUTimer::tick() {
    // 清除超时结点
    if(time_.empty()) {
        return ;
    }
    while(!time_.empty()) {
        auto node = time_.begin()->second.front();
        if(std::chrono::duration_cast<MS>(node.expires - Clock::now()).count() > 0) { 
            break; 
        }
        node.cb();
        time_[node.expires].pop_front();
        ref_.erase(node.id);
        if(time_[node.expires].empty())time_.erase(node.expires);
    }
}

void LFUTimer::pop() {
    auto node = time_.begin()->second.front();
    node.cb();
    time_[node.expires].pop_front();
    ref_.erase(node.id);
    if(time_[node.expires].empty())time_.erase(node.expires);
}

int LFUTimer::GetNextTick() {
    tick();
    size_t res = -1;
    if(!time_.empty()) {
        res = std::chrono::duration_cast<MS>(time_.begin()->first - Clock::now()).count();
        if(res < 0) { res = 0; }
    }
    return res;
}






