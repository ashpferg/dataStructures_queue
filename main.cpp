#include <iostream>

/*  Each queue contains a struct of nodes. Each node is an element of the queue.
*	The Queue also contains pointers to the front and back of the queue, ie the
*	first and last node. 
* 
*	The queue can enqueue (add) or dequeue (remove) elements, as well as print
*	each element. It also uses a method to check is the queue is empty, though this
*	isn't called directly. */
class Queue {

	/* Nodes are the elements of the queue. */
	struct node {

		/* Each node contains a int data value, and two pointers. 
		One points to the element in front of the node, and the other
		to the element behind it.
		
		You could just use a backwards pointer. But using two allows you 
		to iterate through the list in either direction - which I wanted to
		be able to do in the print method. */
		int data;
		node* backwards;
		node* forwards;

		/* Constructor: Initialize each node upon creation. */
		node() {
			std::cout << "Node created." << std::endl << std::endl;
			backwards = NULL;
			forwards = NULL;
			data = NULL;
		}

		/* Destructor: Print a message when we destroy a node so we know it's working. */
		~node() {
			std::cout << "Node deleted." << std::endl;
		}
	};

	/* Front and back are node pointers that point to the first and last element
	   of the queue. */
	public:
	node* front;
	node* back;

	/* Constructor: initialize each queue upon creation. We only use one queue object here. */
	Queue() {
		std::cout << "Queue created" << std::endl << std::endl;
		front = NULL;
		back = front;
	}

	/* Destructor: Print queue deletion message before exiting. */
	~Queue() {
		std::cout << "Queue deleted." << std::endl;
	}

	/* Enqueue: add a node to the queue. */
	void enqueue(int new_data) {
		
		/* Check if list is empty. If it is, both front and back need to point to it. */
		if (isEmpty()) {

			/* Front points to a newly initialized node. */
			front = new node();

			/* Because its the only element, this nodes pointers point to NULL. */
			front->backwards = NULL;
			front->forwards = NULL;

			/* Add the input value as this node's data variable. */
			front->data = new_data;

			/* Point the back pointer to the same element that front points to,
			since its the only element in the list.*/
			back = front;
		}

		/* If list isn't empty, do this. */
		else {

			/* A temporary pointer temp points to the "current" last node in the queue. */
			node* temp = back;

			/* Back ptr is assigned to a new, empty node, and this node gets the input data value. */
			back = new node();
			back->data = new_data;

			/* The new node is going to be the new back of the list. Since nothing is behind it, the
			backwards pointer points to NULL.*/
			back->backwards = NULL;

			/* The new node's forwards pointer needs to point to the previous back of the list (which is temp). */
			back->forwards = temp;

			/* Finally, we have to finish linking the nodes together. If back points to n, then the node ahead of it
			is n-1. n-1's backwards pointer should point to the node behind it, which is back. */
			temp->backwards = back;
		}
	}

	/* Remove a node from the queue. */
	void dequeue(int num_elements_to_remove) {

		/* Remove as many nodes as the user requested. */
		for (int i = 0; i < num_elements_to_remove; i++) {		
				
			/* If the number of elements to dequeue will make the queue empty, this block is called.
			If the front item doesn't have anything behind it, then it's the last element remaining. 
			So delete it and break out of the loop before we try to access unreserved memory. */
			if (front->backwards == NULL) {
				std::cout << "Number of elements to remove is >= length of queue. Removing last element." << std::endl;

				/* Deletes the last node of the queue. */
				delete front;

				/* Reinitialize front and back to NULL and exit the dequeue method. */
				front = NULL;
				back = front;;
				break;
			}

			/* If queue won't be made empty, then do this.
			Start by pointing a temporary node pointer to the front of the queue. */
			node* temp = front;

			/* The first element is going to be removed. So point front to the 2nd node in the list.
			Then delink it by making the new front node point forwards to NULL. */
			front = temp->backwards;
			front->forwards = NULL;

			/* Finally, delete the node that temp is pointing at (the node to be dequeued). If we don't do this,
			we'll have random, inaccessible nodes floating around in memory. */
			delete temp;
		}
	}

	/* Print the data value of each node, from left to right / back to front. */
	void print() {

		/* Make sure we list has elements & we aren't trying to access forbidden memory. */
		if (isEmpty() == false) {

			/* A temporary node pointer is created pointing to the last element. */
			node* traverse = back;
			std::cout << "[Back <---> Front]" << std::endl;

			/* Run until traverse stops pointing at nodes. Print the data at each node. */
			while (traverse != NULL) {
				std::cout << traverse->data << " ";

				/* Have pointer point to the node ahead in the queue. We could also print
				front to back by setting traverse = front, and then iterating with
				traverse = traverse-backwards. */
				traverse = traverse->forwards;
			}
			/* Formatting */
			std::cout << std::endl;
		}

		// Error: Can't print empty queue
		else
			std::cout << "The queue is empty... " << std::endl << std::endl;
	}

	/* Check to see if queue is empty. */
	bool isEmpty() {

		/* If front and back point to NULL, then there are no nodes in queue. Return true if that's the case.*/
		if (front == NULL && back == NULL) {
			return true;
		}

		/* Otherwise, return false. */
		else 
			return false;
	}
};

int main() {

	/* Initialize: q1 is our queue object. Mode controls the interaction with the user.
	this_many_elements is the quantity to be added/removed from queue. */
	Queue q1;
	int mode = NULL;
	int this_many_elements = NULL;

	/* Run until told to quit. */
	while (true) {

		/* Reinitialize each pass. */
		mode = NULL;
		this_many_elements = NULL;

		/* Ask user what they want to do.*/
		//std::cout << "0, 1, 2, 3 (Enqueue, dequeue, print, or quit?): ";
		std::cout << "0: Enqueue, 1: Dequeue, 2: Print, 3: Quit" << std::endl;
		std::cin >> mode;

		/* Quit */
		if (mode == 3)
			break;

		/* Print the queue from left to right ie back to front. */
		else if (mode == 2)
			q1.print();

		/* Dequeue mode */
		else if (mode == 1) {

			/* Ask for # elements to remove. */
			std::cout << "How many elements do you want to dequeue?" << std::endl;
			std::cin >> this_many_elements;

			/* Make sure queue has elements to dequeue. */
			if (q1.isEmpty())
				std::cout << "Cannot dequeue an empty queue." << std::endl << std::endl;

			/* If not empty, dequeue. */
			else {
				std::cout << "Dequeue " << this_many_elements << " elements" << std::endl;
				q1.dequeue(this_many_elements);
			}

		}

		/* Enqueue mode */
		else if (mode == 0) {

			/* Ask for elements to add. */
			std::cout << "How many elements do you want to enqueue?" << std::endl << std::endl;
			std::cin >> this_many_elements;

			/* Run input loop this_many times. */
			for (int i = 0; i < this_many_elements; i++) {
				std::cout << "Enqueue: ";
				int input = NULL;
				std::cin >> input;

				/* Enqueue the input each pass. */
				q1.enqueue(input);
			}
		}

		/* Bad input */
		else
			std::cout << "Improper input, please try again" << std::endl;

	} /* end while loop */

	/* Queue destructor called automatically */
	return 0;
}