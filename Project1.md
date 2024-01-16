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

theoretical peak performance = #cores_per_processors x #clock_speed x 1. 

| System specfication          | Arc1 (Macbook Pro) | Arc2 (Dell XPS 15) | Arc3 | Arc4 |
| ---------------------------- | ------------------ | ------------------ | ---- | ---- |
| Clock Rate                   | 3.2GHz             | 2.3 GHz            |      |      |
| Level 1 Cache                | 2.9MB              | 640 KB             |      |      |
| Level 2 Cache                | 28MB               | 10 MB              |      |      |
| Level 3 Cache                | 24MB               | 24 MB              |      |      |
| Number of Cores / Threads    | 10                 | 8                  |      |      |
| Theoretical Peak Performance | 25.6 Gflops/s      | 18.4 Gflops/s      |      |      |

The performance in (1.3) is much lower than the theoretical value. 

### 1.5 Solution 

![fig1](./image.png)


### 1.6 Solution

## Part 2: The Roofline Model 

*In this part, you will explore the roofline model for analyzing the interplay between arithmetic intensity and memory bandwidth for architectures with complex memory hierarchies. Complete the following exercises on the _SAME_ compute architectures that you used in Part 1 above.*

### Solution

