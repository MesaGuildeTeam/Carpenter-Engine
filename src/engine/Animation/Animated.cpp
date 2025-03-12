/**
 * 
 * @file Animated.cpp
 * @author Kirstin Horvat (MesaGuildeTeam)
 * @details This file contains the definitions of the Animated class
 * 
 */
#include <iostream>
#include "Animated.hpp"


Animated::Animated() {
    m_keyframes = new float[maxSize];
    maxSize = 2;
    arraySize = 0;
};

void Animated::assignValues(const float& keyvalue) {
    if (arraySize == maxSize) {
        float* newArray = new float[(maxSize*2)];
        for (int i = 0; i < arraySize; i++) {
            newArray[i] = m_keyframes[i];
        }
        arraySize = maxSize; // Set the new array size
        maxSize *= 2; // Double the max size of the array
        delete[] m_keyframes; // Delete the old array
        m_keyframes = newArray;
    }
    m_keyframes[arraySize] = keyvalue; // Assign values to keyframes
    updateValue(keyvalue); // Update the deltatime
    ++arraySize; // Increment the number of keyframes
}

void Animated::updateValue(const float& keyvalue) {
    m_DeltaTime += keyvalue; // Update the deltatime
}; 

float Animated::getCurrentValue() {
    return m_keyframes[arraySize];
};

// Test methods
void Animated::printKeyframes() {
    for (int i = 0; i < arraySize; i++) {
        std::cout << m_keyframes[i] << " ";
    }
}

void Animated::printDeltaTime() {
    std::cout << m_DeltaTime << std::endl;
}

void Animated::printArraySize() {
    std::cout << arraySize << std::endl;
}

void Animated::printMaxSize() {
    std::cout << maxSize << std::endl;
}

Animated::~Animated() {
    delete[] m_keyframes;
};