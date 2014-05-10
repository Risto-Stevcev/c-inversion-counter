#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "inversion-counter.h"


long int *inversions;

void
array_cmp(int *arr1, int *arr2, int arrlen)
{
    for (int i = 0; i < arrlen; i++)
        CU_ASSERT(arr1[i] == arr2[i]);
}

int
setup_suite1(void)
{
    inversions = (long int *) calloc( 1, sizeof( long int ) );
    return 0;
}

int
teardown_suite1(void)
{
    free( inversions );
    return 0;
}

void
test_merge_and_count_suite1(void)
{
    int list[8] = {0};
    int sorted_list[] = {1,2,3,4,5,7,19,21};

    int left[] = {1,2,4,7};
    int right[] = {3,5,19,21};

    merge_and_count( left, 4, right, 4, list, inversions );
    array_cmp( list, sorted_list, 8 );
}

void
test_inversion_counter_suite1(void)
{
    int list[] = {1,4,5,2,9,44,7,12,34};
    int merged_list[] = {1,2,4,5,7,9,12,34,44};

    inversion_counter( list, 9, inversions );

    CU_ASSERT( *inversions == 9 );
    array_cmp( list, merged_list, 9 );   
}


int
main ()
{
    CU_pSuite pSuite1 = NULL;

    /* initialize registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add suites to registry */
    pSuite1 = CU_add_suite("Test inversion algorithm", setup_suite1, teardown_suite1);

    if (pSuite1 == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add tests to suite */
    if (  (NULL == CU_add_test(pSuite1, "test merge and count", test_merge_and_count_suite1))
       || (NULL == CU_add_test(pSuite1, "test inversion counter", test_inversion_counter_suite1))  )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* run tests */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
