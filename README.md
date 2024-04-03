g++ 1a.cpp -fopenmp -o 1a
./1a

mpic++ 1b.cpp -o 1b
mpirun -np 2 1b

g++ 2.cpp -fopenmp -o 2
./2

g++ 3.cpp -fopenmp -o 3
./3

g++ 4a.cpp -fopenmp -lgd -o 4a
./4a ip.png op.png

g++ 4b.cpp -fopenmp -lgd -o 4b
./4b a.png

mpicc 5.c -o 5
mpirun -np 2 5

g++ 6.cpp -fopenmp -o 6
./6
