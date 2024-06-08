#include "static_harness.c"

// Hypothetical configuration variables 
uint32_t SMRAM_BASE; // Hypothetical SMRAM base address
uint32_t SMRAM_SIZE; // Hypothetical SMRAM size (1MB)
EFI_PHYSICAL_ADDRESS  mSmmMemLibInternalMaximumSupportAddress;// Maximum support address used to check input buffer
UINTN *CommBufferSize; 

//Use after free 
// Define a structure to hold the key-value pair
typedef struct {
    void *ptr;
    int is_freed;
} MemoryStatus;

// Define a simple hash table
#define TABLE_SIZE 100
MemoryStatus hash_table[TABLE_SIZE];

// Hash function to map a pointer to an index in the hash table
unsigned int hash(void *ptr) {
    return ((unsigned long)ptr) % TABLE_SIZE;
}

// Function to insert or update the status of a memory allocation in the hash table
void set_memory_status(void *ptr, int is_freed) {
    unsigned int index = hash(ptr);
    hash_table[index].ptr = ptr;
    hash_table[index].is_freed = is_freed;
}

// Function to get the status of a memory allocation from the hash table
int get_memory_status(void *ptr) {
    unsigned int index = hash(ptr);
    if (hash_table[index].ptr == ptr) {
        return hash_table[index].is_freed;
    }
    return -1; // Indicates that the pointer is not in the hash table
}



//#include "SmramProfileHandlerHarness.c"
//#include "PiSmmCoreHarness.c"
//#include "DispatcherHarness.c"


//#include "SmmLockBoxHandlerHarness.c"
//#include "PiSmmCommunicationHandlerHarness.c"
//#include "dynamic_harness/Tcg2SmmHarness.c"


//#include "dynamic_harness/SmmLockBoxHarness.c"
//#include "dynamic_harness/VariableSmmHarness.c"
// #include "dynamic_harness/SmmFaultTolerantWriteHarness.c"
//#include "dynamic_harness/RWVariableHarness.c"


//#include "QueryVariableInfoHandlerHarness.c"
//#include "Dhcp6SeekStsOptionHarness.c"
//#include "dynamic_harness/Dhcp6IoHarness.c"
#include "dynamic_harness/PxeBcdhcpHarness.c"

int main()
{
  klee_make_symbolic(&SMRAM_BASE, sizeof(SMRAM_BASE), "SMRAM_BASE");
  klee_make_symbolic(&SMRAM_SIZE, sizeof(SMRAM_SIZE), "SMRAM_SIZE");
  klee_make_symbolic(&mSmmMemLibInternalMaximumSupportAddress, sizeof(mSmmMemLibInternalMaximumSupportAddress), "mSmmMemLibInternalMaximumSupportAddress");
  //verify_SmmLockBox();
  //verify_SmramProfileHandler();
  //verify_PiSmmCore();
 // verify_Dispacher();
  //verify_SmmVariableHandler();
  //verify_SmmFaultTolerantWriteHandler();
  //verify_Tcg2Smm();
  // verify_QueryVariableInfoHandler();
  // verify_RWVariable();
   //verify_Dhcp6SeekStsOption();
 verify_PxeBcParseVendorOptions();
 //verify_Dhcp6SeekStsOption();
}

