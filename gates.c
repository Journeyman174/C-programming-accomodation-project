#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */
    uint64_t mask = (1 << i);
    if((nr & mask) != 0)
        res = 1;
    else
        res = 0;

    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */

    uint64_t mask_set = ((uint64_t)1 << i);
    res = nr ^ mask_set;
   
    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */

    uint64_t mask = ((uint64_t)1 << i);

     res = nr | mask ;
    
    
    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */

    uint64_t mask = ~((uint64_t)1 << i);

     res = nr & mask ;

    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */

    uint8_t c = nand_gate(a,b);
    res = nand_gate(c,c);

    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */

    res = nand_gate(a,a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */

    uint8_t c1, c2;
    c1 = nand_gate(a,a);
    c2 = nand_gate(b,b);
    res = nand_gate(c1,c2);

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */

    uint8_t c1, c2,c3;
    c1 = nand_gate(a,b);
    c2 = nand_gate(c1,a);
    c3 = nand_gate(c1,b);
    res = nand_gate(c2,c3);

    
    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */

    uint8_t d1, s, e1, e2, f;
    d1 = xor_gate(a,b);
    s = xor_gate(d1,c);
    e1 = and_gate(d1,c);
    e2 = and_gate(a,b);
    f = or_gate(e1,e2);
    
    /* octetul res va avea bitul dupa pozitia 0 cu valoarea lui s si bitul dupa pozitia 1 cu valoarea lui f = carry */

    res = (f << 1) | s ; 
    
    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;
    uint64_t j;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */
    uint8_t carry = 0;
    res = 0 ;

    for(j = 0; j <= 63; j++)
        {
            uint64_t m = full_adder((a >> j) & 1, (b >> j) & 1, carry);
            res = res | ((m & (uint64_t)1) << j);
            carry = (m >> (uint64_t)1) & (uint64_t)1 ;
        }
        if(carry == 1)
            return 0; 
    return res ;
}


