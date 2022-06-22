//
//  luabridge_interface.hpp
//  SampleCLib
//
//  Created by Robert Patterson on 6/22/22.
//  Copyright © 2022 Robert Patterson. All rights reserved.
//  (Usage permitted by MIT License. See LICENSE file in this repository.)
//

#ifndef luabridge_interface_hpp
#define luabridge_interface_hpp

#include "lua.hpp"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdocumentation"
#endif
#include "LuaBridge/LuaBridge.h"
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

/** \brief Class wrapper for any finale class from the PDK Framework. See https://pdk.finalelua.com/
 * for full documentation.
 *
 * This class is a wrapper for a LuaRef that represents an instance of a finale class. You can use this in your c++ code
 * or push it back to Lua using the #Push method.
 */

class FCClass
{
   luabridge::LuaRef m_luaRef;

   /** \brief Private constructor. Use one of the Create* functions to constuct an instance. */
   FCClass(luabridge::LuaRef luaRef);
   
   static void ThrowException(lua_State* L, const std::string &msg)
   {
      lua_pushstring(L, msg.c_str());
      luabridge::LuaException::Throw(luabridge::LuaException(L, -1));
   }
   
public:
   /** \brief Creates an instance of the input classname and calls its constructor with no arguments. */
   static FCClass CreateInstance(lua_State* L, const char * const className);
   /** \brief Initializes an instance of the input classname from the Lua stack at location index. */
   static FCClass CreateInstanceFromStack(lua_State* L, const char * const className, const int index);
   
   /** \brief Gets the value of the specified property name.
    *
    * \tparam T the return type of the property.
    * \param propertyName the name of the property to get.
    */
   template<typename T>
   T GetProperty(const char * const propertyName) const
   { return m_luaRef[propertyName].cast<T>(); }
   
   /** \brief Sets the specified property to a new value.
    *
    * \tparam T the type of the property.
    * \param propertyName the name of the property to set.
    * \param value a value of type T that the property will be set to.
    */
   template<typename T>
   void SetProperty(const char * const propertyName, T value)
   { m_luaRef[propertyName] = value; }
   
   /** \brief Executes the specified method.
    *
    * \tparam T the return type of the method (may be <code>void</code>.) Use #FCClass if the return type is
    * a pointer to (or instance of) any type of Finale class definied in the PDK Framework.
    * \tparam Args variadic template for the arguments to the method.
    * \param methodName the name of the method to call.
    * \param args the arguments to the method.
    */
   template<typename T, typename ...Args>
   T ExecuteMethod(const char * const methodName, Args ...args) const
   {
      luabridge::LuaRef methodFunc = m_luaRef[methodName];
      if (! methodFunc.isFunction())
         ThrowException(m_luaRef.state(), std::string(methodName) + " is not a function.");
      if constexpr(std::is_same<T, void>::value)
          methodFunc(m_luaRef, args...);
      else
          return methodFunc(m_luaRef, args...);
   }
   
   /** \brief pushes the current instance to the Lua stack. (Useful for returning a class instance to Lua.) */
   void Push()
   { m_luaRef.push(); }
};

#endif /* luabridge_interface_hpp */
