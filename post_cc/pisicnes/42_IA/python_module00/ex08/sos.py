from errno import ESTALE
import sys

morse = {
    "0": "-----",
    "1": ".----",
    "2": "..---",
    "3": "...--",
    "4": "....-",
    "5": ".....",
    "6": "-....",
    "7": "--...",
    "8": "---..",
    "9": "----.",
    "a": ".-",
    "b": "-...",
    "c": "-.-.",
    "d": "-..",
    "e": ".",
    "f": "..-.",
    "g": "--.",
    "h": "....",
    "i": "..",
    "j": ".---",
    "k": "-.-",
    "l": ".-..",
    "m": "--",
    "n": "-.",
    "o": "---",
    "p": ".--.",
    "q": "--.-",
    "r": ".-.",
    "s": "...",
    "t": "-",
    "u": "..-",
    "v": "...-",
    "w": ".--",
    "x": "-..-",
    "y": "-.--",
    "z": "--..",
    " ": "/",
}


msg_err: str = "ERROR"


def main() -> None:
    try:
        args: list = sys.argv[1:]
        assert len(args) > 0
        arg: str = ""
        arg = " ".join(args)
        tab: list = []
        for char in arg:
            assert morse.get(char.lower()) != None
            tab.append(morse.get(char.lower()))
        print(" ".join(tab))

    except AssertionError:
        print(msg_err)


if __name__ == "__main__":
    main()
