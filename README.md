# SD1_Project

## Konfiguracja C++ (macOS + Windows)

Projekt ma wspolna konfiguracje VS Code, aby dalo sie pracowac w parze na dwoch systemach:

- macOS: kompilacja przez `clang++`
- Windows: kompilacja przez `g++`

### Build

W VS Code uruchom:

- `Terminal -> Run Build Task`
- wybierz: `Build C++ project`

Binarka pojawi sie w katalogu `build/`:

- macOS/Linux: `build/app`
- Windows: `build/app.exe`

### Run

Mozesz uruchomic:

- task: `Run C++ app`

albo debug:

- `Run and Debug`
- konfiguracja: `Debug C++ app`