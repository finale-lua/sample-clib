//
//  sampleclib.h
//  SampleCLib
//
//  Created by Robert Patterson on 3/28/21.
//  Copyright © 2021 Robert Patterson. All rights reserved.
//  (Usage permitted by MIT License. See LICENSE file in this repository.)
//

#ifndef sampleclib_h
#define sampleclib_h

#include <stdio.h>

#include "lua.h"

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

DLLEXPORT int luaopen_sampleclib(lua_State* L);

#endif /* sampleclib_h */
