import importlib
import tkinter as tk
from tkinter import ttk
binds = importlib.import_module("Cpp.out.build.x64-Release.binds")
specs = [
    binds.MachineSpecification("src/Cpp/simulation/machineJsons/enigmaI.json"),
    binds.MachineSpecification("src/Cpp/simulation/machineJsons/enigmaM3.json"),
    binds.MachineSpecificationFour("src/Cpp/simulation/machineJsons/enigmaM4.json")
]
NGrams =[
   binds.BiGram("src/Cpp/ngramData/gramsbi.bin"),
   binds.TriGram("src/Cpp/ngramData/gramstri.bin"),
   binds.QuadGram("src/Cpp/ngramData/gramsquad.bin")
]
alphabet = """A
B
C
D
E
F
G
H
I
J
K
L
M
N
O
P
Q
R
S
T
U
V
W
X
Y
Z"""
def rotor(frame,rotate=False,change=False,rings=False,wires=None,col=0):
    container = tk.Frame(frame,bg="grey60")
    container.grid(column=col,row=0)
    ringBox = tk.Label(container,text="Rings: 1")
    ringBox.grid(column=1,row=0,padx=5,pady=5)
    changeBox = tk.Label(container,text="I")
    changeBox.grid(column=1,row=1,padx=5,pady=5)
    rotateUp = tk.Button(container,text="/\\")
    rotateUp.grid(column=1,row=2,padx=5,pady=5)
    leftLetters = tk.Label(container,text=alphabet)
    rightLetters = tk.Label(container,text=alphabet)
    leftLetters.grid(column=0,row=3,pady=5,sticky="E")
    rightLetters.grid(column=2,row=3,pady=5,sticky="W")
    wiries = tk.Frame(container,width=150,height=450,bg="grey40")
    wiries.grid(column=1,row=3,pady=5)
    rotateDown = tk.Button(container,text="\\/")
    rotateDown.grid(column=1,row=4,padx=5,pady=5)
    if not rotate:
        rotateDown.grid_forget()
        rotateUp.grid_forget()
    if not change:
        changeBox.grid_forget()
    else:
        changeLeft = tk.Button(container,text="<")
        changeLeft.grid(column=0,row=1,pady=5)
        changeRight = tk.Button(container,text=">")
        changeRight.grid(column=2,row=1,pady=5)
    if not rings:
        ringBox.grid_forget()
    else:
        ringLeft = tk.Button(container,text="<")
        ringLeft.grid(column=0,row=0,pady=5)
        ringRight = tk.Button(container,text=">")
        ringRight.grid(column=2,row=0,pady=5)


def simulationTab(simtab):
    visualiser = tk.Frame(simtab,bg = "grey60")
    visualiser.grid(column = 0, row=0, padx=10, pady=10)
    details = tk.Frame(simtab, width=300, height=650, bg= "grey60")
    details.grid(column=1,row=0, padx=10, pady=10)
    stringIO = tk.Frame(simtab, width = 1100, height = 75, bg = "grey60")
    stringIO.grid(column=0,row=1, padx=10, pady=10)
    
    rotor(visualiser,change=True,col=0)
    rotor(visualiser,change=True,rotate=True,rings=True,col=1)
    rotor(visualiser,change=True,rotate=True,rings=True,col=2)
    rotor(visualiser,change=True,rotate=True,rings=True,col=3)
    rotor(visualiser,change=True,rotate=True,rings=True,col=4)
    rotor(visualiser,col=5)
root = tk.Tk()
root.title("Enigma Education Tool")
root.config(background="green")
notebook = ttk.Notebook(root)
notebook.pack(expand=True)
simtab = tk.Frame(notebook, bg="green")
solvetab = tk.Frame(notebook)
simtab.pack(fill='both', expand=True)
simulationTab(simtab)
solvetab.pack(fill='both', expand=True)
notebook.add(simtab, text='Emulator')
notebook.add(solvetab, text='Solver')

root.mainloop()