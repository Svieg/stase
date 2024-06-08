#include "../edk2/MdeModulePkg/Core/PiSmmCore/SmramProfileRecord.c"
//
// Physical pointer to private structure shared between SMM IPL and the SMM Core
//
SMM_CORE_PRIVATE_DATA  *gSmmCorePrivate;
LIST_ENTRY  mSmmPoolLists[SmmPoolTypeMax][MAX_POOL_INDEX];

verify_SmramProfileHandler()
{
  EFI_HANDLE  DispatchHandle;
  CONST VOID  *RegisterContext;

    typedef struct {
    SMRAM_PROFILE_PARAMETER_HEADER    Header;
    BOOLEAN                           RecordingState;
  } COMMBUFFER_STRUCT;


  COMMBUFFER_STRUCT *CommBuffer = malloc(sizeof(COMMBUFFER_STRUCT)); // Allocate memory
  UINTN s_Command;
  UINTN s_ReturnStatus;
  klee_make_symbolic(&s_Command, sizeof(s_Command), "CommBuffer->Header.Command");
  CommBuffer->Header.Command = s_Command;
  klee_make_symbolic(&s_ReturnStatus, sizeof(s_ReturnStatus), "CommBuffer->Header.ReturnStatus");
  CommBuffer->Header.ReturnStatus = s_ReturnStatus;
 
  CommBufferSize = malloc(sizeof(UINTN)); // Allocate memory.
  klee_make_symbolic(CommBufferSize, sizeof(UINTN), "*CommBufferSize"); // Make the allocated memory symbolic.


  klee_make_symbolic(&mSmramReadyToLock, sizeof(mSmramReadyToLock), "mSmramReadyToLock"); 

  mSmramProfileContextPtr = malloc(sizeof(MEMORY_PROFILE_CONTEXT_DATA));
   klee_make_symbolic(mSmramProfileContextPtr, sizeof(MEMORY_PROFILE_CONTEXT_DATA), "*mSmramProfileContextPtr");

  SmramProfileHandler ( DispatchHandle, RegisterContext, CommBuffer, CommBufferSize);
}