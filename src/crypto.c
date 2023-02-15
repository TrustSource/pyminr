#if defined(_WIN32)
#include "asprintf.h"
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT __attribute__((visibility("default")))
#endif

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "crypto_loads.h"
#include "trie.h"

struct T_TrieNode *root;

/**
 * @brief Gets a token from a valid portion of a char array .
 *
 * @param text The text to search from.
 * @param start Begining of search area. If a valid token is found, the
 * effective begining is returned.
 * @param end Effective index of token end.
 * @param maxLen Bounds the search to a limited index.
 */
char *getNextToken(char *text, uint64_t *start, uint64_t *end,
                   uint64_t maxLen) {
  uint64_t startToken = *start;
  uint64_t endToken = 0;
  char *aux;

  while ((startToken < maxLen) && (indexOf(text[startToken]) == -1))
    startToken++;
  endToken = startToken;
  while ((endToken < maxLen) && (indexOf(text[endToken]) != -1))
    endToken++;

  if (startToken == endToken) {
    *start = startToken;
    *end = endToken;
    return NULL;
  }
  aux = (char *)calloc(1, endToken - startToken + 1);

  memcpy(aux, &text[startToken], endToken - startToken);
  aux[endToken - startToken] = '\0';
  *start = startToken;
  *end = endToken;
  return aux;
}

/**
 * @brief Load algorithms definitions from the auto-generated functions.
 *
 */
API_EXPORT void load_crypto_definitions(void) {
  root = (struct T_TrieNode *)calloc(1, sizeof(struct T_TrieNode));
  load_default_crypto();
}

/**
 * @brief Free the memory allocated for the cryptographic definitions.
 *
 */
API_EXPORT void clean_crypto_definitions(void) { cleanCrypto(root); }

API_EXPORT void find_crypto_algorithms(char *src, uint64_t src_ln,
                                       void (*report_result)(char *,
                                                             unsigned short)) {
  char *auxLn;

  uint64_t start = 0;
  uint64_t end = 0;

  while (start < src_ln) {
    auxLn = getNextToken(src, &start, &end, src_ln);
    if (start == end)
      break;
    else {
      start = end;
      if ((auxLn != NULL) && (strlen(auxLn) > 2)) {
        toLower(auxLn);
        struct T_TrieNode *nodo = searchAlgorithm(auxLn, root);
        if (nodo != NULL && nodo->algorithmName != NULL &&
            report_result != NULL) {
          (*report_result)(nodo->algorithmName, nodo->coding);
        }
      }
    }
    if (auxLn != NULL)
      free(auxLn);
  }
}