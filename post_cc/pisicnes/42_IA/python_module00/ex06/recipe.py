cookbook = {
    "sandwich": {
        "ingredients": ["ham", "bread", "cheese", "tomatoes"],
        "meal": "lunch",
        "prep_time": 10,
    },
    "cake": {
        "ingredients": ["flour", "sugar", "eggs"],
        "meal": "dessert",
        "prep_time": 60,
    },
    "salad": {
        "ingredients": ["avocado", "arugula", "tomatoes", "spinach"],
        "meal": "lunch",
        "prep_time": 15,
    },
}


def print_recipe_names():
    """Print all recipe names in the cookbook."""
    if not cookbook:
        print("The cookbook is empty.")
        return
    print("Available recipes:")
    for name in cookbook:
        print(f"- {name}")


def print_recipe_details(name):
    """Print the details of a specific recipe."""
    recipe = cookbook.get(name.lower())
    if recipe:
        print(f"\nRecipe for {name}:")
        print(f"Ingredients list: {recipe['ingredients']}")
        print(f"To be eaten for {recipe['meal']}.")
        print(f"Takes {recipe['prep_time']} minutes of cooking.\n")
    else:
        print(f"Sorry, recipe '{name}' does not exist.\n")


def delete_recipe(name):
    """Delete a recipe from the cookbook."""
    if name.lower() in cookbook:
        del cookbook[name.lower()]
        print(f"Recipe '{name}' deleted.\n")
    else:
        print(f"Recipe '{name}' not found.\n")


def add_recipe():
    """Add a new recipe from user input."""
    name = input("Enter a name:\n>> ").strip().lower()
    if not name:
        print("Recipe name cannot be empty.")
        return
    if name in cookbook:
        print("Recipe already exists. Please choose another name.")
        return

    ingredients = []
    print("Enter ingredients (press ENTER when done):")
    while True:
        ingredient = input(">> ").strip()
        if ingredient == "":
            break
        ingredients.append(ingredient)
    if not ingredients:
        print("A recipe must have at least one ingredient.")
        return

    meal = input("Enter a meal type:\n>> ").strip()
    if not meal:
        print("Meal type cannot be empty.")
        return

    try:
        prep_time = int(input("Enter a preparation time (in minutes):\n>> ").strip())
        if prep_time < 0:
            raise ValueError
    except ValueError:
        print("Preparation time must be a non-negative integer.")
        return

    cookbook[name] = {"ingredients": ingredients, "meal": meal, "prep_time": prep_time}
    print(f"Recipe '{name}' added successfully!\n")


def print_options():
    print("List of available options:")
    print("\t1: Add a recipe")
    print("\t2: Delete a recipe")
    print("\t3: Print a recipe")
    print("\t4: Print the cookbook")
    print("\t5: Quit")


def main():
    print("Welcome to the Python Cookbook !")
    try:
        while True:
            print_options()
            choice = input("Please select an option:\n>> ").strip()
            match choice:
                case "1":
                    add_recipe()
                case "2":
                    name = input("Please enter a recipe name to delete:\n>> ").strip()
                    delete_recipe(name)
                case "3":
                    name = input(
                        "Please enter a recipe name to get its details:\n>> "
                    ).strip()
                    print_recipe_details(name)
                case "4":
                    print_recipe_names()
                case "5":
                    print("Cookbook closed. Goodbye !")
                    break
                case default:
                    print("Sorry, this option does not exist.\n")
    except EOFError:
        print("CTRLD PRESSED")
    except KeyError:
        print("UNKNOWN KEY")


if __name__ == "__main__":
    main()
