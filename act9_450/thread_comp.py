"""
Cuyler Quint
CPS 450
Lab 9

	Compare the time it takes to get max,min and avergae of a data set
	with multi threading vs single threading

"""
import numpy as np
import threading,time

min = 0
max = 0
ave = 0
new_list = []

def get_ave():
	global new_list
	global ave
	ave = np.mean(new_list) 

def get_max():
	global new_list
	global max
	max =  np.max(new_list)


def get_min():
	global new_list
	global min
	min =  np.min(new_list)

def output():
	global ave
	global max
	global min
	print("Average: ", ave)
	print("Max: ", max)
	print("Min: ", min)
	

def multi_worked():
	ave_thread = threading.Thread(target=get_ave)
	min_thread = threading.Thread(target=get_max)
	max_thread = threading.Thread(target=get_min)
	start = time.time()
	ave_thread.start()
	max_thread.start()
	min_thread.start()

	ave_thread.join()
	max_thread.join()
	min_thread.join()
	end = time.time()
	print("Multiple Worked total time: ", end-start)
	output()	

def single_broker():
	get_ave()
	get_max()
	get_min()

def single_worked():
	
	sig_thread = threading.Thread(target=single_broker)
	start = time.time()
	sig_thread.start()
	sig_thread.join()
	end = time.time()

	print("Single Worked total time: ", end-start)
	output()
def main():
	with open("dataset1.txt") as f:
    		lines = f.read().splitlines()
	global new_list
	for item in lines:
    		new_list.append(float(item))
	multi_time = multi_worked()
	single_time = single_worked()

if __name__ == "__main__":
	main()		
