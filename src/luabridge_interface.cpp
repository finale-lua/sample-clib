//
//  luabridge_interface.cpp
//  SampleCLib
//
//  Created by Robert Patterson on 6/22/22.
//  Copyright © 2022 Robert Patterson. All rights reserved.
//  (Usage permitted by MIT License. See LICENSE file in this repository.)
//

#include "luabridge_interface.hpp"

FCClass::FCClass(luabridge::LuaRef luaRef) : m_luaRef(luaRef)
{
   if (! luaRef.isUserdata())
      ThrowException(m_luaRef.state(), "Attempt to initialize FCClass with non-instance variable.");
   if (! luaRef["ClassName"].isFunction())
      ThrowException(m_luaRef.state(), "Attempt to initialize FCClass with instance that is not a Finale class.");
}

FCClass FCClass::CreateInstance(lua_State* L, const char * const className)
{
   luabridge::LuaRef classLuaRef = luabridge::getGlobal(L, "finale")[className];
   if (! classLuaRef.isTable())
      ThrowException(L, std::string(className) + " is not a valid FCClass name.");
   return FCClass(classLuaRef());
}

FCClass FCClass::CreateInstanceFromStack(lua_State* L, const char * const className, const int index)
{
   FCClass retval(luabridge::LuaRef::fromStack(L, 1));
   luabridge::LuaRef classNameReturned = retval.ExecuteMethod<luabridge::LuaRef>("ClassName");
   if (! classNameReturned.isString())
      ThrowException(L, std::string("FCClass::CreateFromStack ClassName for ") + className + " did not return a string.");
   if (0 != strcmp(classNameReturned.tostring().c_str(), className))
      ThrowException(L, std::string("FCClass::CreateFromStack expected instance of ") + className + " but got " + classNameReturned.tostring() + ".");
   return retval;
}
