#include "mythread.h"

using namespace std;


mutex mutex_;
const u_int limit=5;
condition_variable cv_;
struct Job{
    shared_ptr<promise<string>> pro;
    string input;
};
queue<Job> q_job;
void video_capture()
{
    Job job;
    while(true)
    {
        {
            unique_lock<mutex> lock_g(mutex_);
            string temp="video_capture";
            cv_.wait(lock_g,[&]()
            {
                // return false，表示继续等待;
                // return true,表示不等待，跳出wait;
                return q_job.size()<limit;
            });

            job.pro.reset(new promise<string>());
            job.input=temp;
            q_job.push(job);
            // 等待，直到set_value被执行了

        }
            auto result=job.pro->get_future().get();
            cout<<"video_capture()"<<q_job.size()<<endl;
            cout<<"auto result=job.pro->get_future().get();"<<result<<endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void infer_worker()
{
    while(true)
    {
        if(!q_job.empty())
        {
            unique_lock<mutex> lock_g(mutex_);
            auto get_job=q_job.front();
            q_job.pop();
            cv_.notify_one();
            get_job.pro->set_value("set_value");
            cout<<"infer_worker()"<<q_job.size()<<endl;
        }
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

void thread_test()
{
        // cout<<"hello,thread"<<endl;
    // int x=1;
    // std::thread mytobj(func1,1);
    // mytobj.detach();
    // if(mytobj.joinable())
    // {
    //     cout<<"mytobj.joinable()"<<endl;
    //     mytobj.join();
    // }else{
    //     cout<<"mytobj.joinable() is not!"<<endl;
    // }
    // cout<<"This is main()!"<<endl;
    thread capture(video_capture);
    thread infer_capture(infer_worker);
    if(capture.joinable())
    {
        cout<<"capture.joinable()"<<endl;
        capture.join();
    }else{
        cout<<"capture.joinable() is not!"<<endl;
    }


    if(infer_capture.joinable())
    {
        cout<<"infer_capture.joinable()"<<endl;
        infer_capture.join();
    }else{
        cout<<"infer_capture.joinable() is not!"<<endl;
    }
}
int main()
{
    cout<<"This is main()!"<<endl;
    func11();
    return 0;
}