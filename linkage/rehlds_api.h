//
// Minimal ReHLDS engine API snapshot for SV_DropClient, usable only
// for dropping clients without the full engine headers
//
// License: https://github.com/yapb/linkage/blob/master/LICENSE-MIT.txt
// Source: rehlds/public/rehlds/rehlds_api.h + rehlds_interfaces.h, API v3.15
//

#pragma once

// only the DropClient path is exposed, the full upstream header pulls
// half of the engine (archtypes, hookchains, FlightRecorder, ...)
inline constexpr int kRehldsApiVersionMajor = 3;
inline constexpr int kRehldsApiVersionMinor = 15;

inline constexpr char kRehldsHldsApiVersion[] = "VREHLDS_HLDS_API_VERSION001";

// opaque client handle, passed to DropClient without dereferencing
class IGameClient;

// opaque stubs, only used as pointer return types below
class IRehldsHookchains;
class IRehldsServerData;
class IRehldsFlightRecorder;
class IMessageManager;

struct client_t;
struct server_log_s;

class IRehldsServerStatic {
public:
  virtual ~IRehldsServerStatic () {}

  virtual int GetMaxClients () = 0;
  virtual bool IsLogActive () = 0;
  virtual IGameClient *GetClient (int id) = 0;
  virtual client_t *GetClient_t (int id) = 0;
  virtual int GetIndexOfClient_t (client_t *client) = 0;
  virtual int GetMaxClientsLimit () = 0;
  virtual client_t *GetNextClient_t (client_t *client) = 0;
  virtual int GetSpawnCount () = 0;
  virtual void SetSpawnCount (int count) = 0;
  virtual struct server_log_s *GetLog () = 0;
  virtual bool IsSecure () = 0;
  virtual void SetSecure (bool value) = 0;
};

// only the head of upstream RehldsFuncs_t is reproduced here,
// DropClient is its first member, so offset 0 stays valid.
// IRehldsApi + IRehldsServerStatic keep vtable-exact layouts,
// IGameClient passes through opaquely and is never dereferenced
struct RehldsFuncs {
  void (*DropClient) (IGameClient *cl, bool crash, const char *fmt, ...);
};

class IRehldsApi {
public:
  virtual ~IRehldsApi () {}

  virtual int GetMajorVersion () = 0;
  virtual int GetMinorVersion () = 0;
  virtual const RehldsFuncs *GetFuncs () = 0;
  virtual IRehldsHookchains *GetHookchains () = 0;
  virtual IRehldsServerStatic *GetServerStatic () = 0;
  virtual IRehldsServerData *GetServerData () = 0;
  virtual IRehldsFlightRecorder *GetFlightRecorder () = 0;
  virtual IMessageManager *GetMessageManager () = 0;
};

// engine CreateInterface factory (swds.dll / engine_i486.so)
using RehldsCreateInterfaceFn = void *(*)(const char *name, int *ret);
