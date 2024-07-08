#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <semaphore.h>

using namespace std;

sem_t sem;
mutex mtx;

void plane(int id, int runway) {
    {
        lock_guard<mutex> lck(mtx);
        cout << "Plane " << id << " requesting permission to land."<< endl;
    }

    sem_wait(&sem);

    {
        lock_guard<mutex> lck(mtx);
        cout << "Plane " << id << " landing on runway r" << runway << "..." << endl;
    }

    this_thread::sleep_for(chrono::seconds(2));

    {
        lock_guard<mutex> lck(mtx);
        cout << "Plane " << id << " landed on runway r" << runway << "." << endl;
    }

    sem_post(&sem);
}

int main() {
    int n, r;
    cout << "Enter the number of planes to arrive: ";
    cin >> n;
    cout << "Enter the number of runways available: ";
    cin >> r;

    sem_init(&sem, 0, r);

    thread planes[n];
    for (int i = 0; i < n; ++i)
        planes[i] = thread(plane, i + 1, (i % r) + 1);

    for (int i = 0; i < n; ++i)
        planes[i].join();

    sem_destroy(&sem);

    return 0;
}
