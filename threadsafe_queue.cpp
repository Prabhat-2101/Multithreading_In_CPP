#include<condition_variable>
#include<mutex>
#include<queue>
#include<iostream>
using namespace std;

template<typename T>
class Queue{
    queue<T> q;
    mutex mtx;
    condition_variable cond;
    public:
    void push(T item){
        unique_lock<mutex> lock(mtx);
        q.push(item);
        cond.notify_one();
    }
    T front(){
        unique_lock<mutex> lock(mtx);
        cond.wait(lock,[this](){
            return !q.empty();
        });
        T item = q.front();
        return item;
    }
    void pop(){
        unique_lock<mutex> lock(mtx);
        q.pop();
        cond.notify_one();
    }
};

int main(){
    Queue<int> cq;
    cq.push(5);
    cq.push(10);
    cq.push(20);
    cq.pop();
    cout<<cq.front()<<endl;
    cq.pop();
    cout<<cq.front()<<endl;
    return 0;
}