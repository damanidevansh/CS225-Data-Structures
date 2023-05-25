# Final Project README

## Github Organization

### Old Data and New Data

- The airports and routes datasets (CSV files) that were downloaded from the openflight website [OpenFlight](https://openflights.org/data.html) can be found in the oldata directory under root in the repository. The parsed and corrected data used in the graph structure can be found in the newdata directory that is also found in the root of the repository.

### Data Parsing and Correction Files

- Files corresponding to the data correction and parsing steps are found in the root of the repository. The delcaration of these functions are found in data.h and their implementations can be found in data.cpp.

### Airport and Route Files

- Files corresponding to Airport and Route classes can be found in the root directory. The declaration of these classes along with their data members and member functions can be found in airport.h/route.h. The actual implementation is found in airport.cpp and route.cpp.

### Graph Files including implementations of BFS, Dijkstra, and Bellman-Ford

- Files corresponding to the Graph structure can be found in the root of the repository. The declaration of this structure along with its data members and member functions can be found in graph.h. The actual implementation is found in graph.cpp.

### Test Files

- Files corresponding to the tests can be found in the tests directory located in the root of the repository. The directory includes a test.cpp that includes the implementation for all the test cases. Test cases also utilize smaller subsets of the actual dataset to perform tests. These airports and routes datasets (CSV files) can be found in each test case's corresponding directory. For example, the datasets that BFS utilizes for testing is under the bfs directory in the tests directory.

### Main and Executables

- Main.cpp is located in the root of the repository along with the executable files for both main and test.

### Written report and presentation

- The written report, presentation video, as well as other files used throughout the project are found in the documents directory in the root directory. [Link to Report](documents/results.md), [Link to Video](documents/presentation.mp4)

## Running Instructions

- The openflight dataset along with the parsed/corrected dataset is already provided. No need to download any datasets. The location is described under the Github Organization section.

### All commands below should be executed in the terminal in the root of the repository
1. Use `make` to compile main.cpp.

2. After running `make` run `./main` to run your main executable (runs code in main.cpp).

3. To run the tests use `make test`. Run the command `./test` after running the previous command to run your test executable. (runs code in test.cpp). The test cases in test.cpp test all member functions of the graph structure in graph.h as well as the data parsing functions in data.h. main.cpp includes code that runs BFS, Dijkstra, and Bellman-Ford on the parsed/corrected routes and airports datasets located in newdata directory in the root of the repository.
[Link to olddata](olddata/), [Link to newdata](newdata/)




