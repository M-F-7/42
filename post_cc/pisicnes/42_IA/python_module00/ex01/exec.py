from contextlib import nullcontext
from curses.ascii import isalpha, isupper
import sys


def main() -> None:
    args: list = sys.argv
    args.remove(sys.argv[0])

    tab: str = " ".join(args)

    if (len(args) < 1):
        sys.stderr.write('Usage: One arg required' + "\n")
        return

    for i in tab[::-1]:
        if (i.islower()):
            sys.stdout.write(i.upper())
        elif (i.isupper()):
            sys.stdout.write(i.lower())
        else:
            sys.stdout.write(i)
    sys.stdout.write("\n")


if (__name__ == "__main__"):
    main()
