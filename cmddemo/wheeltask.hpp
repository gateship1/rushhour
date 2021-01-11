#ifndef WHEELTASK_HEADER_FILE
#define WHEELTASK_HEADER_FILE

#include <future> // future, promise
#include <iostream>
#include <thread> // thread

#include "threadstopper.hpp"

/* WheelTask
  
  data structure to create a "spinning wheel" on the terminal as the AI performs its solution search
  
*/
struct WheelTask : public ThreadStopper {
    
    WheelTask();

    auto run() -> void; 
    auto spinning_wheel(const size_t&) -> void;
};

#endif // WHEELTASK_HEADER_FILE