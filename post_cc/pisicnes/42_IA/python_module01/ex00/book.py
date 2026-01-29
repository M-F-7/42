from datetime import datetime
from recipe import Recipe
from datetime import date



class Book:
    __name:str
    __last_update:datetime
    __creation_date:datetime
    __recipes_list:dict = {
        "start": [],
        "lunch": [],
        "dessert": []
    }

    def __init__(self, name:str, last_update:datetime)->None:
        self.__name = name
        self.__last_update = last_update
        self.__creation_date = date.today()


    def get_recipe_by_name(self, name)->Recipe:
        """Prints a recipe with the name \texttt{name} and returns the instance"""
        for recype_type in self.__recipes_list:
            for recipe in self.__recipes_list[recype_type]:
                if name == recipe.get_name():
                    print(recipe)
                    return recipe
        print(f"Recipe '{name}' not found")
        return None


    def get_recipes_by_types(self, recipe_type)->str:
        """Gets all recipes names for a given recipe_type """
        recipes = self.__recipes_list.get(recipe_type, [])
        if not recipes:
            raise AttributeError(f"Unkonw attributes {recipe_type}")
        return [recipe.get_name() for recipe in recipes]
    

    def add_recipe(self, recipe)->None:
        """Adds a recipe to the book and updates last_update"""
        if isinstance(recipe, Recipe) == False:
            raise ValueError("Bad type to add Recipe")
        
        recipe_type:str = recipe.get_recipe_type()
        if recipe_type not in self.__recipes_list:
            raise ValueError(f"Invalid recipe type: {recipe_type}")
        self.__recipes_list[recipe_type].append(recipe)
        self.__last_update = date.today()