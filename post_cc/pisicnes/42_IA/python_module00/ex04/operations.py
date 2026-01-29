import sys


def main() -> None:
    args = sys.argv[1:]

    try:
        assert len(args) == 2, "Usage: python operations.py <number1><number2>"
        if args[0].isdigit() == False or args[1].isdigit() == False:
            raise ValueError("Non digit arguments")
        summ: int = int(args[0]) + int(args[1])
        print("Sum :", summ)
        diff: int = int(args[0]) - int(args[1])
        print("Difference: ", diff)
        mult: int = int(args[0]) * int(args[1])
        print("Product: ", mult)
        if not int(args[1]):
            print("Quotient: ERROR (division by zero)")
        else:
            quot: int = int(args[0]) / int(args[1])
            print("Quotient: ", quot)

        if not int(args[1]):
            print("Remainder: ERROR (modulo by zero)")
        else:
            rest: int = int(args[0]) % int(args[1])
            print("Remainder: ", rest)

    except AssertionError as e:
        print(e, file=sys.stderr)
    except ValueError as e:
        print(f"AssertionError: {e}", file=sys.stderr)


if __name__ == "__main__":
    main()
