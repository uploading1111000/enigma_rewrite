import importlib
import random
binds = importlib.import_module("Cpp.out.build.x64-Debug.binds")
big = [random.randint(0,1000) for x in range(1000)]
print(binds.mergesort(big))
