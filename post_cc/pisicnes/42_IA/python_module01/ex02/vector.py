class Vector:
    # __values:list[list[float]]
    # __shape:tuple[int, int]

    def __init__(self, values):
        if isinstance(values, tuple):
            start, stop = values
            if start >= stop:
                raise ValueError("start must be less than stop")
            self.__values = [[float(i)] for i in range(start, stop)]
        elif (isinstance(values, int)):
            self.__values = ([[float(i)] for i in range(values)])
        elif isinstance(values, list):
            self.__values = values
        else:
            raise TypeError("Cannot initializer with this type")
        self.__shape = len(self.__values), len(self.__values[0])

    def __str__(self)->str:
        txt:str = "Vector: "
        txt += ', '.join(str(x) for x in self.__values)
        return txt
    
    def __repr__(self)->str:
        return f"Vector(values={self.__values}, shape={self.__shape})"


    def __add__(self, other):
        if not isinstance(other, Vector):
            raise TypeError("Can only add Vector to Vector")

        if self.__shape != other.__shape:
            raise ValueError("Vectors must have the same shape")
        

        tab:list[list[float]] = []
        for y, y2 in zip(self.__values, other.__values):
            new_row:list[float] = [x + x2 for x, x2 in zip(y, y2)]
            tab.append(new_row)
        return Vector(tab)
    
    def __radd__(self, other):
        return self.__add__(other)

    def __sub__(self, other):
        if not isinstance(other, Vector):
            raise TypeError("Can only add Vector to Vector")

        if self.__shape != other.__shape:
            raise ValueError("Vectors must have the same shape")
        

        tab:list[list[float]] = []
        for y, y2 in zip(self.__values, other.__values):
            new_row:list[float] = [x - x2 for x, x2 in zip(y, y2)]
            tab.append(new_row)
        return Vector(tab)
    

    def __rsub__(self, other):
        return self.__sub__(other)

    def __mul__(self, other):
        raise NotImplementedError("Mul without an int is not implemented")
    
    def __mul__( self, nb:int ):
        tab:list[list[float]] = []
        for y in self.__values:
            new_row:list[float] = [x * nb for x in y]
            tab.append(new_row)
        return Vector(tab)

    def __rmul__(self, nb:int):
        return self.mul(nb)
    
    def __truediv__(self, nb:float):

        if nb == 0:
            raise ZeroDivisionError("float division by zero")
        tab:list[list[float]] = []
        for y in self.__values:
            new_row:list[float] = [x / nb for x in y]
            tab.append(new_row)
        return Vector(tab)

    def __rtruediv__(self, other):
        raise NotImplementedError("Division of a scalar by a Vector is not defined here.")
    def __rtruediv__(self, nb:float):
        raise ArithmeticError("Division of a scalar by a Vector is not defined here.")
    


    def dot(self, other)->int:
        if len(self.__values) != len(other.__values):
            raise ValueError("Vectors must have the same dimension")
        scalar_dot:int = 0
        for y, y2 in zip(self.__values, other.__values):
            for x, x2 in zip(y, y2):
                scalar_dot += x * x2
        return scalar_dot
    

    def T(self):
        transposed = list(map(list, zip(*self.__values)))
        return Vector(transposed)

    def get_shape(self):
        return self.__shape
    
    def get_values(self):
        return self.__values
    