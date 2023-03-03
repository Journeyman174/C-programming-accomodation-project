#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */

    uint16_t res = 0;
    int i,j,k,l,m,n,spel,r1;
    for (i=0; i<=63; i++)
    {   
        uint64_t mask = ((uint64_t)1 << i);
        if((memory & mask) != 0)
            {
                spel=1;
                for (j = 1; j < 5; j++)
                    {  
                        k=i+j ;
                        uint64_t mask_1 = ((uint64_t)1<<k) ;
                        if ((memory & mask_1 ) != 0)
                           spel=spel+1;
                        else 
                           break;
                    }
                if (spel == 5 )
                    {
                    m=i+5;
                    res=0;
                    for (l=0; l< 16;l++) 
                         {
                             n=m+l;
                             uint64_t mask_2 = ((uint64_t)1 << n);
                            if((memory & mask_2) != 0)
                                r1 = 1;
                            else
                                r1 = 0;
                            if (r1 == 0)
                                {
                                uint16_t  mask11 = ~((uint16_t)1 << l);
                                res = res & mask11 ;
                                }
                            else
                                {
                                uint16_t mask12 = ((uint16_t)1 << l);
                                res = res | mask12 ;
                                }

                        }  
                    }
            }
    }
    /* TODO */

    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */

    uint16_t res = 0;
    int i,j,k,l,m,n,spel,r1;
    for (i=63; i >= 0; i--)
    {   
        uint64_t mask = ((uint64_t)1 << i);
        if((memory & mask) != 0)
            {
                spel=1;
                for (j = 1; j < 3; j++)
                    {  
                        k=i-j ;
                        uint64_t mask_1 = ((uint64_t)1<<k) ;
                        if ((memory & mask_1 ) != 0)
                           spel=spel+1;
                        else 
                           break;
                    }
                if (spel == 3 )
                    {
                    m=i-3;
                    n=m+1;
                    res=0;
                    for (l=15; l >= 0; l--) 
                         {
                             n=n-1;
                             uint64_t mask_2 = ((uint64_t)1 << n);
                            if((memory & mask_2) != 0)
                                r1 = 1;
                            else
                                r1 = 0;
                            if (r1 == 0)
                                {
                                uint16_t  mask11 = ~((uint16_t)1 << l);
                                res = res & mask11 ;
                                }
                            else
                                {
                                uint16_t mask12 = ((uint16_t)1 << l);
                                res = res | mask12 ;
                                }

                        }  
                    }
            }
    }

    /* TODO */

    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = -1;
    res=spell^key;

    /* TODO */

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */
    uint32_t res = -1, mask;
    uint8_t i, nr = 0;
    uint16_t value;
    
    for (i=0; i<15; i++)
        {
        mask = 1 << i;
        if((enemy & mask) != 0)
            nr++;
        }
    if (!(nr % 2))
    {
        value = enemy & (1- enemy);
        res =  (9ULL << 28) + value;
    }
    else
    {   value= - enemy;
        res = (6ULL << 28) +value;

    }

    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = -1;
    res = cocktail << 16;
    return res;

    /* TODO */

    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    uint8_t res = -1, k=0, i;
    uint64_t mask;
    for(i=0; i<64; i++)
    {
        mask = 1ULL <<i;
        if((mask & map) != 0)
            k++;
    }

    switch(k)
    {
        case 0 :
            res = 0;
            break;
        case 2 :
            res = 1; 
            break;
        case 64 :
            res = 2;
            break;
        default :
            if(!(k % 4))
                res = 0;
            else
                res = 3 ;    
               
    }
    
    /* TODO */
    return res;
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    /* TODO */

    uint8_t i, c1, c2, r = 0;
    uint32_t mask;

    for(i = 0; i < 32; i++)
    {
        mask = 1 << i;
        if((mask & map) != 0) 
        {   if (!r)
            {  c1 = i;
                r = 1;
            }
            else
                c2 = i;    

        }
    }

    return c2 - c1;
}
