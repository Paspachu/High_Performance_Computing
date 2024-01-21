#%%
import numpy as np
import matplotlib.pyplot as plt
import csv

#%%
"""Problem 1"""
with open("./p1/write.txt") as file:
    lines = [line.rstrip() for line in file]
write = np.array([float(x) for x in lines])
with open("./p1/read.txt") as file:
    lines = [line.rstrip() for line in file]
read = np.array([float(x) for x in lines])
plt.plot(np.array([32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384]), write[1:], '-o', label="write")
plt.plot(np.array([32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384]), read[1:], '-o', label="read")
plt.xlabel("Dimension")
plt.ylabel("Bandwidth (in MB/s)")
plt.title("Bandwidth of write and read")
plt.legend(loc="lower right")
plt.savefig("hw4_p1_plot.png")
# plt.show()

# %%
"""Problem 2"""
with open("./p2/time.txt") as file:
    data = csv.reader(file, delimiter="\t")
    data = list(data)
data

#%%
time = np.array([float(v[-1]) for v in data])
plt.plot(range(1, 11), time)
plt.xlabel("Thread Count")
plt.ylabel("Time (in seconds)")
plt.title("Strong Scaling Efficiency")
plt.show()

#%%
with open("./p2/error.txt") as file:
    data = csv.reader(file, delimiter="\t")
    data = list(data)
data

#%%
error = np.array([float(v[-1]) for v in data])
plt.plot(range(1, 7), error)
plt.xlabel("Number of points to partition (in log base 10)")
plt.ylabel("Error (in log)")
plt.title("Numerical Error (using 5 threads)")
plt.show()

# %%
"""Problem 3"""
with open("./p3/time.txt") as file:
    data = csv.reader(file, delimiter="\t")
    data = list(data)
data

#%%
time = np.array([float(v[-2]) for v in data])
plt.plot(range(1, 41), time)
plt.xlabel("Process Count")
plt.ylabel("Time (in seconds)")
plt.title("Strong Scaling Efficiency")
plt.show()

#%%
with open("./p3/error.txt") as file:
    data = csv.reader(file, delimiter="\t")
    data = list(data)
data

#%%
error = np.array([float(v[-1]) for v in data])
plt.plot(range(1, 7), error)
plt.xlabel("Number of points to partition (in log base 10)")
plt.ylabel("Error (in log)")
plt.title("Numerical Error (using 10 processes)")
plt.show()

# %%
"""Problem 4"""
with open("./p4/bandwidth.txt") as file:
    data = csv.reader(file, delimiter="\t")
    data = list(data)
data

#%%
Bcast = np.array([float(v[0])/(1024*1024) for v in data])
my = np.array([float(v[1])/(1024*1024) for v in data])
plt.plot(range(3, 28), Bcast, '-o', label='Bacst')
plt.plot(range(3, 28), my, '-o', label='my_broadcast')
plt.xlabel("Message size (in log base 2)")
plt.ylabel("Bandwidth (in MB/s)")
plt.title("Bandwidth of Bcast vs my_broadcast")
plt.legend(loc='upper left')
plt.show()


# %%
