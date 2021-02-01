#include "threadstopper.hpp"

// constructor
ThreadStopper::ThreadStopper() : future_obj(stop_signal.get_future()) {
}

// move constructor
ThreadStopper::ThreadStopper(ThreadStopper &&obj) : stop_signal(std::move(obj.stop_signal)),
    future_obj(std::move(obj.future_obj)) {
}

// function executed by thread
auto ThreadStopper::operator()() -> void { 
    run(); 
} 

/* stop_signal_received
  
  a boolean that can change the stop_signal data member from true to false upon receipt of a stop signal
  
  return:
    true if a stop signal has been received
    false otherwise
*/
auto ThreadStopper::stop_signal_received() -> bool {
    return future_obj.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout ? false : true;
}

/* stop
  
  stop the thread
*/
auto ThreadStopper::stop() -> void { 
    stop_signal.set_value();
    std::cout << "\r            " << std::endl; // like a typewriter...
    return;
}