import importlib
binds = importlib.import_module("Cpp.out.build.x64-Debug.binds")
print(binds.sort([1,3,5,2,4,6]))
