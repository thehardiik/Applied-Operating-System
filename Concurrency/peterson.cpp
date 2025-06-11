#include <iostream>
#include <thread>

#define N 2
#define TRUE 1
#define FALSE 0

int turn = 0;
int interested[N] = {FALSE, FALSE};
int x = 0;

void enter_section(int process){
    int other = 1 - process;
    interested[process] = TRUE; 
    turn = process;
    while(turn == process && interested[other]);
}

void leave_section(int process){
    interested[process] = FALSE;
}

class thread_class {
public:

    void operator()(int process){

        for(int i = 0; i < 1000000; i++){
            enter_section(process);
            x++;
            std::cout << "Thread " << process << " " << x << std::endl;
            leave_section(process);
        }
    }
};

int main(int argc, char* argv[]){
    thread_class obj;

    std::thread t1(obj, 0);
    std::thread t2(obj, 1);
    t1.join();
    t2.join();
    std::cout << "Final value of x: " << x << std::endl;
    return 0;
}

// Idea :- Turn == Process means it is this process's turn to wait.
        // Turn == Other means i.e, Turn != Process means it is other process's is waiting, that means other process is not in critical section. So we can enter critical section.
        // Interested[other] == False means other process is out of critical section.
        // So for any of the above conditions, we can enter critical section.


