# AP_Task4

**This project was built by Daniel Lifshitz and Adira Weiss.**

**In this project we implemented a server and a client to run the KNN algorithm from the previous assignment.<br>
The client will sends two files of vectors to the server who will run the KNN algorithm and send a prediction which then wil be printed by the client*



## Explanations

When the client program connects to a server, an option menu is printed.

The client sends the server one of the following numbers: {1,2,3,4,5,8}

For each number the server will execute a different command.

### Command 1

The server will ask the client to input a train file (The path to the file)

After the client will enter the path the server will ask from the client to input a test file (The path to the file)

The train file: A csv file holding numbers in the first x columns and their type.

For example: 

             5,2,5,2,3.1,blue
             
             5,1,63,5,3,red
             
             5.3,2.3,5.4,3.1,blue

The test file: A csv file holding numbers in the first x columns.

For example:

             5,2,5,2,3.1
             
             5,1,63,5,3
             
             5.3,2.3,5.4,3.1

If the client enters a correct train file but an incorrect test file we will not replace the train file.

### Command 2

The server will ask the client to input a k (integer) and a distance metric (string).

If the client enters an incorrect k or an incorrect distance metric we will return an invalid input accordingly.

note that the default K and metric are 5 and AUC.

### Command 3

The server will classify all the data in the test file using the data in the train file.

The distance metric would be the one entered in command 2.

The k will be the minimum between the k entered in 2 and the number of points in the train file.

### Command 4

The server will send the data classified in command 3 to the client.

### Command 5

The server will ask the client to input a path for the file he wants to save (assuming that the path has the file name)

The server will send the output as in command 4.

### Command 8

Terminates the program.




**Run and compile**
The project has a given ```Makefile``` for you to use when compiling the code.

To compile both the server and the client you can use the following command:

```
make
```

To run the server program use the following command:
```
./server.out port
```
To run the client program use the following command:
```
./client.out ip port
```
<br>**Arguments in run command:**
* ip
    * must be a valid ip address.
* port
    * must be a valid port number (0-65535).

**Example Server**
````
./server.out 5555
````

**Example Client**
````
./client.out 127.0.0.1 5555
````

**For any Invalid input in the run command, the program will print an error message and exit the program.**<br>

**Input Instructions for Client:**
* The program will receive the following input from the user:
````
int
````
* The input must be an integer and must be one of the following {1,2,3,4,5,8}

After inputting one of those numbers you will initaite a command please look at "Explanations" for the commands

* All vectors in the .csv file must be the same size.
* Valid distance metric:
  * AUC
  * MAN
  * CHB
  * CAN
  * MIN
* K - number of neighbors to check.
  * K must be a number bigger than zero and smaller than the number of vectors in the .csv file.
  * Must be an integer.
