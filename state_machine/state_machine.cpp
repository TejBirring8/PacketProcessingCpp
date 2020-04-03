//
// Created by Tej Birring on 14/10/2019.
//
#include <iostream>
#include <optional>
#include "state_machine.h"
#include "../app/app.h"
using namespace std;
using namespace state_machine;


static StateIndicator current_state{StateIndicator::S0};
static std::optional<StateIndicator> pending_state{};
static std::optional<unsigned long long> pending_timestamp_sec{};


std::string StateToString(StateIndicator state)
{
    return to_string( static_cast<unsigned short>(state) );
};


StateIndicator StatefromPowerValue(unsigned int power_mW)
{
    if (power_mW >= 0 && power_mW <= 200)
        return StateIndicator::S0;
    else if (power_mW >= 300 && power_mW <= 450)
        return StateIndicator::S1;
    else if (power_mW >= 550 && power_mW <= 650)
        return StateIndicator::S2;
    else if (power_mW >= 800 && power_mW <= 1200)
        return StateIndicator::S3;
    else
        return StateIndicator::UNKNOWN;
}


bool IsPowerValueWithinStateThreshold(unsigned int power_mW, StateIndicator state)
{
    /// ------------------------------------------------------------------------
    if (state == StateIndicator::UNKNOWN)
        return false;
    /// this clause makes it impossible to transition to StateIndicator::UNKNOWN

    if (power_mW >= 0 && power_mW <= 200 && state == StateIndicator::S0)
        return true;
    else if (power_mW >= 300 && power_mW <= 450 && state == StateIndicator::S1)
        return true;
    else if (power_mW >= 550 && power_mW <= 650 && state == StateIndicator::S2)
        return true;
    else if (power_mW >= 800 && power_mW <= 1200 && state == StateIndicator::S3)
        return true;

    return false;
}


bool IsValidStateTransition(StateIndicator current, StateIndicator next)
{
    if (current == next)
        return false;

    switch (current)
    {
        // STARTING
        case StateIndicator::S0:
            return (next == StateIndicator::S1);
        // WARM UP
        case StateIndicator::S1:
            return (next == StateIndicator::S2);
        // MAIN SESSION (S2->S3) && COMPLETE (S2->S0)
        case StateIndicator::S2:
            return (next == StateIndicator::S3 || next == StateIndicator::S0);
        // COOL DOWN
        case StateIndicator::S3:
            return (next == StateIndicator::S2);
        // !! INVALID TRANSITION !!
        case StateIndicator::UNKNOWN:
            return false;
    }
}


void state_machine::UpdateStateMachine(unsigned long timestamp_sec, unsigned long long power_mW) {
    if (pending_state.has_value() && IsPowerValueWithinStateThreshold(power_mW, pending_state.value()) )
    {
        /* if this state has been held for >=10ms, it qualifies for transition */
        if (pending_timestamp_sec.value() - timestamp_sec >= 10)
        {
            if (IsValidStateTransition(current_state, pending_state.value()))
            {
                app::ui::Print("S;" + to_string(pending_timestamp_sec.value()) + ";" + StateToString(current_state)
                               + "-" + StateToString(pending_state.value()));

                current_state = pending_state.value();
                pending_state.reset();
                pending_timestamp_sec.reset();
            }
            return;
        }
    }
    else
    {
        /* since no pending state, or pending state no longer qualifies, deduce state from received data */
        pending_state = StatefromPowerValue(power_mW);
        pending_timestamp_sec = timestamp_sec;
    }
}
