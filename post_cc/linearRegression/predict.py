import csv

def load_t():
    with open("thetaValue.csv", "r") as f:
        t0, t1 = map(float, next(csv.reader(f)))
    return t0, t1


def linearRegression(mileage, t0=0, t1=0) :
    estimatePrice =  t0 + (t1 * mileage)
    return estimatePrice

def main():
    try:
        t0, t1 = load_t()
        str = input("Enter a mileage: ")
        nb = int(str)
        print(f"The price is: {linearRegression(nb, t0, t1)}")
    except ValueError:
        print("Need a number as argument")

if (__name__ == "__main__"):
    main()