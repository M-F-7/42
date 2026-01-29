from datetime import date
from book import Book
from recipe import Recipe


def main()->None:
    try:
        kebab = Recipe("Kebab", 1, 5, ["salad", "tomato", "oignon"], "kebabed", "lunch")
        tacos = Recipe("Tacos", 2, 10, ["Fries", "Nuggets", "Cordon bleu"], "Tacosed", "lunch")
        raclette = Recipe("Raclette", 3, 30, ["Potatoes", "cheddar", "Charcuterie"], "Racletted", "dessert")
        tiramisu = Recipe("Tiramisuiiiiiiiiiiiiii", 5, 90, ["Chocolat", "Cream", "idk"], "SUIIIIIIIIIIIII", "dessert")
        recipes = Book("recipe", date.today())


        recipes.add_recipe(kebab)
        recipes.add_recipe(tacos)
        recipes.get_recipe_by_name("Kebab")
        print(recipes.get_recipes_by_types("lunch"))

        recipes.add_recipe(raclette)
        print(recipes.get_recipes_by_types("dessert"))
        
        recipes.add_recipe(tiramisu)
        recipes.get_recipe_by_name(tiramisu.get_name())

        recipes.get_recipe_by_name("Unknown")
        recipes.get_recipe_by_types("Unknown")
    except ValueError as e:
        print(f"ValueError: {e}")
    except AttributeError as e:
        print(f"AttributeError: {e}")


if __name__ == "__main__":
    main()