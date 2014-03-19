#include "Flash.h"
#include <memory.h>


Flash::Flash(UINT32 iFlashSize,UINT32 iSectorSize,UINT32 iBaseAddress)
{
	m_iFlashSize=iFlashSize;
	m_iSectorSize=iSectorSize;
	m_iBaseAddress=iBaseAddress;
	m_pSectorBuffer=new UINT08[m_iSectorSize];
}


Flash::~Flash()
{
	delete[] m_pSectorBuffer;
}


FLASH_STATUS Flash::Set(UINT08* pBuffer,UINT32 iOffset,UINT32 iLength)
{
	if (iOffset+iLength>m_iFlashSize)
		return FLASH_ERROR;

	UINT32 iChunkLength;
	UINT32 iSectorNumber=iOffset/m_iSectorSize;

	///////////////////////////////////////
	// Updating the first sector (below) //

	iChunkLength=m_iSectorSize-(iOffset%m_iSectorSize);
	if (iChunkLength>iLength)
		iChunkLength=iLength;

	/* Compare the contents of the flash sector and the input buffer */
	if (iChunkLength>0 && memcmp((UINT08*)m_iBaseAddress+iOffset,pBuffer,iChunkLength)!=0)
	{
		/* Copy an entire flash sector into 'm_pSectorBuffer' */
		memcpy(m_pSectorBuffer,(UINT08*)m_iBaseAddress+iSectorNumber*m_iSectorSize,m_iSectorSize);

		/* Copy the input buffer into 'm_pSectorBuffer' at the input offset */
		memcpy(m_pSectorBuffer+(iOffset%m_iSectorSize),pBuffer,iChunkLength);

		/* Erase the contents of the flash sector */
		if (EraseSector(iSectorNumber)==FLASH_ERROR)
			return FLASH_ERROR;

		/* Write 'm_pSectorBuffer' into the flash sector */
		if (WriteSector(iSectorNumber,m_pSectorBuffer)==FLASH_ERROR)
			return FLASH_ERROR;
	}

	if (iChunkLength>0)
		iSectorNumber++;
	pBuffer+=iChunkLength;
	iLength-=iChunkLength;

	// Updating the first sector (above) //
	///////////////////////////////////////

	////////////////////////////////////////////
	// Updating the remaining sectors (below) //

	while (iLength>0)
	{
		iChunkLength=m_iSectorSize;
		if (iChunkLength>iLength)
			iChunkLength=iLength;

		/* Compare the contents of the flash sector and the input buffer */
		if (memcmp((UINT08*)m_iBaseAddress+iSectorNumber*m_iSectorSize,pBuffer,iChunkLength)!=0)
		{
			/* Copy an entire flash sector into 'm_pSectorBuffer' */
			memcpy(m_pSectorBuffer,(UINT08*)m_iBaseAddress+iSectorNumber*m_iSectorSize,m_iSectorSize);

			/* Copy the input buffer into 'm_pSectorBuffer' at the beginning */
			memcpy(m_pSectorBuffer,pBuffer,iChunkLength);

			/* Erase the contents of the flash sector */
			if (EraseSector(iSectorNumber)==FLASH_ERROR)
				return FLASH_ERROR;

			/* Write 'm_pSectorBuffer' into the flash sector */
			if (WriteSector(iSectorNumber,m_pSectorBuffer)==FLASH_ERROR)
				return FLASH_ERROR;
		}

		iSectorNumber++;
		pBuffer+=iChunkLength;
		iLength-=iChunkLength;
	}

	// Updating the remaining sectors (above) //
	////////////////////////////////////////////

	return FLASH_OK;
}


FLASH_STATUS Flash::Get(UINT08* pBuffer,UINT32 iOffset,UINT32 iLength)
{
	if (iOffset+iLength>m_iFlashSize)
		return FLASH_ERROR;

	memcpy(pBuffer,(UINT08*)m_iBaseAddress+iOffset,iLength);

    return FLASH_OK;
}
