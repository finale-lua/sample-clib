function plugindef()
    finaleplugin.RequireDocument = false
end
    
require('mobdebug').start() -- for ZeroBrane Studio debugging

--package.cpath = package.cpath .. ";" .. finenv.RunningLuaFolderPath() .. "sampleclib.bundle/Contents/MacOS/?"

print(package.cpath)

local sampleclib = require('sampleclib')
local plus_one = sampleclib.plusone(1)
print("pluseone(1) = ", plus_one)

local str1 = sampleclib.get_string("STR 0001")  -- returns "This is a test" from the string resource table
local str2 = sampleclib.get_string("Invalid")   -- not in the resource table, so returns "Invalid"

--finenv.UI():AlertInfo("pluseone(1) = "..tostring(plus_one), "")

local measures = sampleclib.load_measures()

print("measures count", measures.Count)

for e in eachentrysaved(finenv.Region()) do
    print(sampleclib.entry_duration(e))
    sampleclib.halve_duration(e)
end
