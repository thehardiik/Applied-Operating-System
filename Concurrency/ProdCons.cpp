#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include <queue>
#include <vector>
#include <mutex>

#define BUFFER_SIZE 5

std::queue<int> buffer;
sem_t empty, full;
std::mutex mutex;

void producer (int id){

    for(int i = 0; i < 10; i++){
        sem_wait(&empty);
        // Enter Critical Section
        mutex.lock();

        buffer.push(i);
        std::cout <<  "Produer " << id << " produced: " << i << std::endl;

        mutex.unlock();
        sem_post(&full);

        sleep(1);
    }
}

void consumer (int id){

    for(int i = 0; i < 10; i++){
        sem_wait(&full);
        // Enter Critical Section
        mutex.lock();

        int item = buffer.front();
        buffer.pop();
        std::cout <<  "Consumer " << id << " consumed: " << item << std::endl;

        mutex.unlock();
        sem_post(&empty);

        sleep(2);
    }
}

int main(){
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    std::thread p1(producer, 1);
    std::thread c1(consumer, 1);
    std::thread p2(producer, 2);
    std::thread c2(consumer, 2);

    p1.join();
    c1.join();
    p2.join();
    c2.join();

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
