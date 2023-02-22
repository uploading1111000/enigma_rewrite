import random
print(random.sample(range(0,8),3))
print([random.randint(1,26) for x in range(4)])
print([random.randint(1,26) for x in range(4)])

order = [chr(x) for x in range(65,91)]
random.shuffle(order)
for x in range(10):
    print(order[2*x:2*x+2])
