import numpy as np
from typing import Tuple
from math import sqrt


class TinyStatistician:

    def __init__(self):
        pass

    def mean(self, x)->float:
        if isinstance(x, np.ndarray):
            if x.size == 0:
                return None
        elif not x: #check empty
            return None
        res:float = 0

        if isinstance(x, list):
            for i in x:
                res += i / len(x)
        else:
            for i in x:
                res += i / x.size
        # res = sum(x) / len(x)
        #res = sum(x) / x.size()
        return res
    

    def median(self, x)->float:
        if isinstance(x, np.ndarray):
            if x.size == 0:
                return None
        elif not x: #check empty
            return None
        x = np.sort(x)
        if isinstance(x, list):
            if len(x) % 2 == 0:
                return float((x[len(x) // 2 - 1] + x[len(x) // 2]) / 2)
            return float(x[len(x)  // 2])
        if x.size % 2 == 0:
            return float((x[x.size // 2 - 1] + x[x.size // 2]) / 2)
        return float(x[x.size  // 2])
    

                    
    def quartiles(self, x)->Tuple[float, float]:
        if isinstance(x, np.ndarray):
            if x.size == 0:
                return None
        elif not x: #check empty
            return None
        x = np.sort(x)
        # median:float = self.median(x)
        try:
            if isinstance(x, list):
                length = len(x)
            else:
                length = x.size
        except ValueError as e:
            print(e)
            return None
        if length % 2 == 0:
            q1:float = self.median(x[:length // 2])
            q3:float = self.median(x[length // 2:])
        else:
            q1:float = self.median(x[:length // 2])
            q3:float = self.median(x[length // 2 + 1:])

        return (q1, q3)
    

    def var(self, x)->float:
        if isinstance(x, np.ndarray):
            if not x.all():
                return None
        elif not x: #check empty
            return None
        tab:list = []
        res:float = 0
        mean:float = self.mean(x)
        for elt in x:
            tab.append((elt - mean)**2)
        res = sum(tab) / len(tab)
        return res
    

    def std(self, x):
        if isinstance(x, np.ndarray):
            if not x.all():
                return None
        elif not x: #check empty
            return None
        return sqrt(self.var(x))
        

    


def main():
    foo = TinyStatistician()
    # x:list = [0, 5, 10, 15, 20, 25, 30, 35, 40]
    # y = array('i', [0, 5, 10, 15, 20, 25, 30, 35, 40])
    x:list = [7, 9, 16, 36, 39, 45, 45, 46, 48, 51, 85]
    y = np.ndarray(shape=len(x), buffer=np.array(x), dtype=int)
    try:
        print(f"x mean: {foo.mean(x)}")
        print(f"x median: {foo.median(x)}")
        print(f"x quartiles: {foo.quartiles(x)}")
        print(f"x var: {foo.var(x)}")
        print(f"x var: {foo.std(x)}")

        print()

        print(f"y mean: {foo.mean(y)}")
        print(f"y median: {foo.median(y)}")
        print(f"y quartiles: {foo.quartiles(y)}")
        print(f"y var: {foo.var(y)}")
        print(f"y var: {foo.std(y)}")
    except TypeError as e:
        print(e)

if __name__ == "__main__":
    main()