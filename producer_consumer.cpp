#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <condition_variable>
#define INT int
using namespace std;

mutex mtx;
condition_variable cv_producer,cv_consumer;
INT MAX_BUFFER_SIZE = 10;
INT ITEM_COUNT = 0;


void producer(){
    while(true){
        unique_lock<mutex> lock(mtx); /*lock mutex*/  
        cv_producer.wait(lock,[]{ return ITEM_COUNT<MAX_BUFFER_SIZE; }); /*wait when this condition false*/
        ITEM_COUNT += 1; /*increase item count*/
        cout << "Produced, Buffer Size: " << ITEM_COUNT << endl;
        cv_consumer.notify_one(); /*signal to consumer to consume item*/
        this_thread::sleep_for(500ms);
    }
}

void consumer(){
    while(true){
        unique_lock<mutex> lock(mtx); /*lock mutex*/  
        cv_consumer.wait(lock,[]{ return ITEM_COUNT>0; }); /*wait when this condition false*/
        ITEM_COUNT -= 1; /*decrease item count*/
        cout << "Consumed, Buffer Size: " << ITEM_COUNT << endl;
        cv_producer.notify_one(); /*signal to producer to produce item*/
        this_thread::sleep_for(500ms);
    }
}

int main() {
    thread t1(consumer);
    thread t2(producer);
    
    t1.join();
    t2.join();
    return 0;
}