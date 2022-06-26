#include "mythread.h"
void func1(int x)
{
    std::chrono::milliseconds dura(2000);
    std::this_thread::sleep_for(dura);
    std::cout<<"我的线程func11开始执行了x="<< x <<std::endl;
    return;
}

class InferImpl:public Infer{
public:
    virtual ~InferImpl()
    {
        // stop();
    }
    bool startup(const std::string& file)
    {
        file_=file;
    }

private:
    std::string file_;
    std::thread worker_thread_;
    std::mutex lock_;

};