/**API containing spell check functions
 * @author Jason Quon
 * @email jquon@uoguelph.ca
 * @student number 0969675
 */

#include <stdio.h>
#include <stdlib.h>
#include "HashTableAPI.h"

/**Function hashes a string into an integer
 *@param data - pointer to a string to hash
 *@return integer representation of a string
 **/
int createKey(char *data);

/**Function reads a line from a text file and adds it to a hash table
 *@param file - file to read from
 *@param hashTable - table to add word to
 **/
void readFile(FILE* file, HTable* hashTable);

/**Function allows the user to add a word to the hash table
 *@param hashtable - table to add word to
 **/
void addWord(HTable* hashTable);

/**Function allows the user to remove a word if it exists
 *@param hashTable - table to remove word from
 **/
void removeWord(HTable* hashTable);

/**Runs the spell check simulation
 *@param hashTable - table to compare words to
 **/
void spellCheck(HTable* hashTable);
