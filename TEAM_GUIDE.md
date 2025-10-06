# 🚀 Quick Start Guide - For Team Members

## 📥 Step 1: Clone the Repository

Open your terminal (PowerShell/Command Prompt) and run:

```powershell
git clone https://github.com/Pranjalgit1/DS_PBL.git
cd DS_PBL
```

Or if you already cloned, just pull the latest changes:
```powershell
cd DS_PBL
git pull origin main
```

---

## 🔧 Step 2: Check What You Have

List the files:
```powershell
dir
```

You should see:
```
dictionary.h
dictionary.c
main.c
dictionary_gui.c
dictionary.txt
Makefile
compile_gui.bat
README.md
GUI_INTEGRATION_GUIDE.md
```

---

## 💻 Step 3: Run the CLI Version (Simple - No Installation Needed!)

### **Option A: Using Make (Recommended)**
```powershell
make cli
.\dictionary_app.exe
```

### **Option B: Manual Compilation**
```powershell
gcc -Wall -O2 -std=c99 -o dictionary_app.exe dictionary.c main.c
.\dictionary_app.exe
```

---

## 🎨 Step 4: Run the GUI Version (Requires GTK3)

### **If you DON'T have GTK3 installed:**
Just use the CLI version above! The GUI is optional.

### **If you HAVE GTK3 installed:**
```powershell
.\compile_gui.bat
.\dictionary_gui.exe
```

**To install GTK3 (optional):** See `GUI_INTEGRATION_GUIDE.md`

---

## 📖 Step 5: Using the Dictionary

### **CLI Menu:**
```
1. Search for a word    → Type a word to look up
2. Insert a new word    → Add new word with meaning
3. Save dictionary      → Save changes to file
4. Exit                 → Quit program
```

### **Example Usage:**
```
Enter your choice: 1
Enter word to search: algorithm

--- Word: algorithm ---
Search count: 1
Meanings:
  1. A step-by-step procedure for solving a problem
  2. A set of rules for calculations
```

---

## 🛠️ Step 6: Making Changes

### **Edit the Code:**
1. Open `dictionary.c`, `dictionary.h`, or `main.c` in your editor
2. Make your changes
3. Recompile:
   ```powershell
   make cli
   ```
4. Test:
   ```powershell
   .\dictionary_app.exe
   ```

### **Add More Words:**
Edit `dictionary.txt` file:
```
word|meaning1;meaning2;meaning3
```

Example:
```
python|A high-level programming language;A snake
java|A programming language;An island in Indonesia
```

---

## 📤 Step 7: Pushing Your Changes to GitHub

### **Method 1: Using Git Commands**
```powershell
# Check what changed
git status

# Add your changes
git add dictionary.c main.c
# OR add all changes: git add .

# Commit with message
git commit -m "Your descriptive message here"

# Push to GitHub
git push origin main
```

### **Method 2: Using GitHub Desktop**
1. Open GitHub Desktop
2. Select the repository
3. Check the files you want to commit
4. Write commit message
5. Click "Commit to main"
6. Click "Push origin"

---

## 📋 Common Commands Cheat Sheet

| Task | Command |
|------|---------|
| Compile CLI | `make cli` or `gcc -Wall -O2 -std=c99 -o dictionary_app.exe dictionary.c main.c` |
| Run CLI | `.\dictionary_app.exe` |
| Compile GUI | `.\compile_gui.bat` |
| Run GUI | `.\dictionary_gui.exe` |
| Clean builds | `make clean` |
| Pull updates | `git pull origin main` |
| Check status | `git status` |
| View changes | `git diff` |
| Push changes | `git push origin main` |

---

## 🐛 Troubleshooting

### **Error: "gcc is not recognized"**
**Solution:** Install MinGW or TDM-GCC
- Download: https://jmeubank.github.io/tdm-gcc/
- Install and add to PATH

### **Error: "dictionary.txt not found"**
**Solution:** Make sure you're in the project directory
```powershell
cd DS_PBL
dir  # Should show dictionary.txt
```

### **Error: "Permission denied" when pushing**
**Solution:** Configure Git credentials
```powershell
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"
```

Or use GitHub Desktop for easier authentication.

---

## 📚 Project Structure

```
DS_PBL/
├── dictionary.h           # Header file (data structures)
├── dictionary.c           # Core Trie implementation
├── main.c                 # CLI interface
├── dictionary_gui.c       # GUI interface (optional)
├── dictionary.txt         # Dictionary data (2928 words)
├── Makefile               # Build automation
├── compile_gui.bat        # GUI compilation script
└── README.md              # Full documentation
```

---

## 🎯 Quick Demo for Presentation

```powershell
# Step 1: Clone and enter directory
git clone https://github.com/Pranjalgit1/DS_PBL.git
cd DS_PBL

# Step 2: Compile
gcc -Wall -O2 -std=c99 -o dictionary_app.exe dictionary.c main.c

# Step 3: Run
.\dictionary_app.exe

# Step 4: Demo features
# - Search: algorithm
# - Insert: test|This is a test word
# - Save and exit
```

---

## 👥 Team Workflow

### **Workflow 1: Pull → Edit → Test → Push**
```powershell
git pull origin main           # Get latest changes
# ... make your changes ...
make cli                       # Compile and test
.\dictionary_app.exe          # Verify it works
git add .                      # Stage changes
git commit -m "Add feature X" # Commit
git push origin main          # Push to GitHub
```

### **Workflow 2: Branches (Recommended for Features)**
```powershell
git checkout -b feature-autocomplete  # Create branch
# ... make your changes ...
git add .
git commit -m "Add autocomplete"
git push origin feature-autocomplete
# Then create Pull Request on GitHub
```

---

## ✅ Verification Checklist

Before pushing code, verify:
- [ ] Code compiles without errors: `make cli`
- [ ] Program runs: `.\dictionary_app.exe`
- [ ] Search works (test with "algorithm")
- [ ] Insert works (add a test word)
- [ ] Dictionary loads (2928 words message appears)
- [ ] No memory leaks (program exits cleanly)

---

## 🆘 Need Help?

1. **Read Documentation:** `README.md` or `GUI_INTEGRATION_GUIDE.md`
2. **Check Issues:** https://github.com/Pranjalgit1/DS_PBL/issues
3. **Ask Team:** Contact team members on your communication channel

---

## 📝 Example: Adding a New Feature

Let's say you want to add a "count words" feature:

```powershell
# 1. Pull latest
git pull origin main

# 2. Create branch (optional but recommended)
git checkout -b feature-count-words

# 3. Edit dictionary.c - add function:
# int count_words(TrieNode *root) { ... }

# 4. Edit dictionary.h - add declaration:
# int count_words(TrieNode *root);

# 5. Edit main.c - add menu option

# 6. Test
make cli
.\dictionary_app.exe

# 7. Commit and push
git add dictionary.c dictionary.h main.c
git commit -m "Add word count feature"
git push origin feature-count-words

# 8. Create Pull Request on GitHub
```

---

## 🎓 For Beginners

### **Never used Git before?**

**Windows:** Download GitHub Desktop
- https://desktop.github.com/
- It's a GUI tool (no commands needed)

**Basic Git Learning:**
1. Clone = Download project
2. Pull = Get latest updates
3. Add = Mark files to save
4. Commit = Save with message
5. Push = Upload to GitHub

---

**Happy Coding! 🚀**

**Repository:** https://github.com/Pranjalgit1/DS_PBL
