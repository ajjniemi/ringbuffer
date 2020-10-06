/*****************************************************************************
 *	Includes
 ****************************************************************************/

#include <gtest/gtest.h>
#include "ringbuffer.h"

/*****************************************************************************
 *	Test cases
 ****************************************************************************/

/*
 * 	init_buffer
 */

TEST(init_buffer, NormBuf)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;

	init_buffer(&b, receive_buffer);

	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(receive_buffer, b.head);
	EXPECT_EQ(receive_buffer, b.tail);
}

TEST(init_buffer, NullPtr)
{
	unsigned char *receive_buffer = NULL;
	struct buffer_type b;

	init_buffer(&b, receive_buffer);

	EXPECT_EQ(NULL, b.buffer);
	EXPECT_EQ(NULL, b.head);
	EXPECT_EQ(NULL, b.tail);
}

/*
 * 	empty_buffer
 */

TEST(empty_buffer, NormBuf)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type retVal = BUFFER_FULL;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[3];
	b.tail = &receive_buffer[0];
	retVal = empty_buffer(&b);

	EXPECT_EQ(OK, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[3], b.head);
	EXPECT_EQ(&receive_buffer[3], b.tail);

}

TEST(empty_buffer, NullPtr)
{
	struct buffer_type b;
	error_type retVal = OK;

	b.buffer = NULL;
	b.head = NULL;
	b.tail = NULL;
	retVal = empty_buffer(&b);

	EXPECT_EQ(POINTER_ERROR, retVal);
	EXPECT_EQ(NULL, b.buffer);
	EXPECT_EQ(NULL, b.head);
	EXPECT_EQ(NULL, b.tail);
}

/*
 * 	get_buffer_state
 */

TEST(get_buffer_state, OK)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = BUFFER_FULL;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[0];
	b.tail = &receive_buffer[3];
	retVal = get_buffer_state(&b, &err);

	EXPECT_EQ(3, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[3], b.head);
	EXPECT_EQ(&receive_buffer[0], b.tail);
	EXPECT_EQ(OK, err);
}

TEST(get_buffer_state, BUFFER_OVER_FLOW)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = OK;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = ;
	b.tail = ;
	retVal = get_buffer_state(&b, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(, b.head);
	EXPECT_EQ(, b.tail);
	EXPECT_EQ(BUFFER_OVER_FLOW, err);
}

TEST(get_buffer_state, EMPTY_BUFFER)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = OK;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[3];
	b.tail = &receive_buffer[3];
	retVal = get_buffer_state(&b, &err);

	EXPECT_EQ(0, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[3], b.head);
	EXPECT_EQ(&receive_buffer[3], b.tail);
	EXPECT_EQ(EMPTY_BUFFER, err);
}

TEST(get_buffer_state, POINTER_ERROR)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = OK;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[BUFFER_SIZE];
	b.tail = &receive_buffer[0]-1;
	retVal = get_buffer_state(&b, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[BUFFER_SIZE], b.head);
	EXPECT_EQ(&receive_buffer[0]-1, b.tail);
	EXPECT_EQ(POINTER_ERROR, err);
}

TEST(get_buffer_state, BUFFER_FULL)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = BUFFER_FULL;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[BUFFER_SIZE-1];
	b.tail = &receive_buffer[0];
	retVal = get_buffer_state(&b, &err);

	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[BUFFER_SIZE-1], b.head);
	EXPECT_EQ(&receive_buffer[0], b.tail);
	EXPECT_EQ(BUFFER_FULL, err);
	EXPECT_EQ(BUFFER_SIZE, retVal);
}

/*
 * 	add_char_to_buffer
 */

TEST(add_char_to_buffer, OK)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	char c = '*';
	error_type err = OK;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[6];
	b.tail = &receive_buffer[0];
	retVal = add_char_to_buffer(&b, c, &err);

	EXPECT_EQ(7, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[7], b.head);
	EXPECT_EQ(&receive_buffer[0], b.tail);
	EXPECT_EQ('*', receive_buffer[6]);
	EXPECT_EQ(OK, err);
}

TEST(add_char_to_buffer, BUFFER_OVER_FLOW)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	char c = '*';
	error_type err = OK;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = ;
	b.tail = ;
	retVal = add_char_to_buffer(&b, c, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(, b.head);
	EXPECT_EQ(, b.tail);
	EXPECT_EQ(BUFFER_OVER_FLOW, err);
}

TEST(add_char_to_buffer, EMPTY_BUFFER)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	char c = '*';
	error_type err = EMPTY_BUFFER;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[3];
	b.tail = &receive_buffer[3];
	retVal = add_char_to_buffer(&b, c, &err);

	EXPECT_EQ(1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[4], b.head);
	EXPECT_EQ(&receive_buffer[3], b.tail);
	EXPECT_EQ(OK, err);
	EXPECT_EQ('*', receive_buffer[3]);
}

TEST(add_char_to_buffer, POINTER_ERROR)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	char c = '*';
	error_type err = POINTER_ERROR;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[BUFFER_SIZE];
	b.tail = &receive_buffer[0];
	retVal = add_char_to_buffer(&b, c, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[BUFFER_SIZE], b.head);
	EXPECT_EQ(&receive_buffer[0], b.tail);
	EXPECT_EQ(POINTER_ERROR, err);
}

TEST(add_char_to_buffer, BUFFER_FULL)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	char c = '*';
	error_type err = BUFFER_FULL;
	int retVal = 0;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[BUFFER_SIZE-1];
	b.tail = &receive_buffer[0];
	retVal = add_char_to_buffer(&b, c, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[BUFFER_SIZE-1], b.head);
	EXPECT_EQ(&receive_buffer[0], b.tail);
	EXPECT_EQ(BUFFER_FULL, err);
}

/*
 * 	get_char_from_buffer
 */

TEST(get_char_from_buffer, OK)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = OK;
	char retVal = -2;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[3];
	b.tail = &receive_buffer[0];
	retVal = get_char_from_buffer(&b, &err);

	EXPECT_EQ('0', retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[3], b.head);
	EXPECT_EQ(&receive_buffer[1], b.tail);
	EXPECT_EQ(OK, err);
}

TEST(get_char_from_buffer, BUFFER_OVER_FLOW)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = OK;
	char retVal = -2;

	b.buffer = receive_buffer;
	b.head = ;
	b.tail = ;
	retVal = get_char_from_buffer(&b, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(, b.buffer);
	EXPECT_EQ(, b.head);
	EXPECT_EQ(, b.tail);
	EXPECT_EQ(BUFFER_OVER_FLOW, err);
}

TEST(get_char_from_buffer, EMPTY_BUFFER)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = EMPTY_BUFFER;
	char retVal = -2;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[3];
	b.tail = &receive_buffer[3];
	retVal = get_char_from_buffer(&b, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[3], b.head);
	EXPECT_EQ(&receive_buffer[3], b.tail);
	EXPECT_EQ(EMPTY_BUFFER, err);
}

TEST(get_char_from_buffer, POINTER_ERROR)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = POINTER_ERROR;
	char retVal = -2;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[BUFFER_SIZE];
	b.tail = &receive_buffer[0]-1;
	retVal = get_char_from_buffer(&b, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[BUFFER_SIZE], b.head);
	EXPECT_EQ(&receive_buffer[0]-1, b.tail);
	EXPECT_EQ(POINTER_ERROR, err);
}

TEST(get_char_from_buffer, BUFFER_FULL)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = BUFFER_FULL;
	char retVal = -2;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[BUFFER_SIZE-1];
	b.tail = &receive_buffer[0];
	retVal = get_char_from_buffer(&b, &err);

	EXPECT_EQ('0', retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[BUFFER_SIZE-1], b.head);
	EXPECT_EQ(&receive_buffer[0], b.tail);
	EXPECT_EQ(OK, err);
}

/*
 * 	print_buffer
 */

TEST(print_buffer, OK)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = OK;
	int retVal = -2;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[3];
	b.tail = &receive_buffer[0];
	retVal = print_buffer(b, &err);

	EXPECT_EQ(3, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[3], b.head);
	EXPECT_EQ(&receive_buffer[0], b.tail);
	EXPECT_EQ(OK, err);

}

TEST(print_buffer, BUFFER_OVER_FLOW)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = OK;
	int retVal = -2;

	b.buffer = receive_buffer;
	b.head = ;
	b.tail = ;
	retVal = print_buffer(b, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(, b.head);
	EXPECT_EQ(, b.tail);
	EXPECT_EQ(BUFFER_OVER_FLOW, err);
}

TEST(print_buffer, EMPTY_BUFFER)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = EMPTY_BUFFER;
	int retVal = -2;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[3];
	b.tail = &receive_buffer[3];
	retVal = print_buffer(b, &err);

	EXPECT_EQ(0, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[3], b.head);
	EXPECT_EQ(&receive_buffer[3], b.tail);
	EXPECT_EQ(EMPTY_BUFFER, err);
}

TEST(print_buffer, POINTER_ERROR)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = POINTER_ERROR;
	char retVal = -2;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[BUFFER_SIZE];
	b.tail = &receive_buffer[0]-1;
	retVal = print_buffer(b, &err);

	EXPECT_EQ(-1, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[BUFFER_SIZE], b.head);
	EXPECT_EQ(&receive_buffer[0]-1, b.tail);
	EXPECT_EQ(POINTER_ERROR, err);
}

TEST(print_buffer, BUFFER_FULL)
{
	unsigned char receive_buffer[BUFFER_SIZE] = {'0','1','2','3','4','5','6'};
	struct buffer_type b;
	error_type err = BUFFER_FULL;
	int retVal = -2;

	b.buffer = receive_buffer;
	b.head = &receive_buffer[BUFFER_SIZE-1];
	b.tail = &receive_buffer[0];
	retVal = print_buffer(b, &err);

	EXPECT_EQ(BUFFER_SIZE, retVal);
	EXPECT_EQ(receive_buffer, b.buffer);
	EXPECT_EQ(&receive_buffer[BUFFER_SIZE-1], b.head);
	EXPECT_EQ(&receive_buffer[0], b.tail);
	EXPECT_EQ(BUFFER_FULL, err);
}
