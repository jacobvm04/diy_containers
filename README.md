# DIY Containers
This was a project where I implemented a polymorphic container system, supporting various data structures, such as
array lists, heap based priority queues, hash maps, and sorting algorithms such as heap sort. These containers support generic programming (though they are not
typesafe) through the use of void pointers.
Because of this, remember to add values to containers through pointers. e.g. instead of `array_list_add(&array_list, 2);` to add an integer of 2, do 
```
array_list bar = array_list_construct(sizeof(int), 3);
int foo = 2;
array_list_add(&bar, &foo);
```

Because of this use of void pointers to support generic programming, please remember that the pointers returned by the get method
of the containers may be invalidated if the container is structurally changed. 
Another thing to remember is that the remove method of the containers will return a pointer to newly allocated memory to
preserve their values, therefore these pointers must be freed eventually. Also, iterators are supported on all of the containers
except for hash maps currently. Examples of use can be seen in the testing.c file, and the API for the containers is fairly self-explanatory through the reading of the
corresponding header files.