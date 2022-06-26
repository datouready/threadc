#ifndef __mythread__hpp__
#define __mythread__hpp__

#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include <queue>
#include <condition_variable>
#include "func1.h"
// #include <memory>

void func1(int x);
// 封装接口类
class Infer{
public:
    virtual std::shared_future<std::string> commit(const std::string& input)=0;

    virtual ~Infer();
};

std::shared_ptr<Infer> create_infer(const std::string& file);

class Solution{
    // Solution()
    // {
    //     worker_thread_=thread(&Solution::infer_worker,this);
    // }

private:
    void infer_worker()
    {

    }

private:
    std::thread worker_thread_;
};
#endif