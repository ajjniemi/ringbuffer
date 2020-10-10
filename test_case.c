#include <gtest/gtest.h>
#include "ringbuffer.h"

TEST(init_category, basic_test)
{
	unsigned char rx_buffer[BUFFER_SIZE];
	struct buffer_type r;

	init_buffer(&r, rx_buffer);

	EXPECT_EQ(r.head, rx_buffer);
	EXPECT_EQ(r.tail, rx_buffer);
	EXPECT_EQ(r.buffer, rx_buffer);

}

TEST(empty_buffer, basic_test)
{
   	unsigned char rx_buffer[BUFFER_SIZE];
   	struct buffer_type r;
   	error_type err;

	init_buffer(&r, rx_buffer);

	add_char_to_buffer(&r, 'a', &err);

	err = empty_buffer(&r);

   	r.buffer=rx_buffer;
   	r.head=rx_buffer;
   	r.tail=rx_buffer;

   	EXPECT_EQ(err, OK);

   	EXPECT_EQ(r.head, rx_buffer);
   	EXPECT_EQ(r.tail, rx_buffer);
   	EXPECT_EQ(r.buffer, rx_buffer);
}

TEST(get_buffer_state, basic_test)
{
   	unsigned char rx_buffer[BUFFER_SIZE];
	char msg[]={"Hello World"};
   	struct buffer_type r;
	int state, i;
   	error_type err;

	init_buffer(&r, rx_buffer);

   	r.buffer=rx_buffer;
   	r.tail=rx_buffer;
   	r.head=rx_buffer;

	for(i=0;msg[i]!='\0';i++){
		add_char_to_buffer(&r, msg[i], &err);
	}

	state = get_buffer_state(&r, &err);

   	EXPECT_EQ(state, 11);

   	EXPECT_EQ(r.head, rx_buffer+11);
   	EXPECT_EQ(r.tail, rx_buffer);
   	EXPECT_EQ(r.buffer, rx_buffer);
}
TEST(add_char_to_buffer, basic_test)
{
   	unsigned char rx_buffer[BUFFER_SIZE];
   	struct buffer_type r;
   	error_type err;

	init_buffer(&r, rx_buffer);

   	r.buffer=rx_buffer;
   	r.head=rx_buffer;
   	r.tail=rx_buffer;

   	add_char_to_buffer(&r, 'a', &err);

   	EXPECT_EQ(get_char_from_buffer(&r, &err), 'a');

   	EXPECT_EQ(r.head, rx_buffer+1);
   	EXPECT_EQ(r.tail, rx_buffer+1);
   	EXPECT_EQ(r.buffer, rx_buffer);
}
TEST(get_char_from_buffer, basic_test)
{
   	unsigned char rx_buffer[BUFFER_SIZE];
	char msg[]={"Hello World"};
	struct buffer_type r;
	int state, i;
   	error_type err;

	init_buffer(&r, rx_buffer);

   	r.buffer=rx_buffer;
   	r.tail=rx_buffer;
	r.head=rx_buffer;

	for(i=0;msg[i]!='\0';i++){
		add_char_to_buffer(&r, msg[i], &err);
	}

	state = get_buffer_state(&r, &err);
	r.tail=rx_buffer+9;
   	EXPECT_EQ(get_char_from_buffer(&r, &err), 'l');

   	EXPECT_EQ(r.head, rx_buffer+11);
   	EXPECT_EQ(r.tail, rx_buffer+10);
   	EXPECT_EQ(r.buffer, rx_buffer);
}
TEST(print_buffer, basic_test)
{
	unsigned char rx_buffer[BUFFER_SIZE];
   	struct buffer_type r;

   	int state;
  	error_type err;

	init_buffer(&r, rx_buffer);

   	r.buffer=rx_buffer;
   	r.head=rx_buffer+15;
   	r.tail=rx_buffer+2;

   	state = print_buffer(&r,&err);

   	EXPECT_EQ(state, 13);
   	EXPECT_EQ(err, OK);

   	EXPECT_EQ(r.head, rx_buffer+15);
   	EXPECT_EQ(r.tail, rx_buffer+2);
   	EXPECT_EQ(r.buffer, rx_buffer);
}
