import matplotlib.pyplot as plt
import numpy as np

# Load the nanosecond measurements from the file
data = np.loadtxt("time_diff_file.txt")

# Create a histogram to show the distribution
plt.plot(data)
#plt.ylim([1000000000, 1000200000])
plt.ylabel("Time (nanoseconds)")
plt.xlabel("Iteration No.")
plt.title("Ethan OConnor ECE 231 Lab 2 - Measured Time for each Iterations usleep Call:")
plt.show()
