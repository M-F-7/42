kata = {
    "Python": "Guido van Rossum",
    "Ruby": "Yukihiro Matsumoto",
    "PHP": "Rasmus Lerdorf",
}


def main() -> None:
    print(*(f"{k} was created {v}" for k, v in kata.items()), sep="\n")


if __name__ == "__main__":
    main()
