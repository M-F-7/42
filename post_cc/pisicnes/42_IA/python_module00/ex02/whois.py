import sys


def main() -> None:
    args: list = sys.argv[1:]
    if not args:
        print("Usage: One arg required", file=sys.stderr)
        return
    try:
        assert len(args) == 1, "more than one argument is provided"
        assert isinstance(int(args[0]), int)  # except ValueError

        arg: int = int(args[0])
        if arg == 0:
            print("I'm Zero.")
        elif arg % 2 == 0:
            print("I'm Even.")
        else:
            print("I'm Odd.")

    except AssertionError as e:
        print(f"AssertionError: {e}", file=sys.stderr)
    except ValueError:
        print("AssertionError: argument is not an integer", file=sys.stderr)


if __name__ == "__main__":
    main()
