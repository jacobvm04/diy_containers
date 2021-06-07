# DIY Containers
This was a project where I implemented a polymorphic container system, supporting various data structures, such as
array lists, heap based priority queues, hash maps, and sorting algorithms such as heap sort. These containers support generic programming (though they are not
typesafe) through the use of void pointers. Because of this, please remember that the pointers returned by the get method
of the containers may be invalidated if the container is structurally changed. 
Another thing to remember is that the remove method of the containers will return a pointer to newly allocated memory to
preserve their values, therefore these pointers must be freed eventually. Also, iterators are supported on all of the containers
except for hash maps currently. Examples of use can be seen in the testing.c file, and the API for the containers is fairly self-explanatory through the reading of the
corresponding header files.