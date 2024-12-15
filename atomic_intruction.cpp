#include<thread>
#include<atomic>
#include<vector>
#include<iostream>
using namespace std;

static atomic<int> shared_value = 0;

void shared_value_increment(){
    shared_value += 1;
}

int main(){
    vector<thread> threads;
    for(int i=0;i<1000;i++){
        threads.push_back(thread(shared_value_increment));
    }
    for(int i=0;i<1000;i++){
        threads[i].join();
    }
    cout<<"Shared Value: "<<shared_value<<endl;
    return 0;
}