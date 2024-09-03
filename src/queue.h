#ifndef QUEUE_H
#define QUEUE_H

#include "song.h"
#include <sys/queue.h>

// Define a type for the play queue
TAILQ_HEAD(playqueue_tq, Song);

// Declare the play queue head as an external variable
extern struct playqueue_tq playqueue_head;
extern struct playqueue_tq playhistory_head;

// Function declarations for queue operations
void init_queue(struct playqueue_tq *queue); // Initialize the queue
void push_to_head_queue(struct playqueue_tq *queue, struct Song *song);

void push_to_tail_queue(struct playqueue_tq *queue,
                        struct Song *song); // Add a song to the queue
void clear_queue(struct playqueue_tq *queue);

void skip_to_song(struct playqueue_tq *queue, struct Song *song, size_t pos);
struct Song *pop_tail_from_queue(struct playqueue_tq *queue);

struct Song *pop_head_from_queue(
    struct playqueue_tq *queue); // Pop a song from the queue (removes
                                 // and returns the first song)
struct Song *
peek_next_song(struct playqueue_tq *queue); // Peek at the next song in the
                                            // queue without removing it
void remove_song(struct playqueue_tq *queue,
                 struct Song *song); // Remove a specific song from the queue
int is_queue_empty(struct playqueue_tq *queue); // Check if the queue is empty
size_t get_queue_length(
    struct playqueue_tq *queue); // Get the number of songs in the queue

#endif
