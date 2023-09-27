/*
*
*    @Name: Minify JSON C
*    @License: GPL-3.0
*    @Date:     26/09/2023
*    @Repository:   https://github.com/BaseMax/MinifyJSONC
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define static_strlen(string_literal) (sizeof(string_literal) - sizeof(""))

static void skip_oneline_comment(char **input)
{
    *input += static_strlen("//");

    for (; (*input)[0] != '\0'; ++(*input))
    {
        if ((*input)[0] == '\n') {
            *input += static_strlen("\n");
            return;
        }
    }
}

static void skip_multiline_comment(char **input)
{
    *input += static_strlen("/*");

    for (; (*input)[0] != '\0'; ++(*input))
    {
        if (((*input)[0] == '*') && ((*input)[1] == '/'))
        {
            *input += static_strlen("*/");
            return;
        }
    }
}

static void minify_string(char **input, char **output) {
    (*output)[0] = (*input)[0];
    *input += static_strlen("\"");
    *output += static_strlen("\"");

    for (; (*input)[0] != '\0'; (void)++(*input), ++(*output)) {
        (*output)[0] = (*input)[0];

        if ((*input)[0] == '\"') {
            (*output)[0] = '\"';
            *input += static_strlen("\"");
            *output += static_strlen("\"");
            return;
        } else if (((*input)[0] == '\\') && ((*input)[1] == '\"')) {
            (*output)[1] = (*input)[1];
            *input += static_strlen("\"");
            *output += static_strlen("\"");
        }
    }
}

void json_minify(char *json)
{
    char *into = json;

    if (json == NULL)
    {
        return;
    }

    while (json[0] != '\0')
    {
        switch (json[0])
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                json++;
                break;

            case '/':
                if (json[1] == '/')
                {
                    skip_oneline_comment(&json);
                }
                else if (json[1] == '*')
                {
                    skip_multiline_comment(&json);
                }
                else
                {
                    json++;
                }
                break;

            case '\"':
                minify_string(&json, &into);
                break;

            default:
                into[0] = json[0];
                json++;
                into++;
        }
    }

    /* Null-terminate the minified JSON. */
    *into = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    char *inputFilePath = argv[1];
    char *outputFilePath = argv[2];

    FILE *inputFile, *outputFile;
    char *inputBuffer;
    long inputSize, outputSize;

    inputFile = fopen(inputFilePath, "rb");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Get the size of the input file
    fseek(inputFile, 0, SEEK_END);
    inputSize = ftell(inputFile);
    rewind(inputFile);

    // Allocate memory for the input buffer
    inputBuffer = (char *)malloc(inputSize + 1);
    if (inputBuffer == NULL) {
        perror("Error allocating memory for input buffer");
        fclose(inputFile);
        return 1;
    }

    // Read the input file into the input buffer
    fread(inputBuffer, 1, inputSize, inputFile);
    inputBuffer[inputSize] = '\0';
    fclose(inputFile);

    // Minify the JSON
    json_minify(inputBuffer);

    // Open the output file for writing
    outputFile = fopen(outputFilePath, "wb");
    if (outputFile == NULL) {
        perror("Error opening output file");
        free(inputBuffer);
        return 1;
    }

    // Write the minified JSON to the output file
    outputSize = strlen(inputBuffer);
    fwrite(inputBuffer, 1, outputSize, outputFile);
    fclose(outputFile);

    // Free memory
    free(inputBuffer);

    return 0;
}

