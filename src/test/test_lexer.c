#include "lexer.h"
#include "minishell.h"

void compare_lst(t_lst *expected, t_lst *actual, char *description)
{
    if (expected && actual)
    {
        if (expected->value && actual->value)
        {
            int expected_len = ft_strlen(expected->value);
            int actual_len = ft_strlen(actual->value);
            if (expected_len != actual_len || ft_strncmp(expected->value, actual->value, expected_len) != 0)
                printf("\n%s FAILED: Actual value `%s`, expected `%s`\n", description, actual->value, expected->value);
        }
        else if (actual->value && !expected->value)
            printf("\n%s FAILED: Actual value `%s`, Expected NULL\n", description, actual->value);
        else if (expected->value && !actual->value)
            printf("\n%s FAILED: Actual NULL, expected value `%s`\n", description, expected->value);
        

        if (expected->token != actual->token)
            printf("\n%s FAILED: Actual token `%i`, expected `%i`\n", description, actual->token, expected->token);
        
        if (!actual->next && expected->next)
            printf("\n%s FAILED: actual is missing some tokens, expected next: [value: `%s`, token: `%i`]\n", description, expected->next->value, expected->next->token);
        else if (actual->next && !expected->next)
            printf("\n%s FAILED: actual has additional tokens, extra token not expected: [value: `%s`, token: `%i`]\n", description, actual->next->value, actual->next->token);
        else if (!actual->next && !expected->next) 
            printf("\n%s PASSED\n", description);
        else
            compare_lst(expected->next, actual->next, description);
    }
    else if (!actual)
    {
        printf("\n%s FAILED: Actual was NULL, expected value: `%s` token: %d\n", description, expected->value, expected->token);
    } if (!expected)
    {
        printf("\n%s FAILED: Actual was not NULL but NULL was expected, Actual value: `%s` token: %d\n", description, actual->value, actual->token);
    }

}

void test_lexer_should_return_empty_when_input_is_empty(void)
{
    char *input = "";
    t_lst *result;
    t_lst expected;

    result = handle_input(input);

    expected.value = NULL;
    expected.token = -1;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return empty when input is empty");
}

void test_lexer_should_return_single_word(void)
{
    char *input;
    t_lst *result;
    t_lst expected;

    input =  "echo";
    result = handle_input(input);

    expected.value = "echo";
    expected.token = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return single word");
}

void test_lexer_should_return_chars_with_double_quotes(void)
{
    char *input;
    t_lst *result;
    t_lst expected;

    input =  "\"echo\"";
    result = handle_input(input);

    expected.value = "\"echo\"";
    expected.token = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return chars_with_double_quotes");
}

void test_lexer_should_return_chars_with_single_quotes(void)
{
    char *input;
    t_lst *result;
    t_lst expected;

    input =  "\'echo\'";
    result = handle_input(input);

    expected.value = "\'echo\'";
    expected.token = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return chars_with_single_quotes");
}

void test_lexer_should_return_word_with_single_quotes_in_mid_word(void)
{
    char *input;
    t_lst *result;
    t_lst expected;

    input =  "echo\'hello\'";
    result = handle_input(input);

    expected.value = "echo\'hello\'";
    expected.token = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return chars_and_single_quotes");
}

void test_lexer_should_return_chars_with_double_quotes_in_mid_word(void)
{
    char *input;
    t_lst *result;
    t_lst expected;

    input =  "echo\"hello\"";
    result = handle_input(input);

    expected.value = "echo\"hello\"";
    expected.token = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return chars and double quotes");
}

void test_lexer_should_return_chars_and_multi_closed_quotes(void)
{
    char *input;
    t_lst *result;
    t_lst expected;
    t_lst expected_second;

    input =  "\"\"\"echo\" hi";
    result = handle_input(input);

    expected.value = "\"\"\"echo\"";
    expected.token = 0;
    expected_second.value = "hi";
    expected_second.token = 0;
    expected.next = &expected_second;
    expected.prev = NULL;
    expected_second.next = NULL;
    expected_second.prev = &expected;

    compare_lst(&expected, result, "Should return chars and multi closed quotes");
}

void test_lexer_should_return_multiple_types_of_chars(void)
{
    char *input;
    t_lst *result;
    t_lst expected;
    t_lst expected_second;

    input =  "echo \" |$USER|\"";
    result = handle_input(input);

    expected.value = "echo";
    expected.token = 0;
    expected_second.value = "\" |$USER|\"";
    expected_second.token = 0;
    expected.next = &expected_second;
    expected.prev = NULL;
    expected_second.next = NULL;
    expected_second.prev = &expected;

    compare_lst(&expected, result, "Should return multiple types of chars");
}

void test_lexer_should_return_metachars(void)
{
    char *input = "|";
    t_lst *result;
    t_lst expected;

    result = handle_input(input);

    expected.value = NULL;
    expected.token = 1;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return only metachars");
}

void test_lexer_should_return_word_and_metachars(void)
{
    char *input = "ls|grep";
    t_lst *result;
    t_lst expected;
    t_lst two;
    t_lst three;

    result = handle_input(input);

    expected.value = "ls";
    expected.token = 0;
    two.value = NULL;
    two.token = 1;
    three.value = "grep";
    three.token = 0;
    expected.next = &two;
    expected.prev = NULL;
    two.next = &three;
    two.prev = &expected;
    three.next = NULL;
    three.prev = &two;
    compare_lst(&expected, result, "Should return only metachars");
}

void test_lexer(void)
{
    test_lexer_should_return_empty_when_input_is_empty();
    test_lexer_should_return_single_word();
    test_lexer_should_return_chars_with_double_quotes();
    test_lexer_should_return_chars_with_single_quotes();
    test_lexer_should_return_word_with_single_quotes_in_mid_word();
    test_lexer_should_return_chars_with_double_quotes_in_mid_word();
    test_lexer_should_return_chars_and_multi_closed_quotes();
    test_lexer_should_return_multiple_types_of_chars();
    test_lexer_should_return_metachars();
    test_lexer_should_return_word_and_metachars();
}