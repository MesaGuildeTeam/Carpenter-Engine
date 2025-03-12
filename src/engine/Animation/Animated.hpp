/**
 * 
 * @file Animated.hpp
 * @author Kirstin Horvat (MesaGuildeTeam)
 * @details This file contains the declarations of the Animated class
 * 
 */

/**
 * [keyframe, keyframe + deltatime , etc.....] with the values of the keyframes
 * 
 */

#ifndef ANIMATED_HPP
#define ANIMATED_HPP

class Animated {
    private:
        float m_keyvalue; // Current keyframe
        float* m_keyframes; // Array that stores keyframes over time
        float m_DeltaTime; // Change in time to update the values 
        int arraySize;
        int maxSize; // Number of keyframes
    public:
        Animated(); // Default constructor
        void assignValues(const float& keyvalue);// Assign values to keyframes (keyframe: where you want to start and end the animation)
        void updateValue(const float& value); // Update the deltatime
        float getCurrentValue(); // Return the float value of the current keyframe
        ~Animated(); // Destructor


        // Methods for testing
        void printKeyframes();
        void printDeltaTime();
        void printArraySize();
        void printMaxSize();






};

#endif // ANIMATED_HPP