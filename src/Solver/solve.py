import importlib
binds = importlib.import_module("Cpp.out.build.x64-Debug.binds")
print(binds.sort([2,1,3]))
