#include "static_harness.c"

//#include "edk2/MdeModulePkg/Universal/LockBox/SmmLockBox/SmmLockBox.c"
//#include "edk2/MdeModulePkg/Universal/Variable/RuntimeDxe/VariableSmm.c"
#include "harden_edk2/MdeModulePkg/Universal/LockBox/SmmLockBox/SmmLockBox.c"

#define MAX_BUFFER_SIZE 1024
int main() {
  VOID        *CommBuffer = malloc(sizeof(VOID));
  UINTN *CommBufferSize = malloc(sizeof(UINTN)); 
 
  klee_make_symbolic(&CommBuffer, sizeof(CommBuffer), "CommBuffer"); 
  klee_make_symbolic(&CommBufferSize, sizeof(CommBufferSize), "CommBufferSize");

  // Call the function with the symbolic buffer and size
  EFI_STATUS status = SmmLockBoxHandler(NULL, NULL, CommBuffer, CommBufferSize);
  //EFI_STATUS status = SmmVariableHandler(NULL, NULL, CommBuffer, CommBufferSize);
  

  return (status == EFI_SUCCESS) ? 0 : 1;
}
