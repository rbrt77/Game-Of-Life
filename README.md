# Conway's Game of Life – Proiect în C

Acest proiect implementează o variantă personalizată a **Conway's Game of Life** în limbajul C, cu reguli modificate, structură de arbore binar pentru evoluția generațiilor și posibilitatea reconstrucției generației inițiale.

## Ce face programul

Programul simulează evoluția unei matrici de celule vii și moarte conform unor reguli personalizate ale jocului Life. În plus, permite:
- Evoluția matricei folosind două reguli diferite.
- Construirea unui arbore binar cu toate generațiile rezultate.
- Parcurgerea arborelui în preordine și afișarea diferențelor dintre generații.
- Reconstrucția generației 0 pornind de la generația finală, folosind o stivă de liste.



## Cum se utilizează

### Cerințe
- Compilator C (ex: `gcc`)
- Sistem de operare: Linux sau Windows cu un terminal compatibil

### Compilare

```bash
gcc main.c functii.c -o game
```

Pentru bonus:
```bash
gcc taskbonus.c -o bonus
```

### Rulare

```bash
./game input.txt
```

Pentru bonus:
```bash
./bonus input.txt output.txt
```

Fișierul `input.txt` trebuie să conțină datele de intrare în formatul specificat în enunț.

## Structura proiectului

- `main.c` – Conține Taskurile 1–3: citirea datelor, evoluția matricei, construirea arborelui binar și parcurgerea acestuia.
- `taskbonus.c` – Conține doar Taskul Bonus: reconstrucția generației 0 din generația finală.
- `functii.c` – Implementările tuturor funcțiilor auxiliare folosite în proiect.
- `functiigof.h` – Header ce declară toate funcțiile și structurile.
- `README.md` – Documentația proiectului (acest fișier).

## Funcții importante

- `citire()` – Citește matricea și valorile T, N, M, K din fișier.
- `schimbare3()` – Aplică regula personalizată (celula devine vie dacă are exact 2 vecini).
- `Arbore` – Structura arborelui binar, cu modificări stocate la fiecare nod.
- `preordine()` – Parcurge arborele în preordine și aplică modificările.
- `reconstruire_bonus()` – Reconstruiește matricea inițială folosind o stivă de liste.


