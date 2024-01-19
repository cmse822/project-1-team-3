import subprocess
import re
import numpy as np
import matplotlib.pyplot as plt

def main():

    # Create Ns
    N_max, N_step =  1000, 20
    Ns = np.arange(1, N_max, N_step)
    Gflops_s = np.zeros(int(N_max/N_step))

    # Iterate over Ns
    for N in Ns:
        print("Iteration", int(N/N_step), "out of", int(N_max/N_step))
        output  = subprocess.getoutput("g++ -o Part1.exe Part1.cpp")
        output2 = subprocess.getoutput("./Part1.exe " + str(N))
        match = re.search(r'Gflops/s:\s+(\d+(\.\d+)?)', output2)
        Gflops_s[int(N/N_step)] = match.group(1)

    # Plot values 
    fig, ax = plt.subplots(figsize =(6, 4))
    ax.set_title('Measuring performance')
    ax.set_ylabel('Gflops/s')
    ax.set_xlabel('N')
    ax.plot(Ns, Gflops_s)
    plt.savefig("Performance.png")

main()