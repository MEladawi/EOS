
#include "stdint.h"

//Initialize the EIDE harddisk controller.
extern	void		InitializeHDD(void);

//Write "SectorsCount" sectors to EIDE HDD controller at address "LBA" from buffer "WriteBuffer"
extern	void		HDD_WriteSectors (uint32 LBA, uint32 SectorsCount, uint16* WriteBuffer);

//Read "SectorsCount" sectors From EIDE HDD controller at address "LBA" to buffer "ReadBuffer"
extern	void		HDD_ReadSectors  (uint32 LBA, uint32 SectorsCount, uint16* ReadBuffer);

extern	uint32	MaxLBA;

