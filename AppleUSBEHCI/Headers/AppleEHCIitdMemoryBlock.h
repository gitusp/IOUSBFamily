/*
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1998-2003 Apple Computer, Inc.  All Rights Reserved.
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */


#include <IOKit/IOBufferMemoryDescriptor.h>

#include "AppleUSBEHCI.h"
#include "USBEHCI.h"

class AppleEHCIitdMemoryBlock : public IOBufferMemoryDescriptor
{
    OSDeclareDefaultStructors(AppleEHCIitdMemoryBlock);
    
#define ITDsPerBlock	(kEHCIPageSize / sizeof(EHCIIsochTransferDescriptorShared))

private:
    IOPhysicalAddress				_sharedPhysical;
    EHCIIsochTransferDescriptorSharedPtr	_sharedLogical;
    AppleEHCIitdMemoryBlock			*_nextBlock;
    
public:

    static AppleEHCIitdMemoryBlock 		*NewMemoryBlock(void);
    void					SetNextBlock(AppleEHCIitdMemoryBlock *next);
    AppleEHCIitdMemoryBlock			*GetNextBlock(void);
    UInt32					NumTDs(void);
    IOPhysicalAddress				GetPhysicalPtr(UInt32 index);
    EHCIIsochTransferDescriptorSharedPtr	GetLogicalPtr(UInt32 index);
    
};