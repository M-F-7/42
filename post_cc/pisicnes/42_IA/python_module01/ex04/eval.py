class Evaluator:
    def __init__(self):
        pass

    @staticmethod
    def zip_evaluate(coefs:list[float], words:list[str])->float:
        if len(words) != len(coefs):
            return -1
        result:float = 0
        for x, x2 in zip(words, coefs):
            result +=  float(len(x)) * x2
        return result


    @staticmethod
    def enumerate_evaluate(coefs:list[float], words:list[str])->float:
        if len(words) != len(coefs):
            return -1
        result:float = 0
        for idx in enumerate(coefs):
            result += idx[1] * float(len(words[idx[0]]))
        return result
    
def main():
    words = ["Le", "Lorem", "Ipsum", "est", "simple"]
    coefs = [1.0, 2.0, 1.0, 4.0, 0.5]
    print(Evaluator.zip_evaluate(coefs, words))
    print(Evaluator.enumerate_evaluate(coefs, words))
    
    #Evaluator.zip_evaluate(coefs, words)
    #Evaluator.enumerate_evaluate(coefs, words)
    
    words = ["Le", "Lorem", "Ipsum", "n’", "est", "pas", "simple"]
    coefs = [0.0, -1.0, 1.0, -12.0, 0.0, 42.42]
    print(Evaluator.zip_evaluate(coefs, words))
    print(Evaluator.enumerate_evaluate(coefs, words))




if __name__ == "__main__":
    main()