#include<thread>
#include<iostream>
#include<mutex>
using namespace std;
int count = 0;

mutex m;
void fun(){
    int s = 100000;
    m.lock();
    while(s--){
        count += 1;
    }
    m.unlock();
    cout<<count<<endl;
}

int main(){
    thread t1(fun);
    thread t2(fun);
    t1.join();
    t2.join();
    cout<<"After execution of T1&T2 Count: "<<count<<endl;
    thread t3(fun);
    t3.join();
    cout<<"After execution of T3 Count: "<<count<<endl;
    return 0;
}