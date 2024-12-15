#include<thread>
#include<iostream>
#include<vector>
using namespace std;

mutex global_lock;
static int shared_value = 0;

void shared_value_increment(){
    shared_value = shared_value + 1;
}

void shared_value_increment_noerror(){
    global_lock.lock();
    shared_value = shared_value + 1;
    global_lock.unlock();   /* removing this will lead to deadlock*/
}

void shared_value_increment_nodeadlock(){
    lock_guard<mutex> lock(global_lock);  /*auto unlocking is done when cursor is out of the function scope.*/
    shared_value = shared_value + 1;
}

int main(){
    vector<thread> threads;
    for(int i=1;i<=100;i++){
        threads.push_back(thread(shared_value_increment_nodeadlock));
    }
    
    for(int i=0;i<100;i++) threads[i].join();
    
    cout<<"Shared Value: "<<shared_value<<endl;
    
    return 0;
}