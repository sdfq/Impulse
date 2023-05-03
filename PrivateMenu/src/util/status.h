#pragma once

/*Generic*/
#define STATUS_SUCCESS				(0x000u)
#define STATUS_NOTHING				(0x001u)
#define STATUS_FATAL				(0x002u)
#define STATUS_WARNING				(0x003u)
#define STATUS_UNKNOWN				(0x004u)
#define STATUS_ALREADYINITIALIZED	(0x005u)

/*Auth*/
#define STATUS_AUTHORIZING			(0x101u)
#define STATUS_WRONGCREDENTIALS		(0x102u)
#define STATUS_CANTCONNECT			(0x103u)
#define STATUS_EMPTY				(0x104u)
#define STATUS_WRONGHWID			(0x105u)
#define STATUS_DISABLED				(0x106u)
#define STATUS_BANNED				(0x107u)
#define STATUS_NOTPAID				(0x108u)
#define STATUS_MENUOFFLINE			(0x109u)
#define STATUS_AUTHCUSTOM			(0x110u)
#define STATUS_AUTOLOGIN			(0x111u)
#define STATUS_ALLFIELDS			(0x112u)
#define STATUS_OUTDATED				(0x113u)

typedef uint32_t Status;
