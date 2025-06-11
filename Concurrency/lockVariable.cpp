#include <iostream>
#include <thread>

int lock = 0;

class thread_class {
public:
    void operator()(int& x){

        for(int i = 0;i < 10000; i++){
        
            while(lock != 0);
            lock = 1;
            x++;
            lock = 0;
        }

    }

};

// The problem with the loop is that while loop and lock update is not atomic.

int main(){

    int x = 0;      // Shared variable
    thread_class obj; // Functor class to be used with threads

    std::thread t1(obj, std::ref(x));       // Create first thread
    std::thread t2(obj, std::ref(x));       // Create second thread

    t1.join();  // Wait for first thread to finish
    t2.join();  // Wait for second thread to finish


    // Unexpected output:
    std::cout << "Final value of x: " << x << std::endl;

    return 0;
}




