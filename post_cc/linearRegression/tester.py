from predict import linearRegression, load_t
from train import db, train
import numpy as np
import math
import matplotlib.pyplot as plt

train()

#BONUS
def main():
    tab_error = []
    t0, t1 = load_t()
    for mile, price in zip(db["km"], db["price"]):
        error = linearRegression(mile, t0, t1) - price
        tab_error.append(error ** 2)

    MSE = sum(tab_error) / len(tab_error)
    RMSE = math.sqrt(MSE)


    print(f"Precision Rate: {RMSE}") #Mean error

    plt.figure()
    plt.scatter(db["km"], db["price"], s=8)
    plt.xlabel("mileage")
    plt.ylabel("price")
    plt.title("Price/Mileage")
    plt.grid(True, alpha=0.3)
    x_line = np.array([db["km"].min(), db["km"].max()])
    y_line = linearRegression(x_line, t0, t1)
    plt.plot(x_line, y_line, color="red", label=f"y = {t0:.1f} + {t1:.5f} x")
    plt.show()


if (__name__ == "__main__"):
    main()
