import importlib
binds = importlib.import_module("Cpp.out.build.x64-Release.binds")
specs = [
    binds.MachineSpecification("src/Cpp/simulation/machineJsons/enigmaI.json"),
    binds.MachineSpecification("src/Cpp/simulation/machineJsons/enigmaM3.json"),
    binds.MachineSpecificationFour("src/Cpp/simulation/machineJsons/enigmaM4.json")
]
IOC = binds.IndexOfCoincidence()
solverMachine = binds.SolverMachine(spec = specs[0],ciphertext = "HELLOWORLD")
solverMachine.findRotors()