#include "queue.h"
#include <stdio.h>
#include <sys/queue.h>

// Define the play queue head
struct playqueue_tq playqueue_head;
struct playqueue_tq playhistory_head;

// Initialize the queue
void init_queue(struct playqueue_tq *queue) { TAILQ_INIT(queue); }

// Add a song to the queue
void push_to_tail_queue(struct playqueue_tq *queue, struct Song *song) {
  struct Song *song_copy = deep_copy_song(song);
  if (song_copy == NULL) {
    perror("Failed to copy song");
    return;
  }
  TAILQ_INSERT_TAIL(queue, song_copy, songs);
}

// Add a song to the queue
void push_to_head_queue(struct playqueue_tq *queue, struct Song *song) {
  struct Song *song_copy = deep_copy_song(song);
  if (song_copy == NULL) {
    perror("Failed to copy song");
    return;
  }
  TAILQ_INSERT_HEAD(queue, song_copy, songs);
}

// Pop a song from the queue (removes and returns the first song)
struct Song *pop_head_from_queue(struct playqueue_tq *queue) {
  struct Song *song = TAILQ_FIRST(queue);
  if (song != NULL) {
    TAILQ_REMOVE(queue, song, songs);
  }
  return song;
}

void skip_to_song(struct playqueue_tq *queue, struct Song *song, size_t pos) {
  while (pos > 0) {
    puts("Popping from queue");
    pop_head_from_queue(queue);
    pos--;
  }
}

struct Song *pop_tail_from_queue(struct playqueue_tq *queue) {
  struct Song *song = TAILQ_LAST(queue, playqueue_tq);
  if (song != NULL) {
    TAILQ_REMOVE(queue, song, songs);
  }

  return song;
}

// Peek at the next song in the queue without removing it
struct Song *peek_next_song(struct playqueue_tq *queue) {
  return TAILQ_FIRST(queue);
}

// Remove a specific song from the queue
void remove_song(struct playqueue_tq *queue, struct Song *song) {
  TAILQ_REMOVE(queue, song, songs);
}

// Check if the queue is empty
int is_queue_empty(struct playqueue_tq *queue) { return TAILQ_EMPTY(queue); }

void add_to_back(struct playqueue_tq *queue, struct Song *song) {
  TAILQ_INSERT_TAIL(queue, song, songs);
}

// Get the number of songs in the queue
size_t get_queue_length(struct playqueue_tq *queue) {
  size_t count = 0;
  struct Song *song = NULL;
  TAILQ_FOREACH(song, queue, songs) { count++; }
  return count;
}

void clear_queue(struct playqueue_tq *queue) { TAILQ_INIT(queue); }
