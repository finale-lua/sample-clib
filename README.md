# sample-clib
Sample C++ library that can be loaded by Lua on Finale (_RGP Lua_ plugin).

If you wish to write your own C or C++ library that can be loaded into lua scripts running under _RGP Lua_, you can use the build files (and sample source code) as a template. You can similarly use it to build existing libraries from open-source projects.

To access functions in the library:

- Copy the output library `sampleclib.dll` (Windows) or `sampleclib.dylib` (macOS) to the same folder as your script.
- Configure your script in _RGP Lua_.
- Add the following code to your script:

```lua
local sampleclib = require('sampleclib')
```

The sample libary has several functions, including some that demonstrate how to access and modify instances of classes from the PDK Framework in C++ code.

### plusone(inp_number)

Adds one to an input number. You can think of this as a “Hello World” function.

```lua
local plus_one = sampleclib.plusone(1)
print("pluseone(1) = ", plus_one)
```

### load_measures()

Returns an instance of `FCMeasures` with all the measures loaded for the current document.

```lua
local measures = sampleclib.load_measures()
print("measures count", measures.Count)
```

### entry_duration(entry)

Returns the duration of the input instance of `FCNoteEntry`.

```lua
for e in eachentry(finenv.Region()) do
    print(sampleclib.entry_duration(e))
end
```

### halve_duration(entry)

Halves the duration of the input instance of `FCNoteEntry`.

```lua
for e in eachentrysaved(finenv.Region()) do
    sampleclib.halve_duration(e)
end
```

See `test/test_sampleclib.lua` for working examples of this code.

# Debugging From Your IDE

The XCode (macOS) and Visual Studio (Windows) build files are set up to launch Finale when you run the Debug configuiration. Each operating system requires some extra steps.

## macOS

To debug on macOS, you have to change the permissions on the Finale.app bundle to allow debugging. There are instructions [here](https://helpx.adobe.com/photoshop/kb/debug-plugins-in-photoshop-bigsur.html) for PhotoShop on Big Sur (and earlier) that you can use as a guide for doing the same with Finale. Unfortunately, these instructions may not work in Monterey, due to a change in how the XCode command line utilities work. (However, once the Finale.app bundle has its debugging permissions enabled, you can use it with Monterey.) If I discover a technique for Monterey I will update this Readme file.

The `SampleCLib-Debug` scheme is already set to launch `/Applications/Finale.app`.

## Windows

In Visual Studio, open the property pages for the Debug | x64 configuration. In the `Common Properties->Debugging` tab, specify the path to `Finale.exe`. The default location for Finale 27 is

`C:\Program Files\MakeMusic\Finale\27\Finale.exe`


## To debug your C++ code:

- Place a test script in the `test` subfolder, or use `test/test_sampleclib.lua`.
- Run Finale from XCode (macOS) or Visual Studio (Windows) using the Debug configuration.
- Set breakpoints as required in the C library.
- In Finale, run your test script that calls the `sampleclib` file as above.
- The debugger should break at your breakpoints when the script calls `sampleclib`.
