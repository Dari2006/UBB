from random import sample
from math import perm, comb
from itertools import permutations, combinations

#print(help(permutations))

def aranjamente(cuvant, k, NrTotal = False, aleator = False):

    if(NrTotal):

        return perm(len(cuvant), k)
    elif aleator:
        return sample(cuvant, k)
    else:
        return list(permutations(cuvant, k))

res = aranjamente('word', 2, aleator=True)
if(isinstance(res, list)):
    for a in res:
        print(a)

if(isinstance(res, int)):
    print(res)


def combinari(cuvant, k, NrTotal = False, aleator = False):

    if(NrTotal):

        return perm(len(cuvant), k)
    elif aleator:
        return sample(cuvant, k)
    else:
        return list(combinations(cuvant, k))


print("--------")

res = combinari('word', 2, NrTotal=True)

if(isinstance(res, list)):
    for a in res:
        print(a)

if(isinstance(res, int)):
    print(res)