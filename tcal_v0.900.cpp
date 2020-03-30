// tcal_v0.900.cpp : Defines the entry point for the console application.

//

 

 

#include "stdafx.h"

 

#include <stdio.h>

#include <math.h>

#include <stdarg.h>

#include <stdlib.h>     /* malloc, free, rand */

#include <stdio.h>     /* malloc, free, rand */

#include <ctype.h>

 

typedef double                                 INT64;

typedef unsigned int      UINT32;

typedef signed int                            INT32;

typedef unsigned short UINT16;

typedef unsigned char   UINT8;

 

/*****************************************************************

* version 0.100; in.txt is from VFS_AHCICmdCheck_csv.pevs

* version 0.200; in.txt is from VFS_AHCICmdCheck_csv.pevs

*                                                             dynamic cmdsdb buffer size

* version 0.300; in.txt is from VFS_AHCICmdCheck_csv_all_decimal.pevs

process with decimal

0.301;

* version 0.400; in.txt is from VFS_AHCICmdCheck_csv_dec_hex_mixed.pevs

0.401; increase CmdSdbBUFSize 128 -> 2048

* version 0.500;

* version 0.501;

* version 0.502;

* version 0.503; first code to sort by 4096 line unit

* version 0.504;

* version 0.505;

* version 0.506; first code to sort and confirmation

* version 0.600; first code to sort and confirmation, fixed issue from 0.506

* version 0.601;

* version 0.602; generate cmdlbasc and CmdExeTimeCal file

* version 0.603; fixed ordering confirmation issue.

*                Input   -> LBA:hex, SC:hex, TagNum:dec

*                Output  -> LBA:dec, SC:dec, TagNum:dec, CmdExeTime:dec

* version 0.700; tag number is hex in input file

* version 0.701;

*                Input   -> LBA:hex, SC:hex, TagNum:hex

*                Output  -> LBA:dec, SC:dec, TagNum:hex, CmdExeTime:dec

* version 0.702; fixed "SET FEATURE", "IDENTIFY DEVICE" handling, Cmd/SDB buffer was not cleared.

* version 0.702; do not display "SET FEATURE", "IDENTIFY DEVICE" command

* version 0.800; SDB input should be BIT wise.(00001000, 00004000)

*****************************************************************/

#define K1234567             "*************************************************************"

#define VERSION              "   Command Execution Time Cal ver 0.800   "

#define INPUTTYPE         "Input   -> LBA:hex, SC:hex, TagNum:hex, SDB:00001000"

#define OUTPUTTYPE     "Output  -> LBA:dec, SC:dec, TagNum:hex, CmdExeTime:dec"

#define BLANKLINE 0

 

FILE *fin, *fidx, *fusec, *fcmd, *flba, *fsc, *ftag, *fbypass;

FILE *fout, *foutt, *foutt1, *foutc, *fouts, *fouts1;

 

UINT16 CntCmd0idx = 0, CntCmd1us = 0, CntCmd2cmd = 0, CntCmd3lba = 0, CntCmd4sc = 0, CntCmd5tag = 0;

UINT16 CntSdb0idx = 0, CntSdb1us = 0, CntSdb2cmd = 0, CntSdb4bit = 0;

 

#define CmdSdbBUFSize               2048//256//1024              //KK_

#define SdbBUFCheck                    1024//128//512                                 //KK_

#define reorderBUFSize 4096//256//1024              //KK_

 

#define DebugPrintf                                       0              //KK_

#define DebugSETFEAUTRE                         0              //KK_

 

#define HexInput                                             0              //KK_ 0:hex, 1:decimal, 2:hex/dec mixed

#define DecInput                                             1              //KK_ 0:hex, 1:decimal, 2:hex/dec mixed

#define HexDecInput                                     2              //KK_ 0:hex, 1:decimal, 2:hex/dec mixed

#define InputFileType                    HexDecInput     //KK_

#define tagHex                                                 1              //KK_

 

struct Cmd{

                char Cmd0idx[32];

                char  Cmd1us[32];

                char Cmd2cmd[32];

                char Cmd3lba[32];

                char  Cmd4sc[32];

                char Cmd5tag[32];

                char Cmd6ExeTime[32];

                UINT32 Cmd0idxNum;

                INT64    Cmd1usNum;

                UINT32 Cmd3lbaNum;

                UINT32 Cmd4scNum;

                UINT32 Cmd5tagNum;

                UINT32 CmdExeTime;

};

 

struct Sdb{

                char Sdb0idx[32];

                char  Sdb1us[32];

                char Sdb2cmd[32];

                char Sdb3bit[32];

                UINT32 Sdb0idxNum;

                INT64 Sdb1usNum;

                UINT32 Sdb3bitNum;

};

 

struct Cmd stcmd[CmdSdbBUFSize];

struct Sdb stsdb[CmdSdbBUFSize];

struct Cmd stmisccmd[100];

struct Cmd sttemp;

struct Cmd streorder[reorderBUFSize];

UINT16 sttempcnt = 0;

char       c;

UINT16 stcmdemptyflag = 0, stsdbemptyflag = 0;

UINT32 cmdindex = 0, sdbindex = 0, misccmdindex = 0;

UINT32  reorderindex = 0, reorderGroup = 0, jjreorder, kkreorder;

INT32    iireorder;

UINT32  displaylineindex;

UINT32 cmdindexcnt, sdbindexcnt;

UINT16 commacnt = 0;

UINT16  reorderindextmp = 0;

UINT16 ii = 0, jj = 0, kk = 0;

UINT16 j, k, l, m;

UINT32 BitShift0, BitShift1, BitShift2;

UINT16  lbasize, scsize, tagsize, misccmdin = 0;

UINT16  sdbtagsize = 0;

UINT32 LineCount;

INT64    Cmd1usNumForMiscCmdExeTime;

UINT32 tempcmdexesum = 0, acccmdexesum = 0; //KK_

 

UINT16 aa = 0, bb = 0, cc = 0, dd = 0, ee = 0, ff = 0;

 

UINT16 CharArraySizeCheck(char *ptr)

{

                int offset = 0;

                int count = 0;

                while (*(ptr + offset) != '\0')

                {

                                ++count;

                                ++offset;

                }

                return count;

}

 

UINT16 ch2hex(char ch)

{

                if (isdigit(ch))                     return (ch - '0');

                if (islower(ch))                  return (ch - 'a' + 10);

                if (isupper(ch))                  return (ch - 'A' + 10);

}

 

UINT32 str2hex(char arr[8])

{

                return ((ch2hex(arr[0]) << 28) | (ch2hex(arr[1]) << 24) | (ch2hex(arr[2]) << 20) | (ch2hex(arr[3]) << 16) | (ch2hex(arr[4]) << 12) | (ch2hex(arr[5]) << 8) | (ch2hex(arr[6]) << 4) | ch2hex(arr[7]));

}

 

UINT32 str2dec(char arr[8], UINT16 size)

{

                if (size == 8)

                {

                                return ((ch2hex(arr[0]) * (1 << 28)) + (ch2hex(arr[1]) * (1 << 24)) + (ch2hex(arr[2]) * (1 << 20)) + (ch2hex(arr[3])*(1 << 16)) + (ch2hex(arr[4])*(1 << 12)) + (ch2hex(arr[5])*(1 << 8)) + (ch2hex(arr[6])*(1 << 4)) + ch2hex(arr[7]));

                }

                else if (size == 7)

                {

                                return ((ch2hex(arr[0]) * (1 << 24)) + (ch2hex(arr[1]) * (1 << 20)) + (ch2hex(arr[2]) * (1 << 16)) + (ch2hex(arr[3])*(1 << 12)) + (ch2hex(arr[4])*(1 << 8)) + (ch2hex(arr[5])*(1 << 4)) + ch2hex(arr[6]));

                }

                else if (size == 6)

                {

                                return ((ch2hex(arr[0]) * (1 << 20)) + (ch2hex(arr[1]) * (1 << 16)) + (ch2hex(arr[2]) * (1 << 12)) + (ch2hex(arr[3])*(1 << 8)) + (ch2hex(arr[4])*(1 << 4)) + ch2hex(arr[5]));

                }

                else if (size == 5)

                {

                                return ((ch2hex(arr[0]) * (1 << 16)) + (ch2hex(arr[1]) * (1 << 12)) + (ch2hex(arr[2]) * (1 << 8)) + (ch2hex(arr[3])*(1 << 4)) + ch2hex(arr[4]));

                }

                else if (size == 4)

                {

                                return ((ch2hex(arr[0]) * (1 << 12)) + (ch2hex(arr[1]) * (1 << 8)) + (ch2hex(arr[2]) * (1 << 4)) + ch2hex(arr[3]));

                }

                else if (size == 3)

                {

                                return ((ch2hex(arr[0]) * (1 << 8)) + (ch2hex(arr[1]) * (1 << 4)) + ch2hex(arr[2]));

                }

                else if (size == 2)

                {

                                return ((ch2hex(arr[0]) * (1 << 4)) + ch2hex(arr[1]));

                }

                else if (size == 1)

                {

                                return (ch2hex(arr[0]));

                }

}

 

//void ReorderByIdx(int iteration);

void SortAndDisplay(int iteration);

void SortAndDisplayAgain(int iteration);

void DisplayOnly(int displayline);

void DisplaySomeFactor();

void DisplayCommandOnly();

void fetch();

void DisplayOnlyTmp();

 

void main()

{

                printf("%s\n", K1234567);

                printf("%s\n", VERSION);

                printf("%s\n", INPUTTYPE);

                printf("%s\n", OUTPUTTYPE);

                printf("%s\n", K1234567);

 

                fin = fopen("1.log", "r");

                fouts = fopen("2inCmdAnalysis.log", "w");

                DisplayOnlyTmp();

                fclose(fouts); fclose(fin);

 

                fin = fopen("2inCmdAnalysis.log", "r");

                foutt  = fopen("3CmdOnlySec.txt", "w");

                foutt1 = fopen("3CmdOnly.txt", "w");

               

                DisplayCommandOnly();

 

                printf("\n");

 

                fclose(foutt1); fclose(foutt); fclose(fin);

                printf("Command Display Only\n");

                printf("\n");

 

}

 

void DisplayOnlyTmp()

{

                displaylineindex = 0;

 

                while ((c = fgetc(fin)) != EOF)

                {

                                switch (commacnt)

                                {

                                case 0:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd0idx[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 1:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd1us[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 2:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd2cmd[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fcmd);

                                                }

                                                break;

                                case 3:

                                                //if(c == 0x0a)                                    //0x0A=LF, 0x0D=CR for "SDB"

                                                if ((c == 0x0a) || (c == 0x0d))                                       //0x0A=LF, 0x0D=CR for "SDB"

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd3lba[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,flba);

                                                }

                                                break;

                                case 4:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd4sc[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fsc);

                                                }

                                                break;

                                case 5:

                                                //if(c == 0x0a)                                    //0x0A=LF, 0x0D=CR for "READ FPDMA", "WRITE FPDMA"

                                                if ((c == 0x0a) || (c == 0x0d))

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd5tag[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                default:

                                                break;

                                }

                                if (c == 0x2c)                                                       //if c= comma

                                {

                                                sttempcnt = 0;

                                                commacnt++;

                                }

 

                                if ((c == '\t') || (c == ' ')) //the end of line -> 0x0A=LF, 0x0D=CR, to process line after line feed.

                                {

                                }

                                else if (c == 0x0a)              //the end of line -> 0x0A=LF, 0x0D=CR, to process line after line feed.

                                {

                                                sttempcnt = 0;

                                                if (commacnt == 5)

                                                {

                                                                fprintf(fouts, "%s,%s,%s,%s,%s,%s\n", sttemp.Cmd0idx, sttemp.Cmd1us, sttemp.Cmd2cmd,

                                                                                sttemp.Cmd3lba, sttemp.Cmd4sc, sttemp.Cmd5tag);

                                                }

                                                else if (commacnt == 3)

                                                {

                                                                UINT16 i = 0, j = 0, k = 0, incnt = 0;

                                                                UINT16 SaveSDB[32];

 

                                                                for (i = 8; i >= 1; i--)

                                                                {

                                                                                for (j = 0; j < 4; j++)

                                                                                {

                                                                                                if (((ch2hex(sttemp.Cmd3lba[i - 1]) >> j) & 1) == 1)

                                                                                                {

                                                                                                                k++;

                                                                                                                SaveSDB[k - 1] = (7 - (i - 1)) * 4 + j;

                                                                                                }

                                                                                }

                                                                }

                                                                //printf("%x%x%x%x%x%x%x%x  ", ch2hex(sttemp.Cmd3lba[0]), ch2hex(sttemp.Cmd3lba[1]), ch2hex(sttemp.Cmd3lba[2]), ch2hex(sttemp.Cmd3lba[3]),

                                                                //            ch2hex(sttemp.Cmd3lba[4]), ch2hex(sttemp.Cmd3lba[5]), ch2hex(sttemp.Cmd3lba[6]), ch2hex(sttemp.Cmd3lba[7]));

                                                                //printf("k = %x\n", k);

                                                                if (k == 1)

                                                                {

                                                                                //            printf("%s,%s,%s,%x\n", sttemp.Cmd0idx, sttemp.Cmd1us, sttemp.Cmd2cmd, SaveSDB[k-1]);

                                                                                fprintf(fouts, "%s,%s,%s,%x\n", sttemp.Cmd0idx, sttemp.Cmd1us, sttemp.Cmd2cmd, SaveSDB[k - 1]);

                                                                }

                                                                else

                                                                {

                                                                                for (i = 0; i < k; i++)

                                                                                {

                                                                                                //                            printf("%s,%s,%s,%x\n", sttemp.Cmd0idx, sttemp.Cmd1us, sttemp.Cmd2cmd, SaveSDB[i]);

                                                                                                fprintf(fouts, "%s,%s,%s,%x\n", sttemp.Cmd0idx, sttemp.Cmd1us, sttemp.Cmd2cmd, SaveSDB[i]);

                                                                                }

                                                                }

                                                                k = 0;

                                                }

 

                                                //clear sttemp char array.

                                                for (ii = 0; ii<32; ii++)

                                                {

                                                                sttemp.Cmd0idx[ii] = 0;

                                                                sttemp.Cmd1us[ii] = 0;

                                                                sttemp.Cmd2cmd[ii] = 0;

                                                                sttemp.Cmd3lba[ii] = 0;

                                                                sttemp.Cmd4sc[ii] = 0;

                                                                sttemp.Cmd5tag[ii] = 0;

                                                                sttemp.Cmd6ExeTime[ii] = 0;

                                                }

                                                commacnt = 0;

                                                displaylineindex++;

 

                                } //if(c == 0x0a)

                } //while((c=fgetc(fin)) != EOF)

}

 

void DisplayOnly(int displayline)

{

                displaylineindex = 0;

 

                while (((c = fgetc(fin)) != EOF) && (displaylineindex < displayline))

                {

                                switch (commacnt)

                                {

                                case 0:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd0idx[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 1:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd1us[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 2:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd2cmd[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fcmd);

                                                }

                                                break;

                                case 3:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd3lba[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,flba);

                                                }

                                                break;

                                case 4:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd4sc[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fsc);

                                                }

                                                break;

                                case 5:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR for "READ FPDMA", "WRITE FPDMA"

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd5tag[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                case 6:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR for "READ FPDMA", "WRITE FPDMA"

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd6ExeTime[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                default:

                                                break;

                                }

                                if (c == 0x2c)                                                       //if c= comma

                                {

                                                sttempcnt = 0;

                                                commacnt++;

                                }

 

                                if (c == 0x0a)       //the end of line -> 0x0A=LF, 0x0D=CR, to process line after line feed.

                                {

                                                sttempcnt = 0;

                                                fprintf(fouts, "%s,%s,%s,%s,%s,%s,%s\n", sttemp.Cmd0idx, sttemp.Cmd1us, sttemp.Cmd2cmd,

                                                                sttemp.Cmd3lba, sttemp.Cmd4sc, sttemp.Cmd5tag, sttemp.Cmd6ExeTime);

 

                                                //clear sttemp char array.

                                                for (ii = 0; ii<32; ii++)

                                                {

                                                                sttemp.Cmd0idx[ii] = 0;

                                                                sttemp.Cmd1us[ii] = 0;

                                                                sttemp.Cmd2cmd[ii] = 0;

                                                                sttemp.Cmd3lba[ii] = 0;

                                                                sttemp.Cmd4sc[ii] = 0;

                                                                sttemp.Cmd5tag[ii] = 0;

                                                                sttemp.Cmd6ExeTime[ii] = 0;

                                                }

                                                commacnt = 0;

                                                displaylineindex++;

 

                                } //if(c == 0x0a)

                } //while((c=fgetc(fin)) != EOF)

}

 

void SortAndDisplay(int iteration)

{

                UINT16 outcnt, incnt;

 

                reorderGroup = 0;

                reorderindex = 0;

 

                while ((c = fgetc(fin)) != EOF)

                {

                                switch (commacnt)

                                {

                                case 0:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd0idx[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 1:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd1us[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 2:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd2cmd[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fcmd);

                                                }

                                                break;

                                case 3:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd3lba[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,flba);

                                                }

                                                break;

                                case 4:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd4sc[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fsc);

                                                }

                                                break;

                                case 5:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR for "READ FPDMA", "WRITE FPDMA"

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd5tag[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                case 6:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR for "READ FPDMA", "WRITE FPDMA"

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd6ExeTime[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                default:

                                                break;

                                }

                                if (c == 0x2c)                                                       //if c = comma

                                {

                                                sttempcnt = 0;

                                                commacnt++;

                                }

 

                                if (c == 0x0a)       //the end of line -> 0x0A=LF, 0x0D=CR, to process line after line feed.

                                {

                                                sttempcnt = 0;

                                                reorderindextmp = reorderindex % iteration;

 

                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                {

                                                                streorder[reorderindextmp].Cmd0idx[k] = sttemp.Cmd0idx[k];

                                                                streorder[reorderindextmp].Cmd1us[k] = sttemp.Cmd1us[k];

                                                                streorder[reorderindextmp].Cmd2cmd[k] = sttemp.Cmd2cmd[k];

                                                                streorder[reorderindextmp].Cmd3lba[k] = sttemp.Cmd3lba[k];

                                                                streorder[reorderindextmp].Cmd4sc[k] = sttemp.Cmd4sc[k];

                                                                streorder[reorderindextmp].Cmd5tag[k] = sttemp.Cmd5tag[k];

                                                                streorder[reorderindextmp].Cmd6ExeTime[k] = sttemp.Cmd6ExeTime[k];

                                                }

                                                //streorder[reorderindextmp].Cmd0idxNum  = atoi(streorder[reorderindextmp].Cmd0idx);

                                                streorder[reorderindextmp].Cmd0idxNum = sttemp.Cmd0idxNum = atoi(streorder[reorderindextmp].Cmd0idx);

 

                                                //clear sttemp char array.

                                                for (ii = 0; ii<32; ii++)

                                                {

                                                                sttemp.Cmd0idx[ii] = 0;

                                                                sttemp.Cmd1us[ii] = 0;

                                                                sttemp.Cmd2cmd[ii] = 0;

                                                                sttemp.Cmd3lba[ii] = 0;

                                                                sttemp.Cmd4sc[ii] = 0;

                                                                sttemp.Cmd5tag[ii] = 0;

                                                                sttemp.Cmd6ExeTime[ii] = 0;

                                                }

                                                if ((reorderindextmp) == (iteration - 1))

                                                {

                                                                //printf("((reorderindextmp) == (iteration-1))\n");

                                                                for (outcnt = 0; outcnt<(iteration - 1); ++outcnt)

                                                                {

                                                                                for (incnt = 0; incnt<(iteration - 1 - outcnt); ++incnt)

                                                                                {

                                                                                                if (streorder[incnt].Cmd0idxNum >= streorder[incnt + 1].Cmd0idxNum)

                                                                                                {

                                                                                                                //printf("before %d:%s,%s, %d:%s,%s\n", incnt, streorder[incnt].Cmd0idx, streorder[incnt].Cmd1us, incnt+1, streorder[incnt+1].Cmd0idx, streorder[incnt+1].Cmd1us);

                                                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                                                {

                                                                                                                                sttemp.Cmd0idx[k] = streorder[incnt + 1].Cmd0idx[k];

                                                                                                                                sttemp.Cmd1us[k] = streorder[incnt + 1].Cmd1us[k];

                                                                                                                                sttemp.Cmd2cmd[k] = streorder[incnt + 1].Cmd2cmd[k];

                                                                                                                                sttemp.Cmd3lba[k] = streorder[incnt + 1].Cmd3lba[k];

                                                                                                                                sttemp.Cmd4sc[k] = streorder[incnt + 1].Cmd4sc[k];

                                                                                                                                sttemp.Cmd5tag[k] = streorder[incnt + 1].Cmd5tag[k];

                                                                                                                                sttemp.Cmd6ExeTime[k] = streorder[incnt + 1].Cmd6ExeTime[k];

                                                                                                                }

                                                                                                                sttemp.Cmd0idxNum = streorder[incnt + 1].Cmd0idxNum;

 

                                                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                                                {

                                                                                                                                streorder[incnt + 1].Cmd0idx[k] = streorder[incnt].Cmd0idx[k];

                                                                                                                                streorder[incnt + 1].Cmd1us[k] = streorder[incnt].Cmd1us[k];

                                                                                                                                streorder[incnt + 1].Cmd2cmd[k] = streorder[incnt].Cmd2cmd[k];

                                                                                                                                streorder[incnt + 1].Cmd3lba[k] = streorder[incnt].Cmd3lba[k];

                                                                                                                                streorder[incnt + 1].Cmd4sc[k] = streorder[incnt].Cmd4sc[k];

                                                                                                                                streorder[incnt + 1].Cmd5tag[k] = streorder[incnt].Cmd5tag[k];

                                                                                                                                streorder[incnt + 1].Cmd6ExeTime[k] = streorder[incnt].Cmd6ExeTime[k];

                                                                                                                }

                                                                                                                streorder[incnt + 1].Cmd0idxNum = streorder[incnt].Cmd0idxNum;

 

                                                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                                                {

                                                                                                                                streorder[incnt].Cmd0idx[k] = sttemp.Cmd0idx[k];

                                                                                                                                streorder[incnt].Cmd1us[k] = sttemp.Cmd1us[k];

                                                                                                                                streorder[incnt].Cmd2cmd[k] = sttemp.Cmd2cmd[k];

                                                                                                                                streorder[incnt].Cmd3lba[k] = sttemp.Cmd3lba[k];

                                                                                                                                streorder[incnt].Cmd4sc[k] = sttemp.Cmd4sc[k];

                                                                                                                                streorder[incnt].Cmd5tag[k] = sttemp.Cmd5tag[k];

                                                                                                                                streorder[incnt].Cmd6ExeTime[k] = sttemp.Cmd6ExeTime[k];

                                                                                                                }

                                                                                                                streorder[incnt].Cmd0idxNum = sttemp.Cmd0idxNum;

                                                                                                }

                                                                                }

                                                                }

                                                                for (outcnt = 0; outcnt<(iteration); outcnt++)

                                                                {

                                                                                fprintf(fouts, "%s,%s,%s,%s,%s,%s,%s\n", streorder[outcnt].Cmd0idx, streorder[outcnt].Cmd1us, streorder[outcnt].Cmd2cmd,

                                                                                                streorder[outcnt].Cmd3lba, streorder[outcnt].Cmd4sc, streorder[outcnt].Cmd5tag, streorder[outcnt].Cmd6ExeTime);

                                                                }

                                                                reorderGroup++;

                                                }              //if((reorderindextmp) == (iteration-1))

 

                                                //clear sttemp char array.

                                                for (ii = 0; ii<32; ii++)

                                                {

                                                                sttemp.Cmd0idx[ii] = 0;

                                                                sttemp.Cmd1us[ii] = 0;

                                                                sttemp.Cmd2cmd[ii] = 0;

                                                                sttemp.Cmd3lba[ii] = 0;

                                                                sttemp.Cmd4sc[ii] = 0;

                                                                sttemp.Cmd5tag[ii] = 0;

                                                                sttemp.Cmd6ExeTime[ii] = 0;

                                                }

                                                commacnt = 0;

                                                reorderindex++;

 

 

                                } //if(c == 0x0a)

                } //while((c=fgetc(fin)) != EOF)

                iireorder = reorderindex - (reorderGroup * reorderBUFSize);

                printf("remaining line = %d\n", iireorder);

                if (iireorder >= 0)

                {

                                reorderindextmp = iireorder % iteration;

 

                                //clear sttemp char array.

                                for (ii = 0; ii<32; ii++)

                                {

                                                sttemp.Cmd0idx[ii] = 0;

                                                sttemp.Cmd1us[ii] = 0;

                                                sttemp.Cmd2cmd[ii] = 0;

                                                sttemp.Cmd3lba[ii] = 0;

                                                sttemp.Cmd4sc[ii] = 0;

                                                sttemp.Cmd5tag[ii] = 0;

                                                sttemp.Cmd6ExeTime[ii] = 0;

                                }

 

                                for (outcnt = 0; outcnt<(iireorder - 1); ++outcnt)

                                {

                                                for (incnt = 0; incnt<(iireorder - 1 - outcnt); ++incnt)

                                                {

                                                                if (streorder[incnt].Cmd0idxNum >= streorder[incnt + 1].Cmd0idxNum)

                                                                {

                                                                                //printf("before %d:%s,%s, %d:%s,%s\n", incnt, streorder[incnt].Cmd0idx, streorder[incnt].Cmd1us, incnt+1, streorder[incnt+1].Cmd0idx, streorder[incnt+1].Cmd1us);

                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                {

                                                                                                sttemp.Cmd0idx[k] = streorder[incnt + 1].Cmd0idx[k];

                                                                                                sttemp.Cmd1us[k] = streorder[incnt + 1].Cmd1us[k];

                                                                                                sttemp.Cmd2cmd[k] = streorder[incnt + 1].Cmd2cmd[k];

                                                                                                sttemp.Cmd3lba[k] = streorder[incnt + 1].Cmd3lba[k];

                                                                                                sttemp.Cmd4sc[k] = streorder[incnt + 1].Cmd4sc[k];

                                                                                                sttemp.Cmd5tag[k] = streorder[incnt + 1].Cmd5tag[k];

                                                                                                sttemp.Cmd6ExeTime[k] = streorder[incnt + 1].Cmd6ExeTime[k];

                                                                                }

                                                                                sttemp.Cmd0idxNum = streorder[incnt + 1].Cmd0idxNum;

 

                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                {

                                                                                                streorder[incnt + 1].Cmd0idx[k] = streorder[incnt].Cmd0idx[k];

                                                                                                streorder[incnt + 1].Cmd1us[k] = streorder[incnt].Cmd1us[k];

                                                                                                streorder[incnt + 1].Cmd2cmd[k] = streorder[incnt].Cmd2cmd[k];

                                                                                                streorder[incnt + 1].Cmd3lba[k] = streorder[incnt].Cmd3lba[k];

                                                                                                streorder[incnt + 1].Cmd4sc[k] = streorder[incnt].Cmd4sc[k];

                                                                                                streorder[incnt + 1].Cmd5tag[k] = streorder[incnt].Cmd5tag[k];

                                                                                                streorder[incnt + 1].Cmd6ExeTime[k] = streorder[incnt].Cmd6ExeTime[k];

                                                                                }

                                                                                streorder[incnt + 1].Cmd0idxNum = streorder[incnt].Cmd0idxNum;

 

                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                {

                                                                                                streorder[incnt].Cmd0idx[k] = sttemp.Cmd0idx[k];

                                                                                                streorder[incnt].Cmd1us[k] = sttemp.Cmd1us[k];

                                                                                                streorder[incnt].Cmd2cmd[k] = sttemp.Cmd2cmd[k];

                                                                                                streorder[incnt].Cmd3lba[k] = sttemp.Cmd3lba[k];

                                                                                                streorder[incnt].Cmd4sc[k] = sttemp.Cmd4sc[k];

                                                                                                streorder[incnt].Cmd5tag[k] = sttemp.Cmd5tag[k];

                                                                                                streorder[incnt].Cmd6ExeTime[k] = sttemp.Cmd6ExeTime[k];

                                                                                }

                                                                                streorder[incnt].Cmd0idxNum = sttemp.Cmd0idxNum;

 

                                                                                //printf("after %d:%s,%s, %d:%s,%s\n", incnt, streorder[incnt].Cmd0idx, streorder[incnt].Cmd1us, incnt+1, streorder[incnt+1].Cmd0idx, streorder[incnt+1].Cmd1us);

                                                                                //printf(" \n");

                                                                }

                                                }

                                }

                                for (outcnt = 0; outcnt<(iireorder); outcnt++)

                                {

                                                fprintf(fouts, "%s,%s,%s,%s,%s,%s,%s\n", streorder[outcnt].Cmd0idx, streorder[outcnt].Cmd1us, streorder[outcnt].Cmd2cmd,

                                                                streorder[outcnt].Cmd3lba, streorder[outcnt].Cmd4sc, streorder[outcnt].Cmd5tag, streorder[outcnt].Cmd6ExeTime);

                                }

 

                                //clear sttemp char array.

                                for (ii = 0; ii<32; ii++)

                                {

                                                sttemp.Cmd0idx[ii] = 0;

                                                sttemp.Cmd1us[ii] = 0;

                                                sttemp.Cmd2cmd[ii] = 0;

                                                sttemp.Cmd3lba[ii] = 0;

                                                sttemp.Cmd4sc[ii] = 0;

                                                sttemp.Cmd5tag[ii] = 0;

                                                sttemp.Cmd6ExeTime[ii] = 0;

                                }

                }

}

 

void SortAndDisplayAgain(int iteration)

{

                UINT16 outcnt, incnt;

 

                reorderGroup = 0;

                reorderindex = 0;

 

                while ((c = fgetc(fin)) != EOF)

                {

                                switch (commacnt)

                                {

                                case 0:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd0idx[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 1:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd1us[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 2:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd2cmd[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fcmd);

                                                }

                                                break;

                                case 3:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd3lba[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,flba);

                                                }

                                                break;

                                case 4:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd4sc[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fsc);

                                                }

                                                break;

                                case 5:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR for "READ FPDMA", "WRITE FPDMA"

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd5tag[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                case 6:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR for "READ FPDMA", "WRITE FPDMA"

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd6ExeTime[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                default:

                                                break;

                                }

                                if (c == 0x2c)                                                       //if c = comma

                                {

                                                sttempcnt = 0;

                                                commacnt++;

                                }

 

                                if (c == 0x0a)       //the end of line -> 0x0A=LF, 0x0D=CR, to process line after line feed.

                                {

                                                sttempcnt = 0;

 

                                                if (reorderindex < (iteration / 2))

                                                {

                                                                fprintf(fouts, "%s,%s,%s,%s,%s,%s,%s\n", sttemp.Cmd0idx, sttemp.Cmd1us, sttemp.Cmd2cmd,

                                                                                sttemp.Cmd3lba, sttemp.Cmd4sc, sttemp.Cmd5tag, sttemp.Cmd6ExeTime);

                                                                //clear sttemp char array.

                                                                for (ii = 0; ii<32; ii++)

                                                                {

                                                                                sttemp.Cmd0idx[ii] = 0;

                                                                                sttemp.Cmd1us[ii] = 0;

                                                                                sttemp.Cmd2cmd[ii] = 0;

                                                                                sttemp.Cmd3lba[ii] = 0;

                                                                                sttemp.Cmd4sc[ii] = 0;

                                                                                sttemp.Cmd5tag[ii] = 0;

                                                                                sttemp.Cmd6ExeTime[ii] = 0;

                                                                }

 

                                                }

                                                else

                                                {

                                                                reorderindextmp = (reorderindex - (iteration / 2)) % iteration;

 

                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                {

                                                                                streorder[reorderindextmp].Cmd0idx[k] = sttemp.Cmd0idx[k];

                                                                                streorder[reorderindextmp].Cmd1us[k] = sttemp.Cmd1us[k];

                                                                                streorder[reorderindextmp].Cmd2cmd[k] = sttemp.Cmd2cmd[k];

                                                                                streorder[reorderindextmp].Cmd3lba[k] = sttemp.Cmd3lba[k];

                                                                                streorder[reorderindextmp].Cmd4sc[k] = sttemp.Cmd4sc[k];

                                                                                streorder[reorderindextmp].Cmd5tag[k] = sttemp.Cmd5tag[k];

                                                                                streorder[reorderindextmp].Cmd6ExeTime[k] = sttemp.Cmd6ExeTime[k];

                                                                }

                                                                //streorder[reorderindextmp].Cmd0idxNum  = atoi(streorder[reorderindextmp].Cmd0idx);

                                                                streorder[reorderindextmp].Cmd0idxNum = sttemp.Cmd0idxNum = atoi(streorder[reorderindextmp].Cmd0idx);

 

                                                                //clear sttemp char array.

                                                                for (ii = 0; ii<32; ii++)

                                                                {

                                                                                sttemp.Cmd0idx[ii] = 0;

                                                                                sttemp.Cmd1us[ii] = 0;

                                                                                sttemp.Cmd2cmd[ii] = 0;

                                                                                sttemp.Cmd3lba[ii] = 0;

                                                                                sttemp.Cmd4sc[ii] = 0;

                                                                                sttemp.Cmd5tag[ii] = 0;

                                                                                sttemp.Cmd6ExeTime[ii] = 0;

                                                                }

                                                                if ((reorderindextmp) == (iteration - 1))

                                                                {

                                                                                //printf("((reorderindextmp) == (iteration-1))\n");

                                                                                for (outcnt = 0; outcnt<(iteration - 1); ++outcnt)

                                                                                {

                                                                                                for (incnt = 0; incnt<(iteration - 1 - outcnt); ++incnt)

                                                                                                {

                                                                                                                if (streorder[incnt].Cmd0idxNum >= streorder[incnt + 1].Cmd0idxNum)

                                                                                                                {

                                                                                                                                //printf("before %d:%s,%s, %d:%s,%s\n", incnt, streorder[incnt].Cmd0idx, streorder[incnt].Cmd1us, incnt+1, streorder[incnt+1].Cmd0idx, streorder[incnt+1].Cmd1us);

                                                                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                                                                {

                                                                                                                                                sttemp.Cmd0idx[k] = streorder[incnt + 1].Cmd0idx[k];

                                                                                                                                                sttemp.Cmd1us[k] = streorder[incnt + 1].Cmd1us[k];

                                                                                                                                                sttemp.Cmd2cmd[k] = streorder[incnt + 1].Cmd2cmd[k];

                                                                                                                                                sttemp.Cmd3lba[k] = streorder[incnt + 1].Cmd3lba[k];

                                                                                                                                                sttemp.Cmd4sc[k] = streorder[incnt + 1].Cmd4sc[k];

                                                                                                                                                sttemp.Cmd5tag[k] = streorder[incnt + 1].Cmd5tag[k];

                                                                                                                                                sttemp.Cmd6ExeTime[k] = streorder[incnt + 1].Cmd6ExeTime[k];

                                                                                                                                }

                                                                                                                                sttemp.Cmd0idxNum = streorder[incnt + 1].Cmd0idxNum;

 

                                                                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                                                                {

                                                                                                                                                streorder[incnt + 1].Cmd0idx[k] = streorder[incnt].Cmd0idx[k];

                                                                                                                                                streorder[incnt + 1].Cmd1us[k] = streorder[incnt].Cmd1us[k];

                                                                                                                                                streorder[incnt + 1].Cmd2cmd[k] = streorder[incnt].Cmd2cmd[k];

                                                                                                                                                streorder[incnt + 1].Cmd3lba[k] = streorder[incnt].Cmd3lba[k];

                                                                                                                                                streorder[incnt + 1].Cmd4sc[k] = streorder[incnt].Cmd4sc[k];

                                                                                                                                                streorder[incnt + 1].Cmd5tag[k] = streorder[incnt].Cmd5tag[k];

                                                                                                                                                streorder[incnt + 1].Cmd6ExeTime[k] = streorder[incnt].Cmd6ExeTime[k];

                                                                                                                                }

                                                                                                                                streorder[incnt + 1].Cmd0idxNum = streorder[incnt].Cmd0idxNum;

 

                                                                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                                                                {

                                                                                                                                                streorder[incnt].Cmd0idx[k] = sttemp.Cmd0idx[k];

                                                                                                                                                streorder[incnt].Cmd1us[k] = sttemp.Cmd1us[k];

                                                                                                                                                streorder[incnt].Cmd2cmd[k] = sttemp.Cmd2cmd[k];

                                                                                                                                                streorder[incnt].Cmd3lba[k] = sttemp.Cmd3lba[k];

                                                                                                                                                streorder[incnt].Cmd4sc[k] = sttemp.Cmd4sc[k];

                                                                                                                                                streorder[incnt].Cmd5tag[k] = sttemp.Cmd5tag[k];

                                                                                                                                                streorder[incnt].Cmd6ExeTime[k] = sttemp.Cmd6ExeTime[k];

                                                                                                                                }

                                                                                                                                streorder[incnt].Cmd0idxNum = sttemp.Cmd0idxNum;

                                                                                                                }

                                                                                                }

                                                                                }

                                                                                for (outcnt = 0; outcnt<(iteration); outcnt++)

                                                                                {

                                                                                                fprintf(fouts, "%s,%s,%s,%s,%s,%s,%s\n", streorder[outcnt].Cmd0idx, streorder[outcnt].Cmd1us, streorder[outcnt].Cmd2cmd,

                                                                                                                streorder[outcnt].Cmd3lba, streorder[outcnt].Cmd4sc, streorder[outcnt].Cmd5tag, streorder[outcnt].Cmd6ExeTime);

                                                                                }

                                                                                reorderGroup++;

                                                                }              //if((reorderindextmp) == (iteration-1))

 

                                                                //clear sttemp char array.

                                                                for (ii = 0; ii<32; ii++)

                                                                {

                                                                                sttemp.Cmd0idx[ii] = 0;

                                                                                sttemp.Cmd1us[ii] = 0;

                                                                                sttemp.Cmd2cmd[ii] = 0;

                                                                                sttemp.Cmd3lba[ii] = 0;

                                                                                sttemp.Cmd4sc[ii] = 0;

                                                                                sttemp.Cmd5tag[ii] = 0;

                                                                                sttemp.Cmd6ExeTime[ii] = 0;

                                                                }

                                                }

                                                commacnt = 0;

                                                reorderindex++;

 

                                } //if(c == 0x0a)

                } //while((c=fgetc(fin)) != EOF)

                iireorder = (reorderindex - (iteration / 2)) - (reorderGroup * reorderBUFSize);

                printf("remaining line = %d\n", iireorder);

                if (iireorder != 0)

                {

                                reorderindextmp = iireorder % iteration;

 

                                //clear sttemp char array.

                                for (ii = 0; ii<32; ii++)

                                {

                                                sttemp.Cmd0idx[ii] = 0;

                                                sttemp.Cmd1us[ii] = 0;

                                                sttemp.Cmd2cmd[ii] = 0;

                                                sttemp.Cmd3lba[ii] = 0;

                                                sttemp.Cmd4sc[ii] = 0;

                                                sttemp.Cmd5tag[ii] = 0;

                                                sttemp.Cmd6ExeTime[ii] = 0;

                                }

 

                                for (outcnt = 0; outcnt<(iireorder - 1); ++outcnt)

                                {

                                                for (incnt = 0; incnt<(iireorder - 1 - outcnt); ++incnt)

                                                {

                                                                if (streorder[incnt].Cmd0idxNum >= streorder[incnt + 1].Cmd0idxNum)

                                                                {

                                                                                //printf("before %d:%s,%s, %d:%s,%s\n", incnt, streorder[incnt].Cmd0idx, streorder[incnt].Cmd1us, incnt+1, streorder[incnt+1].Cmd0idx, streorder[incnt+1].Cmd1us);

                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                {

                                                                                                sttemp.Cmd0idx[k] = streorder[incnt + 1].Cmd0idx[k];

                                                                                                sttemp.Cmd1us[k] = streorder[incnt + 1].Cmd1us[k];

                                                                                                sttemp.Cmd2cmd[k] = streorder[incnt + 1].Cmd2cmd[k];

                                                                                                sttemp.Cmd3lba[k] = streorder[incnt + 1].Cmd3lba[k];

                                                                                                sttemp.Cmd4sc[k] = streorder[incnt + 1].Cmd4sc[k];

                                                                                                sttemp.Cmd5tag[k] = streorder[incnt + 1].Cmd5tag[k];

                                                                                                sttemp.Cmd6ExeTime[k] = streorder[incnt + 1].Cmd6ExeTime[k];

                                                                                }

                                                                                sttemp.Cmd0idxNum = streorder[incnt + 1].Cmd0idxNum;

 

                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                {

                                                                                                streorder[incnt + 1].Cmd0idx[k] = streorder[incnt].Cmd0idx[k];

                                                                                                streorder[incnt + 1].Cmd1us[k] = streorder[incnt].Cmd1us[k];

                                                                                                streorder[incnt + 1].Cmd2cmd[k] = streorder[incnt].Cmd2cmd[k];

                                                                                                streorder[incnt + 1].Cmd3lba[k] = streorder[incnt].Cmd3lba[k];

                                                                                                streorder[incnt + 1].Cmd4sc[k] = streorder[incnt].Cmd4sc[k];

                                                                                                streorder[incnt + 1].Cmd5tag[k] = streorder[incnt].Cmd5tag[k];

                                                                                                streorder[incnt + 1].Cmd6ExeTime[k] = streorder[incnt].Cmd6ExeTime[k];

                                                                                }

                                                                                streorder[incnt + 1].Cmd0idxNum = streorder[incnt].Cmd0idxNum;

 

                                                                                for (k = 0; k<32; k++)                                      // save temp command line into stcmd

                                                                                {

                                                                                                streorder[incnt].Cmd0idx[k] = sttemp.Cmd0idx[k];

                                                                                                streorder[incnt].Cmd1us[k] = sttemp.Cmd1us[k];

                                                                                                streorder[incnt].Cmd2cmd[k] = sttemp.Cmd2cmd[k];

                                                                                                streorder[incnt].Cmd3lba[k] = sttemp.Cmd3lba[k];

                                                                                                streorder[incnt].Cmd4sc[k] = sttemp.Cmd4sc[k];

                                                                                                streorder[incnt].Cmd5tag[k] = sttemp.Cmd5tag[k];

                                                                                                streorder[incnt].Cmd6ExeTime[k] = sttemp.Cmd6ExeTime[k];

                                                                                }

                                                                                streorder[incnt].Cmd0idxNum = sttemp.Cmd0idxNum;

 

                                                                                //printf("after %d:%s,%s, %d:%s,%s\n", incnt, streorder[incnt].Cmd0idx, streorder[incnt].Cmd1us, incnt+1, streorder[incnt+1].Cmd0idx, streorder[incnt+1].Cmd1us);

                                                                                //printf(" \n");

                                                                }

                                                }

                                }

                                for (outcnt = 0; outcnt<(iireorder); outcnt++)

                                {

                                                fprintf(fouts, "%s,%s,%s,%s,%s,%s,%s\n", streorder[outcnt].Cmd0idx, streorder[outcnt].Cmd1us, streorder[outcnt].Cmd2cmd,

                                                                streorder[outcnt].Cmd3lba, streorder[outcnt].Cmd4sc, streorder[outcnt].Cmd5tag, streorder[outcnt].Cmd6ExeTime);

                                }

 

                                //clear sttemp char array.

                                for (ii = 0; ii<32; ii++)

                                {

                                                sttemp.Cmd0idx[ii] = 0;

                                                sttemp.Cmd1us[ii] = 0;

                                                sttemp.Cmd2cmd[ii] = 0;

                                                sttemp.Cmd3lba[ii] = 0;

                                                sttemp.Cmd4sc[ii] = 0;

                                                sttemp.Cmd5tag[ii] = 0;

                                                sttemp.Cmd6ExeTime[ii] = 0;

                                }

                } //if(iireorder != 0)

}

 

void fetch()

{

                char       c;

                UINT16 i;

 

                i = 0;

                fin = fopen("outtotal.txt", "r");

                //            fusec = fopen("usec.txt", "w");

                //            fcmd  = fopen("cmd.txt" , "w");

                flba = fopen("lba.txt", "w");

                fsc = fopen("sc.txt", "w");

                //            ftag  = fopen("tag.txt" , "w");

 

                while ((c = fgetc(fin)) != EOF)

                {

                                if (c == 0x2c)                                       //if input is comma

                                {

                                                i++;

                                }

                                switch (i)

                                {

                                case 1:

                                                if (c != 0x2c)

                                                {

                                                                //fputc(c,fusec);

                                                }

                                                break;

                                case 2:

                                                if (c != 0x2c)

                                                {

                                                                //fputc(c,fcmd);

                                                }

                                                break;

                                case 3:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                fputc(c, flba);

                                                }

                                                break;

                                case 4:

                                                if (c != 0x2c)

                                                {

                                                                fputc(c, fsc);

                                                }

                                                break;

                                case 5:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                //fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                default:

                                                break;

                                }

                                if (c == 0x0a)                                                       //0x0A=LF, 0x0D=CR

                                {

                                                i = 0;

                                                //fputc('\n',fusec);

                                                //fputc('\n',fcmd);

                                                //if(i==5)

                                                fputc('\n', flba);

                                                fputc('\n', fsc);

                                                //fputc('\n',ftag);

                                }

                }

                //fclose(ftag);

                fclose(fsc); fclose(flba);

                //fclose(fcmd);

                //fclose(fusec);

                fclose(fin);

 

}

 

void DisplayCommandOnly()

{

 

                while ((c = fgetc(fin)) != EOF)

                {

                                switch (commacnt)

                                {

                                case 0:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd0idx[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 1:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd1us[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fusec);

                                                }

                                                break;

                                case 2:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd2cmd[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fcmd);

                                                }

                                                break;

                                case 3:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd3lba[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,flba);

                                                }

                                                break;

                                case 4:

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd4sc[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,fsc);

                                                }

                                                break;

                                case 5:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR for "READ FPDMA", "WRITE FPDMA"

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd5tag[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                case 6:

                                                if (c == 0x0a)                                       //0x0A=LF, 0x0D=CR for "READ FPDMA", "WRITE FPDMA"

                                                                break;

                                                if (c != 0x2c)

                                                {

                                                                sttemp.Cmd6ExeTime[sttempcnt] = c;

                                                                sttempcnt++;

                                                                //                                                            fputc(c,ftag);

                                                }

                                                //i=0;

                                                break;

                                default:

                                                break;

                                }

                                if (c == 0x2c)                                                       //if c= comma

                                {

                                                sttempcnt = 0;

                                                commacnt++;

                                }

 

                                if (c == 0x0a)       //the end of line -> 0x0A=LF, 0x0D=CR, to process line after line feed.

                                {

                                                sttempcnt = 0;

 

                                                //KK_

                                                if ((sttemp.Cmd2cmd[0] == 'D') && (sttemp.Cmd2cmd[1] == 'A')) m = 6;

                                                if ((sttemp.Cmd2cmd[0] == 'R') && (sttemp.Cmd2cmd[1] == 'E') && (sttemp.Cmd2cmd[2] == 'A') && (sttemp.Cmd2cmd[3] == 'D') && (sttemp.Cmd2cmd[4] == ' ') && (sttemp.Cmd2cmd[5] == 'F'))

                                                                m = 50; //KK_ org value = 60

                                                if ((sttemp.Cmd2cmd[0] == 'W') && (sttemp.Cmd2cmd[1] == 'R') && (sttemp.Cmd2cmd[2] == 'I') && (sttemp.Cmd2cmd[3] == 'T') && (sttemp.Cmd2cmd[4] == 'E') && (sttemp.Cmd2cmd[5] == ' ') && (sttemp.Cmd2cmd[6] == 'F'))

                                                                m = 140; //KK_ org value = 61

                                                if ((sttemp.Cmd2cmd[0] == 'S') && (sttemp.Cmd2cmd[1] == 'M')) m = 176;

                                                if ((sttemp.Cmd2cmd[0] == 'F') && (sttemp.Cmd2cmd[1] == 'L')) m = 234;

                                                if ((sttemp.Cmd2cmd[0] == 'I') && (sttemp.Cmd2cmd[1] == 'D')) m = 236;

                                                if ((sttemp.Cmd2cmd[0] == 'S') && (sttemp.Cmd2cmd[1] == 'E')) m = 239;

 

                                                lbasize = CharArraySizeCheck(sttemp.Cmd3lba);

                                                scsize = CharArraySizeCheck(sttemp.Cmd4sc);

                                                sttemp.Cmd3lbaNum = str2dec(sttemp.Cmd3lba, lbasize);

                                                sttemp.Cmd4scNum = str2dec(sttemp.Cmd4sc, scsize);

 

                                                //KK_ if (!((sttemp.Cmd2cmd[0] == 'S') && (sttemp.Cmd2cmd[1] == 'D')) || !((sttemp.Cmd2cmd[0] == 'i') && (sttemp.Cmd2cmd[1] == 'd')) || !((sttemp.Cmd2cmd[0] == 'O') && (sttemp.Cmd2cmd[1] == 'u')))

                                                if (!((sttemp.Cmd2cmd[0] == 'S') && (sttemp.Cmd2cmd[1] == 'D')))

                                                {

                                                                if (!((sttemp.Cmd0idx[0] == 'i') && (sttemp.Cmd0idx[1] == 'd')))

                                                                {

                                                                                if (!((sttemp.Cmd0idx[0] == 'O') && (sttemp.Cmd0idx[1] == 'u')))

                                                                                {

                                                                                                //KK_fprintf(fouts, "%d,%s,%s,%s\n", m, sttemp.Cmd3lba, sttemp.Cmd4sc, sttemp.Cmd1us);

                                                                                                fprintf(foutt, "%d,%d,%d,%s\n", m, sttemp.Cmd3lbaNum, sttemp.Cmd4scNum, sttemp.Cmd1us);

                                                                                                fprintf(foutt1, "%s,%s,%s\n", sttemp.Cmd2cmd, sttemp.Cmd3lba, sttemp.Cmd4sc);

                                                                                }

                                                                }

                                                }

                                                //clear sttemp char array.

                                                for (ii = 0; ii<32; ii++)

                                                {

                                                                sttemp.Cmd0idx[ii] = 0;

                                                                sttemp.Cmd1us[ii] = 0;

                                                                sttemp.Cmd2cmd[ii] = 0;

                                                                sttemp.Cmd3lba[ii] = 0;

                                                                sttemp.Cmd4sc[ii] = 0;

                                                                sttemp.Cmd5tag[ii] = 0;

                                                                sttemp.Cmd6ExeTime[ii] = 0;

                                                }

                                                commacnt = 0;

                                } //if(c == 0x0a)

                } //while((c=fgetc(fin)) != EOF)

}