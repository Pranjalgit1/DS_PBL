# 📋 Quick Commands - Share This With Your Team!

## 🚀 Setup (One Time Only)

```powershell
git clone https://github.com/Pranjalgit1/DS_PBL.git
cd DS_PBL
```

---

## 💻 Run the Program

### **Method 1: Using Makefile (Easiest)**
```powershell
make cli
.\dictionary_app.exe
```

### **Method 2: Direct Compilation**
```powershell
gcc -Wall -O2 -std=c99 -o dictionary_app.exe dictionary.c main.c
.\dictionary_app.exe
```

---

## 🔄 Update Your Code

```powershell
git pull origin main
```

---

## 📤 Push Your Changes

```powershell
git add .
git commit -m "Your message here"
git push origin main
```

---

## ✅ Full Workflow

```powershell
# 1. Get latest code
git pull origin main

# 2. Make your changes in VS Code or any editor

# 3. Test
make cli
.\dictionary_app.exe

# 4. If it works, push it
git add .
git commit -m "Describe what you changed"
git push origin main
```

---

## 🆘 Quick Fixes

### If compile fails:
```powershell
make clean
make cli
```

### If git push fails:
```powershell
git pull origin main
# Resolve conflicts if any
git push origin main
```

### Check what changed:
```powershell
git status
git diff
```

---

## 📖 More Help

- **Full Guide:** See `TEAM_GUIDE.md` in the repository
- **README:** See `README.md` for features
- **Repository:** https://github.com/Pranjalgit1/DS_PBL

---

## 💡 Pro Tips

- **Before editing:** Always run `git pull origin main`
- **After editing:** Test with `make cli` before pushing
- **Use descriptive commit messages:** "Add search feature" not "update"
- **Small commits:** Commit often with small changes

---

**Repository Link:** https://github.com/Pranjalgit1/DS_PBL

**Share this file with your teammates!** 📤
