#include "../edk2//MdeModulePkg/Universal/QueryVariableInfo/QueryVariableInfo.c"
#include "../edk2//MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteSmm.c"
void verify_QueryVariableInfoHandler()
{
  EFI_HANDLE  DispatchHandle;
  CONST VOID  *RegisterContext;
  UINTN    sym_MaximumVariableStorageSize;
  UINTN    sym_RemainingVariableStorageSize;
  UINTN    sym_MaximumVariableSize;
  CommBufferSize = malloc(sizeof(UINTN)); // Allocate memory for one UINTN.
  
  klee_make_symbolic(CommBufferSize, sizeof(UINTN), "CommBufferSize"); // Make the allocated memory symbolic.

  UINTN *CommBuffer = malloc(sizeof(UINTN)); // Allocate memory for one UINTN.
  
  //klee_make_symbolic(&sym_MaximumVariableStorageSize, sizeof(sym_MaximumVariableStorageSize), "CommBuffer->MaximumVariableStorageSize");
  //klee_make_symbolic(&sym_RemainingVariableStorageSize, sizeof(sym_RemainingVariableStorageSize), "CommBuffer->MaximumVariableStorageSize");
  //klee_make_symbolic(&sym_MaximumVariableSize, sizeof(sym_MaximumVariableSize), "CommBuffer->MaximumVariableStorageSize");
  //CommBuffer->MaximumVariableSize = sym_MaximumVariableSize;
  //CommBuffer->MaximumVariableStorageSize = sym_MaximumVariableStorageSize;
  //CommBuffer->RemainingVariableStorageSize = sym_RemainingVariableStorageSize;

  //klee_make_symbolic(&inDxe, sizeof(inDxe), "inDxe");
  QueryVariableInfoHandler ( DispatchHandle, RegisterContext, CommBuffer, CommBufferSize);
}