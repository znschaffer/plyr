#include "queue.h"
#include <stdio.h>

// Define the play queue head
struct playqueue_tq playqueue_head;

// Initialize the queue
void init_queue() { TAILQ_INIT(&playqueue_head); }

// Add a song to the queue
void add_to_queue(struct Song *song) {
  struct Song *song_copy = deep_copy_song(song);
  if (song_copy == NULL) {
    perror("Failed to copy song");
    return;
  }
  TAILQ_INSERT_TAIL(&playqueue_head, song_copy, songs);
}

// Pop a song from the queue (removes and returns the first song)
struct Song *pop_from_queue() {
  struct Song *song = TAILQ_FIRST(&playqueue_head);
  if (song != NULL) {
    TAILQ_REMOVE(&playqueue_head, song, songs);
  }
  return song;
}

// Peek at the next song in the queue without removing it
struct Song *peek_next_song() { return TAILQ_FIRST(&playqueue_head); }

// Remove a specific song from the queue
void remove_song(struct Song *song) {
  TAILQ_REMOVE(&playqueue_head, song, songs);
}

// Check if the queue is empty
int is_queue_empty() { return TAILQ_EMPTY(&playqueue_head); }

// Add to front of queue
void add_to_front(struct Song *song) {
  TAILQ_INSERT_HEAD(&playqueue_head, song, songs);
}

// Get the number of songs in the queue
size_t get_queue_length() {
  size_t count = 0;
  struct Song *song = NULL;
  TAILQ_FOREACH(song, &playqueue_head, songs) { count++; }
  return count;
}

void clear_queue() { TAILQ_INIT(&playqueue_head); }
