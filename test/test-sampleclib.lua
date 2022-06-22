function plugindef()
    finaleplugin.RequireDocument = false
end
    
require('mobdebug').start() -- for ZeroBrane Studio debugging

local sampleclib = require('sampleclib')
local plus_one = sampleclib.plusone(1)
print("pluseone(1) = ", plus_one)

--finenv.UI():AlertInfo("pluseone(1) = "..tostring(plus_one), "")

local measures = sampleclib.load_measures()

print("measures count", measures.Count)

for e in eachentrysaved(finenv.Region()) do
    print(sampleclib.entry_duration(e))
    sampleclib.halve_duration(e)
end
