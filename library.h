#ifndef STDI_LIBRARY_H
#define STDI_LIBRARY_H

#if defined(__cplusplus)
extern "C"
{
#endif

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
char* raw_read_line();

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
char* read_line();

/**
 * @brief Reads a specified number of bytes from standard input (stdin) into a buffer.
 *
 * This function uses a low-level system call to read data from the standard input.
 *
 * @param buffer A pointer to the buffer where the read data will be stored.
 * @param size The maximum number of bytes to read.
 * @return The number of bytes read, or -1 if an error occurs.
 */
ssize_t fread_line(char* buffer, size_t size);

/**
 * @brief Reads a single character from standard input (stdin).
 *
 * This function uses a low-level system call to read one byte from stdin.
 *
 * @return The character read from stdin, or '\0' if an error occurs.
 */
char read_char();

#if defined(__cplusplus)
}
#endif

#endif //STDI_LIBRARY_H