# 📚 Advanced Dictionary System# DS_PBL# DS_PBL



A high-performance dictionary implementation using **Trie data structure** in C with both **CLI** and **GUI** interfaces.3rd sem data structures project: Advanced Dictionary.



---



## ✨ Features## Milestone 1: Core Dictionary Implementation ✅# Data Structures Used



- 🌲 **Trie-based Storage**: Efficient O(L) word lookup where L is word length- Trie: To store words efficiently and support fast search and autocomplete.

- 📖 **Multiple Meanings**: Support for multiple definitions per word

- 💾 **File Persistence**: Save and load dictionary from text files### Features Implemented:- Linked List: To store multiple meanings/synonyms for each word.

- 🔢 **Search Counter**: Track word lookup frequency

- 🔤 **Case Insensitive**: Handles uppercase/lowercase automatically1. ✅ **Initialize Dictionary** - Load words from file into Trie data structure- Hash Map: (Optional) For quick word-frequency tracking.

- 🖥️ **Dual Interface**: CLI and GTK3 GUI versions

- 📊 **2928 Words**: Pre-loaded dictionary2. ✅ **Search Function** - Find words and display meanings- Heap (Priority Queue): To maintain top searched words (most frequent lookups).



---3. ✅ **Insert Function** - Add new words with meanings- Dynamic Arrays: For loading dictionary data from file and managing results.



## 🚀 Quick Start4. ✅ **Save Function** - Persist dictionary to file- DP Table (2D Array): For computing edit distance in spell checker.



### **CLI Version (No dependencies)**- Structs: For TrieNode, WordEntry, and Stats tracking.

```powershell

# Compile## Data Structures Used# Step-by-Step Algorithm

make cli

- **Trie**: Efficient storage and fast search for words (O(L) complexity)1. Initialize Dictionary

# Run

.\dictionary_app.exe- **Linked List**: Store multiple meanings for each word- Load words and meanings from file into Trie.

```

- **Structs**: TrieNode, WordEntry, MeaningNode- Build supporting structures for frequency and synonyms.

### **GUI Version (Requires GTK3)**

```powershell

# Compile

.\compile_gui.bat## File Structure2. Insert Word



# Run```- Traverse characters into Trie, creating nodes if needed.

.\dictionary_gui.exe

```DS_PBL-1/- Mark end-of-word and attach meaning/synonyms.



---├── dictionary.h       # Header file with structures and function declarations- Update file storage for persistence.



## 📁 Project Structure├── dictionary.c       # Implementation of Trie operations



```├── main.c            # Interactive menu program3. Search Word

DS_PBL-1/

├── dictionary.h           # Header file with data structures├── dictionary.txt    # Dictionary data (word|meaning1;meaning2)- Traverse Trie by characters.

├── dictionary.c           # Core Trie implementation

├── main.c                 # CLI interface├── Makefile          # Build automation- If found, return meaning and increment search frequency.

├── dictionary_gui.c       # GTK3 GUI interface

├── dictionary.txt         # Dictionary data (2928 words)└── README.md         # This file- If not found, trigger spell-check suggestions.

├── dictionary_app.exe     # Compiled CLI version

├── dictionary_gui.exe     # Compiled GUI version```

├── compile_gui.bat        # GUI compilation script

├── Makefile               # Build automation4. Autocomplete

└── README.md              # This file

```## How to Run- Traverse Trie to prefix node.



---- Perform DFS from that node to collect all completions.



## 🗂️ Data Structures### Method 1: Using Makefile (Recommended)- Print results with meanings.



### **TrieNode**```bash

```c

typedef struct TrieNode {make              # Compile the program5. Spell Checker

    struct TrieNode *children[26];  // a-z

    bool is_end_of_word;make run          # Compile and run- Use dynamic programming to compute edit distance between input and words in dictionary.

    struct WordEntry *word_entry;

} TrieNode;make clean        # Clean compiled files- Suggest words within a given edit distance threshold.

```

```

### **WordEntry**

```c6. Top Words

typedef struct WordEntry {

    struct MeaningNode *meanings;### Method 2: Direct Compilation- Use max-heap to return most searched words.

    int search_count;

} WordEntry;```bash- Update frequency count on each successful search.

```

gcc -Wall -O2 -std=c99 -o dictionary_app.exe dictionary.c main.c

### **MeaningNode**

```c.\dictionary_app.exe7. Save and Exit

typedef struct MeaningNode {

    char *meaning;```- Dump dictionary content and metadata back to file for persistence.

    struct MeaningNode *next;

} MeaningNode;Complexity

```

## UsageLookup: O(L), where L is length of word.

---

Insertion: O(L).

## 📄 File Format

When you run the program, you'll see:Autocomplete: O(L + K), where K is number of completions.

Dictionary file (`dictionary.txt`) uses pipe-separated format:

``````Spell Check: O(N * L^2), where N is number of words, L is word length (using DP).

word|meaning1;meaning2;meaning3

# Comments start with #========================================Heap Operations (Top words): O(log N).

```

      ADVANCED DICTIONARY SYSTEMSpace: O(N * L) for Trie nodes and meanings.

**Example:**

```========================================

algorithm|A step-by-step procedure for solving a problem;A set of rules for calculations

data|Facts and statistics;Information in digital form1. Search for a word# Basic CLI (Optional)

```

2. Insert a new word- Menu-driven interface with options:

---

3. Save dictionary  1. Search word

## 🛠️ Compilation

4. Exit  2. Add word

### **Method 1: Using Makefile**

```bash========================================  3. Delete word

# Build CLI version

make cli```  4. Autocomplete suggestions



# Build GUI version  5. Spell check suggestions

make gui

### Examples:  6. Show most searched words

# Run CLI

make run- **Search**: Type `1`, then enter word like `hello`- Input: user queries or file with words.



# Clean builds- **Insert**: Type `2`, enter word and meaning- Output: meanings, suggestions, and statistics.

make clean

```- **Save**: Type `3` to save changes# Learning Value



### **Method 2: Manual**- **Exit**: Type `4` to quit (auto-saves)- Strong understanding of Tries and their applications in dictionaries.

```bash

# CLI version- Practice with heaps, hash maps, and dynamic programming.

gcc -Wall -O2 -std=c99 -o dictionary_app.exe dictionary.c main.c

## Dictionary File Format- Learn persistence by saving/loading dictionary to/from files.

# GUI version (Windows with GTK3)

.\compile_gui.bat- Gain experience with autocomplete and spell check algorithms.

```

File: `dictionary.txt`- Reinforce modular programming in C with multiple components.

---

```# Possible Extensions

## 💻 Usage

# Comment lines start with #- Multilingual dictionary support (store meanings in multiple languages).

### **CLI Version**

```bashword1|meaning1;meaning2;meaning3- Add thesaurus-like functionality with synonyms and antonyms.

.\dictionary_app.exe

```word2|single meaning- Compression: Use Huffman coding to compress stored dictionary.



**Menu:**word3|first meaning;second meaning- Graphical User Interface (GUI) for interactive search and suggestions.

1. 🔍 **Search Word** - Look up word meanings

2. ➕ **Insert Word** - Add new word with meanings```- Networking: Allow multiple clients to query dictionary server.

3. 💾 **Save Dictionary** - Write changes to file

4. 🚪 **Exit** - Quit program- Voice-based input using speech-to-text libraries.



### **GUI Version**## Complexity Analysis- Integration with text editors for real-time spell check and autocomplete.

```bash

.\dictionary_gui.exe- **Search**: O(L) where L = word length

```- **Insert**: O(L) where L = word length

- **Load**: O(N*L) where N = number of words

**Features:**- **Space**: O(N*L) for entire Trie

- 🔍 **Search** - Find words and meanings

- ➕ **Add Word** - Add new entries with dialog## Adding Oxford Dictionary Words

- 💾 **Save** - Persist changes to file

- 📊 **Stats** - View dictionary statisticsSimply edit `dictionary.txt` and add words in this format:

- 🗑️ **Clear** - Clear results```

- ℹ️ **About** - Application infophilosophy|the study of fundamental nature of knowledge;a theory underlying conduct

algorithm|step-by-step procedure;computational method

---knowledge|facts and information acquired through experience;awareness

```

## 🔧 Core Functions

## Future Milestones (Planned)

| Function | Purpose | Complexity |- Autocomplete functionality

|----------|---------|------------|- Spell checker with edit distance

| `create_trienode()` | Allocate new node | O(1) |- Top searched words (using heap)

| `insert_word()` | Add word to Trie | O(L) |- Advanced features as needed

| `search_word()` | Find word in Trie | O(L) |
| `load_dictionary()` | Read from file | O(N*L) |
| `save_dictionary()` | Write to file | O(N*L*M) |
| `free_trie()` | Cleanup memory | O(N*L) |

**Where:**
- N = number of words
- L = average word length
- M = average meanings per word

---

## 📊 Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Insert    | O(L)           | O(L)            |
| Search    | O(L)           | O(1)            |
| Delete    | O(L)           | O(1)            |
| Load File | O(N*L)         | O(N*L)          |
| Save File | O(N*L*M)       | O(1)            |

---

## 🎯 Project Status

### ✅ **Completed:**
- ✅ Core Trie implementation
- ✅ File I/O operations
- ✅ Interactive CLI menu
- ✅ GTK3 GUI interface
- ✅ Memory management
- ✅ 2928 words loaded
- ✅ Multiple meanings support
- ✅ Search count tracking

### 🔜 **Future Enhancements:**
- Auto-complete suggestions
- Spell checker
- Top searched words
- Word categories/tags
- Export to different formats

---

## 📝 Requirements

### **CLI Version:**
- GCC compiler
- Standard C library

### **GUI Version:**
- MSYS2 with MinGW64
- GTK+ 3.0 development libraries
- pkg-config

---

## 🤝 Contributing

This is a Data Structures project implementing Milestone 1: Core Dictionary with Trie.

---

## 📜 License

Educational project - Free to use and modify.

---

**Built with ❤️ using C and GTK3**
