//
//  sampleclib.h
//  SampleCLib
//
//  Created by Robert Patterson on 3/28/21.
//  Copyright © 2021 Robert Patterson. All rights reserved.
//

#ifndef rgptest_h
#define rgptest_h

#include <stdio.h>

#include "lua.h"

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

DLLEXPORT int luaopen_libLuaInterfaceTest(lua_State* L);

#endif /* rgptest_h */
