/**
 * 
 * @file Animated.hpp
 * @author Kirstin Horvat (MesaGuildeTeam)
 * @details This file contains the declarations of the Animated class
 * 
 */

class Animated {
    private:
        float m_keyvalue;
        int m_keyframes; // Array that stores keyframes over time
        float m_DeltaTime; // Change in time to update the values 
    public:
        Animated(); // Constructor
        // assign values to keyframes (keyframe: where you want to start and end the animation)
        void UpdateValue(int value); // update the deltatime
        int GetCurrentValue(); // return the float value of the current keyframe




}