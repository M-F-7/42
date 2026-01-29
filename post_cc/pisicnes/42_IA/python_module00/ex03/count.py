import sys
import string


def details(arg: str) -> None:
    """Program:
    Summary:
        This program analyze the content of a string
        It counts the number of upper characters, lower characters,punctuation and spaces
    Arguments:
        - string : the string to analyze
    Return Values:
        - int : the number of upper-case char
        - int : the number of lower-case char
        - int : the number of punctuation and spaces char
    """

    upper_count = sum(1 for char in arg if char.isupper())
    lower_count = sum(1 for char in arg if char.islower())
    punctuation_count = sum(1 for char in arg if char in string.punctuation)
    space_count = sum(1 for char in arg if char.isspace())

    printable_length = len(arg)

    print(f"The text contains {printable_length} printable character(s):")

    print(f"Upper-case characters: {upper_count}")
    print(f"Lower-case characters: {lower_count}")
    print(f"Punctuation characters: {punctuation_count}")
    print(f"Space characters: {space_count}")


def text_analyzer() -> None:

    try:
        if len(sys.argv[1:]) != 1:
            print("What is the text to analyze?")
            arg = input(">> ")
        else:
            arg: str = sys.argv[1]
        assert arg, "Empty Arguments"
        assert isinstance(arg, str), "argument is not a string"
        if arg.isdigit():
            raise ValueError("argument is not a string")
        details(arg).__doc__

    except AssertionError as e:
        print(f"AssertionError: {e}", file=sys.stderr)
    except ValueError as e:
        print(f"AssertionError: {e}", file=sys.stderr)
    except TypeError as e:
        print(e, file=sys.stderr)


def main() -> None:
    if len(sys.argv[1:]) > 1:
        print("Too many arguments provided", file=sys.stderr)
        return
    text_analyzer()


if __name__ == "__main__":
    main()
