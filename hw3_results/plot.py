#%%
import numpy as np
import matplotlib.pyplot as plt

# %%
with open("./default/mm_jki_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {jki} in default (float)")
plt.show()

# %%
with open("./default/mm_jki_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {jki} in default (double)")
plt.show()

# %%
with open("./default/mm_kij_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {kij} in default (float)")
plt.show()

# %%
with open("./default/mm_kij_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {kij} in default (double)")
plt.show()

# %%



# %%
with open("./O3/mm_jki_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {jki} in O3 (float)")
plt.show()

# %%
with open("./O3/mm_jki_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {jki} in O3 (double)")
plt.show()

# %%
with open("./O3/mm_kij_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {kij} in O3 (float)")
plt.show()

# %%
with open("./O3/mm_kij_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {kij} in O3 (double)")
plt.show()

#%%



# %%
with open("./fastmath/mm_jki_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {jki} in fastmath (float)")
plt.show()

# %%
with open("./fastmath/mm_jki_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {jki} in fastmath (double)")
plt.show()

# %%
with open("./fastmath/mm_kij_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {kij} in fastmath (float)")
plt.show()

# %%
with open("./fastmath/mm_kij_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(2, 513), performance)
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {kij} in fastmath (double)")
plt.show()

#%%



# %%
with open("./Strassen.txt") as file:
    lines = [line.rstrip() for line in file]
performance = np.array([float(x) for x in lines])
plt.plot(range(1, 10), performance)
plt.xlabel("Size of n (in base 2)")
plt.ylabel("Performance")
plt.title("Performance of Strassen")
plt.show()

# %%



# %%
with open("./default/mm_jki_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance_default = np.array([float(x) for x in lines])
with open("./O3/mm_jki_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance_O3 = np.array([float(x) for x in lines])
with open("./fastmath/mm_jki_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance_fastmath = np.array([float(x) for x in lines])

#%%
plt.plot(range(2, 513), performance_default, "-b", label="Default")
plt.plot(range(2, 513), performance_O3, "-r", label="O3")
plt.plot(range(2, 513), performance_fastmath, "-g", label="Fastmath")
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {jki} (float)")
plt.legend(loc="lower right")
plt.show()

# %%
with open("./default/mm_kij_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance_default = np.array([float(x) for x in lines])
with open("./O3/mm_kij_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance_O3 = np.array([float(x) for x in lines])
with open("./fastmath/mm_kij_float.txt") as file:
    lines = [line.rstrip() for line in file]
performance_fastmath = np.array([float(x) for x in lines])

#%%
plt.plot(range(2, 513), performance_default, "-b", label="Default")
plt.plot(range(2, 513), performance_O3, "-r", label="O3")
plt.plot(range(2, 513), performance_fastmath, "-g", label="Fastmath")
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {kij} (float)")
plt.legend(loc="lower right")
plt.show()

# %%
with open("./default/mm_jki_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance_default = np.array([float(x) for x in lines])
with open("./O3/mm_jki_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance_O3 = np.array([float(x) for x in lines])
with open("./fastmath/mm_jki_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance_fastmath = np.array([float(x) for x in lines])

#%%
plt.plot(range(2, 513), performance_default, "-b", label="Default")
plt.plot(range(2, 513), performance_O3, "-r", label="O3")
plt.plot(range(2, 513), performance_fastmath, "-g", label="Fastmath")
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {jki} (double)")
plt.legend(loc="lower right")
plt.show()

# %%
with open("./default/mm_kij_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance_default = np.array([float(x) for x in lines])
with open("./O3/mm_kij_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance_O3 = np.array([float(x) for x in lines])
with open("./fastmath/mm_kij_double.txt") as file:
    lines = [line.rstrip() for line in file]
performance_fastmath = np.array([float(x) for x in lines])

#%%
plt.plot(range(2, 513), performance_default, "-b", label="Default")
plt.plot(range(2, 513), performance_O3, "-r", label="O3")
plt.plot(range(2, 513), performance_fastmath, "-g", label="Fastmath")
plt.xlabel("Size of n")
plt.ylabel("Performance")
plt.title("Performance of {kij} (double)")
plt.legend(loc="lower right")
plt.show()

# %%
