from curses.ascii import isdigit
import random

def generator(text, sep=" ", option=None):
    if isinstance(text, str) == False:
        yield "ERROR"
        return
    if option != "shuffle" and option != "unique" and option != "ordered":
        if option != None:
            yield "ERROR"
            return 
    split:list = text.split(sep)
    tab:list = []
    if option == "shuffle":
        while split:
            word = random.randint(0, len(split) - 1)
            tab.append(split.pop(word))
    elif option == "unique":
        for word in split:
            if word in tab:
                continue
            tab.append(word)
    elif option == "ordered":
        tab = sorted(split)
    else:
        tab = split

    for word in tab:
        yield word


def main():
    try:
        text = "SAUT A TOI JEUNE ABERANT PIRATE"
        for word in generator(text, option="unique"):
            print(word)
    except (ValueError,TypeError) as e:
        print(e)

if __name__ == "__main__":
    main()