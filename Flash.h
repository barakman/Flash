#ifndef FLASH_H
#define FLASH_H


typedef unsigned char  UINT08;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;
typedef enum {FLASH_OK,FLASH_ERROR} FLASH_STATUS;


///////////////////////////////////////////////////////////////////////////
//                                                                       //
// CLASS NAME:  Flash                                                    //
//                                                                       //
// DESCRIPTION: A flash is a Non-Volatile and Read-Only type of memory.  //
//              It is divided into basic memory units called 'Sectors'.  //
//              In order to update data that is stored in the flash,     //
//              each sector that contains the data must first be erased  //
//              and then written again.                                  //
//              This class provides a convenient interface that allows   //
//              users to access the flash as if it were a regular RAM.   //
//              Data can be written into the flash at any offset and in  //
//              any length (within the flash address space).             //
//                                                                       //
// REMARKS:     In order to support a specific type of flash with the    //
//              provided interface, a concrete subclass of this class    //
//              should implement the EraseSector and WriteSector         //
//              operations, using the flash driver.                      //
//                                                                       //
// AUTHOR:      Barakman (barakman@yahoo.com)                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////


class Flash
{
public:
	Flash(UINT32 iFlashSize,UINT32 iSectorSize,UINT32 iBaseAddress);
	virtual ~Flash();
public:
	FLASH_STATUS Set(UINT08* pBuffer,UINT32 iOffset,UINT32 iLength);
	FLASH_STATUS Get(UINT08* pBuffer,UINT32 iOffset,UINT32 iLength);
protected:
	virtual FLASH_STATUS EraseSector(UINT32 iSectorNumber)=0;
	virtual FLASH_STATUS WriteSector(UINT32 iSectorNumber,UINT08* pSectorBuffer)=0;
protected:
	UINT32  m_iFlashSize;
	UINT32  m_iSectorSize;
	UINT32  m_iBaseAddress;
private:
	UINT08* m_pSectorBuffer;
};


#endif
