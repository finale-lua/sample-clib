//
//  luabridge_interface.cpp
//  SampleCLib
//
//  Created by Robert Patterson on 6/22/22.
//  Copyright © 2022 Robert Patterson. All rights reserved.
//  (Usage permitted by MIT License. See LICENSE file in this repository.)
//

#include "luabridge_interface.hpp"

bool check_framework_class(luabridge::LuaRef class_instance, const char * class_name_expected)
{
   if (! class_instance.isUserdata())
      return false;
   luabridge::LuaRef classname_method = class_instance["ClassName"];
   if (! classname_method.isFunction())
      return false;
   luabridge::LuaRef class_name = classname_method(class_instance);
   if (! class_name.isString())
      return false;
   std::string classname_string = class_name.tostring();
   return (0 == strcmp(classname_string.c_str(), class_name_expected));
}
