#ifndef __GATT_SERVICE_ANCS__
#define __GATT_SERVICE_ANCS__

// Notification Source: UUID 9FBF120D-6301-42D9-8C58-25E699A21DBD (notifiable)
#define ANCS_NOTIF_SRC_CHAR_UUID        0x1DBD // Last 2 bytes of the 128bit-16bytes UUID
// Control point: UUID 69D1D8F3-45E1-49A8-9821-9BBDFDAAD9D9 (writeable with response)
#define ANCS_CTRL_PT_CHAR_UUID          0xD9D9
// Data Source: UUID 22EAC6E9-24D6-4BB5-BE44-B36ACE7C7BFB (notifiable)
#define ANCS_DATA_SRC_CHAR_UUID         0x7BFB
// CategoryID Values
#define CategoryIDOther                 0
#define CategoryIDIncomingCall          1
#define CategoryIDMissedCall            2
#define CategoryIDVoicemail             3
#define CategoryIDSocial                4
#define CategoryIDSchedule              5
#define CategoryIDEmail                 6
#define CategoryIDNews                  7
#define CategoryIDHealthAndFitness      8
#define CategoryIDBusinessAndFinance    9
#define CategoryIDLocation              10
#define CategoryIDEntertainment         11


// ANCS discovery states
enum
{
  DISC_IDLE = 0x00,                       // Idle state
  
  DISC_ANCS_START = 0x10,            // ANCS service
  DISC_ANCS_SVC,                     // Discover service
  DISC_ANCS_CHAR,                    // Discover all characteristics
  DISC_ANCS_CCCD,                    // Discover ANCS CCCD
  
  DISC_FAILED = 0xFF                      // Discovery failed
};

// ANCS handle cache indexes
enum
{
  HDL_ANCS_NTF_NOTIF_START,             // ANCS notification characteristic start handle
  HDL_ANCS_NTF_NOTIF_END,               // ANCS notification characteristic end handle
  HDL_ANCS_NTF_CCCD,                    // ANCS notification CCCD 
  HDL_ANCS_CTRL_PT_START,
  HDL_ANCS_CTRL_PT_END,
  HDL_ANCS_DATA_SRC_START,             // ANCS data source characteristic start handle
  HDL_ANCS_DATA_SRC_END,               // ANCS data source characteristic end handle
  HDL_ANCS_DATA_SRC_CCCD,              // ANCS data source CCCD
  HDL_CACHE_LEN
};

u_int8 Ancs_subsNotifSrc(u_int16 handle);
void get_ancs_characteristic(t_gatt_event_params *p_gatt_event_params);

void get_ancs_notification(u_int8 *p_notification_params,u_int8 len);
void ancs_state_set(u_int8 value);
u_int8 ancs_state_get(void);
#endif
