kata = "The right format"


def main() -> None:
    # print(f"{'-' * (42 - len(kata))}{kata}", end="")
    print(f"{kata:->42}", end="")


if __name__ == "__main__":
    main()
