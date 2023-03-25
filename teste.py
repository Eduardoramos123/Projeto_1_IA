
def print_current_time():
    from time import time, ctime
    print('Today is', ctime(time()))


print_current_time()
