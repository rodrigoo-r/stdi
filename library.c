#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "library.h"

#ifndef STDI_READ_LINE_BUFFER_SIZE
#define STDI_READ_LINE_BUFFER_SIZE 250
#endif

#ifndef EOF
#define EOF (-1)
#endif

// Define true/false values
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/**
 * @brief Reads a specified number of bytes from standard input (stdin) into a buffer.
 *
 * This function uses a low-level system call to read data from the standard input.
 *
 * @param buffer A pointer to the buffer where the read data will be stored.
 * @param size The maximum number of bytes to read.
 * @return The number of bytes read, or -1 if an error occurs.
 */
ssize_t fread_line(char* buffer, const size_t size)
{
    return syscall(SYS_read, STDIN_FILENO, buffer, size);
}

/**
 * @brief Reads a line of input from standard input (stdin) using a low-level system call.
 *
 * This function dynamically allocates memory to store the input line. It reads characters
 * one by one until a newline or EOF is encountered. If the buffer size is exceeded, it
 * reallocates memory to accommodate additional characters.
 *
 * @note This function is marked as deprecated due to its computational expense and reliance
 *       on low-level system calls. Use with caution.
 *
 * @return A pointer to the dynamically allocated string containing the input line, or NULL
 *         if an error occurs (e.g., memory allocation failure or read error).
 *
 * @warning The caller is responsible for freeing the memory allocated for the returned string.
 */
// @deprecated - Computationally expensive, use at your own risk.
char* raw_read_line()
{
    // Allocate the string (+1 for the null terminator)
    char *buffer = malloc(sizeof(char) * (STDI_READ_LINE_BUFFER_SIZE + 1));

    // Check for allocation failure
    if (buffer == NULL)
    {
        return NULL;
    }

    size_t written = 0;
    size_t length = 0;

    // Keep reading until we find a newline or EOF
    while (TRUE)
    {
        // Check if we have enough space
        if (written == STDI_READ_LINE_BUFFER_SIZE)
        {
            // Reallocate immediately (+1 for the null terminator)
            char *new_buffer = realloc(buffer, sizeof(char) * (STDI_READ_LINE_BUFFER_SIZE + length + 1));
            if (new_buffer == NULL)
            {
                free(buffer);
                return NULL;
            }

            // Reassign the buffer
            buffer = new_buffer;
            written = 0;
        }

        // Make a syscall to get a character fom the stdin
        char c;
        const ssize_t bytes_read = fread_line(&c, 1);

        // Check for failure
        if (bytes_read == -1)
        {
            free(buffer);
            return NULL;
        }

        // Stop if we find a newline or EOF
        if (c == '\0' || c == EOF)
        {
            // Add a null terminator
            buffer[length] = '\0';
            break;
        }

        // Write the character
        buffer[length] = c;

        written++;
        length++;
    }

    return buffer;
}

/**
 * @brief Reads a line of input from standard input (stdin) using a low-level system call.
 *
 * This function dynamically allocates memory to store the input line. It reads characters
 * until a newline or EOF is encountered. If the buffer size is exceeded, it reallocates
 * memory to accommodate additional characters.
 *
 * @note This function is similar to `raw_read_line` but uses a more efficient approach
 *       for reading chunks of data instead of single characters.
 *
 * @return A pointer to the dynamically allocated string containing the input line, or NULL
 *         if an error occurs (e.g., memory allocation failure or read error).
 *
 * @warning The caller is responsible for freeing the memory allocated for the returned string.
 */
char* read_line()
{
    // Advice: call fflush(stdout) before calling read_line()
    // Or flush_write_buffer() from stdo which is compatible with
    // fluentlibc

    // Allocate a buffer (+1 for null terminator)
    char *buffer = malloc(sizeof(char) * (STDI_READ_LINE_BUFFER_SIZE + 1));

    // Check for allocation failure
    if (buffer == NULL)
    {
        return NULL;
    }

    // Initialize tracking variables
    size_t written = 0;
    size_t length = 0;

    // Read until we find EOF
    while (TRUE)
    {
        // Check if we have to reallocate the buffer
        if (written == STDI_READ_LINE_BUFFER_SIZE)
        {
            // Reallocate immediately (+1 for null terminator)
            char *new_buffer = realloc(buffer, sizeof(char) * (STDI_READ_LINE_BUFFER_SIZE + length + 1));
            // Check for realloc errors
            if (new_buffer == NULL)
            {
                free(buffer);
                return NULL;
            }

            written = 0;
            buffer = new_buffer;
        }

        // Check if we have to read
        if (written == 0)
        {
            // Increment the counter
            const ssize_t bytes_read = fread_line(
                buffer + length,
                STDI_READ_LINE_BUFFER_SIZE - length
             );

            // Handle errors
            if (bytes_read == -1)
            {
                free(buffer);
                return NULL;
            }

            // Check if no bytes were read
            if (bytes_read == 0)
            {
                // Add a null terminator
                buffer[length] = '\0';
                return buffer;
            }

            written += bytes_read;
            length += bytes_read;
        }

        // Check if we have an EOF or newline
        if (length > 0 && (buffer[length - 1] == EOF || buffer[length - 1] == '\n'))
        {
            // Add a null terminator
            buffer[length - 1] = '\0';
            return buffer;
        }
    }
}

/**
 * @brief Reads a single character from standard input (stdin).
 *
 * This function uses a low-level system call to read one byte from stdin.
 *
 * @return The character read from stdin, or '\0' if an error occurs.
 */
char read_char()
{
    char c;
    const ssize_t bytes_read = fread_line(&c, 1);
    // Handle errors
    if (bytes_read == 1)
    {
        return c;
    }

    return '\0';
}