import numpy as np
from ScrapBooker import ScrapBooker
spb = ScrapBooker()
arr1 = np.arange(0,25).reshape(5,5)
print(arr1)
print(spb.crop(arr1, (3,1),(1,0))) # PROBLEME DEPENDS SI ON EXCLUT OU PAS LE DIM[n] car la resultat mauvais
#Output :
# array([[ 5],
# [10],
# [15]])
arr2 = np.array("A B C D E F G H I".split() * 6).reshape(-1,9)
print(arr2)
print(spb.thin(arr2,3,1)) 
#AUCUN SENS LE RESULTAT
#Output :
# array([[’A’, ’B’, ’D’, ’E’, ’G’, ’H’, ’J’, ’K’],
# [’A’, ’B’, ’D’, ’E’, ’G’, ’H’, ’J’, ’K’],
# [’A’, ’B’, ’D’, ’E’, ’G’, ’H’, ’J’, ’K’],
# [’A’, ’B’, ’D’, ’E’, ’G’, ’H’, ’J’, ’K’],
# [’A’, ’B’, ’D’, ’E’, ’G’, ’H’, ’J’, ’K’],
# [’A’, ’B’, ’D’, ’E’, ’G’, ’H’, ’J’, ’K’]], dtype=’<U1’)
arr3 = np.array([[1, 2, 3],[1, 2, 3],[1, 2, 3]])
print(spb.juxtapose(arr3, 3, 0))
#Output :
# array([[1, 2, 3, 1, 2, 3, 1, 2, 3],
# [1, 2, 3, 1, 2, 3, 1, 2, 3],
# [1, 2, 3, 1, 2, 3, 1, 2, 3]])
# 11

arr4 = np.array([[1, 2, 3],[1, 2, 3],[1, 2, 3]])
print(spb.mosaic(arr4, (2, 2)))
