#include "SimpleFlash.h"
#include <memory.h>


SimpleFlash::SimpleFlash(UINT32 iFlashSize,UINT32 iSectorSize,UINT32 iBaseAddress):
	Flash(iFlashSize,iSectorSize,iBaseAddress)
{
}


SimpleFlash::~SimpleFlash()
{
}


FLASH_STATUS SimpleFlash::EraseSector(UINT32 iSectorNumber)
{
	UINT08* pFlashSector=(UINT08*)m_iBaseAddress+iSectorNumber*m_iSectorSize;
	memset(pFlashSector,0,m_iSectorSize);
	return FLASH_OK;
}


FLASH_STATUS SimpleFlash::WriteSector(UINT32 iSectorNumber,UINT08* pSectorBuffer)
{
	UINT08* pFlashSector=(UINT08*)m_iBaseAddress+iSectorNumber*m_iSectorSize;
	memcpy(pFlashSector,pSectorBuffer,m_iSectorSize);
	return FLASH_OK;
}
