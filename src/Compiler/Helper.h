/*
 * Helper.h
 * 
 * This file is part of the XShaderCompiler project (Copyright (c) 2014-2016 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef XSC_HELPER_H
#define XSC_HELPER_H


#include <string>
#include <sstream>
#include <cmath>
#include <type_traits>
#include <memory>
#include <algorithm>


namespace Xsc
{


//! Alternative to std::make_unique for strict C++11 support.
template <typename T, typename... Args>
std::unique_ptr<T> MakeUnique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
std::shared_ptr<T> MakeShared(Args&&... args)
{
    #ifdef XSC_ENABLE_MEMORY_POOL
    return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
    #else
    return std::make_shared<T>(std::forward<Args>(args)...);
    #endif
}

// Converts the specified string into a value from type T.
template <typename T>
T FromString(const std::string& s)
{
    T value = T(0);
    std::stringstream stream;
    stream << s;
    stream >> value;
    return value;
}

// Removes all entries from the specified container for which the specified predicate is true.
template <typename Cont, typename Pred>
void EraseIf(Cont container, Pred pred)
{
    container.erase(
        std::remove_if(container.begin(), container.end(), pred),
        container.end()
    );
}

// Converts the specified strin to lower case.
std::string ToLower(const std::string& s);

// Converts the specified strin to upper case.
std::string ToUpper(const std::string& s);


} // /namespace Xsc


#endif



// ================================================================================