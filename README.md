# AP_Task4

**This project was built by Daniel Lifshitz and Adira Weiss.**

**In this project we implemented a server and a client to run the KNN algorithm from the previous assignment.<br>
The client will receive a vector from the user, send it to the server who will run the algorithm and send a prediction which then wil bee printed by the client*



## Explanitions

The client send the server one of the following numbers: {1,2,3,4,5,8}

For each number the server will exacute a different command and for 8 the client will end the program.

### Command 1

The server will ask the client to input a train file (The path to the file)

After the client will enter the path the server will ask from the client to input a test file (The path to the file)

The train file: A csv file holding numbers in the first x columns and their type.

For example: 1,2,3,4,5,red
             5,2,5,2,3.1,blue
             5,1,63,5,3,red
             5.3,2.3,5.4,3.1,blue

The test file: A csv file holding numbers in the first x columns.

For example: 1,2,3,4,5
             5,2,5,2,3.1
             5,1,63,5,3
             5.3,2.3,5.4,3.1

If the client enters a correct train file but an incorrect test file we will not replace the train file.

We check if the number of columns is the same throughout the file but not between the two files, this we check in command 3.

### Command 2

The server will ask the client to input a k (integer) and a distance metric (string).

If the client enters an incorrect k or an incorrect distance metric we will return invalid input.
             
The distance metric can be: AUC,MAN,CHB,CAN,MIN

The k can be any number.

### Command 3

The server will classify all the data in the test file using the data in the train file.

The distance metric would be the one entered in command 2.

The k will be the minimum between the k entered in 2 and the number of points in the test file.

### Command 4

The server will print to the screen all the data classified in command 3.

Using command 4 will clean the classified data thats being held meaning using command 4 twice in a row will ask you to classify the data the second time.

### Command 5

The server will ask the client to input a path for the file he want to save (assuming that the path has the file name)

The server will write the output that would have been written in command 4 into the file.

Using command 5 will also clean the classified data thats being held.

### serverTimer

To make sure no client forgot to send 8 we have a timer of between 1 and 2 minutes until the client is kicked out from the loop.




**Run and compile**
The project has a given ```Makefile``` for you to use when compiling the code.

You have a few options to compile the code:
If you want to compile both the server and the client you can use the following command:

```
make server
```

and run the server with:
```
./serverrun port
```
and to run the client with:
```
./clientrun ip port
```
If you want to only use server or client you can use the following commands:

In order to compile the server code type in:
```
make server
```
and to run it:
```
./serverrun port
```
And the same goes for the client, run this client command after you've run the server command (and while it's running):
```
make client
```
and to run it:
```
./clientrun ip port
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

After inputting one of those numbers you will initaite a command please look at "Explanitions" for the commands

* All vectors in the .csv file must be the same size.
* A distance metric:
  * AUC
  * MAN
  * CHB
  * CAN
  * MIN
* K - number of neighbors to check.
  * K must be a number bigger than zero and smaller than the number of vectors in the .csv file.
  * Must be an integer.

**Example**
If you input:
```
1 2 3 4 MAN 5
```
You will get:
```
Iris-versicolor
```
**For invalid input of any kind, the program will print an error message and ask you to input a new number.**
