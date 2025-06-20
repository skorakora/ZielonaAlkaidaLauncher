
# Zielona Alkaida Launcher

Prosty launcher do Minecrafta napisany w C++ z wykorzystaniem **GLFW**, **ImGui** oraz **CMake**. Projekt kompatybilny z **Visual Studio 2022**.

---

## ✅ Wymagania

- Visual Studio 2022 (z toolsetem C++)
- Git (do klonowania submodułów)
- CMake ≥ 3.15

---

## 📦 Jak zbudować projekt

1. **Sklonuj repozytorium z submodułami**:

```bash
git clone --recurse-submodules <repo-url>
cd ZielonaAlkaidaLauncher
```

2. **Stwórz folder build i uruchom CMake**:

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
```

3. **Otwórz projekt w Visual Studio** i ustaw `ZielonaAlkaidaLauncher` jako projekt startowy.

4. **Uruchom projekt** (`F5`).

---

## ⚠️ Ważne

- Plik czcionki **arialbd.ttf** oraz plik tła **backround.jpg** **muszą znajdować się w tym samym katalogu co plik `.exe`**.
- Program należy uruchamiać **bezpośrednio przez wygenerowany plik `.exe`**, a nie przez Visual Studio. Uruchomienie przez Visual Studio może spowodować problemy z lokalizacją plików i program może nie działać poprawnie. (Naprawa tego problemu jest planowana).

---

## 📁 Struktura katalogów

```
ZielonaAlkaidaLauncher/
├── main.cpp
├── CMakeLists.txt
├── extern/
│   ├── imgui/     (submoduł)
│   └── glfw/      (submoduł)
├── build/         (ignorowane przez git)
├── .gitignore
└── README.md
```

---

## 🛠️ Autor

Daniel Skórski
