//
//  main.c
//  base64Ex
//
//  Created by 雨张 on 2018/5/17.
//  Copyright © 2018年 雨张. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
long len(char * msg)
{
    long length = 0;
    while(*msg)
    {
        msg++;
        length++;
    }
    return length;
}
char * base64Encode(char * msg)
{
    static unsigned char * B64_T =(unsigned char *) "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    long length     = len(msg);
    long dif        = length % 3;
    long fillingLen = length + (dif==0?0:3-dif);
    long alignLen   = length - dif;
    long b64Len     = (fillingLen / 3) << 2;
    char * base64   = malloc(b64Len +1);
    assert(base64!=0);
    base64[b64Len]  = 0;
    for(long msgIx=0,b64Ix=0;msgIx < alignLen;msgIx+=3,b64Ix+=4)
    {
        base64[b64Ix]   = B64_T[msg[msgIx] >> 2];
        base64[b64Ix+1] = B64_T[((msg[msgIx] & 3)    << 4) | (msg[msgIx+1] >> 4)];
        base64[b64Ix+2] = B64_T[((msg[msgIx+1] & 15) << 2) | (msg[msgIx+2] >> 6)];
        base64[b64Ix+3] = B64_T[msg[msgIx+2]   & 63];
    }
    
    if(dif == 1)
    {
        long b64Ix      = alignLen / 3 << 2;
        base64[b64Ix]   = B64_T[(msg[alignLen] & 252) >> 2];
        base64[b64Ix+1] = B64_T[(msg[alignLen] & 3) << 4];
        base64[b64Ix+2] = '=';
        base64[b64Ix+3] = '=';
    }
    else if(dif == 2)
    {
        long msgIx      = alignLen;
        long b64Ix      = alignLen / 3 << 2;
        base64[b64Ix]   = B64_T[(msg[msgIx]   & 252) >> 2];
        base64[b64Ix+1] = B64_T[((msg[msgIx]  & 3)   << 4) | ((msg[msgIx+1] & 240) >>4)];
        base64[b64Ix+2] = B64_T[(msg[msgIx+1] & 15) << 2];
        base64[b64Ix+3] = '=';
    }
    
    return base64;
}
char * base64Decode(char * b64)
{
    static unsigned char d_t[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,62,0,0,0,63,52,53,54,55,56,57,58,59,60,61,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,0,0,0,0,0,0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
    long b64len = len(b64);
    long msglen = (b64len >> 2)*3;
    
    char * msg  = malloc(msglen+1);
    assert(msg!= 0);
    for(int b64Ix = 0 ,msgIx = 0;b64Ix < b64len;b64Ix+=4,msgIx +=3)
    {
        msg[msgIx]   = d_t[b64[b64Ix]] << 2   | d_t[b64[b64Ix+1]]  >> 4 ;
        msg[msgIx+1] = d_t[b64[b64Ix+1]] << 4 | d_t[b64[b64Ix+2]] >> 2  ;
        msg[msgIx+2] = d_t[b64[b64Ix+2]] << 6 | d_t[b64[b64Ix+3]] ;
    }
    return msg;
}
int main(int argc, const char * argv[]) {
    // insert code here...

    char * base64 = base64Encode("helloworld!");
    printf("%s\n",base64);
    char * msg    = base64Decode(base64);
    printf("%s\n",msg);
    printf("Hello, World!\n");
    return 0;
}
