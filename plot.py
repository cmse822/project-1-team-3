import subprocess
import re
import numpy as np
import matplotlib.pyplot as plt

def main():

    # Create Ns
    N_max, N_step =  5000, 100
    Ns = np.arange(1, N_max+2, N_step)

    Gflops_s = np.zeros(int(N_max/N_step)+1)

    # Iterate over Ns
    for N in Ns:
        #out  = subprocess.getoutput("g++ -o Part1.exe Part1.cpp")
        output = subprocess.getoutput("./Part1.exe " + str(N))
        match = re.search(r'Gflops/s:\s+(\d+(\.\d+)?)', output)
        Gflops_s[int(N/N_step)] = match.group(1)
        print("Finished Iteration", int(N/N_step), "out of", int(N_max/N_step), "with result", match.group(1))

    # Plot values 
    fig, ax = plt.subplots(figsize =(6, 4))
    ax.set_title('Measuring performance')
    ax.set_ylabel('Gflops/s')
    ax.set_xlabel('N')
    ax.plot(Ns, Gflops_s)
    plt.savefig("Performance.png")

main()