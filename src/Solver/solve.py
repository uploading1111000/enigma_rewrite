import importlib
binds = importlib.import_module("Cpp.out.build.x64-Release.binds")
spec = binds.MachineSpecification("E:/Programming/Project/src/Solver/Cpp/simulation/machineJsons/enigmaI.json")
print(spec.getName())
