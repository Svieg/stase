#include "../edk2/MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteSmm.c"

verify_SmmFaultTolerantWriteHandler()
{
  EFI_HANDLE  DispatchHandle;
  CONST VOID  *RegisterContext;
  VOID        *CommBuffer = malloc(sizeof(VOID));
  UINTN *CommBufferSize = malloc(sizeof(UINTN)); 
 
  klee_make_symbolic(CommBuffer, sizeof(VOID), "CommBuffer"); 
  klee_make_symbolic(CommBufferSize, sizeof(UINTN), "CommBufferSize");
  SmmFaultTolerantWriteHandler ( DispatchHandle, RegisterContext, CommBuffer, CommBufferSize);
}