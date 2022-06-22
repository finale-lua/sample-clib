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
#include "LuaBridge/LuaBridge.h"

bool check_framework_class(luabridge::LuaRef class_instance, const char * class_name);


#endif /* luabridge_interface_hpp */
