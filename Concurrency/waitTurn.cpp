#include <iostream>
#include <thread>

int turn = 0;

class thread1 {
public:
    void non_critical_section(){
        int a = 0;
        while(++a < 1000000);
    }
    
    void operator()(int& x){
        
        while(x < 2000){
            while(turn != 1);
            x++;
            std::cout << "Thread 1 " << x << std::endl;
            turn = 0;
            non_critical_section();
        }
    }

};

class thread2{
public:

    void non_critical_section(){
        int a = 0;
        while(++a < 10);
    }

    void operator()(int& x){
        
        while(x < 2000){
            while(turn != 0);
            x++;
            std::cout << "Thread 2 " << x << std::endl;
            turn = 1;
            non_critical_section();
        }
    }
};

int main(){

    int x = 0;      // Shared variable
    thread1 obj1;
    thread2 obj2;

    std::thread t1(obj1, std::ref(x));       // Create first thread
    std::thread t2(obj2, std::ref(x));       // Create second thread

    t1.join();  // Wait for first thread to finish
    t2.join();  // Wait for second thread to finish

    std::cout << "Final value of x: " << x << std::endl;
    return 0;

}