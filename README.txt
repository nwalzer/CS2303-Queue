Nathan Walzer - nwalzer

SUMMARY:
This program simulates a bank where customers arrive, wait in line, are served, and then leave.
It deals with both individual lines for tellers as well as a single shared line. It keeps
track of the total time spent serving customers, total break time, maximum wait time for a
customer, and average time spent in the bank.

HOW TO RUN:
In Eclipse - Running in Eclipse requires the user to alter the run configurations. 
The user should create a new C/C++ Application launch configuration using this project 
as the 'project' and putting 'qSim' as the C/C++ Application. Arguments must be added (SEE ARGUMENTS)

In the Command Line - Once in the directory containing this project run the 'make' 
command. This will link the files, create several object files, and create an executable 
file called 'qSim' The program can then be run by typing the command './qSim' and arguments
must be added (SEE ARGUMENTS)

ARGUMENTS:
In order to run the program the following arguments must be given:
In Eclipse: #customers #tellers simulationTime avgServiceTime <seed>
In the Command Shell: ./qSim #customers #tellers simulationTime avgServiceTime <seed>

Where -
#customers is an integer specifying the total number of customers that will enter the bank
#tellers is an integer specifying the total number of tellers in the bank
simulationTime is a float representing the total time, in minutes, the bank will be open for
avgServiceTime is a float representing the average time it takes a teller to serve a customer
seed is an optional integer specifying the seed. If left blank or 0, the program uses the time as the seed

PROBLEMS:
The only problem I encountered was trying to visualize how everything panned out. For awhile I didn't
understand how two tellers could be serving two customers at the same time, since the computer can only
do one thing at a time. It took a lot of written work to figure out that the event queue and global clock
made it so that it was simulated two events occurring concurrently.

REPRESENTATION:
Events: Events are represented as 4 different things. An event parent class, a teller event derived class,
and a customer event derived class split into two parts. Each of the types of events have a starting
time, located in the parent class. In the teller event class there is also a field for the number teller
associated with that event. Rather than putting a teller pointer in each teller event I have it so that
it contains the index of the teller being referenced, and all tellers are stored in an array in the main
program. For customer events I have an actual customer associated with each event, mainly so that I could
easily calculate the times I needed to output. Each customer event also has a field so that I could
specify whether the event was a customer arriving or a customer leaving, which are handled differently from
each other. 

Customer: A customer is represented by a single class. There is only one field, which is the time the customer
arrived/will arrive at the bank. 

Teller: A teller is represented as a single class. The only field is the line of customers the teller has.

Within the main program there is an EventQueue and an array of tellers. The tellers are not really dealt
with directly. they are mostly referenced through their index numbers (hence why teller event has an int
instead of a teller pointer). This just made it generally easier for me to pass around tellers and debug
the program

CITING:
The only code that I know for a fact is available online is the code for the node structs. They are generic
structs I have worked with in the past which I have been taught as being used almost everywhere. I did not
take the node code from online, however I am aware that it is available online


ANALYSIS:
Based on the three test cases I have documented, as well as dozens of undocumented tests, single queue and
multi queue both have pros and cons to them.

Single queue consistently had significantly lower maximum wait times, the largest of which varied by nearly
11 minutes, though it appears as if the difference shrinks as the number of customers grows.

Although multi queue always had a maximum wait time that was greater than the single queue's, the average
wait time for all tests was lower than the single queue's. And for larger amounts of customers the multi
queue had much lower totalservice and total idle times