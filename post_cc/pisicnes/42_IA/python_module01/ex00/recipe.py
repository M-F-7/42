from multiprocessing import Value
import re


class Recipe:
    __name:str
    __cooking_lvl:int
    __cooking_time:int
    __ingredients:list
    __description:str
    __recipe_type:str

    def __init__(self, name:str, cooking_lvl:int, cooking_time:int, ingredients:list, description:str, recipe_type:str)->None:
        self.__name = name
        if not name:
            raise ValueError("Name cannot be empty")
        
        if (cooking_lvl < 1 or cooking_lvl > 5):
            raise ValueError("Cooking_lvl has a bad value")
        self.__cooking_lvl = cooking_lvl

        if (cooking_time < 0):
            raise ValueError("Cookingtime cannot be negative")
        self.__cooking_time = cooking_time

        if not ingredients or ingredients[0] == "":
            raise ValueError("Ingredients cannot be empty")
        self.__ingredients = ingredients

        self.__description = description

        if (recipe_type != "lunch" and recipe_type != "start" and recipe_type != "dessert"):
            raise ValueError("Recipetype has a bad value")
        self.__recipe_type = recipe_type

    def __str__(self)->str:
        txt = f"Recipe: {self.__name}\n"
        txt += f"\tCooking level: {self.__cooking_lvl}/5\n"
        txt += f"\tCooking time: {self.__cooking_time} mins\n"
        txt += f"\tIngredients: {', '.join(self.__ingredients)}\n"
        txt += f"\tDescription: {self.__description}\n"
        txt += f"\tType: {self.__recipe_type}\n"
        return txt
    
    def get_name(self)->str:
        return self.__name
    def get_recipe_type(self)->str:
        return self.__recipe_type