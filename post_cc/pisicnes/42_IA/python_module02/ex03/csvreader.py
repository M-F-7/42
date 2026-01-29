import re


class CsvReader():
    def __init__(self, filename=None, sep=',', header=True, skip_top=0, skip_bottom=0):
        self.__filename = filename
        self.__sep = sep
        self.__header = header
        self.__skip_top = skip_top
        self.__skip_bottom = skip_bottom
        self.__file = None


    def __enter__(self):
        try:
            self.__file = open(self.__filename, 'r')
        except OSError:
            print("Cannot open the file")
            return 
        self.__tab:list = []
        first_line = self.__file.readline()
        self.__file.seek(0) #put the pointeur back to the start
        nb_elt = first_line.count(self.__sep) + 1

        if self.__header == True:
            if self.__skip_top > 0:
                self.__skip_top -= 1
            else:
                row = re.split(r"[;,\n]", first_line.strip())
                row = [x.strip() for x in row if x]
                self.__tab.append(row)
        for line in self.__file:
            if line == first_line:
                continue
            if self.__skip_top > 0:
                self.__skip_top -= 1
                continue
            row = re.split(r"[;,\n]", line.strip())
            row = [x.strip() for x in row if x]
            if (len(row) != nb_elt):
                return None
            self.__tab.append(row)
    
        while self.__skip_bottom > 0:
            self.__tab.pop(len(self.__tab) - self.__skip_bottom)
            self.__skip_bottom -=1
        self.__file.seek(0)
        return self


    def __exit__(self, exc_type, exc_value, exc_traceback):
        self.__file.close()
    
    
    def getdata(self):
        """ Retrieves the data/records from skip_top to skip bottom.
        Returns:
        nested list (list(list, list, ...)) representing the data.
        """
        return self.__tab


    def getheader(self):
        if self.__header == False:
            return None
        header = self.__file.readline()
        row = re.split(r"[;,\n]", header.strip())
        row = [x.strip() for x in row if x]
        self.__file.seek(0)
        return row