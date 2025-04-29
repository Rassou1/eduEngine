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
        currentState = newState;
        //Add animation blending logic here
        newState.EnterState();
    }

}