import importlib
import os
binds = importlib.import_module("Cpp.out.build.x64-Release.binds")
specifications = []
specifications.append(binds.MachineSpecification("src/Solver/Cpp/simulation/machineJsons/enigmaI.json"))
specifications.append(binds.MachineSpecification("src/Solver/Cpp/simulation/machineJsons/enigmaM3.json"))
specifications.append(binds.MachineSpecificationFour("src/Solver/Cpp/simulation/machineJsons/enigmaM4.json"))
machine = binds.MachineFour(specifications[2])
print(machine.encryptWord("AHAHAHHAHAHA"))