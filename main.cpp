#include "mythread.h"
#include <thread>

using namespace std;

int main()
{
    cout<<"hello,thread"<<endl;
    int x=1;
    std::thread mytobj(func1,1);
    if(mytobj.joinable())
    {
        cout<<"mytobj.joinable()"<<endl;
        mytobj.join();
    }

    return 0;
}