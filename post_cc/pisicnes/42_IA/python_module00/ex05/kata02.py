import sys

kata = (2019, 9, 25, 3, 30)


def main() -> None:
    days: str = f"{kata[1]:02}"
    months: str = f"{kata[2]:02}"
    year: str = f"{kata[0]:04}"
    hour: str = f"{kata[3]:02}"
    mins: str = f"{kata[4]:02}"
    print(f"{days}/{months}/{year} {hour}:{mins}")


if __name__ == "__main__":
    main()
