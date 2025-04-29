#pragma once
#include "PlayerControllerSystem.hpp"
#include "MeshComponent.hpp"

class State {
protected:
    StateMachine* stateMachine;
    MeshComponent mesh;

public:
    State(StateMachine* stateMachine, MeshComponent mesh)
        :stateMachine(stateMachine) , mesh(mesh)
    {}

    virtual ~State() = default;

    virtual void EnterState() {}
    virtual void ExitState() {}
    virtual void Update() {}
};

// Example of inheriting from State
class IdleState : public State {
public:
    // Constructor calling base class constructor
    IdleState(StateMachine* stateMachine, MeshComponent mesh)
    {
        this->mesh = mesh;
        this->stateMachine = stateMachine;
    }

    void EnterState() override {
        // Implementation specific to DerivedState
    }

    void ExitState() override {
        // Implementation specific to DerivedState
    }

    void Update() override {
        // Implementation specific to DerivedState
    }
};

class WalkingState : public State {
public:
    // Constructor calling base class constructor
    WalkingState(StateMachine* stateMachine, MeshComponent mesh)
    {
        
    }

    void EnterState() override {
        // Implementation specific to DerivedState
    }

    void ExitState() override {
        // Implementation specific to DerivedState
    }

    void Update() override {
        // Implementation specific to DerivedState
    }
};