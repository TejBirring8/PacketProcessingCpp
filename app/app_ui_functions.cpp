//
// Created by Tej Birring on 15/10/2019.
//
#include "iostream"
#include "app.h"


void app::ui::Print(const std::string &message)
{
    using namespace std;
    cout << message << "\n" << flush;
}
