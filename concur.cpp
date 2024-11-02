/*
Contains concurrency and multithreaaing stuff
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <mutex>

using SC = std::chrono::steady_clock;

// #define E1
// #define E2
// #define E3
// #define E4
// #define E5
#define E6

int main(){

    // thread safe code
    #ifdef E1
    std::thread threadB = std::thread([](){
        std::cout << "from the 2nd thread of execution\n";
    });

    std::cout << "from the 1st thread of execution\n";
    threadB.join();
    #endif

    #ifdef E2
    // setting a deadline 10 seconds from now
    auto deadline = SC::now() + std::chrono::milliseconds(1);
    auto counter = 0;
    // now both these threads should inc the val of counter, each second passed
    // until the deadline is reached, however this is a data race, bc 
    // there can be simultaneous read and write access to the poor counter
    std::thread threadB = std::thread([&](){
        while(SC::now() < deadline) {
            std::cout << (++counter) << std::endl;
        }
    });

    while(SC::now() < deadline) {
        std::cout << (++counter) << std::endl;
    }
    threadB.join();
    // this results in UB behavior due to no sync
    #endif 

    #ifdef E3
    // Now we use atomic types 
    // setting a deadline 10 seconds from now
    auto deadline = SC::now() + std::chrono::milliseconds(1);
    std::atomic<int> counter = 0;
    // now both these threads should inc the val of counter, each second passed
    // until the deadline is reached, however this is a data race, bc 
    // there can be simultaneous read and write access to the poor counter
    std::thread threadB = std::thread([&](){
        while(SC::now() < deadline) {
            std::cout << (++counter) << std::endl;
        }
    });

    while(SC::now() < deadline) {
        std::cout << (++counter) << std::endl;
    }
    threadB.join();

    // This is no more UB
    // There is no more physical data race, as atomic
    // synchronises primitve types across all the threads
    // every execution however still returns a different 
    // answer, this has a bug now (semantic data race)
    // but it is not UB, by the standard.

    #endif

// BUSY WAITING example using std::atomic<bool>
    #ifdef E4
    // Now, let's try to have logical sync, where want to
    // keep a thread busy or waiting before starting the executtion
    // we obviously here use an atomic bool to avoid data race between it
    // bool ready = false;
    std::atomic<bool> ready = false;
    std::thread threadB = std::thread([&](){
        while(!ready){
            std::cout << "thread2\n";
        }
    });
    // DO SOME WORK 
    // now open the gate for the 1st thread to run
    std::cout << "thread1\n";
    ready = true;
    threadB.join();
    
    // This might seem feasible but in reality it is actually shit
    // CPU TIME WASTE on a single core
    // This is not waiting but Wait, Spin-wait

    // Not Concurrent UB but UB can occur in threadB by the compiler
    // because the compiler may try to store the val in a register 
    // because it sees that the value is never modified within this thread  
    // (this is a completely legal compiler optmisiation and the mistake of the programmer to let this take place)
    // and not get it updated (hoisted by the compiler)
    #endif

    // Mutex time
    #ifdef E5

    std::mutex mtx;
    // Lock the resource
    mtx.lock();

    std::thread threadB = std::thread([&](){
        // Acquire lock or wait for it to get unlocked
        mtx.lock();
        std::cout << "i get here afterwards\n";
    });
    std::cout << "i print here first\n";
    // Release the mutex lock now
    mtx.unlock();
    threadB.join();
    #endif 

    #ifdef E6

    // Now, Mutexes are more generally used to lock and secure critical sections
    class Token{
        private:
            std::vector<int> v;
            size_t size;
            std::mutex mtx;
        public:
            std::mutex mtx;
            Token(int n): v(n,0) {};
            // return the token at ith index
            int getToken(decltype(v), int i){
                // to prevent data race or UB in the access of this token
                // we use a mutex to lock this resource here
                // std::mutex mtx;
                mtx.lock();
                
                // do some random shit (critical section here)
                int x = 0;
                for(int i = 0; i < v.size(); i++){
                    x += v[i];
                }

                // now we're done with accessing the CS
                // so we unlock the mutex
                mtx.unlock();
                return x;
            }
            // this function however, is pretty garbage and has more errors than solutions
            // number 1
            // we cannot guarantee the exception safety in case that the access to the 
            // vector<int> throws an Exception, could be riskier if we were using
            // a custom container
            // we need to make it so that the mutex and all other resources are released
            // in the destructor call

            int getTokenbutBetter(decltype(v), int i){
                // Now this is nothing but a wrapper offering RAII for the mtx
                // within the scope it is defined

                // Generally defined like this for a mutex
                // std::lock_guard<std::mutex> locker (mtx);
                std::lock_guard locker(mtx); // Using C++17's CTAD you can just do this
                // RAII to the rescue yayy
            }
    };

    Token t(10);
    // now, we have a token array of size 10

    #endif


    // #ifdef E7

    // Now just like any other object or memory that we can allocate
    // Mutex is also just a resource at the end of the night(yes)
    // In a sense that you need to call delete for an object on the heap to free it
    // you should also call .unlock() on the dear std::mutex
    // but as we have unique_ptr to take care of resources via RAII
    // we also have sm like this for mutexes to manage their ownership and 
    // their deconstruction
    

    // use lock_guard if you're not going to pass around the mutex around the functions
    // otherwise try to use unqiue_lock as it has better functions for this.
    // std::unique_lock<std::mutex> foo(std::unique_lock<std::mutex> lk) {
        // if(rand()){
        //     lk.unlock(); // prematurely clean up the resource
        // }
        // return lk;
    // }

    // Uniquelock just like unique is MOVABLE not COPYABLE


    // babe wake up the 17th addition just dropped for concurrency
    // official ref 
    // The class scoped_lock is a mutex wrapper that provides a convenient 
    // RAII-style mechanism for owning zero or more mutexes for the duration of a scoped block.
    // When a scoped_lock object is created, it attempts to take ownership of the
    //  mutexes it is given. When control leaves the scope in which the scoped_lock object was created, 
    // the scoped_lock is destructed and the mutexes are released. If several mutexes are given, deadlock 
    // avoidance algorithm is used as if by std::lock.


    // C++17 added scoped_lock which is a new and improved version
    // of the std::lock_guard, it can take multiple mutexes at the same time
    // wink wink
    // what this means is, it has a initialiser list constuctor (that is not what it means or refers to, this is simply my guess at how the internal impelmentation probably is)
    // so what it really means is that you can use to lock multiple mutexes or unlock them
    
    // now where the fuck would you need this really,
    // take for example this, a class token with a secret key and a public key

    class Token{
        public:
            std::mutex mtx;
            int publicKey;
            Token(int x, int y): publicKey(x), hashKey(y){};
            
            // Now, let's define a function where we merge two keys, for this
            // we obviously need to use mutexes for both the rhs and lhs Token
            // now the addition of scopedd lock saves us a sum total of 3-4 lines 
            // while having us constanly remember over 20 lines of jargon, impressive right?
            // (this is also non-copyable)


            int mergeToken(Token a, Token b){
                // without using CTAD here, you can end up with a rather ugly code
                std::scoped_lock scpedLock(a.mtx,b.mtx);

                // this above there is the equivalent of
                // (using std::lock and std::lock_guard)
                // std::lock(a.m, b.m);
                // std::lock_guard<std::mutex> lk1(a.m, std::adopt_lock);
                // std::lock_guard<std::mutex> lk2(b.m, std::adopt_lock);

                // (if unique_locks are needed, e.g. for condition variables)   
                // std::unique_lock<std::mutex> lk1(e1.m, std::defer_lock);
                // std::unique_lock<std::mutex> lk2(e2.m, std::defer_lock);
                // std::lock(lk1, lk2);
            }
        private:
            int hashKey;

    };



    // alot of yapping but here's a summary
    // unique_lock (C++11) implements movable mutex ownership wrapper
    // lock_guard (C++11) implements a strictly scope-based mutex ownership wrapper
    // scoped_lock (C++17) deadlock-avoiding RAII wrapper for multiple mutexes

    // C++11 also introduced thread-safe static initialisation




}