#ifndef _APP_HPP
#define _APP_HPP

#include "Task.hpp"

class App : public FreeRTOS::Task {
public:
    App() : Task("App", 512, tskIDLE_PRIORITY+1) {};
    void Run() override;
};

#endif