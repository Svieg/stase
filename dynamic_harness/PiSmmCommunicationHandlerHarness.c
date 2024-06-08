#include "../edk2/UefiCpuPkg/PiSmmCommunication/PiSmmCommunicationSmm.c"

verify_PiSmmCommunicationHandler()
{
EFI_HANDLE  DispatchHandle;
CONST VOID  *RegisterContext;
VOID    *CommBuffer;

klee_make_symbolic(&CommBuffer, sizeof(CommBuffer), "CommBuffer"); 
klee_make_symbolic(&CommBufferSize, sizeof(CommBufferSize), "CommBufferSize");
PiSmmCommunicationHandler( DispatchHandle, RegisterContext, CommBuffer, CommBufferSize);
}