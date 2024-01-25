import subprocess
import re
import numpy as np
import matplotlib.pyplot as plt

def main():

    # Create Ns
    N_max, N_step =  2000, 20
    Ns = np.arange(N_step, N_max+1, N_step)
    Gflops_s = np.zeros(int(N_max/N_step)) 
    f = open("graphData.txt", "a")

    # Iterate over Ns
    for N in Ns:
        sum = 0
        # Iterate multiple times for each N to reduce fluctuations
        for i in range(5):
            #out  = subprocess.getoutput("g++ -o Part1.exe Part1.cpp") # We don't necessarily want to compile everytime. It just wastes time. 
            output = subprocess.getoutput("./Part1.exe " + str(N))
            match = re.search(r'Gflops/s:\s+(\d+(\.\d+)?)', output)
            sum += float(match.group(1))
        res = sum/5
        Gflops_s[int(N/N_step)-1] = res
        print("Finished Iteration", int(N/N_step), "out of", int(N_max/N_step), "with result", res)
        f.write(str(N) + "    " + str(res) + "\n")
    f.close()

    # Plot With Theoretical Performance 
    fig, ax = plt.subplots(figsize =(6, 4))
    ax.set_title('Measuring performance')
    ax.set_ylabel('Gflops/s')
    ax.set_xlabel('N')
    ax.plot(Ns, Gflops_s, label = "Performance Result from Matrix-Matrix Calculation ")
    plt.axhline(y = 18.4, color = 'r', linestyle = '-', label = "Theoretical Peak Performance")
    plt.yscale("log")
    plt.legend()
    plt.savefig("Performance_With_Theoretical.png")

    # PLot Without Theoretical Performance 
    fig, ax = plt.subplots(figsize =(6, 4))
    ax.set_title('Measuring performance')
    ax.set_ylabel('Gflops/s')
    ax.set_xlabel('N')
    ax.plot(Ns, Gflops_s, label = "Performance Result from Matrix-Matrix Calculation ")
    plt.legend()
    plt.savefig("Performance_Without_Theoretical.png")

main()