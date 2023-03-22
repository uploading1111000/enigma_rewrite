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
machine = binds.Machine(specs[0])
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
class tkRotor():
    def __init__(self, container,index):
        col = 3 * index
        leftLetters = tk.Label(container,text=alphabet)
        rightLetters = tk.Label(container,text=alphabet)
        leftLetters.grid(column=col+0,row=4,pady=5,sticky="E")
        rightLetters.grid(column=col+2,row=4,pady=5,sticky="W")
        self.wiries = tk.Canvas(container,width=150,height=450,bg="grey40")
        self.wiries.grid(column=col+1,row=4,pady=5)
        if index == 0 or (index >= 2 and index <= 4):
            changeLeft = tk.Button(container,text="<", command=self.changeButtonDown)
            changeLeft.grid(column=col+0,row=1,pady=5)
            changeRight = tk.Button(container,text=">", command=self.changeButtonUp)
            changeRight.grid(column=col+2,row=1,pady=5)
            self.changeBox = tk.Label(container,text="I")
            self.changeBox.grid(column=col+1,row=1,padx=5,pady=5)
        if index >= 2 and index <= 4:
            ringLeft = tk.Button(container,text="<",command=self.ringLeft)
            ringLeft.grid(column=col+0,row=0,pady=5)
            ringRight = tk.Button(container,text=">",command=self.ringRight)
            ringRight.grid(column=col+2,row=0,pady=5)
            self.positionIndicator =tk.Label(container,text="1")
            self.positionIndicator.grid(column=col+1,row=2,padx=5,pady=5)
            rotateDown = tk.Button(container,text="\\/",command=self.positionButtonDown)
            rotateDown.grid(column=col+1,row=5,padx=5,pady=5)
            rotateUp = tk.Button(container,text="/\\",command=self.positionButtonUp)
            rotateUp.grid(column=col+1,row=3,padx=5,pady=5)
            self.ringBox = tk.Label(container,text="Rings: 1")
            self.ringBox.grid(column=col+1,row=0,padx=5,pady=5)
        self.index=index
        self.update()


    def updateWiries(self, wirings, turnovers):
        def convert(yI):
            return yI * 15 + 40
        self.wiries.delete("all")
        for i,j in enumerate(wirings):
            self.wiries.create_line(150,convert(i),0,convert(j-1),fill="black",width=2)
        for turnover in turnovers:
            if 1 <= turnover and 26 >= turnover:
                self.wiries.create_line(130,convert(turnover-1),20,convert(turnover-1),fill="red",width=5)
        

    def update(self):
        global machine
        wirings = machine.getWiring(self.index)
        turnovers = [0,0]
        if self.index <= 4 and self.index >= 2:
            self.changeBox.configure(text=machine.getRotorID(self.index-2))
            self.positionIndicator.configure(text=str(machine.getPosition(self.index-2)))
            self.ringBox.configure(text=("Ring: " + str(machine.getRing(self.index-2))))
            turnovers = machine.getTurnpoints(self.index-2)
       
        self.updateWiries(wirings,turnovers)

    def changeButtonUp(self):
        if self.index >=2 and self.index <= 4:
            prePos = machine.getPosition(self.index-2)
            machine.incrementRotor(self.index-2)
            machine.setPosition(self.index-2,prePos)
        self.update()

    def changeButtonDown(self):
        if self.index >=2 and self.index <= 4:
            prePos = machine.getPosition(self.index-2)
            machine.decrementRotor(self.index-2)
            machine.setPosition(self.index-2,prePos)
        self.update()

    def positionButtonUp(self):
        machine.decrementPosition(self.index-2)
        self.update()

    def positionButtonDown(self):
        machine.incrementPosition(self.index-2)
        self.update()

    def ringLeft(self):
        machine.decrementRing(self.index-2)
        self.update()

    def ringRight(self):
        machine.incrementRing(self.index-2)
        self.update()

class visualiser:
    def __init__(self,simtab):
        self.box = tk.Frame(simtab,bg = "grey60")
        self.box.grid(column = 0, row=0, padx=10, pady=10)
        self.rotors = [tkRotor(self.box,i) for i in range(6)]


def simulationTab(simtab):
    global visualiser
    visualiser(simtab)
    details = tk.Frame(simtab, width=300, height=650, bg= "grey60")
    details.grid(column=1,row=0, padx=10, pady=10)
    stringIO = tk.Frame(simtab, width = 1100, height = 75, bg = "grey60")
    stringIO.grid(column=0,row=1, padx=10, pady=10)
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