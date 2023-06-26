# 5words-25uniqueletters
based on Stand-up Maths video, using graph theory and bit manipulation in C to find 5 5 letter words with 25 unique letters

# Pre-processing 

firstly I took a list of all 5 letter words considered to be valid by wordle, you can find them in the ``` words.txt ``` file (about 15k words).
I applied ```first.c``` on the words to filter out all the words with repeated letters like "hello" "witty" and the result is stored in ``` wordsFiltered1.txt ``` file.
Then I applied ```second.c``` on the filtered words to remove the anagrams and that made the words about 6.7k stored in ```NoAnagram.txt``` file.
Now that all the words have distinct letters and no anagrams exist we change the characters to a custom 26 bit binary representation.

# 26 bit custom binary representation
There are 26 bits corresponding to 26 alphabet characters and if a bit is high that means there is a letter there, and since I removed words with repeated letters then there will be no bits that need to be overlapped with other bits.

for example "zebra" will be

  abcdefghijklmnopqrstuvwxyz
 
 11001000000000000100000001  which will then be stored in a file called ``` binaryRep.txt``` as an unsigned integer the code for this is in the ```third.c``` file.
This was done to decrease code run time as all I need to do is to do bitwise AND ```&``` to see if the two words have a matching letter or not. 
# Post-processing
in the ```final.c ``` file Initially, the program creates a graph from the word representations. If two words' binary representations don't overlap in letters, they are connected in the graph. An adjacency matrix is used to represent the graph. The Bron-Kerbosch technique is then used to search the graph for the most maximum cliques. Each pair of connected nodes forms a clique, which is a subset of nodes. Since they represent word combinations with 25 different letters, cliques of size 5 are of particular importance to us in this situation.The three sets R (current clique), P (potential candidates to add to the clique), and X (excluded candidates) are taken into account by the Bron-Kerbosch method in order to recursively locate all possible cliques. The technique employs several optimisations to prevent computations that are not essential.

When the process is finished, the program prints any word combinations that contain 25 different letters. If not, a notice stating that no such combinations were discovered is displayed.
one solution is ![image](https://github.com/samalouty/5words-25uniqueletters/assets/128055267/702f87a7-9d40-4559-a4f2-2385a5b3662f)
