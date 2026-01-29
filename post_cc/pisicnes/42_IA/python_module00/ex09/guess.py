from multiprocessing import Value
from random import randint

nb = randint(1, 99)


def main():
    print("This is an interactive guessing game!")
    print("You have to enter a number between 1 and 99 to find out the secret number.")
    print("Type 'exit' to end the game")
    print("Good luck!")
    line: str = ""
    count: int = 0
    try:
        while 1:
            print("What's your guess between 1 and 99?")
            line = input(">> ")
            try:
                value: int = int(line)
            except ValueError:
                print("Enter a valid number")
                continue
            count += 1
            match value:
                case value if value == nb:
                    print("Congratulations, you've got it!")
                    print(f"You won in {count} attempts!")
                    return
                case value if value < nb:
                    print("Too low!")
                case value if value > nb:
                    print("Too high!")
                case default:
                    print("default case")
    except EOFError:
        print("CTRLD PRESSED")


if __name__ == "__main__":
    main()
