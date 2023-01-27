# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -std=c++11
 
# **************************************************

# Both server and client.
a.out: Server.o ClientMain.o ServerMain.o Client.o ClientInputCheck.o SafetyChecks.o Point.o KNN.o CalcDist.o SocketIO.o StandardIO.o CLI.o UploadFile.o AlgorithmSettings.o ClassifyData.o DisplayResult.o DownloadResult.o
	$(CC) $(CFLAGS) Client.o ClientMain.o ClientInputCheck.o StandardIO.o SocketIO.o -o client.out -lpthread
	$(CC) $(CFLAGS) Server.o ServerMain.o SafetyChecks.o Point.o KNN.o CalcDist.o SocketIO.o CLI.o UploadFile.o AlgorithmSettings.o ClassifyData.o DisplayResult.o DownloadResult.o -o server.out -lpthread


# Only client.
client.out: Client.o ClientMain.o ClientInputCheck.o StandardIO.o SocketIO.o
	$(CC) $(CFLAGS) Client.o ClientMain.o ClientInputCheck.o StandardIO.o SocketIO.o -o Client.out

# Only server.
server.out: Server.o ServerMain.o SafetyChecks.o Point.o KNN.o CalcDist.o SocketIO.o UploadFile.o AlgorithmSettings.o ClassifyData.o DisplayResult.o DownloadResult.o
	$(CC) $(CFLAGS) Server.o ServerMain.o SafetyChecks.o Point.o KNN.o CalcDist.o SocketIO.o UploadFile.o AlgorithmSettings.o ClassifyData.o DisplayResult.o DownloadResult.o -o Client.out


Server.o: Server.cpp SafetyChecks.h Point.h KNN.h
	$(CC) $(CFLAGS) Server.cpp -c

ServerMain.o: Server.o SafetyChecks.h Point.h KNN.h
	$(CC) $(CFLAGS) ServerMain.cpp -c

Client.o: Client.cpp ClientInputCheck.h SafetyChecks.h Point.h KNN.h
	$(CC) $(CFLAGS) Client.cpp -c

ClientMain.o: Client.o ClientInputCheck.h
	$(CC) $(CFLAGS) ClientMain.cpp -c

ClientInputCheck.o: ClientInputCheck.h
	$(CC) $(CFLAGS) ClientInputCheck.cpp -c

SafetyChecks.o: SafetyChecks.h SafetyChecks.cpp
	$(CC) $(CFLAGS) SafetyChecks.cpp -c

Point.o: Point.h Point.cpp
	$(CC) $(CFLAGS) Point.cpp -c

KNN.o: KNN.h KNN.cpp
	$(CC) $(CFLAGS) KNN.cpp -c

CalcDist.o: CalcDist.h CalcDist.cpp
	$(CC) $(CFLAGS) CalcDist.cpp -c

SocketIO.o: SocketIO.h SocketIO.cpp DefaultIO.h
	$(CC) $(CFLAGS) SocketIO.cpp -c

StandardIO.o: StandardIO.h StandardIO.cpp DefaultIO.h
	$(CC) $(CFLAGS) StandardIO.cpp -c

CLI.o: CLI.h CLI.cpp
	$(CC) $(CFLAGS) CLI.cpp -c

UploadFile.o: UploadFile.h UploadFile.cpp DefaultIO.h Command.h
	$(CC) $(CFLAGS) UploadFile.cpp -c

AlgorithmSettings.o: AlgorithmSettings.h AlgorithmSettings.cpp DefaultIO.h Command.h
	$(CC) $(CFLAGS) AlgorithmSettings.cpp -c

ClassifyData.o: ClassifyData.h ClassifyData.cpp DefaultIO.h Command.h
	$(CC) $(CFLAGS) ClassifyData.cpp -c

DisplayResult.o: DisplayResult.h DisplayResult.cpp DefaultIO.h Command.h
	$(CC) $(CFLAGS) DisplayResult.cpp -c

DownloadResult.o: DownloadResult.h DownloadResult.cpp DefaultIO.h Command.h
	$(CC) $(CFLAGS) DownloadResult.cpp -c

clean:
	rm *.o *.out
