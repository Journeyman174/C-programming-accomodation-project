#include "communication.h"
#include "util_comm.h"
#include <string.h>
#include <stdio.h>


/* Task 1 - The Beginning */

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */
    send_squanch('R' - 'A' + 1);
    send_squanch('I' - 'A' + 1);
    send_squanch('C' - 'A' + 1);
    send_squanch('K' - 'A' + 1);
}


void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */
     int i;
     for(i=0; i < 5; i++)    
     {
      char  c = recv_squanch() + 'A' - 1;
      fprintf(stdout,"%c", c);
     }
}


void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */
     int i;
     for(i=0; i<10; i++)
     {
         char  c = recv_squanch() + 'A' - 1;
         send_squanch(c - 'A' + 1);
         send_squanch(c - 'A' + 1);

     }
}


/* Task 2 - Waiting for the Message */

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */
     int i;
     char mesaj[] = "HELLOTHERE";
     uint8_t lungime = strlen(mesaj);
     send_squanch((lungime)<<2);
     for(i=0; i<lungime; i++ )
        send_squanch(mesaj[i] -'A' +1);
}


void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */
     int i;
     uint8_t mask = 0x0f;
     uint8_t lungime = ((recv_squanch() >> 2) & mask);
     fprintf(stdout,"%d", lungime);
    for(i = 0; i < lungime ; i++)    
     {
      char  c = recv_squanch() + 'A' - 1;
      fprintf(stdout,"%c", c);
     }
}




void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */
    int i;
    uint8_t mask = 0x0f;
    uint8_t lungime = ((recv_squanch() >> 2) & mask);
    char mesaj[100];
    char mesaj_send1[] = "PICKLERICK";
    char mesaj_send2[] = "VINDICATORS";
    for(i = 0; i < lungime ; i++)    
        mesaj[i] = recv_squanch() + 'A' - 1;

    if (mesaj[lungime-1] == 'P')
        {
            uint8_t lungime1=strlen(mesaj_send1);
            send_squanch((lungime1)<<2);
            for(i=0; i<lungime1; i++ )
                send_squanch(mesaj_send1[i] -'A' +1);
        }
    else
        {
            uint8_t lungime2=strlen(mesaj_send2);
            send_squanch((lungime2)<<2);
            for(i=0; i<lungime2; i++ )
                send_squanch(mesaj_send2[i] -'A' +1);
        }
    

}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */
    int i,j;
    uint8_t res = 0;
    uint8_t r1,r2,mask11,mask12,mask,mask21,mask22;
    j=0;
    for (i = 0; i < 8; i++)
        {
            /*get_bit(c1,i)*/
            mask = (1 << i);
            if((c2 & mask) != 0)
                r1 = 1;
            else
                r1 = 0;
            if (r1 == 0)
                {
        /*        clear_bit(res,i+1); */
                mask11 = ~(1 << j);
                res = res & mask11 ;
            }
        else
            {
        /*        activate_bit(res,i+1); */
            mask12 = (1 << j);
            res = res | mask12 ;
            }
          /*get_bit(c2,i)*/
        j=j+1;
        if((c1 & mask) != 0)
            r2 = 1;
        else
            r2 = 0;
        if (r2 == 0)
            {
        /*        clear_bit(res,i); */
            mask21 = ~(1 << j);
            res = res & mask21 ;
            }
        else
            {
        /*        activate_bit(res,i+1); */
            mask22 = (1 << j);
            res = res | mask22 ;
            }
        j=j+1;
         }
    send_squanch(res) ;   
}



uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;

    /* TODO */
    int i, j, k;
    uint8_t r,mask11,mask12,mask,mask21,mask22;
     j=0;
     k=4;
    for (i = 0; i < 8; i++)
        {
            mask = (1 << i); 
            if((c & mask) != 0)
                r = 1;
            else
                 r = 0;
            if (i % 2 == 0)
                {    
                    /*este i par deci c2 poz 0 in res*/
                    if (r == 0)
                        {
                        /* bit=0        c2 in res - clear_bit(res,j); */
                        mask11 = ~(1 << j);
                        res = res & mask11 ;
                        }
                    else
                    {
                        /* bit=1       activate_bit(res,j); */
                         mask12 = (1 << j);
                         res = res | mask12 ;
                    }
                    j=j+1;
                }
            else
                    {    
                    /*este impat deci c1 poz 4 in res get_bit(c,i)*/
                    if (r == 0)
                        {
                        /* bit=0       c1 in res - clear_bit(res,k); */
                        mask21 = ~(1 << k);
                        res = res & mask21 ;
                        }
                    else
                        {
                        /* bit=1       activate_bit(res,k); */
                         mask22 = (1 << k);
                        res = res | mask22 ;
                        }
                     k=k+1;
                    }
            }
    return res;
}
