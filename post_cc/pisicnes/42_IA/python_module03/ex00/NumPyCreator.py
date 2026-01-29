from typing import Iterable
import numpy as np
import struct 


class NumPyCreator:
    
    def __init__(self):
        pass


    def from_list(self, lst, dtype=None):
        # lst = [item for sublist in lst for item in sublist]
        # buffer = struct.pack('i'*len(lst), *lst)
        # BAS NIVEAU # return np.ndarray(shape=(len(lst),), buffer=buffer, dtype=dtype)
        return np.array(lst, dtype=object) if isinstance(lst, list) else None

    def from_tuple(self, tpl, dtype=None):
        return np.array(tpl, dtype=object) if isinstance(tpl, tuple) else None

    def from_iterable(self, itr, dtype=None):
        return np.array(itr, dtype=object) if isinstance(itr, Iterable) else None

    def from_shape(self, shape, value=0, dtype=None):
        return np.array([[value for _ in range(shape[1])]for _ in range(shape[0])], dtype=object)

    def random(self, shape, dtype=None):
        return np.array([[np.random.rand() for _ in range(shape[1])]for _ in range(shape[0])], dtype=object)

    def identity(self, n, dtype=None):
        return np.array([[1 if a == b else 0 for a in range(n)]for b in range(n)], dtype=object)

