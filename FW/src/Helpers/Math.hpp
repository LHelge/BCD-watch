#ifndef _MATH_HPP
#define _MATH_HPP


/**
 * @brief Find the absolute value of X
 * 
 * @tparam T Datatype of X
 * @param x Value of X
 * @return T Positive X
 */
template<typename T>
T abs(T x) {
    return x >= 0 ? x : -x;
}


/**
 * @brief Find the minimum of X & Y
 * 
 * @tparam T datatype of values
 * @param x Value X
 * @param y Value Y
 * @return T The least of X & Y
 */
template<typename T>
T min(T x, T y) {
    return x <= y ? x : y;
}


/**
 * @brief Find the maximum of X & Y
 * 
 * @tparam T datatype of values
 * @param x Value X
 * @param y Value Y
 * @return T The greatest of X & Y
 */
template<typename T>
T max(T x, T y) {
    return x >= y ? x : y;
}


/**
 * @brief Clamp a numerical value between a minimum and a maximum
 * 
 * @tparam T datataype of value
 * @param x Value to clamp
 * @param min Minimum value
 * @param max Maximum value
 * @return T The clamped value
 */
template<typename T>
T clamp(T x, T min, T max) {
    return min(max(x, min), max);
}

#endif // _MATH_HPP