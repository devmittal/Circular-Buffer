#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../inc/ring.h"

/*int init(void)
{
	create_buffers(3);
	init(3,0);
	init(5,1);
	init(10,2);
	select_buffer(0);
	return 0;
}*/

void test_create_buffer(void)
{
	CU_ASSERT_PTR_NOT_NULL(create_buffers(3));
	CU_ASSERT_PTR_NOT_NULL(ring_collector);
}

void test_init_buffer(void)
{
	CU_ASSERT_EQUAL(init(3,0), 1);
	CU_ASSERT_EQUAL(ring->Length, 3);
	CU_ASSERT_PTR_NOT_NULL(ring);
}

void test_select_buffer(void)
{
	CU_ASSERT_EQUAL(select_buffer(0), 1);
	CU_ASSERT_PTR_NOT_NULL(ring);
}

void test_insert_buffer(void)
{
	int i;
	for(i=0; i<3;i++)
	{
		CU_ASSERT_EQUAL(insert_data(ring, 1), 1);
	}
	CU_ASSERT_EQUAL(insert_data(ring,1), 0);
}

void test_remove_buffer(void)
{
	int i;
	char data;
	for(i=0; i<3;i++)
	{
		CU_ASSERT_EQUAL(remove_data(ring,&data), 1);
	}
	CU_ASSERT_EQUAL(remove_data(ring,&data), 0);
}

void test_display_buffer(void)
{
	char data;
	insert_data(ring, 1);	
	CU_ASSERT_EQUAL(entries(ring), 1);
	remove_data(ring,&data);
	CU_ASSERT_EQUAL(entries(ring), 0);
}

int main()
{
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_pSuite suite = NULL;
	
	suite = CU_add_suite("Circular Buffer Unit Testing", NULL, NULL);

	if(suite == NULL)
		return CU_get_error();

	if(NULL == CU_add_test(suite, "Create Buffers Test", test_create_buffer) ||
	   NULL == CU_add_test(suite, "Initialize buffer Test", test_init_buffer) ||
	   NULL == CU_add_test(suite, "Select Buffer Test", test_select_buffer) ||
	   NULL == CU_add_test(suite, "Insert Test", test_insert_buffer) ||
	   NULL == CU_add_test(suite, "Remove Test", test_remove_buffer) ||
	   NULL == CU_add_test(suite, "Display Buffer Test", test_display_buffer))
		return CU_get_error();

	CU_basic_set_mode(CU_BRM_VERBOSE);
	if(CUE_SUCCESS != CU_basic_run_tests())
		return CU_get_error();

	CU_set_output_filename("CircularBuffer");
	CU_automated_run_tests();

	CU_cleanup_registry();
}
