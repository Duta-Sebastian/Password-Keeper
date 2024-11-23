[ENG]
# Password-Keeper
## Project Description
The Password Keeper application enables users to manage their passwords in a secure database.
It offers functionality to efficiently and safely store and organize passwords, as well as the option to generate new, customized passwords on demand.

## Notes
1. PostgreSQL Installation:
    - To build the project, you must first install [PostgreSQL](https://www.postgresql.org/download/) on your computer.
2. Running the Application Locally:
   - To use the application locally, you need to install [Docker](https://docs.docker.com/engine/install/), use the command
   `docker compose up` in the project's [infrastructure](./infrastructure) folder, and create a new file named `.env` in the src folder.
   Fill this file with the details from [compose.yml](./infrastructure/compose.yaml) , following the format described in the .env.template file.
3. Running Tests:
   - To run the tests, add either the env.bat or env.sh file (the former for Windows, the latter for POSIX systems)
   to the environment file settings of your toolchain (File | Settings | Build, Execution, Deployment | Toolchains) under the Environment File section.
   Tests can be run either by executing the cmake-build-debug/tests/Password-Keeper-Test-Runner file or by running the ctest command in the cmake-build-debug folder.

## CI/CD Pipeline
The CI/CD pipeline is configured in GitHub Actions and includes multiple stages to ensure code quality, compatibility, and functionality across various platforms.

1. Code Quality Validation:
   - The first two stages validate code correctness and ensure no warnings are generated (using Cppcheck and Clang-Tidy).

2. Compatibility Testing Across Multiple Operating Systems:
   - The next five stages ensure proper code execution on major operating systems (Linux, macOS, and Windows) and perform memory checks using MSAN, ASAN, and Valgrind to identify potential memory leaks and other memory-related issues.

3. Functional Test Execution:
   - The final stage runs functional tests to verify that the application behaves as expected.

In all stages involving the execution of the application, a PostgreSQL service is included to ensure proper application functionality.

[RO]
# Password-Keeper

## Descriere proiect

Aplicația este un Password Keeper care permite utilizatorilor să își gestioneze parolele într-o bază de date securizată.
Aceasta oferă funcționalitatea de a stoca și organiza parolele într-un mod eficient și sigur, precum și opțiunea de a
genera parole noi, personalizate, la cerere.

## Mentiuni
1. Instalare PostgreSQL:
   - Pentru a construi proiectul trebuie sa instalati mai intai [PostgreSQL](https://www.postgresql.org/download/) pe
   calculatorul dumneavoastra.
2. Folosirea aplicatiei local:
    - Pentru a folosi aplicatia local trebuie sa instalati [Docker](https://docs.docker.com/engine/install/),sa folositi comanda
      `docker compose up` in folderul [infrastructure](./infrastructure) din proiect, sa create un nou fisier numit `.env` in
      folderul [src](./src) si sa il completati cu datale din [compose.yml](./infrastructure/compose.yaml) 
      in modul prezentat in fisierul [.env.template](.env.template)
3. Rularea testelor:
    - Pentru a rula testele trebuie sa adaugati unul dintre fisierele [env.bat](env.bat) sau [env.sh](env.sh) (primul pentru
      Windows, al doilea pentru sisteme POSIX) in setarile toolchain-ului pe care il folositi (`File | Settings | Build, Execution, Deployment | Toolchains`)
      la rubrica `Environment File`. Testele se ruleaza ori ruland executabilul `cmake-build-debug/tests/Password-Keeper-Test-Runner` ori ruland comanda ctest in folderul `cmake-build-debug`.

## Pipeline
Pipeline-ul CI/CD este configurat în [GitHub Actions](./.github/workflows/cmake.yml) și include mai multe etape pentru a asigura calitatea codului, compatibilitatea și funcționalitatea pe diferite platforme.

Verificarea calității codului:
Primele două etape validează corectitudinea codului și se asigură că nu generează warnings ( folosind `Cppcheck` si `Clang-Tidy` ).

Testarea compatibilității pe multiple sisteme de operare:
Următoarele cinci etape asigură rularea corectă a codului pe principalele sisteme de operare (Linux, macOS și Windows) și efectuează verificări de memorie folosind MSAN, ASAN și Valgrind, pentru a identifica posibile memory leaks și alte probleme legate de memorie.

Rularea testelor funcționale:
Ultima etapă rulează testele pentru a verifica dacă aplicația funcționează conform așteptărilor.

În toate etapele care implică rularea aplicatiei este inclus un serviciu PostgreSQL pentru a permite rularea corectă a aplicației.

## Milestone #0

- [ ] Nume proiect (poate fi schimbat ulterior)
- [ ] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Milestone #1

#### Cerințe

- [ ] definirea a minim **3-4 clase** folosind compunere cu clasele definite de voi
- [ ] constructori de inițializare cu parametri
- [ ] pentru o aceeași (singură) clasă: constructor de copiere, `operator=` de copiere, destructor
- [ ] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [ ] cât mai multe `const` (unde este cazul)
- [ ] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese, dintre care cel puțin
  1-2 funcții mai complexe
    - nu doar citiri/afișări sau adăugat/șters elemente într-un/dintr-un vector
- [ ] scenariu de utilizare a claselor definite:
    - preferabil sub formă de teste unitare, mai ales dacă vorbim de aplicații consolă
    - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
    - vor fi adăugate în fișierul `tastatura.txt` DOAR exemple de date de intrare de la tastatură (dacă există); dacă
      aveți nevoie de date din fișiere, creați alte fișiere separat
- [ ] tag de `git`: de exemplu `v0.1`
- [ ] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Milestone #2

#### Cerințe

- [ ] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [ ] moșteniri:
    - minim o clasă de bază și **3 clase derivate** din aceeași ierarhie
    - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
    - [ ] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază
        - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
        - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
        - afișare virtuală, interfață non-virtuală
    - [ ] apelarea constructorului din clasa de bază din constructori din derivate
    - [ ] clasă cu atribut de tip pointer la o clasă de bază cu derivate; aici apelați funcțiile virtuale prin pointer
      de bază, eventual prin interfața non-virtuală din bază
        - [ ] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
        - [ ] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens
        - [ ] smart pointers (recomandat, opțional)
- [ ] excepții
    - [ ] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim **3** clase pentru erori
      specifice
    - [ ] utilizare cu sens: de exemplu, `throw` în constructor (sau funcție care întoarce un obiect), `try`/`catch` în
      `main`
    - această ierarhie va fi complet independentă de ierarhia cu funcții virtuale
- [ ] funcții și atribute `static`
- [ ] STL
- [ ] cât mai multe `const`
- [ ] funcții *de nivel înalt*, de eliminat cât mai mulți getters/setters/funcții low-level
- [ ] tag de `git`: de exemplu `v0.2`

## Milestone #3

#### Cerințe

- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o clasă șablon cu sens; minim **2 instanțieri**
    - [ ] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse

- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit
