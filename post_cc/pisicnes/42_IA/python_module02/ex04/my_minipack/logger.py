import time
from random import randint
import os

from hamcrest import contains_exactly

with open("machine.log", "w") as f:
    pass

def log(funct):
    def wrapper(*args, **kwargs):
        path = "./machine.log"
        flags = os.O_RDWR | os.O_CREAT | os.O_APPEND
        mode = 0o666
        file:int = os.open(path=path, flags=flags, mode=mode)

        start = time.perf_counter()
        result = funct(*args, **kwargs)
        end = time.perf_counter()
        duration_ms = end - start


        key:str = "USER"
        fname = funct.__name__
        if fname == "make_coffee" or fname == "add_water":
            msg = f"({os.getenv(key)}) Running: {fname:<19}[ exec-time = {duration_ms:.3f} s ]"
        else:
            duration_ms *= 1000
            msg = f"({os.getenv(key)}) Running: {fname:<19}[ exec-time = {duration_ms:.3f} ms ]"
        content = str.encode(msg + "\n")
        os.write(file, content)
        os.close(file)
        return result
    return wrapper


class CoffeeMachine():
    water_level = 100

    @log
    def start_machine(self):
        if self.water_level > 20:
            return True
        else:
            print("Please add water!")
            return False
        
    @log
    def boil_water(self):
        return "boiling..."
    
    @log
    def make_coffee(self):
        if self.start_machine():
            for _ in range(20):
                time.sleep(0.1)
                self.water_level -= 1
            print(self.boil_water())
            print("Coffee is ready!")

    @log
    def add_water(self, water_level):
        time.sleep(randint(1, 5))
        self.water_level += water_level
        print("Blub blub blub...")


if __name__ == "__main__":
    machine = CoffeeMachine()
    for i in range(0, 5):
        machine.make_coffee()
    machine.make_coffee()
    machine.add_water(70)