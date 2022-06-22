//
//  sampleclib.hpp
//  SampleCLib
//
//  Created by Robert Patterson on 3/28/21.
//  Copyright © 2021 Robert Patterson. All rights reserved.
//  (Usage permitted by MIT License. See LICENSE file in this repository.)
//

#ifndef sampleclib_hpp
#define sampleclib_hpp

#include <stdio.h>

#include "lua.hpp"

#ifdef _MSC_VER
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif


#ifdef __cplusplus
extern "C" {
#endif

DLLEXPORT int luaopen_sampleclib(lua_State* L);

#ifdef __cplusplus
}
#endif

#endif // sampleclib_hpp
