Flash
=====

General:
A flash is a Non-Volatile and Read-Only type of memory, which is divided into basic units called 'Sectors'.
In order to update data that is stored in the flash, each sector that contains the data must first be erased and then written again.

Description:
Class Flash provides a convenient interface that allows users to access the flash as if it were a regular RAM.
Data can be written into the flash at any offset and in any length (within the flash address space).
In order to support a specific type of flash with the provided interface, a concrete subclass of this class should implement the EraseSector and WriteSector operations, using the flash driver.
