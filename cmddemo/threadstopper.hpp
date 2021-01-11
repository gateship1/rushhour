#ifndef THREADSTOPPER_HEADER_FILE
#define THREADSTOPPER_HEADER_FILE

#include <future> // future, promise
#include <iostream>
#include <thread> // thread

/* ThreadStopper
  
  a class meant to create a stoppable thread
   
*/
struct ThreadStopper {
    
    // constructors
    ThreadStopper();
    ThreadStopper(ThreadStopper&&);
    
    /* operator=
      
      overloaded assignment operator
      
      parameters:
        obj, the object whose stop_signal and future_object are to be moved to the
             current ThreadStopper object
    */
    ThreadStopper& operator=(ThreadStopper&& obj) {
        stop_signal = std::move(obj.stop_signal);
        future_obj = std::move(obj.future_obj);
        return *this;
    }
    
    virtual void run() = 0; // function to be called by thread function
    
    auto operator()() -> void;
    
    auto stop_signal_received() -> bool;
    
    auto stop() -> void;
    
    private:
        std::promise<void> stop_signal;
        std::future<void> future_obj;
};

#endif // THREADSTOPPER_HEADER_FILE