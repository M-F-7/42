from collections.abc import Iterable

def ft_filter(function_to_apply, iterable):
    """Filter the result of function apply to all elements of the iterable.
    Args:
    function_to_apply: a function taking an iterable.
    iterable: an iterable object (list, tuple, iterator).
    Return:
    An iterable.
    None if the iterable can not be used by the function.
    """
    valid:bool = False
    if isinstance(iterable, list) == True:
        valid = True
    if isinstance(iterable, tuple) == True:
        valid = True
    if isinstance(iterable, Iterable) == True:
        valid = True

    if valid == False:
        raise TypeError("ERROR the type is not iterable")
    
    for elt in iterable:
        if function_to_apply(elt) == True:
            yield elt
    

# Example 2:
x = [1, 2, 3, 4, 5]
# test:int = 0
print(ft_filter(lambda dum: not (dum % 2), x))
# Output:
# <generator object ft_filter at 0x7f709c777d00> # The adress will be different
print(list(ft_filter(lambda dum: not (dum % 2), x)))

# Output:
[2, 4]