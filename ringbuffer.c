#include "ringbuffer.h"

void init_buffer(struct buffer_type *b, unsigned char *buffer){
	b->head = buffer;
	b->tail = buffer;
 	b->buffer = buffer;
}
error_type empty_buffer(struct buffer_type *b){
}
int get_buffer_state(struct buffer_type *b, error_type *err){
}
int add_char_to_buffer(struct buffer_type *b, unsigned char c, error_type *err){
}
char get_char_from_buffer(struct buffer_type *b, error_type *err){
}
int print_buffer(struct buffer_type *b, error_type *err){
}

