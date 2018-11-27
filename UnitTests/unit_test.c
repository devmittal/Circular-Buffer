/*****************************************************************************
​ ​* ​ ​ @file​ ​  unit_test.c
​ * ​ ​ @brief​ ​ This file consists of the unit test functionality with different
 *           test cases. 
 *   @Tools_Used GCC
​ * ​ ​ @author​  Devansh Mittal, ​​Souvik De
​ * ​ ​ @date​ ​ November 27th, 2018
​ * ​ ​ @version​ ​ 1.0
*****************************************************************************/

#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../inc/ring.h"

/* Create buffer test */
void test_create_buffer(void)
{
	/* Check if the structure pointer pointing to space allocated to buffers is not null */
	CU_ASSERT_PTR_NOT_NULL(create_buffers(3));
	CU_ASSERT_PTR_NOT_NULL(ring_collector);
}

/* initialize Buffer Test */
void test_init_buffer(void)
{
	/* Check if the initialization of the 0th buffer is successful with length 3  and the resultant pointer is NULL*/
	CU_ASSERT_EQUAL(init(3,0,3), 1);
	CU_ASSERT_PTR_NULL(ring);

	/* Check if the initialization of the 2nd buffer is successful with length 5  and the resultant pointer is NULL*/
	CU_ASSERT_EQUAL(init(5,2,3), 1);
	CU_ASSERT_PTR_NULL(ring);

	/* Check if the allocation of the 1st buffer with a large size is successful and the resultant pointer is NULL*/
	CU_ASSERT_EQUAL(init(100000,1,3), 1);
	CU_ASSERT_PTR_NULL(ring);

	/* Check if initialization of buffer greater than that allocated is unsuccessful */
	CU_ASSERT_EQUAL(init(5,4,3), -1);
}

/* Select buffer Test */
void test_select_buffer(void)
{
	/* Check that selecting invalid buffer results in null pointer */
	select_buffer(5);
	CU_ASSERT_PTR_NULL(ring);

	/* Check that selecting valid buffer results in non null pointer */
	select_buffer(0);
	CU_ASSERT_PTR_NOT_NULL(ring);
}

/* insert buffer test */
void test_insert_buffer(void)
{
	int i;
	
	/* Check if insertion of data is successful till the size limit */ 
	for(i=0; i<3;i++)
	{
		CU_ASSERT_EQUAL(insert_data(ring, 1), 1);
	}

	/* Check if insertion of data is unsuccessful after the size limit */
	CU_ASSERT_EQUAL(insert_data(ring,1), 0);
}

/* remove buffer test */
void test_remove_buffer(void)
{
	int i;
	char data;

	/* Check if removal of data is successful till data exists */ 
	for(i=0; i<3;i++)
	{
		CU_ASSERT_EQUAL(remove_data(ring,&data), 1);
	}

	/* Check if removal of data is unsuccessful when no data exists */
	CU_ASSERT_EQUAL(remove_data(ring,&data), 0);
}

/* display buffer test */
void test_display_buffer(void)
{
	char data;

	/* Check if successful display of data when data exists in buffer */
	insert_data(ring, 1);	
	CU_ASSERT_EQUAL(entries(ring), 1);

	/* Check if unsuccessful display of data when no data exists in buffer */
	remove_data(ring,&data);
	CU_ASSERT_EQUAL(entries(ring), 0);
}

/* resize buffer test */
void test_resize_buffer(void)
{	
	resize(5,0,3);

	/* Checks if resizing the buffer is successful and results in non null pointer */ 
	CU_ASSERT_PTR_NOT_NULL(ring);

	/* Checks if the resized buffer length is the one input by user */
	CU_ASSERT_EQUAL(ring->Length,5);
}

int main()
{
	/* Initialize CUnit test registry */
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_pSuite suite = NULL;
	
	/* Add suite to the registry */
	suite = CU_add_suite("Circular Buffer Unit Testing", NULL, NULL);

	if(suite == NULL)
		return CU_get_error();
	
	/* Add tests to the suite */
	if(NULL == CU_add_test(suite, "Create Buffers Test", test_create_buffer) ||
	   NULL == CU_add_test(suite, "Initialize buffer Test", test_init_buffer) ||
	   NULL == CU_add_test(suite, "Select Buffer Test", test_select_buffer) ||
	   NULL == CU_add_test(suite, "Insert Test", test_insert_buffer) ||
	   NULL == CU_add_test(suite, "Remove Test", test_remove_buffer) ||
	   NULL == CU_add_test(suite, "Display Buffer Test", test_display_buffer) ||
	   NULL == CU_add_test(suite, "Resize Buffer Test", test_resize_buffer))
		return CU_get_error();

	/* Run all the tests in basic mode */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	if(CUE_SUCCESS != CU_basic_run_tests())
		return CU_get_error();

	/* Run all the tests in automated mode and send the results to the XML file called CircularBuffer */
	CU_set_output_filename("CircularBuffer");
	CU_automated_run_tests();

	/* Clean the registry */
	CU_cleanup_registry();
}
