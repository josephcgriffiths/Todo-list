# To-Do Application for the Terminal
This is my attempt at craeting a todo application in C, for no reason other than I want to learn the language and data structures.

I think this is a fun / somewhat challenging project that has significantly improved my understanding of pointers and linked lists.

It's no where near complete and I'm working on it day-by-day when I have the chance. So far, I have created the node struct, allowed the user to add a task, and delete a task through specifying the index.

# Goals for this Small Application
I would like to make the user-experiance more fluid, but that is not on the list of priorities for this project. I just want to make sure:
a) I understand the functionality that goes into a todo list
b) I can implement those functions

Something I have wanted to do in this project is to place asserts everywhere as a means of avoiding errors/understanding where I have gone wrong.

So far with my limited experience I have run into seg faults on numerous occasions and have spent more time debugging. I have seen online that asserts may help me when debugging.

In the last commit I was glad I managed to add a new field to the struct for tasks. This saw me adding a number, along with functions that manage the numbers as a task is deleted.

# Latest Editions

I have added a few more features since the last commit:
1) The screen clears after every command, this looks neater in the terminal.
2) I have added statuses now so you can keep track of tasks that have been completed.

The next thing I am planning on adding is a save button that saves all the tasks to a .txt file. This will then be read from everytime the application is run, effectively creating a todo list that can be used. Whilst this project was just a fun project, I plan on using it to have projects I want to complete in the future on there.
