/*
 *  Randomizer.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef RANDOMIZER_HPP_
#define RANDOMIZER_HPP_

#include "Vector.hpp"
#include <ctime>
#include <cstdlib>

namespace asteroids
{

/**
 * @brief   Helper class to encapsulate random generator fuctions.
 */
class Randomizer
{
private:
    /**
     * @brief   Ctor.
     */
    Randomizer() {};

    static Randomizer* p_instance;

public:
    /**
     * @brief   Instance access method
     */
    static Randomizer* instance();

    /**
     * @brief   Dtor.
     */
    virtual ~Randomizer() 
    {
        if(p_instance)
        {
            delete p_instance;
        }
    };

    /**
     * @brief   Returns a random number between high and low
     */
    float getRandomNumber(float low, float high);

    /**
     * @brief Get the Random Int object
     */
    int getRandomInt(int a, int b);

    /**
     * @brief   Returns a random with coordinated between -range and +range
     */
    Vector3f getRandomVertex(float range);
};

} /* namespace asteroids */

#endif /* RANDOMIZER_HPP_ */
