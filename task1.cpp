#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sched.h>
#include <pthread.h>
using namespace std;
using namespace std::chrono;

// Function that represents a unit of work
void* work(void* arg) {
    // Calculating Fibonacci's Numbers
    long long a = 0, b = 1, c, i;
    for (i = 0; i < 100000000; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return NULL;
}

int main() {
    // Number of threads
    const int num_threads = 5;
    // Vector to store the completion times of each thread
    vector<double> completion_times;
    pthread_t threads[num_threads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // Set the scheduling policy to be tested
    // SCHED_RR for real-time scheduling
    // SCHED_OTHER for the default scheduling policy
    struct sched_param param;
    param.sched_priority = 50; // valid priority value
    int policy = SCHED_FIFO; // or SCHED_RR
    pthread_attr_setschedpolicy(&attr, policy);
    pthread_attr_setschedparam(&attr, &param);
     sched_setscheduler(0, policy, &param);

    // Start the timer
    auto start_time = high_resolution_clock::now();

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], &attr, work, NULL);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Stop the timer
    auto end_time = high_resolution_clock::now();

    // Calculate the completion times of each thread
    for (int i = 0; i < num_threads; i++) {
        auto thread_start_time = start_time + (end_time - start_time) / num_threads * i;
        auto thread_end_time = start_time + (end_time - start_time) / num_threads * (i + 1);
        completion_times.push_back(duration_cast<milliseconds>(thread_end_time - thread_start_time).count());
    }

    // Calculate the throughput
    auto total_time = duration_cast<milliseconds>(end_time - start_time).count();
    double throughput = num_threads / (total_time / 1000.0);

    // Calculate the average waiting time
    double avg_waiting_time = accumulate(completion_times.begin(), completion_times.end(), 0.0) / num_threads;

    // Calculate the average latency
    double avg_latency = avg_waiting_time / throughput;
    int sched = sched_getscheduler(0);
if (sched == SCHED_OTHER) {
    cout << "SCHED_OTHER\n";
} else if (sched == SCHED_RR) {
    cout << "SCHED_RR\n";
} else if (sched == SCHED_FIFO) {
    cout << "SCHED_FIFO\n";
} else {
    cout << "Unknown policy\n";
}   cout << "Total execution time: "<< total_time<<" ms" <<endl;
    cout << "Throughput: " << throughput << " threads/second" << endl;
    cout << "Average waiting time: " << avg_waiting_time << " ms" << endl;
    cout << "Average latency: " << avg_latency << " ms/thread" << endl;
    return 0;
    }