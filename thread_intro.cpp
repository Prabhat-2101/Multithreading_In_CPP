#include<thread>
#include<iostream>
using namespace std;

void hello(){
    cout<<"Hello Thread id: "<<this_thread::get_id()<<endl;
    for(int i=0;i<5;i++) cout<<"hello\n";
}
void hii(){
    cout<<"Hii Thread id: "<<this_thread::get_id()<<endl;
    for(int i=0;i<5;i++) cout<<"hii\n";
}

int main(){
    cout<<"Main Thread id: "<<this_thread::get_id()<<endl;
    auto namaste = [](){
        cout<<"Namaste Thread id: "<<this_thread::get_id()<<endl;
        for(int i=0;i<5;i++) cout<<"namaste\n";
    };
    thread t1(hello);
    thread t2(hii);
    thread t3(namaste);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}