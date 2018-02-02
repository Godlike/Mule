/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_TEMPLATES_SINGLETON_HPP
#define MULE_TEMPLATES_SINGLETON_HPP

namespace mule
{
namespace templates
{

/** @brief  Template class describing singleton implementation
 *
 *  To use singleton semantics class @c C shall be a child
 *  of this class. If necessary, the child object shall friend
 *  this class in order to allow the usage of non-public
 *  constructor and destructor.
 *
 *  @tparam C   class that inherits Singleton semantics
 */
template <class C>
class Singleton
{
public:
    /** @brief  Returns the singleton instance
     *
     *  If no instance was stored, creates one
     *
     *  @return reference to singleton instance
     */
    static C& Instance();

    /** @brief  Destroys stored instance */
    static void Destroy();

protected:
    Singleton() = default;
    ~Singleton() = default;

private:
    //! Pointer to singleton instance
    static C* s_instance;

    Singleton(Singleton const& other) = delete;
    Singleton& operator=(Singleton const& other) = delete;

    Singleton(Singleton&& other) = delete;
    Singleton& operator=(Singleton&& other) = delete;
};

}
}

#include <mule/templates/Singleton.imp>

#endif // MULE_TEMPLATES_SINGLETON_HPP
