 #include "../edk2/MdeModulePkg/Core/PiSmmCore/Dispatcher.c"

 //
// SMM Core Private Data structure that contains the data shared between
// the SMM IPL and the SMM Core.
//
SMM_CORE_PRIVATE_DATA  mSmmCorePrivateData = {
  SMM_CORE_PRIVATE_DATA_SIGNATURE,    // Signature
  NULL,                               // SmmIplImageHandle
  0,                                  // SmramRangeCount
  NULL,                               // SmramRanges
  NULL,                               // SmmEntryPoint
  FALSE,                              // SmmEntryPointRegistered
  FALSE,                              // InSmm
  NULL,                               // Smst
  NULL,                               // CommunicationBuffer
  0,                                  // BufferSize
  EFI_SUCCESS                         // ReturnStatus
};


EFI_SMM_DRIVER_ENTRY  *mSmmCoreDriverEntry;

//
// Global pointer used to access mSmmCorePrivateData from outside and inside SMM
//
SMM_CORE_PRIVATE_DATA  *gSmmCorePrivate = &mSmmCorePrivateData;

 verify_Dispacher()
 {
    EFI_HANDLE  DispatchHandle = NULL; // Initialize as needed
    CONST VOID  *RegisterContext = NULL; // Initialize as needed
    //Symbolic execution harness
    // UINTN    *CommBuffer;
    // UINTN   *CommBufferSize;
    // klee_make_symbolic(&CommBuffer, sizeof(CommBuffer), "CommBuffer"); 
    // klee_make_symbolic(&CommBufferSize, sizeof(CommBufferSize), "CommBufferSize");

    VOID *CommBuffer = malloc(sizeof(VOID));// Allocate memory
    klee_make_symbolic(CommBuffer, sizeof(*CommBuffer), "CommBuffer");    // Initialize the communication buffer with symbolic values

    CommBufferSize = malloc(sizeof(UINTN)); // Allocate memory.
    klee_make_symbolic(CommBufferSize, sizeof(UINTN), "*CommBufferSize"); // Make the allocated memory symbolic.

    SmmDriverDispatchHandler (DispatchHandle, RegisterContext, CommBuffer, CommBufferSize);
 }