#include "stdafx.h"
#include "InputComponent.h"

InputComponent::InputComponent(std::shared_ptr<GameObject> parent) :
	Component(parent)
{}

void InputComponent::update( const float fDeltaTimeSeconds)
{
}

void InputComponent::init()
{

}

void InputComponent::draw()
{
}
