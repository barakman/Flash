///////////////////////////////////////////////////////////////////////////
//                                                                       //
// FILE NAME:   TestSimpleFlash.cpp                                      //
//                                                                       //
// DESCRIPTION: Test the interface of the Flash abstract class           //
//              using an instance of the SimpleFlash concrete subclass:  //
//              -Create two files, each in the size of the flash.        //
//              -Fill the flash with the contents of the 1st file.       //
//              -Fill the 2nd file with the contents of the flash.       //
//                                                                       //
// REMARKS:     The type of flash being tested here is a simple RAM.     //
//              You can apply the same test for any type you implement.  //
//              After you run the program, you should compare the files. //
//              Alternatively, you can run the batch file RunAndCompare. //
//                                                                       //
// AUTHOR:      Barakman (barakman@yahoo.com)                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////


#include "SimpleFlash.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define FLASH_SIZE  65536
#define SECTOR_SIZE 1024
#define MAX_BYTES   4096
#define INTO_FLASH  "IntoFlash.bin"
#define FROM_FLASH  "FromFlash.bin"


void CreateRandomFile()
{
	FILE* pFile=fopen(INTO_FLASH,"wb");
	for (int i=0; i<FLASH_SIZE; i++)
		fputc((int)(rand()%256),pFile);
	fclose(pFile);
}


void Test(Flash* pFlash)
{
	FILE*  pFile;
	UINT32 iOffset;
	UINT32 iLength;
	UINT08 aBuffer[MAX_BYTES];

	/* Fill the flash with the contents of the 1st file */
	pFile=fopen(INTO_FLASH,"rb");
	for (iOffset=0; iOffset<FLASH_SIZE; iOffset+=iLength)
	{
		/* Copy a random number of bytes from the 1st file into the flash */
		iLength=rand()%MAX_BYTES;
		if (iLength>FLASH_SIZE-iOffset)
			iLength=FLASH_SIZE-iOffset;
		fread(aBuffer,iLength,1,pFile);
		pFlash->Set(aBuffer,iOffset,iLength);
	}
	fclose(pFile);

	/* Fill the 2nd file with the contents of the flash */
	pFile=fopen(FROM_FLASH,"wb");
	for (iOffset=0; iOffset<FLASH_SIZE; iOffset+=iLength)
	{
		/* Copy a random number of bytes from the flash into the 2nd file */
		iLength=rand()%MAX_BYTES;
		if (iLength>FLASH_SIZE-iOffset)
			iLength=FLASH_SIZE-iOffset;
		pFlash->Get(aBuffer,iOffset,iLength);
		fwrite(aBuffer,iLength,1,pFile);
	}
	fclose(pFile);
}


int main()
{
	UINT08      aBaseAddress[FLASH_SIZE];
	SimpleFlash cSimpleFlash(FLASH_SIZE,SECTOR_SIZE,(UINT32)aBaseAddress);

	srand((unsigned int)time(NULL));

	CreateRandomFile();

	Test(&cSimpleFlash);

	return 0;
}
