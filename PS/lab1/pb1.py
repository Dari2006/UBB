from random import sample
from math import factorial
from itertools import permutations

cuvant = 'randomise'
permutations = list(permutations(cuvant))
#a)
#for perm in permutations:
   # print(perm)
#print(help(sample))
print("\n")

#b)
nrPermutari = factorial(len(cuvant))

print(nrPermutari)

#c)
permutareAleatoare = sample(cuvant, len(cuvant))

print(permutareAleatoare)