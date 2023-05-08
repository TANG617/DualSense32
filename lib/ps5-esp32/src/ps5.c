#include "ps5.h"
#include <esp_system.h>
#include <string.h>

#include "ps5_int.h"

/********************************************************************************/
/*                              C O N S T A N T S */
/********************************************************************************/

static const uint8_t hid_cmd_payload_ps5_enable[] = {0x43, 0x02};


/********************************************************************************/
/*                         L O C A L    V A R I A B L E S */
/********************************************************************************/
uint8_t output_sequence_counter = 0;

static ps5_connection_callback_t ps5_connection_cb = NULL;
static ps5_connection_object_callback_t ps5_connection_object_cb = NULL;
static void* ps5_connection_object = NULL;

static ps5_event_callback_t ps5_event_cb = NULL;
static ps5_event_object_callback_t ps5_event_object_cb = NULL;
static void* ps5_event_object = NULL;

static bool is_active = false;

/********************************************************************************/
/*                      P U B L I C    F U N C T I O N S */
/********************************************************************************/

/*******************************************************************************
**
** Function         ps5Init
**
** Description      This initializes the bluetooth services to listen
**                  for an incoming ps5 controller connection.
**
**
** Returns          void
**
*******************************************************************************/
void ps5Init() {
  sppInit();
  ps5_l2cap_init_services();
}

/*******************************************************************************
**
** Function         ps5IsConnected
**
** Description      This returns whether a ps5 controller is connected, based
**                  on whether a successful handshake has taken place.
**
**
** Returns          bool
**
*******************************************************************************/
bool ps5IsConnected() { return is_active; }

/*******************************************************************************
**
** Function         ps5Enable
**
** Description      This triggers the ps5 controller to start continually
**                  sending its data.
**
**
** Returns          void
**
*******************************************************************************/
void ps5Enable() {
  uint16_t length = sizeof(hid_cmd_payload_ps5_enable);
  uint8_t hidCommand[ps5_SEND_BUFFER_SIZE];

  hidCommand[0] = hid_cmd_code_set_report | hid_cmd_code_type_feature;
  hidCommand[1] = hid_cmd_identifier_ps5_enable;

  // hidCommand[0] = 0x43;
  // hidCommand[1] = 0x09;

  memcpy(hidCommand+2, hid_cmd_payload_ps5_enable, length);

  ps5_l2cap_send_hid(&hidCommand, length);
  ps5SetLed(200, 0, 0);
}

uint32_t hashTable[] = {
    0xd202ef8d, 0xa505df1b, 0x3c0c8ea1, 0x4b0bbe37, 0xd56f2b94, 0xa2681b02, 0x3b614ab8, 0x4c667a2e,
    0xdcd967bf, 0xabde5729, 0x32d70693, 0x45d03605, 0xdbb4a3a6, 0xacb39330, 0x35bac28a, 0x42bdf21c,
    0xcfb5ffe9, 0xb8b2cf7f, 0x21bb9ec5, 0x56bcae53, 0xc8d83bf0, 0xbfdf0b66, 0x26d65adc, 0x51d16a4a,
    0xc16e77db, 0xb669474d, 0x2f6016f7, 0x58672661, 0xc603b3c2, 0xb1048354, 0x280dd2ee, 0x5f0ae278,
    0xe96ccf45, 0x9e6bffd3, 0x762ae69, 0x70659eff, 0xee010b5c, 0x99063bca, 0xf6a70, 0x77085ae6,
    0xe7b74777, 0x90b077e1, 0x9b9265b, 0x7ebe16cd, 0xe0da836e, 0x97ddb3f8, 0xed4e242, 0x79d3d2d4,
    0xf4dbdf21, 0x83dcefb7, 0x1ad5be0d, 0x6dd28e9b, 0xf3b61b38, 0x84b12bae, 0x1db87a14, 0x6abf4a82,
    0xfa005713, 0x8d076785, 0x140e363f, 0x630906a9, 0xfd6d930a, 0x8a6aa39c, 0x1363f226, 0x6464c2b0,
    0xa4deae1d, 0xd3d99e8b, 0x4ad0cf31, 0x3dd7ffa7, 0xa3b36a04, 0xd4b45a92, 0x4dbd0b28, 0x3aba3bbe,
    0xaa05262f, 0xdd0216b9, 0x440b4703, 0x330c7795, 0xad68e236, 0xda6fd2a0, 0x4366831a, 0x3461b38c,
    0xb969be79, 0xce6e8eef, 0x5767df55, 0x2060efc3, 0xbe047a60, 0xc9034af6, 0x500a1b4c, 0x270d2bda,
    0xb7b2364b, 0xc0b506dd, 0x59bc5767, 0x2ebb67f1, 0xb0dff252, 0xc7d8c2c4, 0x5ed1937e, 0x29d6a3e8,
    0x9fb08ed5, 0xe8b7be43, 0x71beeff9, 0x6b9df6f, 0x98dd4acc, 0xefda7a5a, 0x76d32be0, 0x1d41b76,
    0x916b06e7, 0xe66c3671, 0x7f6567cb, 0x862575d, 0x9606c2fe, 0xe101f268, 0x7808a3d2, 0xf0f9344,
    0x82079eb1, 0xf500ae27, 0x6c09ff9d, 0x1b0ecf0b, 0x856a5aa8, 0xf26d6a3e, 0x6b643b84, 0x1c630b12,
    0x8cdc1683, 0xfbdb2615, 0x62d277af, 0x15d54739, 0x8bb1d29a, 0xfcb6e20c, 0x65bfb3b6, 0x12b88320,
    0x3fba6cad, 0x48bd5c3b, 0xd1b40d81, 0xa6b33d17, 0x38d7a8b4, 0x4fd09822, 0xd6d9c998, 0xa1def90e,
    0x3161e49f, 0x4666d409, 0xdf6f85b3, 0xa868b525, 0x360c2086, 0x410b1010, 0xd80241aa, 0xaf05713c,
    0x220d7cc9, 0x550a4c5f, 0xcc031de5, 0xbb042d73, 0x2560b8d0, 0x52678846, 0xcb6ed9fc, 0xbc69e96a,
    0x2cd6f4fb, 0x5bd1c46d, 0xc2d895d7, 0xb5dfa541, 0x2bbb30e2, 0x5cbc0074, 0xc5b551ce, 0xb2b26158,
    0x4d44c65, 0x73d37cf3, 0xeada2d49, 0x9ddd1ddf, 0x3b9887c, 0x74beb8ea, 0xedb7e950, 0x9ab0d9c6,
    0xa0fc457, 0x7d08f4c1, 0xe401a57b, 0x930695ed, 0xd62004e, 0x7a6530d8, 0xe36c6162, 0x946b51f4,
    0x19635c01, 0x6e646c97, 0xf76d3d2d, 0x806a0dbb, 0x1e0e9818, 0x6909a88e, 0xf000f934, 0x8707c9a2,
    0x17b8d433, 0x60bfe4a5, 0xf9b6b51f, 0x8eb18589, 0x10d5102a, 0x67d220bc, 0xfedb7106, 0x89dc4190,
    0x49662d3d, 0x3e611dab, 0xa7684c11, 0xd06f7c87, 0x4e0be924, 0x390cd9b2, 0xa0058808, 0xd702b89e,
    0x47bda50f, 0x30ba9599, 0xa9b3c423, 0xdeb4f4b5, 0x40d06116, 0x37d75180, 0xaede003a, 0xd9d930ac,
    0x54d13d59, 0x23d60dcf, 0xbadf5c75, 0xcdd86ce3, 0x53bcf940, 0x24bbc9d6, 0xbdb2986c, 0xcab5a8fa,
    0x5a0ab56b, 0x2d0d85fd, 0xb404d447, 0xc303e4d1, 0x5d677172, 0x2a6041e4, 0xb369105e, 0xc46e20c8,
    0x72080df5, 0x50f3d63, 0x9c066cd9, 0xeb015c4f, 0x7565c9ec, 0x262f97a, 0x9b6ba8c0, 0xec6c9856,
    0x7cd385c7, 0xbd4b551, 0x92dde4eb, 0xe5dad47d, 0x7bbe41de, 0xcb97148, 0x95b020f2, 0xe2b71064,
    0x6fbf1d91, 0x18b82d07, 0x81b17cbd, 0xf6b64c2b, 0x68d2d988, 0x1fd5e91e, 0x86dcb8a4, 0xf1db8832,
    0x616495a3, 0x1663a535, 0x8f6af48f, 0xf86dc419, 0x660951ba, 0x110e612c, 0x88073096, 0xff000000

};

// uint32_t hashTable[] = {
//         0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
//         0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
//         0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
//         0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
//         0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
//         0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
//         0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
//         0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
//         0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
//         0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
//         0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
//         0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
//         0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
//         0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
//         0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
//         0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
//         0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
//         0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
//         0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
//         0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
//         0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
//         0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
//         0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
//         0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
//         0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
//         0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
//         0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
//         0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
//         0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
//         0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
//         0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
//         0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
//         0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
//         0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
//         0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
//         0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
//         0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
//         0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
//         0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
//         0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
//         0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
//         0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
//         0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d

// };

uint32_t ps5Compute(uint8_t* buffer) {
    uint32_t result = 0xeada2d49;
    int i;

    for (i = 0; i < 74; i++) {
        result = hashTable[(result & 0xFF) ^ (buffer[i] & 0xFF)] ^ (result >> 8);
    }

    return result;
}

uint32_t crc32(uint32_t crc, uint8_t const *p, size_t len, uint32_t polynomial) {
        // Source: https://github.com/torvalds/linux/blob/c4cf498dc0241fa2d758dba177634268446afb06/lib/crc32.c
        int i;
        while (len--) {
                crc ^= *p++;
                for (i = 0; i < 8; i++)
                        crc = (crc >> 1) ^ ((crc & 1) ? polynomial : 0);
        }
        return crc;
}

/*******************************************************************************
**
** Function         ps5Cmd
**
** Description      Send a command to the ps5 controller.
**
**
** Returns          void
**
*******************************************************************************/
void ps5Cmd(ps5_cmd_t cmd) {
  uint8_t hidCommand[ps5_SEND_BUFFER_SIZE] = {0xA2, 0x31,0x02, 0xFF, 0xFF, 0xF7,0xFF,0xFF};//02,03,04,05
  uint16_t length = ps5_SEND_BUFFER_SIZE;
  
  // hidCommand[2] = (output_sequence_counter++ << 4) | 0x0;
  // hidCommand.code = hid_cmd_code_set_report | hid_cmd_code_type_output;
  // hidCommand.identifier = hid_cmd_identifier_ps5_control;

  // hidCommand.data[ps5_control_packet_index_small_rumble] = cmd.smallRumble;  // Small Rumble
  // hidCommand.data[ps5_control_packet_index_large_rumble] = cmd.largeRumble;  // Big rumble

  // hidCommand.data[ps5_control_packet_index_red+1] = cmd.r;    // Red
  // hidCommand.data[ps5_control_packet_index_green+1] = cmd.g;  // Green
  // hidCommand.data[ps5_control_packet_index_blue+1] = cmd.b;   // Blue

  // // Time to flash bright (255 = 2.5 seconds)
  // hidCommand.data[ps5_control_packet_index_flash_on_time] = cmd.flashOn;
  // // Time to flash dark (255 = 2.5 seconds)
  // hidCommand.data[ps5_control_packet_index_flash_off_time] = cmd.flashOff;

  // int crcChecksum = ps5Compute(hidCommand);

  // hidCommand.data[73] = (crcChecksum & 0x000000FF);
  // hidCommand.data[74] = (crcChecksum & 0x0000FF00) >> 8;
  // hidCommand.data[75] = (crcChecksum & 0x00FF0000) >> 16;
  // hidCommand.data[76] = (crcChecksum & 0xFF000000) >> 24;

  hidCommand[46] = 100; // Red
  hidCommand[47] = 100; // Green
  hidCommand[48] = 100; // Blue
  uint32_t crc = ~crc32(0xFFFFFFFF, (uint8_t const*)hidCommand, sizeof(hidCommand) - 4 /* Do not include the crc32 */,0xedb88320); // Note how the report type is also included in the output report
  hidCommand[75] = crc & 0xFF;
  hidCommand[76] = (crc >> 8) & 0xFF;
  hidCommand[77] = (crc >> 16);
  hidCommand[78] = (crc >> 24);
  ps5_l2cap_send_hid(hidCommand, length);
}

/*******************************************************************************
**
** Function         ps5SetLedOnly
**
** Description      Sets the LEDs on the ps5 controller.
**
**
** Returns          void
**
*******************************************************************************/
void ps5SetLed(uint8_t r, uint8_t g, uint8_t b) {
  ps5_cmd_t cmd = {0};

  cmd.r = r;
  cmd.g = g;
  cmd.b = b;

  ps5Cmd(cmd);
}

// hid_cmd_t ps5SetLed(uint8_t r, uint8_t g, uint8_t b) {
//   ps5_cmd_t cmd = {0};

//   cmd.r = r;
//   cmd.g = g;
//   cmd.b = b;

//   return ps5Cmd(cmd);
// }

/*******************************************************************************
**
** Function         ps5SetOutput
**
** Description      Sets feedback on the ps5 controller.
**
**
** Returns          void
**
*******************************************************************************/
void ps5SetOutput(ps5_cmd_t prevCommand) { ps5Cmd(prevCommand); }

/*******************************************************************************
**
** Function         ps5SetConnectionCallback
**
** Description      Registers a callback for receiving ps5 controller
**                  connection notifications
**
**
** Returns          void
**
*******************************************************************************/
void ps5SetConnectionCallback(ps5_connection_callback_t cb) {
  ps5_connection_cb = cb;
}

/*******************************************************************************
**
** Function         ps5SetConnectionObjectCallback
**
** Description      Registers a callback for receiving ps5 controller
**                  connection notifications
**
**
** Returns          void
**
*******************************************************************************/
void ps5SetConnectionObjectCallback(void* object, ps5_connection_object_callback_t cb) {
  ps5_connection_object_cb = cb;
  ps5_connection_object = object;
}

/*******************************************************************************
**
** Function         ps5SetEventCallback
**
** Description      Registers a callback for receiving ps5 controller events
**
**
** Returns          void
**
*******************************************************************************/
void ps5SetEventCallback(ps5_event_callback_t cb) { ps5_event_cb = cb; }

/*******************************************************************************
**
** Function         ps5SetEventObjectCallback
**
** Description      Registers a callback for receiving ps5 controller events
**
**
** Returns          void
**
*******************************************************************************/
void ps5SetEventObjectCallback(void* object, ps5_event_object_callback_t cb) {
  ps5_event_object_cb = cb;
  ps5_event_object = object;
}

/*******************************************************************************
**
** Function         ps5SetBluetoothMacAddress
**
** Description      Writes a Registers a callback for receiving ps5 controller
*events
**
**
** Returns          void
**
*******************************************************************************/
void ps5SetBluetoothMacAddress(const uint8_t* mac) {
  // The bluetooth MAC address is derived from the base MAC address
  // https://docs.espressif.com/projects/esp-idf/en/stable/api-reference/system/system.html#mac-address
  uint8_t baseMac[6];
  memcpy(baseMac, mac, 6);
  baseMac[5] -= 2;
  esp_base_mac_addr_set(baseMac);
}

/********************************************************************************/
/*                      L O C A L    F U N C T I O N S */
/********************************************************************************/

void ps5ConnectEvent(uint8_t is_connected) {
    if (is_connected) {
        ps5Enable();
    } else {
        is_active = false;
    }
}


void ps5PacketEvent(ps5_t ps5, ps5_event_t event) {
    // Trigger packet event, but if this is the very first packet
    // after connecting, trigger a connection event instead
    if (is_active) {
        if(ps5_event_cb != NULL) {
            ps5_event_cb(ps5, event);
        }

        if (ps5_event_object_cb != NULL && ps5_event_object != NULL) {
            ps5_event_object_cb(ps5_event_object, ps5, event);
        }
    } else {
        is_active = true;

        if(ps5_connection_cb != NULL) {
            ps5_connection_cb(is_active);
        }

        if (ps5_connection_object_cb != NULL && ps5_connection_object != NULL) {
            ps5_connection_object_cb(ps5_connection_object, is_active);
        }
    }
}
