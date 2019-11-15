CFLAGS = -g -Wall

all:	qSim

qSim: PA5_nwalzer.o Customer.o Teller.o TellerQueue.o EventQueue.o Event.o CEvent.o TEvent.o
	g++ $(CFLAGS) PA5_nwalzer.o Customer.o Teller.o TellerQueue.o EventQueue.o Event.o CEvent.o TEvent.o -o qSim

TEvent.o: TEvent.cpp TEvent.h
	g++ $(CLFAGS) -c TEvent.cpp

CEvent.o: CEvent.cpp CEvent.h
	g++ $(CLFAGS) -c CEvent.cpp
	
Event.o: Event.cpp Event.h
	g++ $(CLFAGS) -c Event.cpp
	
EventQueue.o: EventQueue.cpp EventQueue.h
	g++ $(CLFAGS) -c EventQueue.cpp
	
TellerQueue.o: TellerQueue.cpp TellerQueue.h Customer.h
	g++ $(CLFAGS) -c TellerQueue.cpp
	
Teller.o: Teller.cpp Teller.h TellerQueue.h
	g++ $(CLFAGS) -c Teller.cpp
	
Customer.o: Customer.cpp Customer.h
	g++ $(CLFAGS) -c Customer.cpp
	
PA5_nwalzer.o: PA5_nwalzer.cpp
	g++ $(CFLAGS) -c PA5_nwalzer.cpp

clean:
	rm -f *.o qSim
	rm -f -r html latex

# Give command "make docs" to create documentation.	
docs:
	doxygen
