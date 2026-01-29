import pandas as pd
import csv
from predict import linearRegression

t0 = 0.0
t1 = 0.0

with open("thetaValue.csv", "w") as f:
        writer = csv.writer(f)
        writer.writerow([0, 0]) #reset le file a 0

db = pd.read_csv("./data.csv")

# Normalisation
km_mean = db["km"].mean()
km_std = db["km"].std()
price_mean = db["price"].mean()
price_std = db["price"].std()

db["km_norm"] = (db["km"] - km_mean) / km_std                           #x norm = x - x.mean() / x.std
db["price_norm"] = (db["price"] - price_mean) / price_std

learning_rate = 0.005
iterations = 50000

def train():
    global t0, t1, learning_rate, old_cost

    for i in range(iterations):
        sum_t0 = 0.0
        sum_t1 = 0.0

        for km, price in zip(db["km_norm"], db["price_norm"]):
            error = (linearRegression(km, t0, t1) - price)
            sum_t0 += error
            sum_t1 += error * km

        t0 -= learning_rate * (1 / db.shape[0]) * sum_t0
        t1 -= learning_rate * (1 / db.shape[0]) * sum_t1
                  

    real_t1 = t1 * (price_std / km_std)
    real_t0 = price_mean + (t0 * price_std) - real_t1 * km_mean

    with open("thetaValue.csv", "w") as f:
        writer = csv.writer(f)
        writer.writerow([real_t0, real_t1])


def main():
    train()


if (__name__ == "__main__"):
    main()