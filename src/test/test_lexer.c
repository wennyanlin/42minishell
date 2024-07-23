#include "lexer.h"
#include "minishell.h"
#include "macros.h"

void compare_lst(t_token *expected, t_token *actual, char *description)
{
    if (expected && actual)
    {
        if (expected->word && actual->word)
        {
            int expected_len = ft_strlen(expected->word);
            int actual_len = ft_strlen(actual->word);
            if (expected_len != actual_len || ft_strncmp(expected->word, actual->word, expected_len) != 0)
                printf("\n%s %sFAILED%s: Actual value `%s`, expected `%s`\n", description, RED, RESET, actual->word, expected->word);
        }
        else if (actual->word && !expected->word)
            printf("\n%s %sFAILED%s: Actual value `%s`, Expected NULL\n", description, RED, RESET, actual->word);
        else if (expected->word && !actual->word)
            printf("\n%s %sFAILED%s: Actual NULL, expected value `%s`\n", description, RED, RESET, expected->word);
        

        if (expected->metachar != actual->metachar)
            printf("\n%s %sFAILED%s: Actual token `%i`, expected `%i`\n", description, RED, RESET, actual->metachar, expected->metachar);
        
        if (!actual->next && expected->next)
            printf("\n%s %sFAILED%s: actual is missing some tokens, expected next: [value: `%s`, token: `%i`]\n", description, RED, RESET, expected->next->word, expected->next->metachar);
        else if (actual->next && !expected->next)
            printf("\n%s %sFAILED%s: actual has additional tokens, extra token not expected: [value: `%s`, token: `%i`]\n", description, RED, RESET, actual->next->word, actual->next->metachar);
        else if (!actual->next && !expected->next) 
            printf("\n%s %sPASSED%s\n", description, GREEN, RESET);
        else
            compare_lst(expected->next, actual->next, description);
    }
    else if (!actual)
    {
        printf("\n%s %sFAILED%s: Actual was NULL, expected value: `%s` token: %d\n", description, RED, RESET, expected->word, expected->metachar);
    } if (!expected)
    {
        printf("\n%s %sFAILED%s: Actual was not NULL but NULL was expected, Actual value: `%s` token: %d\n", description, RED, RESET, actual->word, actual->metachar);
    }

}

void test_lexer_should_return_empty_when_input_is_empty(void)
{
    char *input = "";
    t_token *result;
    t_token expected;

    result = tokenize(input);

    expected.word = NULL;
    expected.metachar = -1;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return empty when input is empty");
    ft_free_lst(result);
}

void test_lexer_should_return_single_word(void)
{
    char *input;
    t_token *result;
    t_token expected;

    input =  "echo";
    result = tokenize(input);

    expected.word = "echo";
    expected.metachar = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return single word");
    ft_free_lst(result);
}

void test_lexer_should_return_chars_with_double_quotes(void)
{
    char *input;
    t_token *result;
    t_token expected;

    input =  "\"echo\"";
    result = tokenize(input);

    expected.word = "\"echo\"";
    expected.metachar = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return chars_with_double_quotes");
    ft_free_lst(result);
}

void test_lexer_should_return_chars_with_single_quotes(void)
{
    char *input;
    t_token *result;
    t_token expected;

    input =  "\'echo\'";
    result = tokenize(input);

    expected.word = "\'echo\'";
    expected.metachar = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return chars_with_single_quotes");
    ft_free_lst(result);
}

void test_lexer_should_return_word_with_single_quotes_in_mid_word(void)
{
    char *input;
    t_token *result;
    t_token expected;

    input =  "echo\'hello\'";
    result = tokenize(input);

    expected.word = "echo\'hello\'";
    expected.metachar = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return chars_and_single_quotes");
    ft_free_lst(result);
}

void test_lexer_should_return_chars_with_double_quotes_in_mid_word(void)
{
    char *input;
    t_token *result;
    t_token expected;

    input =  "echo\"hello\"";
    result = tokenize(input);

    expected.word = "echo\"hello\"";
    expected.metachar = 0;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return chars and double quotes");
    ft_free_lst(result);
}

void test_lexer_should_return_chars_and_multi_closed_quotes(void)
{
    char *input;
    t_token *result;
    t_token expected;
    t_token expected_second;

    input =  "\"\"\"echo\" hi";
    result = tokenize(input);

    expected.word = "\"\"\"echo\"";
    expected.metachar = 0;
    expected_second.word = "hi";
    expected_second.metachar = 0;
    expected.next = &expected_second;
    expected.prev = NULL;
    expected_second.next = NULL;
    expected_second.prev = &expected;

    compare_lst(&expected, result, "Should return chars and multi closed quotes");
    ft_free_lst(result);
}

void test_lexer_should_return_multiple_types_of_chars(void)
{
    char *input;
    t_token *result;
    t_token expected;
    t_token expected_second;

    input =  "echo \" |$USER|\"";
    result = tokenize(input);

    expected.word = "echo";
    expected.metachar = 0;
    expected_second.word = "\" |$USER|\"";
    expected_second.metachar = 0;
    expected.next = &expected_second;
    expected.prev = NULL;
    expected_second.next = NULL;
    expected_second.prev = &expected;

    compare_lst(&expected, result, "Should return multiple types of chars");
    ft_free_lst(result);
}

void test_lexer_should_return_metachars(void)
{
    char *input = "|";
    t_token *result;
    t_token expected;

    result = tokenize(input);

    expected.word = NULL;
    expected.metachar = 1;
    expected.next = NULL;
    expected.prev = NULL;

    compare_lst(&expected, result, "Should return only metachars");
    ft_free_lst(result);
}


void test_lexer_should_return_unclose_single_quote(void)
{
    char *input = "echo \"'\"";
    t_token *result;
    t_token expected;
    t_token expected_second;

    result = tokenize(input);

    expected.word = "echo";
    expected.metachar = 0;
    expected_second.word = "\"'\"";
    expected_second.metachar = 0;
    expected.next = &expected_second;
    expected.prev = NULL;
    expected_second.next = NULL;
    expected_second.prev = &expected;

    compare_lst(&expected, result, "Should unclose_single_quote");
    ft_free_lst(result);
}

void test_lexer_should_return_word_and_metachars(void)
{
    char *input = "ls|grep";
    t_token *result;
    t_token expected;
    t_token two;
    t_token three;

    result = tokenize(input);

    expected.word = "ls";
    expected.metachar = 0;
    two.word = NULL;
    two.metachar = 1;
    three.word = "grep";
    three.metachar = 0;
    expected.next = &two;
    expected.prev = NULL;
    two.next = &three;
    two.prev = &expected;
    three.next = NULL;
    three.prev = &two;
    compare_lst(&expected, result, "Should return only metachars");
    ft_free_lst(result);
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
    test_lexer_should_return_unclose_single_quote();
}