import matplotlib.pyplot as plt
import numpy as np

class ColorFilter:
    def invert(self, array:np.ndarray):
        """
        Inverts the color of the image received as a numpy array.
        Args:
        -----
        array: numpy.ndarray corresponding to the image.
        Return:
        -------
        array: numpy.ndarray corresponding to the transformed image.
        None: otherwise.
        Raises:
        -------
        This function should not raise any Exception.
        """
        return 1.0 - array.copy()

        #Authorized functions: .copy
        #Authorized operators: +,-,=



    def to_blue(self, array):
        """
        Applies a blue filter to the image received as a numpy array.
        Args:
        -----
        array: numpy.ndarray corresponding to the image.
        Return:
        -------
        array: numpy.ndarray corresponding to the transformed image.
        None: otherwise.
        Raises:
        -------
        This function should not raise any Exception.
        """
        new = np.zeros(shape=array.shape, dtype=array.dtype)
        for i in range(array.shape[2]):
            if i == 2:
                new[:, :, i] = array[:, :, i] * 1.0 
            else:
                new[:, :, i] = array[:, :, i] * 0.2
        return new
        #Authorized functions: .copy, .zeros,.shape,.dstack
        #Authorized operators: =


    def to_green(self, array):
        """
        Applies a green filter to the image received as a numpy array.
        Args:
        -----
        array: numpy.ndarray corresponding to the image.
        Return:
        -------
        array: numpy.ndarray corresponding to the transformed image.
        None: otherwise.
        Raises:
        -------
        This function should not raise any Exception.
        """
        #Authorized functions: .copy
        #Authorized operators: *, =
        new = np.copy(array)
        for i in range(array.shape[2]):
            if i == 1:
                new[:, :, i] = array[:, :, i] * 1.0
            else:
                new[:, :, i] = array[:, :, i] * 0.2
        return new

    def to_red(self, array):
        """
        Applies a red filter to the image received as a numpy array.
        Args:
        -----
        array: numpy.ndarray corresponding to the image.
        Return:
        -------
        array: numpy.ndarray corresponding to the transformed image.
        None: otherwise.
        Raises:
        -------
        This function should not raise any Exception.
        """
        #Authorized functions: .copy, .to_green,.to_blue
        #Authorized operators: -,+, =
        new = np.copy(array)
        for i in range(array.shape[2]):
            if i == 0:
                new[:, :, i] = array[:, :, i] * 1.0
            else:
                new[:, :, i] = array[:, :, i] * 0.2
        return new


    def to_celluloid(self, array):
        """
        Applies a celluloid filter to the image received as a numpy array.
        Celluloid filter must display at least four thresholds of shades.
        Be careful! You are not asked to apply black contour on the object,
        you only have to work on the shades of your images.
        Remarks:
        celluloid filter is also known as cel-shading or toon-shading.
        Args:
        -----
        array: numpy.ndarray corresponding to the image.
        Return:
        -------
        array: numpy.ndarray corresponding to the transformed image.
        None: otherwise.
        Raises:
        -------
        This function should not raise any Exception.
        """
        #Authorized functions: .copy, .arange,.linspace, .min, .max
        #Authorized operators: =, <=, >, & (or and)
        new = np.copy(array)
        states = np.linspace(0, 1, 5)# -> [0, 0.25, 0.5, 0.75, 1]
        shades = np.linspace(0, 1, 4)

        for i in range(3):
            r_g_b = new[:, :, i]
            for j in range(len(states) - 1):
                mask = (r_g_b >= states[j]) & (r_g_b < states[j + 1])
                r_g_b[mask] = shades[j]
            new[:, :, i] = r_g_b
                    
        return new


    def to_grayscale(self, array, filter, **kwargs):
        """
        Applies a grayscale filter to the image received as a numpy array.
        For filter = 'mean'/'m': performs the mean of RBG channels.
        For filter = 'weight'/'w': performs a weighted mean of RBG channels.
        Args:
        -----
        array: numpy.ndarray corresponding to the image.
        filter: string with accepted values in ['m','mean','w','weight']
        weights: [kwargs] 3 floats where the sum equals to 1,
        corresponding to the weights of each RBG channels.
        Expecting keys: 'r_weight', 'g_weight' and 'b_weight'.
        -------
        array: numpy.ndarray corresponding to the transformed image.
        None: otherwise.
        Raises:
        -------
        This function should not raise any Exception.
        """
        #Authorized functions: .sum,.shape,.reshape,.broadcast_to,.as_type
        #Authorized operators: *,/, =
        img = array.astype(np.float32)

        if filter.lower() in ('mean', 'm'):
            grey = img.sum(axis=2) / 3

        elif filter.lower() in ('weight', 'w'):
            r = kwargs.get('r', 0.299)
            g = kwargs.get('g', 0.587)
            b = kwargs.get('b', 0.114)
            grey = img[:, :, 0] * r + img[:, :, 1] * g + img[:, :, 2] * b

        grey_rgb = np.broadcast_to(grey[:, :, None], img.shape)

        return grey_rgb