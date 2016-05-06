#Readme

to compile: run make in the command line
    this used g++ to compile

to run: run ./a.out <days> <trades> <filename>
    where filename is the name of the file containing the stocks values
    and days is the number of days in that file
        (if days is larger than the number of days in the file an error will be reported)
    and trades is the number of trades to be computed
        (if trades exceeds the number of trades in the optimal solution, the optimal solution will be returned)

Error Codes
1... file could not be opened
2... invalid number of trades
3... invalid format of input file
4... negative number appeared in input file
5... a decimal number appeared in the input file
6... wrong number of command line args