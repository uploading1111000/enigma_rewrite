from cProfile import label
import importlib
import tkinter as tk
from tkinter import ttk
import re
binds = importlib.import_module("Cpp.out.build.x64-Release.binds")
specs = [
    binds.MachineSpecification("src/Cpp/simulation/machineJsons/enigmaI.json"),
    binds.MachineSpecification("src/Cpp/simulation/machineJsons/enigmaM3.json"),
    binds.MachineSpecificationFour("src/Cpp/simulation/machineJsons/enigmaM4.json")
]
options = [
    specs[0].getName(),
    specs[1].getName(),
    specs[2].getName()
]
indexing = {
    specs[0].getName(): 0,
    specs[1].getName(): 1,
    specs[2].getName(): 2
}
NGrams =[
   binds.BiGram("src/Cpp/ngramData/gramsbi.bin"),
   binds.TriGram("src/Cpp/ngramData/gramstri.bin"),
   binds.QuadGram("src/Cpp/ngramData/gramsquad.bin")
]
specIndex = 0
machine = binds.Machine(specs[0])
alphabet = """Z
Y
X
W
V
U
T
S
R
Q
P
O
N
M
L
K
J
I
H
G
F
E
D
C
B
A"""
class tkRotor():
    def __init__(self, container,index, parent):
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
        self.parent = parent
        self.update()

    def addPath(self, start, end, colour):
        def convert(yI):
            return 415 - (ord(yI)-65) * 15
        self.wiries.create_line(0,convert(start),150,convert(end),fill=colour,width=3)

    def updateWiries(self, wirings, turnovers):
        def convert(yI):
            if yI == 26:
                return 415
            return 415 - yI * 15
        self.wiries.delete("all")
        for i,j in enumerate(wirings):
            self.wiries.create_line(150,convert(i),0,convert(j-1),fill="black",width=2)
        for turnover in turnovers:
            if 1 <= turnover and 26 >= turnover:
                self.wiries.create_line(130,convert(turnover),20,convert(turnover),fill="red",width=5)
        

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
        self.parent.refresh()

    def changeButtonDown(self):
        if self.index >=2 and self.index <= 4:
            prePos = machine.getPosition(self.index-2)
            machine.decrementRotor(self.index-2)
            machine.setPosition(self.index-2,prePos)
        self.parent.refresh()

    def positionButtonUp(self):
        machine.decrementPosition(self.index-2)
        self.parent.refresh()

    def positionButtonDown(self):
        machine.incrementPosition(self.index-2)
        self.parent.refresh()

    def ringLeft(self):
        machine.decrementRing(self.index-2)
        self.parent.refresh()

    def ringRight(self):
        machine.incrementRing(self.index-2)
        self.parent.refresh()

#shamelessly stolen
class IntEntry(tk.Entry):
    def __init__(self, master=None, **kwargs):
        self.var = tk.StringVar()
        tk.Entry.__init__(self, master, textvariable=self.var, **kwargs)
        self.old_value = ''
        self.var.trace('w', self.check)
        self.get, self.set = self.var.get, self.var.set

    def check(self, *args):
        if self.get().isdigit(): 
            self.old_value = self.get()
        else:
            self.set(self.old_value)

class detailsBarSim:
    def __init__(self,simtab):
        self.container = tk.Frame(simtab,bg="grey60")
        self.container.grid(column=1,row=0, padx=10, pady=10)

        self.value = tk.StringVar()
        global options
        self.value.set(options[0])
        menuLabel = tk.Label(self.container,text="Machine type to use:", bg="grey60")
        menuLabel.grid(row=0,column=0)
        self.menu = tk.OptionMenu(self.container,self.value,*options,command=self.machineChange)
        self.menu.grid(row=1,column=0,pady=10)
        print("menu")
        self.rotorOptions = tk.Frame(self.container)
        self.rotorOptions.grid(row=0,column=1,pady=10)
        self.makeRotorOptions()
        print("rotors")
        self.ringOptions = tk.Frame(self.container)
        self.ringOptions.grid(row=0,column=2,pady=10)
        self.makeRingOptions()
        print("rings")
        self.positionOptions = tk.Frame(self.container)
        self.positionOptions.grid(row=0,column=3,pady=10)
        self.makePositionOptions()
        print("positions")
        self.plugboardRow = tk.Frame(self.container)
        self.plugboardRow.grid(row=0,column=4,pady=10)
        self.plugString = tk.StringVar()
        plugLabel = tk.Label(self.plugboardRow,text="Plugboard:")
        plugLabel.grid(row=0,column=0,padx=5)
        plugEntry = tk.Entry(self.plugboardRow,textvariable=self.plugString)
        plugEntry.grid(row=1,column=0,padx=5)
        print("plugboard")

        self.buttonRow = tk.Frame(self.container)
        self.buttonRow.grid(row=0,column=5,pady=10)

    def makeRotorOptions(self):
        print("in rotor")
        global specs
        global specIndex
        options = specs[specIndex].getRotorIDs()
        print(options)
        label = tk.Label(self.rotorOptions,text="Rotors:",bg="grey60")
        label.grid(row=0,column=0,padx=10)
        self.rotorStrings = []
        for i in range(3):
            string = tk.StringVar()
            string.set(options[0])
            dropDown = tk.OptionMenu(self.container,string,*options)
            dropDown.grid(row=i+2,column=0,padx=5)
            self.rotorStrings.append(string)

    def makeRingOptions(self):
        self.rings = []
        label = tk.Label(self.ringOptions,text="Rings:",bg="grey60")
        label.grid(row=0,column=0,padx=10)
        for i in range(3):
            self.rings[i] = IntEntry(self.ringOptions)
            self.rings[i].grid(row=0,column=i+2,padx=5)

    def makePositionOptions(self):
        self.positions = []
        label = tk.Label(self.positionOptions,text="Positions:",bg="grey60")
        label.grid(row=0,column=0,padx=10)
        for i in range(3):
            self.positions[i] = IntEntry(self.positionOptions)
            self.positions[i].grid(row=0,column=i+2,padx=5)

    def machineChange(self,event):
        global indexing
        global specs
        global machine
        global vis
        global specIndex
        index = indexing[self.value.get()]
        specIndex = index
        machine = binds.Machine(specs[index])
        vis.refresh()
        self.makeRotorOptions()

    def errorChange(self,text):
        pass

class visualiser:
    def __init__(self,simtab):
        self.box = tk.Frame(simtab,bg = "grey60")
        self.box.grid(column = 0, row=0, padx=10, pady=10)
        self.rotors = [tkRotor(self.box,i,self) for i in range(6)]
    def refresh(self):
        for rotor in self.rotors:
            rotor.update();
    def keyPress(self,event):
        if not event.char.islower():
            return
        focus = self.box.focus_get()
        if isinstance(focus,tk.Entry):
            return
        path = machine.encryptLetterVerbose(event.char.upper())
        self.refresh()
        for i in range(5):
            self.rotors[5-i].addPath(path[i+1],path[i],"blue")
        self.rotors[0].addPath(path[5],path[5],"blue")
        self.rotors[0].addPath(path[6],path[6],"yellow")
        for i in range(5):
            self.rotors[i+1].addPath(path[i+6],path[i+7],"yellow")


nonalphabetRegex = re.compile('[^A-Z]')
def clean(text):
    upper = text.upper()
    global nonalphabetRegex
    return nonalphabetRegex.sub('', upper)


class stringBox:
    def __init__(self,simtab):
        self.container = tk.Frame(simtab,bg="grey60",height=75)
        self.container.grid(column=0,row=1, padx=10, pady=10)
        self.inText = tk.StringVar()
        self.inText.trace_add("write",self.update)
        self.input = tk.Entry(self.container,width=180,textvariable=self.inText)
        self.input.grid(column=0,row=0,padx=10,pady=10)
        self.outText = tk.StringVar()
        self.output = tk.Entry(self.container,width=180,state="readonly", textvariable=self.outText)
        self.output.grid(column=0,row=1,padx=10,pady=10)

    def update(self,var,index,mode):
        toValidate = self.inText.get()
        if len(toValidate) == 0:
            self.outText.set("")
            return None
        cleaned = clean(toValidate)
        if len(cleaned)==0:
            global detailsBarSim
            detailsBarSim.errorChange("Encrypt string has no readable text")
            self.outText.set("")
            return None
        global machine
        prePos = machine.getPositions()
        word = machine.encryptWord(cleaned)
        self.outText.set(word)
        machine.setPositions(prePos)

root = tk.Tk()
root.title("Enigma Education Tool")
root.config(background="green")
notebook = ttk.Notebook(root)
notebook.pack(expand=True)
simtab = tk.Frame(notebook, bg="green")
solvetab = tk.Frame(notebook)
simtab.pack(fill='both', expand=True)
detailsbarsim = detailsBarSim(simtab)
stringbox = stringBox(simtab)
vis = visualiser(simtab)
root.bind("<KeyPress>",vis.keyPress)
def clearFocus(event):
    global root
    root.focus_set()
root.bind("<Return>",clearFocus)
solvetab.pack(fill='both', expand=True)
notebook.add(simtab, text='Emulator')
notebook.add(solvetab, text='Solver')

root.mainloop()