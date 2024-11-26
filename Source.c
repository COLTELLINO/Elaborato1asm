#include <stdio.h>

void main() {
    // Le stringhe da ordinare (array di puntatori)
    char* strings[] = { "DE PIè FPFHGFO", "AmongUS SUS", "AmongUS SUS", "EEOOEO", "Sium" };
    // Il numero di stringhe nell'array
    int num = sizeof(strings) / sizeof(strings[0]);

    __asm {
        dec num
        xor ebx, ebx
        xor esi, esi

        ricomincio :
            xor ecx, ecx

        ciclo_assegnazione :
            mov edx, [strings + ebx * 4]
            mov edi, [strings + ebx * 4 + 4]

        ciclo_scorrimento :
            mov al, [edx + esi]
            mov ah, [edi + esi]
            inc esi
            cmp al, 0
            je fine
            cmp ah, 0
            je fine
            cmp ah, al
            jl scambio
            jg fine
            je ciclo_scorrimento

        scambio :
            mov[strings + ebx * 4], edi
            mov[strings + ebx * 4 + 4], edx
            inc ecx

        fine :
            inc ebx
            xor esi, esi
            cmp ebx, num
            jl ciclo_assegnazione

            xor ebx, ebx
            xor esi, esi
            cmp ecx, 1
            jae ricomincio
            inc num
    }

    // Stampa su video
    {
        int i;
        for (i = 0; i < num; i++)
            printf("%s\n", strings[i]);
    }
}
