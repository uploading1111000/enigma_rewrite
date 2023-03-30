import importlib
from textwrap import indent
import tkinter as tk
from tkinter import ttk
import re
import time
binds = importlib.import_module("Cpp.out.build.x64-Release.binds")
specs = [
    binds.MachineSpecification("src/Cpp/simulation/machineJsons/enigmaI.json"),
    binds.MachineSpecification("src/Cpp/simulation/machineJsons/enigmaM3.json")
] #global list of specifications that can be made into machines at any time
options = [
    specs[0].getName(),
    specs[1].getName(),
] #options for machine dropdown
indexing = {
    specs[0].getName(): 0,
    specs[1].getName(): 1,
} #converts machine names to spec index
idIndexing = {
    "I" : 0,
    "II" : 1,
    "III" : 2,
    "IV" : 3,
    "V" : 4,
    "VI" : 5,
    "VII" : 6,
    "VIII" : 7
} #converts rotor name to rotor id
IOC = binds.IndexOfCoincidence()
NGrams =[
   binds.BiGram("src/Cpp/ngramData/gramsbi.bin"),
   binds.TriGram("src/Cpp/ngramData/gramstri.bin"),
   binds.QuadGram("src/Cpp/ngramData/gramsquad.bin")
]
specIndex = 0
machine = binds.Machine(specs[0])
solveMachine = binds.SolverMachine(specs[0])
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
        col = 3 * index #each rotor is 3 grids wide
        leftLetters = tk.Label(container,text=alphabet) #text to either side of wires
        rightLetters = tk.Label(container,text=alphabet) 
        leftLetters.grid(column=col+0,row=4,pady=5,sticky="E")
        rightLetters.grid(column=col+2,row=4,pady=5,sticky="W")
        self.wiries = tk.Canvas(container,width=150,height=450,bg="grey40") #wires canvas
        self.wiries.grid(column=col+1,row=4,pady=5)
        if index == 0 or (index >= 2 and index <= 4): #reflector or rotor, change to different rotor or different reflector
            changeLeft = tk.Button(container,text="<", command=self.changeButtonDown)
            changeLeft.grid(column=col+0,row=1,pady=5)
            changeRight = tk.Button(container,text=">", command=self.changeButtonUp)
            changeRight.grid(column=col+2,row=1,pady=5)
            self.changeBox = tk.Label(container,text="I") #ID of current reflector/rotor
            self.changeBox.grid(column=col+1,row=1,padx=5,pady=5)
        if index >= 2 and index <= 4: #is rotor
            ringLeft = tk.Button(container,text="<",command=self.ringLeft) #ring buttons
            ringLeft.grid(column=col+0,row=0,pady=5)
            ringRight = tk.Button(container,text=">",command=self.ringRight)
            ringRight.grid(column=col+2,row=0,pady=5)
            self.positionIndicator =tk.Label(container,text="1") #position number
            self.positionIndicator.grid(column=col+1,row=2,padx=5,pady=5)
            rotateDown = tk.Button(container,text="\\/",command=self.positionButtonDown) #rotate buttons
            rotateDown.grid(column=col+1,row=5,padx=5,pady=5)
            rotateUp = tk.Button(container,text="/\\",command=self.positionButtonUp)
            rotateUp.grid(column=col+1,row=3,padx=5,pady=5)
            self.ringBox = tk.Label(container,text="Rings: 1") #ring number
            self.ringBox.grid(column=col+1,row=0,padx=5,pady=5)
        self.index=index #0 reflector 1 4th rotor 2-4 rotor 5 plugboard
        self.parent = parent #visualiser class
        self.update() #add wires, update all the indicators

    def addPath(self, start, end, colour): #add a lit path (for visualisation)
        def convert(yI):
            return 415 - (ord(yI)-65) * 15
        self.wiries.create_line(0,convert(start),150,convert(end),fill=colour,width=3)

    def updateWiries(self, wirings, turnovers): #build wirings and turnovers
        def convert(yI):
            if yI == 26: #has to be done for some strange reason
                return 415
            return 415 - yI * 15
        self.wiries.delete("all") #clear wires
        for i,j in enumerate(wirings):
            self.wiries.create_line(150,convert(i),0,convert(j-1),fill="black",width=2) #add wires back
        for turnover in turnovers: #add turnovers
            if 1 <= turnover and 26 >= turnover: #0 will indicate no turnover
                self.wiries.create_line(130,convert(turnover),20,convert(turnover),fill="red",width=5)
        

    def update(self):
        global machine
        wirings = machine.getWiring(self.index) #catch all from the machine
        turnovers = [0,0]
        if self.index <= 4 and self.index >= 2: #is rotor
            self.changeBox.configure(text=machine.getRotorID(self.index-2)) #update id
            self.positionIndicator.configure(text=str(machine.getPosition(self.index-2))) #update position number
            self.ringBox.configure(text=("Ring: " + str(machine.getRing(self.index-2)))) #update ring number
            turnovers = machine.getTurnpoints(self.index-2)
        self.updateWiries(wirings,turnovers)

    def changeButtonUp(self): #increment rotor id
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

    def positionButtonUp(self): #increment rotor position
        machine.decrementPosition(self.index-2)
        self.parent.refresh()

    def positionButtonDown(self):
        machine.incrementPosition(self.index-2)
        self.parent.refresh()

    def ringLeft(self): #decrement rotor ring
        machine.decrementRing(self.index-2)
        self.parent.refresh()

    def ringRight(self):
        machine.incrementRing(self.index-2)
        self.parent.refresh()

class IntEntry(tk.Entry): #entry widget that only allows input of numbers between 1-26
    def __init__(self, master=None, **kwargs):
        self.var = tk.StringVar()
        tk.Entry.__init__(self, master, textvariable=self.var, **kwargs)
        self.old_value = ''
        self.var.trace('w', self.check) #binds text box update to check
        self.get, self.set = self.var.get, self.var.set
        self.set(1)

    def check(self, *args):
        new = self.get()
        if len(new) == 0: #empty box needs to be allowed so numbers can change
            self.oldvalue = new
        elif new.isdigit(): #check for non numbers
            if int(new) >= 1 and int(new) <= 26:
                self.oldvalue = new
            else:
                self.set(self.oldvalue)
        else:
            self.set(self.oldvalue) #imperceptibly fast replace new input with old, valid input

    def getValid(self): #returns 1 if box is empty
        val = self.get()
        if len(val) == 0:
            return 1
        return int(val)

class detailsBar:
    def __init__(self,tab,mac=machine,sim=True):
        self.container = tk.Frame(tab,bg="grey60")
        self.container.grid(column=1,row=0, padx=10, pady=10)

        self.value = tk.StringVar() #currently selected machine name
        global options
        self.value.set(options[0])
        menuLabel = tk.Label(self.container,text="Machine type to use:", bg="grey60") 
        menuLabel.grid(row=0,column=0)
        self.menu = tk.OptionMenu(self.container,self.value,*options,command=self.machineChange) #machine selection dropdown
        self.menu.grid(row=1,column=0,pady=10)

        self.rotorOptions = tk.Frame(self.container, bg="grey60")
        self.rotorOptions.grid(row=2,column=0,pady=10)
        self.makeRotorOptions() #rotor selection dropdowns

        self.ringOptions = tk.Frame(self.container, bg="grey60")
        self.ringOptions.grid(row=3,column=0,pady=10)
        self.makeRingOptions() #ring input boxes

        self.positionOptions = tk.Frame(self.container, bg="grey60")
        self.positionOptions.grid(row=4,column=0,pady=10)
        self.makePositionOptions() #position input boxes

        self.plugboardRow = tk.Frame(self.container, bg="grey60")
        self.plugboardRow.grid(row=5,column=0,pady=10)
        self.plugString = tk.StringVar()
        plugLabel = tk.Label(self.plugboardRow,text="Plugboard:",bg="grey60")
        plugLabel.grid(row=0,column=0,padx=5)
        plugEntry = tk.Entry(self.plugboardRow,textvariable=self.plugString,width=44)
        plugEntry.grid(row=0,column=1,padx=5) #plugboard input box

        self.buttonRow = tk.Frame(self.container, bg="grey60") #reset/send buttons
        self.buttonRow.grid(row=6,column=0,pady=10)
        resetButton = tk.Button(self.buttonRow,text="Reset",command=self.reset)
        resetButton.grid(row=0,column=0,padx=10)
        if sim: #no need to send to simulator on solver tab
            sendButton = tk.Button(self.buttonRow,text="Send to Simulator", command = self.send)
            sendButton.grid(row=0,column=1,padx=10)

        self.errorBox = tk.Text(self.container,fg="red",bg="grey60",state="disabled",width=44,height=10)
        self.errorBox.grid(row=7,column=0,pady=10) #error readout

        self.sim = sim
        self.machine = mac #allows usage of solvermachine on solver tab and machine on simulation tab

    def makeRotorOptions(self):
        global specs
        global specIndex
        options = specs[specIndex].getRotorIDs() #list of rotor ids
        label = tk.Label(self.rotorOptions,text="Rotors:",bg="grey60")
        label.grid(row=0,column=0,padx=10)
        self.rotorStrings = [] #stores strings as member for easy access 
        self.dropDown = [] #also stores dropdowns to be modified by solver
        for i in range(3):
            string = tk.StringVar()
            string.set(options[i])
            self.dropDown.append(tk.OptionMenu(self.rotorOptions,string,*options))
            self.dropDown[i].grid(row=0,column=i+2,padx=5)
            self.rotorStrings.append(string)

    def makeRingOptions(self): #ring input boxes
        self.rings = []
        label = tk.Label(self.ringOptions,text="Rings:",bg="grey60")
        label.grid(row=0,column=0,padx=10)
        for i in range(3):
            self.rings.append(IntEntry(self.ringOptions,width=3))
            self.rings[i].grid(row=0,column=i+2,padx=5)

    def makePositionOptions(self): #position input boxes
        self.positions = []
        label = tk.Label(self.positionOptions,text="Positions:",bg="grey60")
        label.grid(row=0,column=0,padx=10)
        for i in range(3):
            self.positions.append(IntEntry(self.positionOptions,width=3))
            self.positions[i].grid(row=0,column=i+2,padx=5)

    def reset(self): #set all values to default
        for ring in self.rings:
            ring.set("1")
        for position in self.positions:
            position.set("1")
        self.plugString.set("")
        global specs
        global specIndex
        options = specs[specIndex].getRotorIDs()
        for i in range(3):
            self.rotorStrings[i].set(options[i])

    def machineChange(self,event): #called on change of machine by dropdown
        global indexing
        global specs
        global vis
        global specIndex
        index = indexing[self.value.get()]
        specIndex = index
        if self.sim:
            global machine #global machine is re-initialised and then self machine references this
            machine = binds.Machine(specs[index])
            self.machine = machine #if only self machine were to be re-initialised then details bar would disconnect from globals
        else:
            global solveMachine
            solveMachine = binds.SolverMachine(specs[index])
            self.machine = solveMachine
        vis.refresh() #change visualiser according to new machine
        stringbox.update()
        for d in self.dropDown: #old dropdowns are now invalid
            d.grid_forget()
        self.makeRotorOptions()
        self.reset() #set all to 0

    def send(self,*args): #updates machine settings in line with details given
        global vis
        global idIndexing
        global stringbox
        self.machine.setRotors([idIndexing[self.rotorStrings[i].get()] for i in range(3)])
        self.machine.setRings([self.rings[i].getValid() for i in range(3)])
        self.machine.setPositions([self.positions[i].getValid() for i in range(3)])
        self.handlePlugboard() #moved to own function for conciseness
        vis.refresh() 
        stringbox.update()

    def handlePlugboard(self):
        raw = self.plugString.get()
        cleaned = clean(raw)
        if len(cleaned) % 2 != 0: #check for odd plugboard length
            self.errorChange("invalid plugboard length. ignoring last letter")
            cleaned = cleaned[:-1]
        pairs = []
        used = set() #used letters
        for index in range(0,len(cleaned),2):
            if cleaned[index] in used or cleaned[index+1] in used: #a letter has already been sued
                print("multiple use")
                self.errorChange("same letter used multiple times in plug. ignoring duplicate pair")
            else:
                pairs.append([cleaned[index],cleaned[index+1]])
                used.add(cleaned[index])
                used.add(cleaned[index+1])
        self.machine.setPlugboard(pairs)

    def errorChange(self,text):
        self.errorBox.config(state="normal") #text box must be made editable before being re-locked
        self.errorBox.insert(tk.END,time.strftime("%H:%M:%S ",time.localtime())) #insert(tk.END) adds the string at bottom
        self.errorBox.insert(tk.END,text + "\n")
        self.errorBox.see("end")
        self.errorBox.config(state="disabled") #relock

    def changeRotors(self, rotors):
        global specs
        global specIndex
        for i in range(3):
            self.rotorStrings[i].set(rotors[i])

    def changePositions(self,positions):
        for i in range(3):
            self.positions[i].set(str(positions[i]))

    def changeRings(self,rings):
        for i in range(3):
            self.rings[i].set(str(rings[i]))

    def changePlugboard(self, plugboard):
        stringRep = ""
        for pair in plugboard:
            stringRep = stringRep + pair + " "
        self.plugString.set(stringRep)

    def retrieve(self): #takes state of machine and puts it into the details inputs
        self.changeRotors(self.machine.getRotorIDs())
        self.changePositions(self.machine.getPositions())
        self.changeRings(self.machine.getRings())
        wiring = self.machine.getWiring(5)
        pairs = []
        marked = set()
        for i,j in enumerate(wiring):
            if (i+1) in marked:
                continue
            elif i + 1 != j: #take wiring and check if it is a plug or not
                marked.add(j)
                marked.add(i+1)
                pairs.append(chr(j+64) + chr(i+65))
        self.changePlugboard(pairs)

class visualiser:
    def __init__(self,simtab):
        self.box = tk.Frame(simtab,bg = "grey60")
        self.box.grid(column = 0, row=0, padx=10, pady=10)
        self.rotors = [tkRotor(self.box,i,self) for i in range(6)]
    def refresh(self): #parent refresh allows rotors to affect each other, and all rotors to be updates at same time
        for rotor in self.rotors:
            rotor.update();
    def keyPress(self,event):
        if not event.char.islower(): #no keyboard input
            return
        focus = self.box.focus_get()
        if isinstance(focus,tk.Entry): #check for entry focus
            return
        path = machine.encryptLetterVerbose(event.char.upper())
        self.refresh()
        for i in range(5): #add rotor4-plugboard wires
            self.rotors[5-i].addPath(path[i+1],path[i],"blue")
        self.rotors[0].addPath(path[5],path[5],"blue") #reflector wires
        self.rotors[0].addPath(path[6],path[6],"yellow")
        for i in range(5): #rotor4-plugboard reverse wires
            self.rotors[i+1].addPath(path[i+6],path[i+7],"yellow")


nonalphabetRegex = re.compile('[^A-Z]') #regex matching anything that is not uppercase alphabet
def clean(text):
    upper = text.upper() #make lowercase upper
    global nonalphabetRegex
    return nonalphabetRegex.sub('', upper) #replace not uppercase alphabet with nothing


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

    def update(self,*args):
        toValidate = self.inText.get()
        if len(toValidate) == 0: #empty text box -> no need to encrypt or give error
            self.outText.set("")
            return None
        cleaned = clean(toValidate) 
        if len(cleaned)==0: #invalid data with no alphabetical text
            global detailsbarsim
            detailsbarsim.errorChange("Encrypt string has no readable text")
            self.outText.set("")
            return None
        global machine
        prePos = machine.getPositions() #get position and set after so encryptword does not permanently affect machine state
        word = machine.encryptWord(cleaned)
        self.outText.set(word)
        machine.setPositions(prePos)

class bigStringBox:
    def __init__(self, tab):
        self.container = tk.Frame(tab,bg="grey60")
        self.container.grid(row=0,column=0,padx=10,pady=10)

        self.inputBox = tk.Text(self.container,width=68,height=35,bg="white")
        self.inputBox.insert(tk.END,"input text here")
        self.inputBox.grid(row=0,column=0,padx=10,pady=10)

        self.outputBox = tk.Text(self.container,width=68,height=35,bg="white",state="disabled") 
        self.outputBox.grid(row=0,column=1,padx=10,pady=10)
    def getText(self):
        raw = self.inputBox.get("1.0",tk.END) #1.0->tk.End is all text
        cleaned = clean(raw)
        if len(cleaned) == 0: #invalid data
            global detailsbarsolve
            detailsbarsolve.errorChange("invalid/zero length cipher text given")
            return ""
        else:
            return cleaned
    def setOut(self,text):
        self.outputBox.config(state="normal") #needs to be editable before editing
        self.outputBox.delete("1.0",tk.END)
        self.outputBox.insert("1.0",text)
        self.outputBox.config(state="disabled")

class buttonsBar:
    def __init__(self,tab):
        self.container = tk.Frame(tab,bg="grey60")
        self.container.grid(row=1,column=0,padx=10,pady=10)
        topRowStrings = ["Solve Rotors","Solve Rings","Solve Plugs","Full Solve"]
        topRowColours = ["white","white","white","lime"]
        topRowCommands = [self.rotorCrack,self.ringCrack,self.plugCrack,self.fullCrack]
        bottomRowStrings = ["Use IOC","Use BiGrams","Use TriGram","Use QuadGram"]
        bottomRowCommands = [self.setAnalyzerIOC,self.setAnalyzerBiGram,self.setAnalyzerTriGram,self.setAnalyzerQuadGram]
        for i in range(4): #arrays of colour, name and command used to prevent code repetition
            v = tk.Button(self.container,text=topRowStrings[i],bg=topRowColours[i],command=topRowCommands[i])
            v.grid(row=0,column=i,padx=10,pady=10)
        for i in range(4):
            v = tk.Button(self.container,text=bottomRowStrings[i],bg="blue",command=bottomRowCommands[i])
            v.grid(row=1,column=i,padx=10,pady=10)

    def rotorCrack(self,*args):
        global detailsbarsolve
        global solveMachine
        global bigstring
        detailsbarsolve.send() #send known settings
        solveMachine.changeCiphertext(bigstring.getText()) #get ciphertext
        solveMachine.findRotors() #crack
        detailsbarsolve.retrieve() #send new settings
        result = solveMachine.encryptWord(bigstring.getText()) #get predicted plaintext
        bigstring.setOut(result) #set predicted plaintext
    
    def ringCrack(self,*args):
        global detailsbarsolve
        global solveMachine
        global bigstring
        solveMachine.changeCiphertext(bigstring.getText())
        detailsbarsolve.send()
        solveMachine.findRings()
        detailsbarsolve.retrieve()
        result = solveMachine.encryptWord(bigstring.getText())
        bigstring.setOut(result)

    def plugCrack(self,*args):
        global detailsbarsolve
        global solveMachine
        global bigstring
        solveMachine.changeCiphertext(bigstring.getText())
        detailsbarsolve.send()
        solveMachine.findPlugs()
        detailsbarsolve.retrieve()
        result = solveMachine.encryptWord(bigstring.getText())
        bigstring.setOut(result)

    def fullCrack(self,*args):
        self.setAnalyzerIOC()
        self.rotorCrack()
        self.setAnalyzerBiGram()
        self.ringCrack()
        self.setAnalyzerQuadGram()
        self.plugCrack()

    def setAnalyzerIOC(self,*args):
        solveMachine.setAnalyzer(IOC)

    def setAnalyzerBiGram(self,*args):
        solveMachine.setAnalyzer(NGrams[0])

    def setAnalyzerTriGram(self,*args):
        solveMachine.setAnalyzer(NGrams[1])

    def setAnalyzerQuadGram(self,*args):
        solveMachine.setAnalyzer(NGrams[2])



root = tk.Tk()
root.title("Enigma Education Tool")
root.config(background="green")
notebook = ttk.Notebook(root)
notebook.pack(expand=True)
simtab = tk.Frame(notebook, bg="green")
solvetab = tk.Frame(notebook, bg = "green")
simtab.pack(fill='both', expand=True)
detailsbarsim = detailsBar(simtab,machine)
stringbox = stringBox(simtab)
vis = visualiser(simtab)
root.bind("<KeyPress>",vis.keyPress)
def clearFocus(event):
    global root
    root.focus_set()
root.bind("<Escape>",clearFocus)
solvetab.pack(fill='both', expand=True)
detailsbarsolve = detailsBar(solvetab,solveMachine,sim=False)
bigstring = bigStringBox(solvetab)
buttonbar = buttonsBar(solvetab)
notebook.add(simtab, text='Emulator')
notebook.add(solvetab, text='Solver')

root.mainloop()