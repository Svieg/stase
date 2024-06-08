// #include "../harden_edk2/OvmfPkg/RWVariable/RWVariable.c"
 #include "../edk2/OvmfPkg/RWVariable/RWVariable.c"

 
void verify_RWVariable()
{
  UINT8  data;
  typedef struct {
    UINT8  Data;
  } COMMBUFFER_STRUCT;

  COMMBUFFER_STRUCT *CommBuffer = malloc(sizeof(COMMBUFFER_STRUCT)); // Allocate memory

  CommBufferSize = malloc(sizeof(UINTN)); // Allocate memory.
  klee_make_symbolic(CommBufferSize, sizeof(UINTN), "*CommBufferSize"); // Make the allocated memory symbolic.

  // Make symbolic
  klee_make_symbolic(CommBuffer, sizeof(*CommBuffer), "CommBuffer"); 
  klee_make_symbolic(&data, sizeof(data), "CommBuffer->data");
  CommBuffer->Data = data;

  // Call the RWVariableHandler function with casting through UINTN
  RWVariableHandler(NULL, NULL, CommBuffer, CommBufferSize);

  // Clean up
  free(CommBuffer);
}