#!/bin/bash


#SBATCH --job-name=hw4_p3


#SBATCH --account=amath

#SBATCH --partition=gpu-rtx6k

#SBATCH --nodes=4

#SBATCH --ntasks-per-node=10

#SBATCH --mem=5G

#SBATCH --gpus=0

#SBATCH --time=00-00:10:00

 

#SBATCH --chdir=/gscratch/amath/mchoi/hw4

#SBATCH --export=all

#SBATCH --output=test-out.txt # where STDOUT goes

#SBATCH --error=test-err.txt  # where STDERR goes

 

# Modules to use (optional).

module load gcc/11.2.0 ompi/4.1.3

 
# Your programs to run.
for i in {1..40}
do    
    mpirun -np $i ./xprob3 100000000
done

mpirun -np 10 ./xprob3 10
mpirun -np 10 ./xprob3 100
mpirun -np 10 ./xprob3 1000
mpirun -np 10 ./xprob3 10000
mpirun -np 10 ./xprob3 100000
mpirun -np 10 ./xprob3 1000000
