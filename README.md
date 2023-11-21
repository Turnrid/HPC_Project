# HPC Project: AwannaCU

## Serial Algorithm

### Instructions for build and execution

- To run the serial implementation, run `$ bash ./run_serial.sh`

### Approach for the serial program

Consider two points 1 (x1,y1,z1) and 2 (x2,y2,z2). point 2 is in the line of sight of point 1 if and only if for every point (x,y,zLine) along the line from (x1,y1,z1) to (x2,y2,z2) z <= zLine, where z is the elevation map value at point (x,y). From this, we can modify Bresenham's algorithm to check z against zLine (called zLineOfSight in serial.cpp) at all points (x,y) in a straight line between (x1,y1) and (x2,y2). Define the following function

- `int countLineOfSight(data, x1, y1, x2, y2)`
    - This function computes a straight line between (x1,y1) and (x2,y2) and then along that line checks zMax against zLineOfSightAtMax. If at some point (x,y) (x1,y1) to (x2,y2), zMax <= zLineOfSightAtMax, then the function iterates a count. The function returns that count at the end of execution.

In `serial(int range)`, the program will read in the data from the file (a helper function to do this is written in `helper_functions.cpp`), then for each pixel (centerX, centerY) in the image, compute `countLineOfSight(data,centerX,centerY,considerX,considerY)`, where (considerX,considerY) iterates over every pixel in the perimeter of 100 pixel square radius. Add the results for all `countLineOfSight` calculations for each (centerX,centerY), and write to an array. After the count has been computed for every pixel, the array holding the counts is written to a file `output_serial.raw`

The `main()` function simply calls the `serial()` function, specifying a range (which is how far away each pixel should look for line of sight)

## CPU Shared Memory Algorithm

### Instructions for build and execution

- To run the cpu shared memory implementation, run `$ bash ./run_cpu_shared.sh {thread_count}`, where `{thread_count}` is the number of threads you want to run the program.

### Approach for the cpu shared memory program

- Start with serial implementation, with `serial(range)` method being changed to `cpu_shared(thread_count, range)`, which must be given a thread count.
- Use OpenMP directives to parallelize the outermost for loop, which iterates over the rows (centerY). This allows the algorithm to take advantage of caching. In practice, this will be a `#pragma omp parallel for`. 
- Inside the for loops, when the local count for a pixel wants to be written to the array, there must be a critical section. For this, we can use `#pragma omp critical` to wrap the write operation.

