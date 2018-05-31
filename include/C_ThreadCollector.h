#ifndef C_THREADCOLLECTOR_H
#define C_THREADCOLLECTOR_H

#include "C_MISThread.h"

class C_ThreadCollector
{ // It manages a linked list of C_MISThreads and points to the beginning of the list via "head" and the end of the list via "tail"
    private:
        C_MISThread * head; // Pointer to the first C_MISThread in the list
        C_MISThread * tail; // Pointer to the last C_MISThread in the list
    public:
        C_ThreadCollector();// Constructor
        void addThread(C_MISThread * P_misThread); // Add a C_MISThread
        void cleanup();	// Perform a clean up by disposing expired C_MISThreads.
        void terminate (); // Wait for all thread C_MISThreads to terminate and cleanup all
        ~C_ThreadCollector(); // Destructor
};


#endif // C_THREADCOLLECTOR_H
