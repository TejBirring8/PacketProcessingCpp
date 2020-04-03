//
// Created by Tej Birring on 14/10/2019.
//
#ifndef CODETEST_STATE_MACHINE_H
#define CODETEST_STATE_MACHINE_H


namespace state_machine {

    enum class StateIndicator {S0, S1, S2, S3, UNKNOWN};

    void UpdateStateMachine(unsigned long timestamp_sec, unsigned long long power_mW);

};


#endif //CODETEST_STATE_MACHINE_H
