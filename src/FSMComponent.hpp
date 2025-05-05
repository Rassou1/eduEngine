#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "LinearVelocityComponent.hpp"
#include "MeshComponent.hpp"

class FSMComponent
{
public:
    enum class State {
        Idle,
        Moving,
        TransitionToIdle,
        TransitionToMoving
    };

private:
    State currentState = State::Idle;
    float blendFactor = 0.0f;
    float blendDuration = 0.3f; 
    float blendTimer = 0.0f;

    int idleAnimIndex = 1;
    int moveAnimIndex = 2;

    float idleAnimTime = 0.0f;
    float moveAnimTime = 0.0f;

    float movementThreshold = 0.1f;

public:
    FSMComponent(int idleIndex, int moveIndex, float blendTime = 0.3f)
        : idleAnimIndex(idleIndex), moveAnimIndex(moveIndex), blendDuration(blendTime) {}

    void Update(float deltaTime, const glm::vec3& velocity)
    {
        float speed = glm::length(velocity);
        bool isMoving = speed > movementThreshold;

        switch (currentState)
        {
        case State::Idle:
            if (isMoving)
            {
                currentState = State::TransitionToMoving;
                blendTimer = 0.0f;
            }
            break;

        case State::Moving:
            if (!isMoving)
            {
                currentState = State::TransitionToIdle;
                blendTimer = 0.0f;
            }
            break;

        case State::TransitionToIdle:
        case State::TransitionToMoving:
        {
            blendTimer += deltaTime;
            blendFactor = glm::clamp(blendTimer / blendDuration, 0.0f, 1.0f);

            if (blendTimer >= blendDuration)
            {
                if (currentState == State::TransitionToIdle)
                {
                    currentState = State::Idle;
                }
                else
                {
                    currentState = State::Moving;
                }
                blendFactor = (currentState == State::Moving) ? 1.0f : 0.0f;
            }
        }
        break;
        }
    }

    void ApplyAnimation(MeshComponent& mesh, float time)
    {
        switch (currentState)
        {
        case State::Idle:
            mesh.mesh->animate(idleAnimIndex, time);
            break;

        case State::Moving:
            mesh.mesh->animate(moveAnimIndex, time);
            break;

        case State::TransitionToIdle:
        case State::TransitionToMoving:
            mesh.mesh->animateBlend(
                idleAnimIndex,
                moveAnimIndex,
                time,
                time,
                (currentState == State::TransitionToMoving) ? blendFactor : (1.0f - blendFactor)
            );
            break;
        }
    }

    State GetCurrentState() const { return currentState; }
    float GetBlendFactor() const { return blendFactor; }
};