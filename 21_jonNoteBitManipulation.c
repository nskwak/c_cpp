#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "unistd.h"
#include "math.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: pointer, pointer of pointer
int main()
{
    int var;
    unsigned int var0, var1;
    signed int var2, var3;
    int i, j, maskingBit;

    /*
    printf("====================================================\n");
    printf("// pointer, pointer pointer \n");
    var = 30;
    printf("var = %d \n", var);
    int *ptr1 = &var;
    printf("ptr1 = %p \n", ptr1);
    int** ptr2 = &ptr1; 
    printf("ptr2 = %p \n", ptr2);

    *ptr1 = 40;
    printf("var = %d \n", var);
    printf("ptr1 = %p \n", ptr1);

    **ptr2 = 50;
    printf("var = %d \n", var);
    printf("ptr2 = %p \n", ptr2);
    */
    printf("====================================================\n");
    printf("// 1's complement, 2's complement \n");
    var1 = 0xfffffffe;
    printf("unsigned var1 = 0x%x,  %d \n", var1, var1);
    var1 = -3;
    printf("unsigned var1 = 0x%x,  %d \n", var1, var1);

    var2 = 0xfffffffe;
    printf("signed var2 = 0x%x,  %d \n", var2, var2);
    var2 = -3;
    printf("signed var2 = 0x%x,  %d \n", var2, var2);
    var2 = 0xffffff8c;
    printf("signed var2 = 0x%x,  %d \n", var2, var2);

    printf("====================================================\n");
    printf("// detect if two integers have opposite signs \n");
    var2 = -3;
    var3 =  3;
    printf("signed var1 = 0x%x,  0x%x => 0x%x\n", var2, var3, (var2^var3)>>31);

    printf("====================================================\n");
    printf("// x * 3.5 = x *(3+0.5) = 3*x + 0.5*x\n");
    printf("//         = x + 2*x + x/2\n");
    printf("//         = x + x<<1 + x>>1\n");
    var = 2;
    printf("%d,  %d\n", (int)(var*3.5), (var+(var<<1)+(var>>1)));

    printf("====================================================\n");
    var0 = 0x10000;
    printf("// detect if 0x%x only 1 bit is set \n", var0);
    if((var0&(var0-1)) == 0) { printf("yes, it has only one bit is set\n"); }
    else { printf("No\n"); }

    printf("====================================================\n");
    var0 = 0x10000; var1 = 4;
    printf("// check if 0x%x is power of 0x%x \n", var0, var1);
    if(((var0&(var0-1)) == 0) && ((var0&0xaaaaaaaa)==0)) { printf("Yes\n"); }
    else { printf("No\n"); }

    printf("====================================================\n");
    var0 = 0x1000; var1 = 2;
    printf("// check if 0x%x is power of 0x%x \n", var0, var1);
    if(((var0&(var0-1)) == 0)) { printf("Yes\n"); }
    else { printf("No\n"); }

    printf("====================================================\n");
    printf("// Bit masking \n");
    var0 = 0xaaaaaaaa;
    i = 7; j = 14; maskingBit;
    maskingBit = ((1 << (j-i+1)) - 1) << i;
    printf("0x%08x & 0x%08x = 0x%08x \n", maskingBit, var0, var0 & maskingBit);

    printf("====================================================\n");
    printf("// swap niddle in a byte \n");
    var0 = 0xaf;
    printf("swap 0x%x is 0x%x \n", var0, ((var0 & 0xf)<<4)|((var0 &0xf0)>>4));

    printf("====================================================\n");
    printf("// convert big-endian to little-endian\n");
    var0 = 0x78563412;
    printf("convert little-endian(0x%x) to big-endian(0x%x) \n"
            , var0, ((var0>>24)|((var0&0x00FF0000)>>8)|((var0&0x0000FF00)<<8)|(var0<<24)));

    printf("====================================================\n");
    printf("// read-modify-write\n");
    int regVal = 0xffff; int curVal; int clearBit, maskBit = 0x00F0; int dataToWr=0x6;
    curVal = regVal;
    curVal = curVal & ~maskBit;
    curVal |= (dataToWr << 4);
    printf("read-modify-write: origin value (0x%x) -> 0x%x\n", regVal, curVal);

    printf("====================================================\n");
    var0 = 27; int poWer = 3;
    printf("// check if %d is power of %d \n", var0, poWer);
    while(var0 > 0)
    {
        int remAin=0;
        remAin = var0 % poWer;
        var0 = var0 / poWer;
        printf("var0: %d, remain: %d \n", var0, remAin);
        if((remAin != 0) && (var0 != 0))
        { 
            printf("this is NOT power of %d\n", poWer); 
            break;
        }
    }

    printf("====================================================\n");
    printf("// double, float, fixed point, floating point\n");
    double b=4, a=5, c=6;
    double d = b*b - 4.0*a*c; 
    double sd = d * d; 
    double r1 = (-b + sd) / (2.0*a); 
    double r2 = (-b - sd) / (2.0*a); 
    printf("double = %.5f\t%.5f\n", r1, r2); 

    float b1=4, a1=5, c1=6;
    float d1 = b1*b1 - 4.0*a1*c1; 
    float sd1 = d1 * d1; 
    float r11 = (-b1 + sd1) / (2.0*a1); 
    float r21 = (-b1 - sd1) / (2.0*a1); 
    printf("float  = %.5f\t%.5f\n", r11, r21); 

    printf("====================================================\n");
    printf("// fixed point arithmetic \n");
    // integer (MSB)    fraction (LSB)
    //       v                 v
    //0000000000000000.0000000000000000
    #define SHIFT_AMOUNT 16 // 2^16 = 65536
    #define SHIFT_MASK ((1 << SHIFT_AMOUNT) - 1) // 65535 (all LSB set, all MSB clear)

    int price = 500 << SHIFT_AMOUNT;
    printf("500 << SHIFT_AMOUNT => 0x%x, %d\n", price, price);
    price += 10 << SHIFT_AMOUNT;
    printf("+= 10 << SHIFT_AMOUNT => 0x%x, %d\n", price, price);
    price *= 3;
    printf("*= 3 => 0x%x, %d\n", price, price);
    price /= 4;
    printf("/= 4 => 0x%x, %d\n", price, price);
    printf("price integer is %d\n", price >> SHIFT_AMOUNT);
    printf("price fraction is %d\n", price & SHIFT_MASK);
    printf("price fraction in decimal is %f\n", ((double)(price & SHIFT_MASK) / (1 << SHIFT_AMOUNT)));
    printf("price is roughly %d.%lld\n", price >> SHIFT_AMOUNT, (long long)(price & SHIFT_MASK) * 100000 / (1 << SHIFT_AMOUNT));

    float priceConfirm = 500;
    priceConfirm += 10; priceConfirm *= 3; priceConfirm /= 4;
    printf("confirm with floating = %f\n", priceConfirm);

    double priceConfirmD = 500;
    priceConfirmD += 10; priceConfirmD *= 3; priceConfirmD /= 4;
    printf("confirm with double = %f\n", priceConfirmD);

    printf("sizeof(int) = %d \n", (int)(sizeof(int)));
    printf("sizeof(float) = %d \n", (int)(sizeof(float)));
    printf("sizeof(double) = %d \n", (int)(sizeof(double)));
    printf("sizeof(long long) = %d \n", (int)(sizeof(long long)));

}
#endif

#if 0
// 2's complement
-2^(n-1) < s < 2^(n-1) - 1
dec	hex	signed
0	0	0
1	1	1
2	2	2
3	3	3
4	4	4
5	5	5
6	6	6
7	7	7
8	8	8
9	9	9
10	A	10
11	B	11
12	C	12
13	D	13
14	E	14
15	F	15
16	10	-16
17	11	-15
18	12	-14
19	13	-13
20	14	-12
21	15	-11
22	16	-10
23	17	-9
24	18	-8
25	19	-7
26	1A	-6
27	1B	-5
28	1C	-4
29	1D	-3
30	1E	-2
31	1F	-1
#endif