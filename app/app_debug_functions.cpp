//
// Created by Tej Birring on 15/10/2019.
//
#include "app.h"
#include "../compile_options.h"


void app::debug::Print(const std::string& message)
{
    if (COMPILE_FOR_DEBUG) app::ui::Print(message);
}


void app::debug::Assert(
    const std::string& namespace_name,
    const std::string& class_name,
    const std::string& function_name,
    bool test_expression,
    const std::string& message)
{
    if (test_expression) return;

    app::ui::Print("namespace: " + namespace_name);
    app::ui::Print("class: " + class_name);
    app::ui::Print("function: " + function_name);
    app::ui::Print("error message: " + message);

    exit(EXIT_FAILURE);
}

