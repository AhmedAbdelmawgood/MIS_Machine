#intial makefile for the program
cc = g++
flag = -I./include -pthread -g
program = serverR
var = TCPServerSocket.o TCPSocket.o C_Variable.o C_REAL.o C_NUMERIC.o C_STRING.o C_CHAR.o C_ADD.o C_MISThread.o C_ThreadCollector.o C_ASSIGN.o C_DIV.o C_FileParser.o C_GET_STR_CHAR.o C_Instruction.o C_JMP.o C_JMPGT.o C_JMPGTE.o C_JMPLT.o C_JMPLTE.o C_JMPNZ.o C_JMPZ.o C_LABEL.o C_MUL.o C_OUT.o C_SET_STR_CHAR.o C_SLEEP.o C_SUB.o C_VAR.o C_ErrorHandler.o MIS.o Connection.o GarbageCollector.o Thread.o
OBJ = $(var:%.o=./objects/%.o)
#test:
#	echo $(OBJ)
$(program) : $(OBJ) Client
	$(cc) $(flag) -o serverR $(OBJ) ./src/server.cpp  -std=gnu++14
Client: ./objects/TCPSocket.o
	$(cc) $(flag) -o clientR ./objects/TCPSocket.o ./src/C_Client.cpp -std=gnu++14
./objects/%.o:  ./include/%.h ./src/%.cpp ./include/includes.h
	$(cc) $(flag) -c ./src/$*.cpp -o ./objects/$*.o -std=gnu++14

clean:
	rm -f ./objects/*.o
	rm -f $(program)
