from collections import defaultdict
from itertools import product
from random import randint

from matplotlib import pyplot as plt
from matplotlib.pyplot import plot, grid, xticks, yticks, title, show

triplete = list(product(range(1,7), repeat=3))

dict = {triplet: 0 for triplet in range(3, 19)}

for i in range(100000):
    aruncare = (randint(1,6), randint(1,6), randint(1,6))
    dict[sum(aruncare)] += 1

plt.plot(dict.keys(), dict.values(),'o')

plt.savefig("dict.png")

print(dict.items())

sum_teoretice = defaultdict(int)

for triplet in triplete:
    sum_teoretice[sum(triplet)] += 1
print(sum_teoretice)

sume = sorted(sum_teoretice.keys())
frecvente_teoretice = [sum_teoretice[s] for s in sume]

plt.bar(sume, frecvente_teoretice)
plt.savefig("sume.png")

