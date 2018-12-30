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
- Contains two programs that use OpenGL to display a graphical representation of a simulation or fractal
- Run ```./fireGL.out``` in the terminal in the project folder for a graphical representation of the ForestFire simulation
- Run ```./main.out``` in the terminal in the project folder to generate and manipulate a fractal
- Use w and s to zoom in and out of the fractal and q to quit
### Huffman
- Huffman encoding and decoding program
- Run ```./decode``` in the terminal in the project folder to decode the text in decodeME.txt and provide compression statistics
- Run ```./encode``` in the terminal in the project folder to encode the message in message.txt and output encoding information to 
output.txt and outmessage.txt
### RayTracing
- Ray tracing program that includes shadows, moving images, and 2D ray tracing
- Run ```./main.out``` in the terminal in the project folder to output a ray traced 2D image of overlapping circles to circles.ppm
- Run ```./shadow.out``` in the terminal in the project folder to output a ray traced 3D perspective image of overlapping circles
 with shadows to shadows.ppm
- Run ```./movie.out``` in the terminal in the project folder to output 100 frames of a gif to the Frames folder.
Then run ```time convert -loop 0 -delay 10 Frames/*png movie.gif``` to combine the frames into a gif called movie.gif
### OrbitalMechanics
- Orbital mechanics program to model a free return path
- Run ```./main.c > orbit.txt``` in the terminal in the project folder to output orbital data sorted by time step to orbit.txt.  
Then run ```gnuplot plot.plt``` to output graphs of distance, speed, and position of the spacecraft.  Open orbit.png to view the free return path. 
### MPIOrbital
- Program to run the orbital mechanics program in parallel using MPI to find the optimal launch angle for a free return
- Run ```time mpirun -np 2 a.out``` in the terminal in the project folder to find the optimal launch angle
- Change number after np flag to number of workers + 1 
### MPIDemo
- Quick demo of MPI library
- Run ```time mpirun -np 2 a.out``` in the terminal in the project folder
- Change number after np flag to number of workers + 1
