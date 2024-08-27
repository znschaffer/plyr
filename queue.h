#ifndef QUEUE_H
#define QUEUE_H

#include "song.h"
#include <sys/queue.h>

// Define a type for the play queue
TAILQ_HEAD(playqueue_tq, Song);

// Declare the play queue head as an external variable
extern struct playqueue_tq playqueue_head;

// Function declarations for queue operations
void init_queue();                    // Initialize the queue
void add_to_queue(struct Song *song); // Add a song to the queue
void add_to_front(struct Song *song);
void clear_queue();

struct Song *pop_from_queue(); // Pop a song from the queue (removes and returns
                               // the first song)
struct Song *
peek_next_song(); // Peek at the next song in the queue without removing it
void remove_song(struct Song *song); // Remove a specific song from the queue
int is_queue_empty();                // Check if the queue is empty
size_t get_queue_length();           // Get the number of songs in the queue

#endif
