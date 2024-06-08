#include "../edk2/SecurityPkg/Tcg/Tcg2Smm/Tcg2Smm.c"
// #include "../edk2/SecurityPkg/Tcg/Tcg2Smm/Tcg2StandaloneMm.c"
//#include "../injected_edk2/injected_Tcg2Smm.c"
verify_Tcg2Smm()
{
    EFI_HANDLE  DispatchHandle = NULL; // Initialize as needed
    CONST VOID  *RegisterContext = NULL; // Initialize as needed
    //Symbolic execution harness
    // UINTN    CommBuffer;
    // UINTN   CommBufferSize;
    // klee_make_symbolic(&CommBuffer, sizeof(CommBuffer), "CommBuffer"); 
    // klee_make_symbolic(&CommBufferSize, sizeof(CommBufferSize), "CommBufferSize");

    TPM_NVS_MM_COMM_BUFFER *CommBuffer = malloc(sizeof(TPM_NVS_MM_COMM_BUFFER));// Allocate memory
    CommBuffer->Function = klee_int("CommBuffer->Function");
    klee_make_symbolic(CommBuffer, sizeof(*CommBuffer), "CommBuffer");    // Initialize the communication buffer with symbolic values

    CommBufferSize = malloc(sizeof(UINTN)); // Allocate memory.
    klee_make_symbolic(CommBufferSize, sizeof(UINTN), "*CommBufferSize"); // Make the allocated memory symbolic.

    TpmNvsCommunciate(DispatchHandle, RegisterContext, CommBuffer, CommBufferSize);
    //PhysicalPresenceCallback(DispatchHandle, RegisterContext, CommBuffer, CommBufferSize);
    //MemoryClearCallback(DispatchHandle, RegisterContext, CommBuffer, CommBufferSize);
}