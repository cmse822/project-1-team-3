# Project 1

## Warm-up

*Review the section in [HPSC](../assets/EijkhoutIntroToHPC2020.pdf) on computing arithmetic intensity for given compute kernels. 
Then, as a group, compute the arithmetic intensities of the following kernels in units of FLOPs/byte, assuming 8 bytes per float.*

```C
  Y[j] += Y[j] + A[j][i] * B[i]
```

```C
  s += A[i] * A[i]
```

```C
  s += A[i] * B[i]
```

```C
  Y[i] = A[i] + C*B[i]
```

### Solution

| Kernel      | Number of flops | Number of bytes | Arithmetic Intensity $[\frac{flop}{byte}]$|
| ----------- | ----------- | ----------- | ----------- |
| `Y[j] += Y[j] + A[j][i] * B[i]`      |    3    |    32    |    $\frac{3}{32}$    |
| `s += A[i] * A[i]`   |    2    |    8    |    $\frac{1}{4}$    |
| `s += A[i] * B[i]`   |    2    |    16    |    $\frac{1}{8}$    |
| `Y[i] = A[i] + C*B[i]`   |    2    |    24    |    $\frac{1}{12}$    |

## Part 1: Matrix-matrix Multiplication

*In this first part of the project, you will test the performance of the basic matrix-matrix multiplication operation as a function of matrix size on multiple compute platforms. Complete the following using at least two different compute architectures (e.g., your laptop and HPCC, or two different node architectures on HPCC).*

### 1.1 Solution 

Please check the code `Part1.cpp`

### 1.2 Solution 

$2N^{3}$, so if $N=100$, this should be $2000000$. 

### 1.3 Solution 

 We test it for 5 times on two different devices: Mackbook Pro with M1 Pro, and HPCC with amd-dev20. The recorded Mflops/s are given in the table below:

|             | Run 1   | Run 2   | Run 3   | Run 4   | Run 5   | Avg.     |
|-------------|---------|---------|---------|---------|---------|----------|
| Macbook     | 194.744 | 226.09  | 176.833 | 258.996 | 292.571 | 229.8468 |
| Dell XPS 15 | 176.4   | 209.1   | 150.0   | 164.9   | 163.3   | 172.74   |
| HPCC        | 177.229 | 180.361 | 161.226 | 161.422 | 160.797 | 168.207  |

### 1.4 Solution

Since we are only running these on one processor we will only consider the theoretical peak performance of a single processor rather than the whole system. Therefore, theoretical peak performance = clock_speed where 1 GHz is 1Gflops/s 

| System specfication          | Arc1 (Macbook Pro) | Arc2 (Dell XPS 15) | Arc3 (HPCC amd-dev20) |
| ---------------------------- | ------------------ | ------------------ | --------------------- |
| Clock Rate                   | 3.2 GHz            | 2.3 GHz            | 2.6 GHz               |
| Level 1 Cache                | 2.9MB              | 640 KB             | 64 Kb                 |
| Level 2 Cache                | 28MB               | 10 MB              | 512 Kb                |
| Level 3 Cache                | 24MB               | 24 MB              | 16.384 Mb             |
| Number of Cores / Threads    | 10                 | 8                  | 64                    |
| Theoretical Peak Performance | 3.2 Gflops/s       | 2.3 Gflops/s       | 2.6 Gflops/s         |

The performance in (1.3) is much lower than the theoretical value. 

### 1.5 Solution 

Here we can see the matrix-matrix performance plotted with the theoretical peak performance of System 76 Wild-dog Pro. 

<!-- ![fig1](./figures/Performance_With_Theoretical.png) -->
![fig1](./figures/Performance_With_Theoretical_system76.png)

We are also plotting the image without the theoretical performance to make out the features of the graph, if any. 

<!-- ![](./figures/Performance_Without_Theoretical.png) -->
![](./figures/Performance_Without_Theoretical_system76.png)


### 1.6 Solution

The realistic calculation time is much smaller than the theoretical peak performance. The large matrix-matrix mutliplications in particular are heavily memory bound which decreases performance. Additionally, we only utilise one processor per system which greatly decreases the realistic performance since all machines used had multiple cores available. There are features in the plot which result from the machine needing to use different levels of cache/memory  (L1, L2, etc.). For large values of $N$, the computer must use lower and lower levels of cache levels which increases time since the computer must go farther and farther away in memory. 

## Part 2: The Roofline Model 

*In this part, you will explore the roofline model for analyzing the interplay between arithmetic intensity and memory bandwidth for architectures with complex memory hierarchies. Complete the following exercises on the _SAME_ compute architectures that you used in Part 1 above.*

### 2.3 Solution

The configuration file used for System 76 (Wild-dog Pro) is shown as follows
```
#
ERT_RESULTS Results.roofline

ERT_DRIVER  driver1
ERT_KERNEL  kernel1

#ERT_FLOPS   1,2,64,128,256
ERT_FLOPS   1,2,4,8
ERT_ALIGN   32

ERT_CC      g++
ERT_CFLAGS  -O3 

ERT_LD      g++
ERT_LDFLAGS 
ERT_LDLIBS

ERT_RUN     ./ERT_CODE

ERT_PRECISION   FP32

ERT_NUM_EXPERIMENTS 2

ERT_MEMORY_MAX 1073741824

ERT_WORKING_SET_MIN 1024

ERT_TRIALS_MIN 1

ERT_GNUPLOT gnuplot
```

We acquired the following roofline plot from ERT

<!-- ![roofline](./figures/roofline.jpg) -->
![roofline](./figures/roofline_system76.jpg)

The peak performance and the bandwidths for L1, L2, L3, L4, L5 and DRAM are shown in the plot along with the ridge points for each (encircled). 

### 2.4 Solution

The arithmetic intensity for each kernel is shown below (copied from textbook):

![](./figures/stat.png)

The performance band for each kernel is marked in the roofline plot below
<!-- ![](./figures/roofline2.jpg) -->
![](./figures/textbook_kernels_system76.jpg)

Based on the arithmetic intensities, SpMV is bandwidth-bound, while the remaining three kernels are computation-bound (will run at peak performance).

To optimize:
* SpMV: optimize memory access and data transmission, for example, locality
* others: better devices

### 2.5 Solution

All four kernels in Part 1 are bandwidth-bounded (marked in the figure below). To improve performance, memory access and data transmission needs to be optimized.

<!-- ![](./figures/roofline3.jpg) -->
![](./figures/part1_kernels_system76.jpg)

### 2.6 Solution

