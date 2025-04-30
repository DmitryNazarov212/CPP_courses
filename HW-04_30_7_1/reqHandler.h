#pragma once
#include "thPool.h"

class ReqHandler
{
private:
    ThreadPool m_pool;
public:
    ReqHandler();
    ~ReqHandler();
    template<typename F, typename... Args> void push_task(F&& f, Args&&... args);
};

template<typename F, typename... Args> void ReqHandler::push_task(F&& f, Args&&... args)
{
    m_pool.push_task(std::forward<F>(f), std::forward<Args>(args)...);
}