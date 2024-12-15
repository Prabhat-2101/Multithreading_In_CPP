#include <thread>
#include <iostream>
#include <unordered_map>
#include <mutex>

using namespace std;

static int ticket_count = 1000;
unordered_map<int, int> store_ticket_count;
mutex global_lock;

void ticket_booking_counter(int counter) {
    while (true) {
        global_lock.lock();
        if (ticket_count > 0) {
            ticket_count--;
            store_ticket_count[counter]++;
        } else {
            global_lock.unlock();
            break;
        }
        global_lock.unlock();
    }
}

int main() {
    thread t1(ticket_booking_counter, 1);
    thread t2(ticket_booking_counter, 2);
    thread t3(ticket_booking_counter, 3);

    t1.join();
    t2.join();
    t3.join();

    int total_tickets_sold = 0;
    for (const auto &counter : store_ticket_count) {
        cout << "Counter " << counter.first << ": " << counter.second << " tickets sold." << endl;
        total_tickets_sold += counter.second;
    }

    cout << "Total tickets sold: " << total_tickets_sold << endl;

    if (total_tickets_sold == 1000) {
        cout << "All tickets accounted for. Consistency verified!" << endl;
    } else {
        cout << "Inconsistency detected! Total tickets do not match." << endl;
    }

    return 0;
}