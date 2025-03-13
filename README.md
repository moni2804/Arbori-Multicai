# Arbori-Multicai - Implementare și Operații

Acest proiect implementează operații pe arbori multicăi, inclusiv parcurgerea unui arbore binar și transformările între cele trei reprezentări ale unui arbore multicăi. Complexitatea tuturor operațiilor este O(n) și se utilizează memorie suplimentară minimă.

## Descrierea Operațiilor Implementate

1. **Parcurgerea unui arbore binar**:
   - **Parcurgere Recursivă**: O funcție care parcurge arborele folosind recursivitatea.
   - **Parcurgere Iterativă**: O funcție care parcurge arborele folosind o stivă, fără recursivitate.

2. **Transformările între cele trei reprezentări ale unui arbore multicăi**:
   - **R1 - Reprezentarea părinte**: Un vector în care fiecare element indică părintele unui nod.
   - **R2 - Arbore multicăi**: Fiecare nod are o listă de copii.
   - **R3 - Arbore binar echivalent**: Fiecare nod are un prim copil și un frate din dreapta.

3. **Funcțiile de transformare**:
   - **T1**: Convertirea din R1 (vectorul de părinți) în R2 (arbore multicăi).
   - **T2**: Convertirea din R2 (arbore multicăi) în R3 (arbore binar echivalent).

4. **Afisare prietenoasă (Pretty Print)**:
   - **R1**: Afișează vectorul de părinți.
   - **R2**: Afișează arborele multicăi cu relațiile părinte-copii.
   - **R3**: Afișează arborele binar echivalent.

## Complexitate

   - **Timp**: Toate transformările și parcurgerile sunt eficiente cu complexitate O(n).
   - **Memorie**: Memoria suplimentară folosită este minimă și depinde de mărimea arborelui (O(n)).







