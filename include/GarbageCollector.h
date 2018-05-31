#include "Connection.h"

// A class to manage expired TCP connection and dispose them one by one
class GarbageCollector
{ // It manages a linked list of connections and points to the beginning of the list via "head" and the end of the list via "tail"
    private:
        Connection * head; // Pointer to the first connection in the list
        Connection * tail; // Pointer to the last connection in the list
    public:
        GarbageCollector();// Constructor
        void addConnection(Connection * connection); // Add a connection
        void cleanup();	// Perform a clean up by disposing expired connections.
	void terminate (); // Wait for all thread connections to terminate and cleanup all
        ~GarbageCollector(); // Destructor
};

