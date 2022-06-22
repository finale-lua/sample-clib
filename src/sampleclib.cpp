//
//  sampleclib.cpp
//  SampleCLib
//
//  Created by Robert Patterson on 3/28/21.
//  Copyright © 2021 Robert Patterson. All rights reserved.
//  (Usage permitted by MIT License. See LICENSE file in this repository.)
//

#include "luabridge_interface.hpp"

#include "sampleclib.hpp"

static int sampleclib_entry_duration(lua_State *L)
{
   luabridge::LuaRef entry = luabridge::LuaRef::fromStack(L, 1);
   if (! check_framework_class(entry, "FCNoteEntry"))
   {
      luaL_error(L, "entry_duration function expected FCNoteEntry instance");
      return 0;
   }
   lua_pushinteger(L, entry["Duration"].cast<int>());
   return 1;
}

static int sampleclib_plusone (lua_State *L)
{
   lua_pushinteger ( L, luaL_checknumber(L, 1) + 1 );
   return 1;
}

static const luaL_Reg sampleclib[] = {
   {"plusone",          sampleclib_plusone},
   {"entry_duration",   sampleclib_entry_duration},
   {NULL, NULL} // sentinel
};

int luaopen_sampleclib (lua_State *L) {
#if LUA_VERSION_NUM <= 501
   luaL_openlib(L, "sampleclib", sampleclib, 0);
#else
   luaL_newlib(L, sampleclib);
#endif
   return 1;
}
