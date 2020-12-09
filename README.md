C Language Unit Test Utility
===============================

C-unit is a unit test utility designed for C language.
Other languages contain exception capture mechanism, which is commonly
used as the basic in a unit test utility. However, there is no library
implementation for exception capture in C language. This project
implements TRY/CATCH primitive and uses it to implement a unit test
facility.

Build cunit
--------------

To compile this project:

    $ ./autogen.sh
    $ make

Then run the sample to see the effect:

    $ ./src/sample/cunit_sample
    sample_case_success:......................Success
    sample_case_failure:........................Error
    cunit_sample.c(58), Value(char) 'b' does not equal 'a'.
    sample_case_error:..........................Error
    cunit_sample.c(100), Exceptions will be caught as errors.
    sample_case_error:..........................Error
    cunit_sample.c(100), Exceptions will be caught as errors.
    sample_case_failure:........................Error
    cunit_sample.c(58), Value(char) 'b' does not equal 'a'.
    sample_case_success:......................Success
    sample_case_success:......................Success
    sample_case_failure:........................Error
    cunit_sample.c(58), Value(char) 'b' does not equal 'a'.
    sample_case_error:..........................Error
    cunit_sample.c(100), Exceptions will be caught as errors.
    run 9 cases. success 3, failure 3, error 3.
    total time 0.2 seconds
    sample_case_success:......................Success
    run 1 cases. success 1, failure 0, error 0.
    total time 0.1 seconds

C unit framework captures test failures, and stops executing the rest of
the same test, and proceeds to the next tests. At the end of the test
suite, C unit framework reports total success/failures.

Use cunit
------------

It's suggested to learn C unit functionalities via
src/sample/cunit_sample.c.

First, let's check its "main" entry:

    int main(int argc, char **argv) {
        /* run test suite */
        CUNIT_RUN_SUITE(sample_suite_mix);
        /* run single test case */
        CUNIT_RUN_CASE(sample_case_success);
        return 0;
    }

It invokes 2 runners, the first runner demonstrates how a test suite can be
run, and the second runner demonstrates how a single test can be run by
the cunit.

Second, let's check how a test suite can be organized:
The first one is a statically defined test suite:

    CUNIT_BEGIN_SUITE(sample_suite_mix)
        CUNIT_INCLUDE_SUITE(sample_suite_1)
        CUNIT_INCLUDE_SUITE(sample_suite_2)
        CUNIT_INCLUDE_CASE(sample_case_success)
        CUNIT_INCLUDE_CASE(sample_case_failure)
        CUNIT_INCLUDE_CASE(sample_case_error)
    CUNIT_END_SUITE

A test suite can include either test suites or test cases.

The below code demonstrates how a suite is dynamically created, it's
useful when the tester wants to include different cases according to some
test philosophy.

    Test sample_suite_1() {
        /* create test suite */
        TestSuite suite = CUNIT_NEW_SUITE(sample_suite_1);
        /* add test cases to the suite */
        CUNIT_ADD_CASE(suite, sample_case_success);
        CUNIT_ADD_CASE(suite, sample_case_failure);
        CUNIT_ADD_CASE(suite, sample_case_error);
        return (Test)suite;
    }

Third, let's examine a test case:

    void CUNITCBK sample_case_failure(void) {
        char b = 'b';
        CUNIT_ASSERT_EQUALS(char, 'a', b);
        /* never reached endless loop */
        while (1) ;
    }

The interesting thing is, cunit automatically fails a case from where it's
false asserted and the follow-up code in the same test case will never be
executed.

Last, let's do more fun with cunit:

    void CUNITCBK sample_case_error(void) {
        CUNIT_TRY {
            /*
             * Use CUNIT_RAISE_EXCEPTION create and throw a new exception.
             * This action will stop TestRunner and cause an TestError.
             */
            CUNIT_RAISE_EXCEPTION("Exceptions will be caught as errors.");
        } CUNIT_CATCH(e) {
            /*
             * Exception and Assertions can be caught use this CUNIT_TRY,
             * CUNIT_CATCH scope. Caller can use CUNIT_DELETE_THROWABLE
             * to destroy caught Throwable instance, or can throw it back
             * to cunit TestRunner using CUNIT_THROW.
             */
            CUNIT_THROW(e);
        } CUNIT_END_CATCH
    }

Yeah! You can freeely to choose to catch the test failure and let the test
to continue or throw it back to cunit runner to stop the test. This is
done by the cunit TRY/CATCH mechanism.

Miscellaneous information
----------------------------

This project also supports Windows Visual Studio environment, and contains
an MS VC plugin to invoke the test cases.

This project has been successfully used in many NEC offshore software
projects delivered by NEC-CAS.
