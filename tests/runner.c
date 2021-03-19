/**
    runner.c
    By: Ammar Ratnani

    Implementation file for running the tests. It simply loops over
    `SUITE_FUNCS` and calls all the functions, running the suites returned. It
    then outputs the data as needed.
*/

#include <stdio.h>
#include "runner.h"


Suite *(*SUITE_FUNCS[])(void) = {
    suite_bare,
    NULL
};


int main(void) {

    // Set up a suite runner
    // Initially null - have to take care of in the loop
    SRunner *runner = NULL;

    // Loop over all the suite functions
    // Remember that the array is terminated by a null, and will therefore
    //  always have at least one element.
    for(Suite *(**sf)(void) = SUITE_FUNCS; *sf != NULL; sf++) {
        // Get the suite to add
        Suite *a = (**sf)();
        // Initialize runner if needed
        if(runner == NULL) {
            runner = srunner_create(a);
        } else {
            srunner_add_suite(runner, a);
        }
    }

    // Run and return
    srunner_run_all(runner, CK_VERBOSE);
    return 0 != srunner_ntests_failed(runner);
}
