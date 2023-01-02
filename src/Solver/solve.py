import importlib
import random
binds = importlib.import_module("Cpp.out.build.x64-Debug.binds")
while True:
    n = int(input("n:"))
    big = [random.randint(0,1000) for x in range(n)]
    print(binds.mergesort(big))
