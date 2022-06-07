# sample-clib
Sample C library that can be loaded by Lua on Finale (_RGP Lua_ plugin).

If you wish to write your own C library that can be loaded into lua scripts running under _RGP Lua_, you can use the build files (and sample source code) as a template. You can similarly use it to build existing libraries from open-source projects.

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

# Debugging From Your IDE

The XCode (macOS) and Visual Studio (Windows) build files are set up to launch Finale when you run the Debug configuiration. Each operating system requires some extra steps.

## macOS

To debug on macOS, you have to change the permissions on the Finale.app bundle to allow debugging. There are instructions [here](https://helpx.adobe.com/photoshop/kb/debug-plugins-in-photoshop-bigsur.html) for PhotoShop on Big Sur (and earlier) that you can use as a guide for doing the same with Finale. Unfortunately, these instructions may not work in Monterey, due to a change in how the XCode command line utilities work. (However, once the Finale.app bundle has its debugging permissions enabled, you can use it with Monterey.) If I discover a technique for Monterey I will update this Readme file.

The `SampleCLib-Debug` scheme is already set to launch `/Applications/Finale.app`.

## Windows

In Visual Studio, open the property pages for the Debug | x64 configuration. In the `Common Properties->Debugging` tab, specify the path to `Finale.exe`. The default location for Finale 27 is

`C:\Program Files\MakeMusic\Finale\27\Finale.exe`


## To debug your C code:

- Place a test script in the `test` subfolder, or use `test/test_sampleclib.lua`.
- Run Finale from XCode (macOS) or Visual Studio (Windows) using the Debug configuration.
- Set breakpoints as required in the C library.
- In Finale, run your test script that calls the `sampleclib` file as above.
- The debugger should break at your breakpoints when the script calls `sampleclib`.
