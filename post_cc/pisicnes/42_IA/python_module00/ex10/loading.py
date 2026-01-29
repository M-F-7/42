from time import sleep
import sys
import time

def ft_progress(lst):
    total = len(lst)
    start_time = time.time()
    
    for i, elem in enumerate(lst):
        elapsed = time.time() - start_time
        percent = 100 * (i + 1) / total
        bar_length = 20
        filled_length = int(bar_length * (i + 1) / total)
        bar = "=" * (filled_length - 1) + ">" + " " * (bar_length - filled_length)
        sys.stdout.write(
            f"\rETA {elapsed:.2f}s [{percent:2.0f}%] [{bar}] {i+1}/{total} | elapsed time {elapsed:.2f}s"
        )
        sys.stdout.flush()
        yield elem
    print()


listy = range(1000)
ret = 0
for elem in ft_progress(listy):
    ret += (elem + 3) % 5
    sleep(0.01)
print()
print(ret)


listy = range(3333)
ret = 0
for elem in ft_progress(listy):
    ret += elem
    sleep(0.005)
print()
print(ret)
