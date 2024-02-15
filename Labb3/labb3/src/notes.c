// @author Ömer Kolsuz & Oscar Svantesson

// Inkludera nödvändiga bibliotek och huvudfilen "notes.h".
#include "notes.h"
#include <stdio.h>
#include <math.h>
#include <string.h>


void freq2note(float frequency, char *stringbuff) {
    // Kolla om frekvensen är inom det accepterade intervallet (E4 till E2).
    if (frequency >= 82.41 && frequency <= 329.63) {
        // Skapa en lista med noter som motsvarar frekvensintervallet.
        char *notes[] = {"E4", "B3", "G3", "F3", "D3", "A2", "E2"};
        
        // Beräkna vilken not som passar bäst för den givna frekvensen.
        int note_nr = round(12 * log2(frequency / 329.63));
        note_nr = note_nr % 26; // Använd modulo för att säkerställa att indexet är inom gränserna.
        
        if (note_nr < 0) {
            note_nr += 26; // Korrigera negativa index.
        }
        
        // Kopiera den beräknade noten till utmatningssträngen.
        strcpy(stringbuff, notes[note_nr]);
    } else {
        // Om frekvensen är okänd eller utanför intervallet, sätt utmatningssträngen till "?".
        strcpy(stringbuff, "?");
    }
}
