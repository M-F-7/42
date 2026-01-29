import numpy as np
import sys

class KmeansClustering:
    def __init__(self, max_iter=20, ncentroid=5):
        self.ncentroid = int(ncentroid) # number of centroids
        self.max_iter = int(max_iter) # number of max iterations to update the centroids
        self.centroids = [] # values of the centroids

    def fit(self, X:np.ndarray):
        if X.size == 0:
            return None
        self.centroids = np.zeros((self.ncentroid, X.shape[1]))
        for i in range(self.ncentroid):
            self.centroids[i] = np.random.rand(X.shape[1])
        # print(self.centroids)
        # print("END")
        # print(X.shape[1])
        

        """
        Run the K-means clustering algorithm.
        For the location of the initial centroids, randomly pick n centroids from the dataset.
        Args:
        -----
        X: has to be an numpy.ndarray, a matrice of dimension m * n.
        Return:
        -------
        None.
        Raises:
        -------
        This function should not raise any Exception.
        """

    def predict(self, X):
        """
        Predict from wich cluster each datapoint belongs to.
        Args:
        -----
        X: has to be an numpy.ndarray, a matrice of dimension m * n.
        Return:
        -------
        the prediction has a numpy.ndarray, a vector of dimension m * 1.
        Raises:
        -------
        This function should not raise any Exception.
        """




def main():
    
    if len(sys.argv) != 4:
        return
    args = {}
    for arg in sys.argv[1:]:
        if '=' in arg:
            key, value = arg.split('=')
            args[key] = value
    
    if not args['filepath'].lower().endswith('.csv'):
        print("Wrong format for the file", file=sys.stderr)
        return 

    with  open(args['filepath'], "r", encoding="utf-8") as fd:
        tab:np.ndarray = ([[]])
        row:list = []
        for line in fd:
            split = line.strip().split(sep=',')    
            row.append(split)
        tab = np.asarray(row)
        # print(tab)
        obj = KmeansClustering(max_iter=args['max_iter'], ncentroid=args['ncentroid'])
        obj.fit(tab)


if __name__ == "__main__":
    main()