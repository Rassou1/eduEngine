#pragma once
#include "States.hpp"

class StateMachine
{
public:
    State currentState;

    void Initialize(State startingState)
    {
        currentState = startingState;
        currentState.EnterState();
    }

    void ChangeState(State newState)
    {
        currentState.ExitState();
        //Add animation blending logic here
        currentState = newState;
        newState.EnterState();
    }

};