#ifndef SIMPLE_FLASH_H
#define SIMPLE_FLASH_H


#include "..\Flash.h"


///////////////////////////////////////////////////////////////////////////
//                                                                       //
// CLASS NAME:  SimpleFlash                                              //
//                                                                       //
// DESCRIPTION: This class derives from Class Flash.                     //
//              The type of flash supported here is a simple RAM.        //
//                                                                       //
// AUTHOR:      Barakman (barakman@yahoo.com)                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////


class SimpleFlash : public Flash
{
public:
	SimpleFlash(UINT32 iFlashSize,UINT32 iSectorSize,UINT32 iBaseAddress);
	virtual ~SimpleFlash();
protected:
	virtual FLASH_STATUS EraseSector(UINT32 iSectorNumber);
	virtual FLASH_STATUS WriteSector(UINT32 iSectorNumber,UINT08* pSectorBuffer);
};


#endif
