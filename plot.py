import subprocess
import re
import seaborn as sns
import numpy as np

def run_command_multiple_times(cmd):
    # The command to be executed
    command = [cmd]

    # Run the command and capture the output
    process = subprocess.run(command, stdout=subprocess.PIPE, text=True)

    # Extract the output as a string
    output = process.stdout

    # Use regular expression to find the Mflops/s value
    match = re.search(r'Mflops/s:\s+(\d+(\.\d+)?)', output)

    if match:
        mflops = match.group(1)
        return float(mflops) / 1000


def measure_time(Ns, repeat_time):
    total_times = []
    for N in Ns:
        time = []
        for _ in range(repeat_time):
            cmd = f"./mat {N}"
            time.append(run_command_multiple_times(cmd))
        total_times.append(np.mean(time))
    return total_times


def main():
    pass