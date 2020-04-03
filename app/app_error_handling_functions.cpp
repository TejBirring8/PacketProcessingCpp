//
// Created by Tej Birring on 15/10/2019.
//
#include <iostream>
#include "app.h"


void app::error_handling::ExitOnError(const std::exception& e)
{
    using namespace std;
    cout << "ERR: " << e.what() << "\n" << flush;
    exit(EXIT_FAILURE);
}


void app::error_handling::ExitOnError(const std::string& message, int error_number)
{
    using namespace std;
    cout << "ERR: " << message << ": " << strerror(error_number) << " [" << to_string(error_number) << "]" << "\n" << flush;
    exit(EXIT_FAILURE);
}


void app::error_handling::ExitOnError(const std::string& message)
{
    using namespace std;
    cout << "ERR: " << message << "\n" << flush;
    exit(EXIT_FAILURE);
}
