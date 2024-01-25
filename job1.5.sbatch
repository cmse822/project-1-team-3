#!/bin/bash --login

#SBATCH --time=02:50:00
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
#SBATCH --mem-per-cpu=3G


module purge
module load GCC/10.3.0 OpenMPI/4.1.1

cd /mnt/home/zhan2204/CMSE822/prog1/projectv1
srun -c 2 1.5.4