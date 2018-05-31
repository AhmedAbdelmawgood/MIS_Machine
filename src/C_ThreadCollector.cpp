#include "C_ThreadCollector.h"
/** Constructor sets head and tail to NULL **/
C_ThreadCollector::C_ThreadCollector(){ head= tail =NULL; }

/** Add a new C_MISThread **/
void C_ThreadCollector::addThread(C_MISThread * P_misThread) {
    if ( head == NULL )	/** If head is null (List empty) point head and tail to the C_MISThread **/
        head = tail = P_misThread;
    else { /** else add to the end and advance tail **/
        tail->setNextThread(P_misThread);
        tail = P_misThread;
    }
}
/** Clean up all finished threads **/
void C_ThreadCollector::cleanup() {
    C_MISThread * cur = head; /** set cur to head **/
    /** Loop and delete all finished MISThreads from the front of the list **/
    for ( ; cur!= NULL && !cur->isRunning(); )
    {
	cur->waitForRunToFinish(); /** Wait for the thread **/
    C_MISThread * cur1 = cur;	/** get a pointer to it **/
    cur = cur->getNextThread(); /** Advance cur **/
	if(cur1 != NULL){
            delete (cur1); /** delete the current connection **/
            cur1 = NULL;
        }
    }
    head = cur; /** Set head to cur **/
    if ( head == NULL) tail = NULL; /** If list is empty set tail to NULL **/
}
/** Invoked upon program termination to Gracefully wait for all running threads to finish **/
void C_ThreadCollector::terminate() {
    C_MISThread * cur = head; /**set cur to head **/
    for ( ;cur!= NULL; ) /** Loop on all connections **/
    {
        cur->waitForRunToFinish(); /** wait for the current connection to finish **/
        C_MISThread * cur1 = cur; /** get a pointer to it **/
        cur = cur->getNextThread(); /** advance cur **/
        if(cur1 != NULL){
            delete (cur1); /** delete the current connection **/
            cur1 = NULL;
        }
    }
    head = tail = NULL; /** set head and tail to NULL as the list should be empty **/
}
C_ThreadCollector::~C_ThreadCollector()
{
    terminate(); /** Invoke terminate to dispose all connections **/
}
