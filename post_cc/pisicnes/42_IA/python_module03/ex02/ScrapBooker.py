import array
import numpy as np

class ScrapBooker:
    def __init__(self):
        pass

    def crop(self, array:np.ndarray, dim, position=(0,0)):
        """
        Crops the image as a rectangle via dim arguments (being the new height
        and width of the image) from the coordinates given by position arguments.
        Args:
        -----
        array: numpy.ndarray
        dim: tuple of 2 integers.
        position: tuple of 2 integers.
        Returns:
        -------
        new_arr: the cropped numpy.ndarray.
        None: (if the combination of parameters is not possible).
        Raises:
        ------
        This function should not raise any Exception.
        """
        shape = array.shape

        if dim[0] + position[0] > shape[0] or dim[1] + position[1] > shape[1]:
            return None
        start_cols, end_cols = (position[0], dim[0]) if position[0] < dim[0] else (dim[0], position[0])
        start_rows, end_rows = (position[1], dim[1]) if position[1] < dim[1] else (dim[1], position[1]) 
        print(f"START COL: {start_cols}\nEND_COL: {end_cols}\nSTART_ROWS: {start_rows}\nEND_ROWS: {end_rows}")
        new_arr = array[start_cols:end_cols + 1, start_rows:end_rows] #+1 PAS NORMAL OU NORMAL SI ON FAIS LA MEME POUR LES ROWS
        
        return new_arr
        
    def thin(self, array:np.ndarray, n, axis):
        """
        Deletes every n-th line pixels along the specified axis (0: vertical, 1: horizontal)
        Args:
        -----
        array: numpy.ndarray.
        n: non null positive integer lower than the number of row/column of the array
        (depending of axis value).
        axis: positive non null integer.
        Returns:
        -------
        new_arr: thined numpy.ndarray.
        None: (if the combination of parameters is not possible).
        Raises:
        ------
        This function should not raise any Exception.
        """
        shape = array.shape

        if axis == 0 and n > shape[0]:
             return None
        if n > shape[1] and axis:
                return None
        indices: np.ndarray[np.int_] = np.arange(shape[axis]) #recup toute la colonne cible par axis
        mask: np.ndarray[np.bool_] = (indices + 1) % n != 0 #stock toutes les valeurs qui ontt le res de l op != 0

        new_arr: np.ndarray = array[mask, :] if axis == 0 else array[:, mask]

        return new_arr
    def juxtapose(self, array, n, axis):
        """
        Juxtaposes n copies of the image along the specified axis.
        Args:
        -----
        array: numpy.ndarray.
        n: positive non null integer.
        axis: integer of value 0 or 1.
        Returns:
        -------
        new_arr: juxtaposed numpy.ndarray.
        None: (if the combination of parameters is not possible).
        Raises:
        -------
        This function should not raise any Exception.
        """
        if n < 0:
             return None
        if axis != 0 and axis != 1:
             return None
        new_array = array
        for i in range(n):
            new_array = np.concatenate((new_array, array), axis=axis)
        return new_array
    


    def mosaic(self, array, dim):
        """
        Makes a grid with multiple copies of the array. The dim argument specifies
        the number of repetition along each dimensions.
        Args:
        -----
        array: numpy.ndarray.
        dim: tuple of 2 integers.
        Return:
        -------
        new_arr: mosaic numpy.ndarray.
        None (combinaison of parameters not compatible).
        Raises:
        -------
        This function should not raise any Exception.
        """
        new_array: np.ndarray = array
        for i in range(2):  # 0=vertical, 1=horizontal
            new_array = self.juxtapose(new_array, dim[i], i)
        return new_array
         