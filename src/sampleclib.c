//
//  sampleclib.c
//  SampleCLib
//
//  Created by Robert Patterson on 3/28/21.
//  Copyright © 2021 Robert Patterson. All rights reserved.
//

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "sampleclib.h"


static int sampleclib_plusone (lua_State *L)
{
   lua_pushnumber ( L, luaL_checknumber(L, 1) + 1 );
   return 1;
}

static const luaL_Reg sampleclib[] = {
   {"plusone",    sampleclib_plusone},
   {NULL, NULL} // sentinel
};

int luaopen_sampleclib (lua_State *L) {
#if LUA_VERSION_NUM <= 501
   luaL_openlib(L, "sampleclib", rgptest, 0);
#else
   luaL_newlib(L, sampleclib);
#endif
   return 1;
}
