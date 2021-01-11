#include "wheeltask.hpp"

WheelTask::WheelTask() { 
    std::cout << "Solving... " << std::flush; 
}

/* run
  
  this function is run in the thread, it creates the "spinning wheel" until an interupt is sent
  
*/
auto WheelTask::run() -> void {
    
    // check if the thread has received a stop request
    size_t i{0};
    while (!this->stop_signal_received()) {
        this->spinning_wheel(i);
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return;
    
}

/* spining wheel
  
  the "spinning wheel" output to the terminal
  
  parameters:
    i, the number of calls - 1 to this function
       it acts as the position indication in the "wheel" array
*/
auto WheelTask::spinning_wheel(const size_t& i) -> void {
    const char wheel[] = {'|', '/', '-', '\\'};
    std::cout << '\b' << wheel[i%4] << std::flush;
    return;
}