//
//  sampleclib.cpp
//  SampleCLib
//
//  Created by Robert Patterson on 3/28/21.
//  Copyright © 2021 Robert Patterson. All rights reserved.
//  (Usage permitted by MIT License. See LICENSE file in this repository.)
//

#if defined(__GNUC__)
#include "Carbon/Carbon.h"
#endif

#include "luabridge_interface.hpp"

#include "sampleclib.hpp"

/** \brief Demonstrates retrieving a string resource from the Library */
static int sampleclib_get_string(lua_State *L)
{
   bool pushed1 = false;
   std::string strKey(luaL_checkstring(L, 1));
#if defined(__GNUC__)
   auto C_to_CFString = [](const std::string &cstring)
      { return CFStringCreateWithCString(kCFAllocatorDefault, cstring.c_str(), kCFStringEncodingUTF8); };
   CFStringRef bundleID = C_to_CFString("com.finalelua.samples.sampleclib");
   CFBundleRef bundleref = CFBundleGetBundleWithIdentifier(bundleID);
   CFRelease(bundleID);
   if (bundleref)
   {
      CFStringRef key = C_to_CFString(strKey.c_str());
      CFStringRef tablename = C_to_CFString("Localizable");
      CFStringRef stringRef = CFCopyLocalizedStringFromTableInBundle (key, tablename, bundleref, CFSTR(""));
      CFRelease(key);
      CFRelease(tablename);
      if (stringRef)
      {
         char szBuffer[500];
         CFStringGetCString(stringRef, szBuffer, sizeof(szBuffer), kCFStringEncodingUTF8);
         CFRelease(stringRef);
         lua_pushstring(L, szBuffer);
         pushed1 = true;
      }
   }
#endif
   if (! pushed1)
      lua_pushfstring(L, "No resource found for %s.", strKey.c_str());
   return  1;
}

/** \brief Demonstrates how to instantiate an FCClass for the FCMeasures collection.
 * This function also loads all measures in the current document.
 *
 * Also includes a demonstration of how to use GetItemAt to retrieve a member of the collection.
 *
 * \returns a loaded FCMeasures collection of all measures in the document.
 */
static int sampleclib_load_measures(lua_State *L)
{
   FCClass measures = FCClass::CreateInstance(L, "FCMeasures");
   measures.ExecuteMethod<bool>("LoadAll");
   // these 2 lines demonstrate how to get a value back that is another FCClass
   FCClass measure = measures.ExecuteMethod<FCClass>("GetItemAt", 0);
   [[maybe_unused]]int width = measure.GetProperty<int>("Width");
   //
   measures.Push(); // this is how you return a value from C++ to Lua.
   return 1; // this is the number of values returned (i.e., pushed).
}

/** \brief Demonstrates modification of an input FCNoteEntry class by halving its duration.
 *
 * stack position 1: an instance of FCNoteEntry as the first parameter .
 */
static int sampleclib_halve_duration(lua_State *L)
{
   FCClass entry = FCClass::CreateInstanceFromStack(L, "FCNoteEntry", 1);
   // You can use either ExecuteMethod or SetProperty here.
   entry.ExecuteMethod<void>("SetDuration", entry.GetProperty<int>("Duration")/2);
//   entry.SetProperty("Duration", entry.GetProperty<int>("Duration")/2);
   return 0;
}

/** \brief Demonstrates reading a property of an input FCNoteEntry class by returning its duration.
 *
 * stack position 1: an instance of FCNoteEntry as the first parameter .
 */
static int sampleclib_entry_duration(lua_State *L)
{
   FCClass entry = FCClass::CreateInstanceFromStack(L, "FCNoteEntry", 1);
   lua_pushinteger(L, entry.GetProperty<int>("Duration"));
   return 1;
}

/** \brief demonstrates a simple mathematical calculation that adds 1 to an input value.
 *
 * stack position 1: the value to add to
 * \return the value + 1
 */
static int sampleclib_plusone (lua_State *L)
{
   lua_pushnumber ( L, luaL_checknumber(L, 1) + 1 );
   return 1;
}

static const luaL_Reg sampleclib[] = {
   {"plusone",          sampleclib_plusone},
   {"entry_duration",   sampleclib_entry_duration},
   {"halve_duration",   sampleclib_halve_duration},
   {"load_measures",    sampleclib_load_measures},
   {"get_string",       sampleclib_get_string},
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
