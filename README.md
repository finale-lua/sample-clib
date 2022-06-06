# sample-clib
Sample C library that can be loaded by Lua on Finale (_RGP Lua_ plugin).

If you wish to write your own C library that can be loaded into lua scripts running under _RGP Lua_, you can use the build files (and sample source code) as a template. You can similarly use it to build existing libraries from source code.

The sample libary has exactly one function, `plusone`, that adds one to an input number.

To call it:

- Copy the output library `sampleclib.dll` (Windows) or `sampleclib.dylib` (macOS) to the same folder as your script.
- Configure your script in _RGP Lua_.
- Add the following code to your script:

```lua
local sampleclib = require('sampleclib')
local plus_one = sampleclib.plusone(1)
print("pluseone(1) = ", plus_one)
```

(See `test/test_sampleclib.lua` for an example of this code.

The XCode (macOS) and Visual Studio (Windows) build files are set up to launch Finale 27 automatically. Note that to debug on macOS, you have to change the permissions on the Finale.app bundle to allow debugging. There are instructions [here](https://helpx.adobe.com/photoshop/kb/debug-plugins-in-photoshop-bigsur.html) for PhotoShop on Big Sur (and earlier) that you can use as a guide for doing the same with Finale. Unfortunately, these may not work in Monterey, due to a change in how the XCode command line utilities work. If I discover a technique for Monterey I will update this Readme file.

You may need to modify the directories of Finale in the build files.

To debug your code:

- Run Finale from XCode or Visual Studio in Debug mode.
- Set breakpoints as required in the c library.
- Run your lua script that calls the `sampleclib` file as above.
- Your debugger should break at your breakpoints.

