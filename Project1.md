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

| Kernel      | Number of ops | Number of bytes | Arithmetic Intensity $[\frac{flop}{byte}]$|
| ----------- | ----------- | ----------- | ----------- |
| `Y[j] += Y[j] + A[j][i] * B[i]`      |    3    |    32    |    $\frac{3}{32}$    |
| `s += A[i] * A[i]`   |    2    |    8    |    $\frac{1}{4}$    |
| `s += A[i] * B[i]`   |    2    |    16    |    $\frac{1}{8}$    |
| `Y[i] = A[i] + C*B[i]`   |    2    |    24    |    $\frac{1}{12}$    |

## Part 1: Matrix-matrix Multiplication

*In this first part of the project, you will test the performance of the basic matrix-matrix multiplication operation as a function of matrix size on multiple compute platforms. Complete the following using at least two different compute architectures (e.g., your laptop and HPCC, or two different node architectures on HPCC).*

### Solution

| System specfication | Arc1  | Arc2  | Arc3  | Arc4  |
| ----------- | --------- | ---- | ---- | ----- |
| Clock Rate  |  |  |  |  |
| Level 1 Cache |  |  |  |  |
| Level 2 Cache |  |  |   |  |
| Level 3 Cache |  |  |  |  |
| Number of Cores / Threads |  |  |  |  |

![fig1](./image.png)

## Part 2: The Roofline Model 

*In this part, you will explore the roofline model for analyzing the interplay between arithmetic intensity and memory bandwidth for architectures with complex memory hierarchies. Complete the following exercises on the _SAME_ compute architectures that you used in Part 1 above.*

### Solution

![fig1](./image.png)
