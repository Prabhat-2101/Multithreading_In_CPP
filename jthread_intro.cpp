#include<thread>
#include<iostream>
using namespace std;

void hello(int count){
    cout<<"Hello Thread id: "<<this_thread::get_id<<endl;
    for(int i=0;i<count;i++) cout<<"hello"<<endl;
}

void hii(int count){
    cout<<"Hii Thread id: "<<this_thread::get_id<<endl;
    for(int i=0;i<count;i++) cout<<"hii"<<endl;
}

int main(){
    jthread t1(hello,5);
    jthread t2(hii,5);
    return 0;
}