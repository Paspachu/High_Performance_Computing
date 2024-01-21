#%%
import numpy as np
import matplotlib.pyplot as plt

# %%
with open("./Separately/L1_performance_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L1 (using double, ran separately)")
plt.show()

# %%
with open("./Separately/L1_performance_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L1 (using float, ran separately)")
plt.show()

# %%
with open("./Separately/L1_unroll_performance_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.bar(range(0, 7), performance)
plt.xlabel("Block size in log base 2")
plt.ylabel("Performance")
plt.title("Performance of L1 Unroll (using double, ran separately)")
plt.show()

# %%
with open("./Separately/L2_performance_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L2 (using double, ran separately)")
plt.show()

# %%
with open("./Separately/L2_performance_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L2 (using float, ran separately)")
plt.show()

# %%
with open("./Separately/L3_performance_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025, 14), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L3 (using double, ran separately)")
plt.show()

# %%
with open("./Separately/L3_performance_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025, 14), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L3 (using float, ran separately)")
plt.show()

#%%





# %%
with open("./Together/L1_performance_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L1 (using double, ran together)")
plt.show()

# %%
with open("./Together/L1_performance_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L1 (using float, ran together)")
plt.show()

# %%
with open("./Together/L1_unroll_performance_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.bar(range(0, 7), performance)
plt.xlabel("Block size in log base 2")
plt.ylabel("Performance")
plt.title("Performance of L1 Unroll (using double, ran together)")
plt.show()

# %%
with open("./Together/L2_performance_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L2 (using double, ran together)")
plt.show()

# %%
with open("./Together/L2_performance_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L2 (using float, ran together)")
plt.show()

# %%
with open("./Together/L3_performance_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025, 14), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L3 (using double, ran together)")
plt.show()

# %%
with open("./Together/L3_performance_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 1025, 14), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of L3 (using float, ran together)")
plt.show()

# %%
