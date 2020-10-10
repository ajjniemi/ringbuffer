#include "ringbuffer.h"

void init_buffer(struct buffer_type *b, unsigned char *buffer){
	b->head = buffer;
	b->tail = buffer;
 	b->buffer = buffer;
}
error_type empty_buffer(struct buffer_type *b){
	b->tail=b->head;
	return OK;
}
int get_buffer_state(struct buffer_type *b, error_type *err){
	if(b->head < b->buffer || b->head > b->buffer+BUFFER_SIZE){
		*err=POINTER_ERROR;
		return -1;
	}
	else if(b->tail < b->buffer || b->tail > b->buffer+BUFFER_SIZE){
		*err=POINTER_ERROR;
		return -1;
	}
	else{
		*err=OK;
		return b->head - b->tail;
	}
}

int add_char_to_buffer(struct buffer_type *b, unsigned char c, error_type *err){
	if(b->head == (b->buffer+BUFFER_SIZE-1)){
		*(b->head)=c;
		b->head = b->buffer;
	}
	else{
		*(b->head)=c;
		b->head++;
	}
}
char get_char_from_buffer(struct buffer_type *b, error_type *err){
	char c;
	if(b->tail==b->head){
	}
	else{
		c=*(b->tail);
		b->tail++;
		return c;
	}
}
int print_buffer(struct buffer_type *b, error_type *err){
	char buf[BUFFER_SIZE];
	for(int i=0;i<b->head-b->tail;i++){
		char buf[i]={*(i+b->tail)};
	}
	printf("%s", buf);
	return get_buffer_state(b, err);
}
