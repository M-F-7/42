kata = (0, 4, 132.42222, 10000, 12345.67)


def main() -> None:
    module: str = "module_" + f"{kata[0]:0>2}"
    ex: str = "ex_" + f"{kata[1]:0>2}"
    first: str = f"{kata[2]:.2f}"
    second: str = f"{kata[3]:.2e}"
    third: str = f"{kata[4]:.2e}"
    print(f"{module}, {ex} : {first}, {second}, {third}")


if __name__ == "__main__":
    main()
