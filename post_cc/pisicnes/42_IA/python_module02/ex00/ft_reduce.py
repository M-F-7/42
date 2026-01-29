from collections.abc import Iterable
from functools import reduce

def ft_reduce(function, iterable):
    """Apply function of two arguments cumulatively.
    Args:
    function_to_apply: a function taking an iterable.
    iterable: an iterable object (list, tuple, iterator).
    Return:
    A value, of same type of elements in the iterable parameter.
    None if the iterable can not be used by the function.
    """
    valid:bool = False
    if isinstance(iterable, list) == True:
        valid = True
        res:list = []
    if isinstance(iterable, tuple) == True:
        valid = True
        res:tuple = ()
    if isinstance(iterable, Iterable) == True:
        valid = True
        res:iter = ([])
# 
    if valid == False:
        raise TypeError("ERROR the type is not iterable")
    
    it = iter(iterable)
    value = next(it)
    #decale le pointeur it avance sur le deuxieme elt
    for nextelt in it:
        value = function(value, nextelt)
    return value

# # Example 3:
lst = ['H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd']
# print(print(reduce(lambda u, v: u + v, lst)))
print(reduce(lambda u, v: u + v, lst))
print((ft_reduce(lambda u, v: u + v, lst)))
# Output:
# "Hello world"