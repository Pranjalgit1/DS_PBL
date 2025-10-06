# DS_PBL
3rd sem data structures project : Advanced dictionary

# Data Structures Used
- Trie: To store words efficiently and support fast search and autocomplete.
- Linked List: To store multiple meanings/synonyms for each word.
- Hash Map: (Optional) For quick word-frequency tracking.
- Heap (Priority Queue): To maintain top searched words (most frequent lookups).
- Dynamic Arrays: For loading dictionary data from file and managing results.
- DP Table (2D Array): For computing edit distance in spell checker.
- Structs: For TrieNode, WordEntry, and Stats tracking.
# Step-by-Step Algorithm
1. Initialize Dictionary
- Load words and meanings from file into Trie.
- Build supporting structures for frequency and synonyms.

2. Insert Word
- Traverse characters into Trie, creating nodes if needed.
- Mark end-of-word and attach meaning/synonyms.
- Update file storage for persistence.

3. Search Word
- Traverse Trie by characters.
- If found, return meaning and increment search frequency.
- If not found, trigger spell-check suggestions.

4. Autocomplete
- Traverse Trie to prefix node.
- Perform DFS from that node to collect all completions.
- Print results with meanings.

5. Spell Checker
- Use dynamic programming to compute edit distance between input and words in dictionary.
- Suggest words within a given edit distance threshold.

6. Top Words
- Use max-heap to return most searched words.
- Update frequency count on each successful search.

7. Save and Exit
- Dump dictionary content and metadata back to file for persistence.
Complexity
Lookup: O(L), where L is length of word.
Insertion: O(L).
Autocomplete: O(L + K), where K is number of completions.
Spell Check: O(N * L^2), where N is number of words, L is word length (using DP).
Heap Operations (Top words): O(log N).
Space: O(N * L) for Trie nodes and meanings.

# Basic CLI (Optional)
- Menu-driven interface with options:
  1. Search word
  2. Add word
  3. Delete word
  4. Autocomplete suggestions
  5. Spell check suggestions
  6. Show most searched words
- Input: user queries or file with words.
- Output: meanings, suggestions, and statistics.
# Learning Value
- Strong understanding of Tries and their applications in dictionaries.
- Practice with heaps, hash maps, and dynamic programming.
- Learn persistence by saving/loading dictionary to/from files.
- Gain experience with autocomplete and spell check algorithms.
- Reinforce modular programming in C with multiple components.
# Possible Extensions
- Multilingual dictionary support (store meanings in multiple languages).
- Add thesaurus-like functionality with synonyms and antonyms.
- Compression: Use Huffman coding to compress stored dictionary.
- Graphical User Interface (GUI) for interactive search and suggestions.
- Networking: Allow multiple clients to query dictionary server.
- Voice-based input using speech-to-text libraries.
- Integration with text editors for real-time spell check and autocomplete.
