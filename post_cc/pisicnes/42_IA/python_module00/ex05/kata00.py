import sys

kata = (19, 42, 21)


def main() -> None:
    sys.stdout.write("The 3 numbers are: ")
    print(", ".join(str(x) for x in kata))


if __name__ == "__main__":
    main()
