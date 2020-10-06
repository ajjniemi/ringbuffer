#define BUFFER_SIZE 1024
enum error_type {OK, BUFFER_OVER_FLOW, EMPTY_BUFFER, POINTER_ERROR, BUFFER_FULL};
struct buffer_type{
	unsigned char *head;
	unsigned char *tail;
	unsigned char *buffer;
};
void init_buffer(struct buffer_type *b, unsigned char *buffer);
error_type empty_buffer(struct buffer_type *b);
int get_buffer_state(struct buffer_type *b, error_type *err);
int add_char_to_buffer(struct buffer_type *b, unsigned char c, error_type *err);
char get_char_from_buffer(struct buffer_type *b, error_type *err);
int print_buffer(struct buffer_type *b, error_type *err);

