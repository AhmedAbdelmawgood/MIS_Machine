// Static method passed to pthread_create
void * Thread::run(void * arg)
{
	Thread * me = (Thread *) arg; // Cast the arg to Thread * which is the current thread
        // Push the cleanup static function to the cleanup functions stack to be invoked within pthread_exit
        // Notice the close curly bracket that substitute for the complementary pthread_cleanup_pop
//        pthread_cleanup_push(cleanup,arg); }
//   	pthread_detach (me->pthread);
	me->threadMainBody(arg); //Invoke the thread main function body
	me->cleanup(arg);
        pthread_exit(NULL); // Invoke pthread_exit to terminate and invoke the cleanup functions.
}
