class GotCharacter:
    _first_name:str
    _is_alive:bool

    def __init__(self, first_name:str):
        self._first_name = first_name
        self._is_alive = True

    def __str__(self)->str:
        txt:str = ""

        txt += f"{self._first_name} is alive ? {self._is_alive}"
        return txt

class Stark(GotCharacter):
    """\nA class representing the Stark family.\n"""

    __family_name:str
    __house_words:str


    def __init__(self, first_name=None):
        super().__init__(first_name)
        self.__family_name = "Stark"
        self.__house_words = "Winter is Coming"

    
    def __str__(self)->str:
        txt:str = ""

        txt += f"{self._first_name} is alive ? {self._is_alive}\n"
        txt += f"From {self.__family_name} '{self.__house_words}'"
        return txt
    

    def print_house_words(self)->None:
        print(self.__house_words)

    def die(self)->None:
        self._is_alive = False

    def revive(self)->None:
        self._is_alive = True

    def attack(self, Parent:GotCharacter)->None:
        if not self._is_alive:
            raise AttributeError("The child cannot attack if is dead Idiot !!")
        print(f"{self._first_name} is attacking {Parent._first_name}")

def main()->None:
    parent_char = GotCharacter("parent_char")
    print(parent_char)

    child_char = Stark("child_char")
    print(child_char.__doc__)
    child_char.die()
    print(child_char)
    try:
        child_char.revive()
        child_char.attack(parent_char)
    except AttributeError as e:
        print(e)


if __name__ == "__main__":
    main()