# Parallel-Computing

### ForestFire
- Models the spread of a forest fire for various probabilities that an individual fire spreads to the next tree
- Run ``` ./onestep.out``` for one step of the model and provides a graphical representation of a forest fire spreading
- Run ``` ./main.out``` for overall statistics of forest fire spreading with different probabilities
### MPIForestFire
- Uses MPI library to run the ForestFire project in parallel
- Run ```time mpirun -np 2 a.out``` to run ForestFire in parallel
- Change number after np flag to number of workers + 1
- MPI Runtime Graph.png is a graph of runtime as the number of workers active in the cluster increases
### OpenGL
- Run ```./fireGL.out``` in the terminal in the project folder for a graphical representation of the ForestFire simulation
- Run ```./main.out``` in the terminal in the project folder to generate and manipulate a fractal
- Use w and s to zoom in and out of the fractal and q to quit
### Huffman
- Huffman encoding and decoding program
- Run ```./decode``` in the terminal in the project folder to decode the text in decodeME.txt and provide compression statistics
- Run ```./encode``` in the terminal in the project folder to encode the message in message.txt and output encoding information to 
output.txt and outmessage.txt
### MPIDemo
- Quick demo of MPI library
- Run ```time mpirun -np 2 a.out``` in the terminal in the project folder
- Change number after np flag to number of workers + 1
