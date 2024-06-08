#include "../edk2/NetworkPkg/Dhcp6Dxe/Dhcp6Io.c"
#include "../edk2/NetworkPkg/Dhcp6Dxe/Dhcp6Utility.c"
//
// GLOBALS
//
EFI_IPv6_ADDRESS  mAllDhcpRelayAndServersAddress = {
  { 0xFF, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2 }
};


UINT16
SwapBytes16 (
  UINT16                    Value
  )
{
  return (UINT16) ((Value<< 8) | (Value>> 8));
}

UINT32
SwapBytes32 (
  UINT32                    Value
  )
{
  UINT32  LowerBytes;
  UINT32  HigherBytes;

  LowerBytes  = (UINT32) SwapBytes16 ((UINT16) Value);
  HigherBytes = (UINT32) SwapBytes16 ((UINT16) (Value >> 16));
  return (LowerBytes << 16 | HigherBytes);
}

#define NTOHS(x)  SwapBytes16 (x)

#define HTONS(x)    NTOHS(x)

EFI_GUID  gEfiDhcp6ServiceBindingProtocolGuid;

void verify_Dhcp6SeekStsOption()
{
     DHCP6_INSTANCE    *Instance = malloc(sizeof(DHCP6_INSTANCE));
     EFI_DHCP6_CONFIG_DATA    *Config = malloc(sizeof(EFI_DHCP6_CONFIG_DATA));
     Instance->Config = Config;  // Assign the allocated Config to Instance->Config
     UINT16    type;
     klee_make_symbolic(&type , sizeof(UINT16), "Instance->Config->IaDescriptor.Type");
     Instance->Config->IaDescriptor.Type = type;

   
   
     EFI_DHCP6_PACKET *Packet = malloc(sizeof(EFI_DHCP6_PACKET));
     UINT8 dhcp6_option;
     klee_make_symbolic(&dhcp6_option, sizeof(UINT8), "*Packet->Dhcp6.Option");
     *Packet->Dhcp6.Option = dhcp6_option;
     UINT32 packet_length;
     klee_make_symbolic(&packet_length, sizeof(UINT32), "Packet->Length");
     Packet->Length = packet_length;
    

      
     UINT8             *Option = malloc(sizeof(UINT8));
     klee_make_symbolic(Option, sizeof(*Option), "*Option");
    
     //Dhcp6SeekStsOption(Instance, Packet, &Option);
     Dhcp6SendRequestMsg(Instance);
}