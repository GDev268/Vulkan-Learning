#include "App.hpp"

#include <stdlib.h>
#include <iostream>
#include <stdexcept>

int main(){
    Tutorial::FirstApp app = Tutorial::FirstApp();

    try{
        app.run();
    }
    catch(const std::exception e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
