// Problème 2 du TP7. Permet d'allumer une lumière de couleur différente selon
// l'intensité de la lumière fournie à la cellule photosensible.
// Par Brandon Roberge et Abdeljelil Malti.
// Équipe 66 groupe 3
// 28 février 2016

// Broches utilisees :
// Cellule photosensible: PORTA3,
// DEL: PORTB0 et PORTB1

#include <avr/io.h>
#include "can.h"

void initialize(){
    DDRA = 0x00; // PORT A est en mode entree
    DDRB = 0xff; // PORT B est en mode sortie
    DDRC = 0xff; // PORT C est en mode sortie
    DDRD = 0x00; // PORT D est en mode entree
}


int main(){
    initialize();

    uint8_t positionDuCapteur = 0x02;
    can can;

    uint8_t selecteurAmbre = 0;

    while(true){
        uint16_t valeur = can.lecture(positionDuCapteur);

        //Décalage afin d'avoir 8 bits.
        valeur = valeur >> 2;

        //Si l'intensité est faible ( 33% ou inferieur ).
        if(valeur <= 85){
            PORTB = 0x01;
        }//Si l'intensité est moyenne ( 66% ou inferieur ).
        else if(valeur <= 170){
            if(selecteurAmbre)
                PORTB = 0x01;
            else
                PORTB = 0x02;
            selecteurAmbre = selecteurAmbre != 0 ? 0 : 1;
        }//Si l'intensité est forte ( 66% à 100% ).
        else{
            PORTB = 0x02;
        }

    }
}


