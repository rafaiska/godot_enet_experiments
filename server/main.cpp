#include <cstdlib>
#include <enet/enet.h>
#include <enet/types.h>
#include <sstream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "actor.h"
#include "actor_serializer.h"
#include "map.h"
#include "physics_processor.h"
#include "timer.h"
#include "vector.h"
#include "actor_serializer.h"
#include <nlohmann/json.hpp>

#include <spdlog/spdlog.h>

#define NETWORK_UPDATE_DELAY_MS 50

using json = nlohmann::json;

void setup_asteroids(std::vector<rapinae::RWActor> &asteroids) {
  for (rapinae::RWActor &a : asteroids) {
    rapinae::Vector2 *position = new rapinae::Vector2(0.0, 0.0);
    rapinae::Vector2 *lin_vel = new rapinae::Vector2(100.0, 0.0);
    a.add_or_update_attr("position", position);
    a.add_or_update_attr("lin_vel", lin_vel);
    a.add_or_update_attr("rot_vel", 1.0);
    a.add_or_update_attr("scene", "Asteroid1.tscn");
  }
}

void send_map_data(const ENetEvent &event, const rapinae::SMap &map) {
  json map_data = {
      {"mapdata", std::format("({:d}|{:d})", map.get_w(), map.get_h())}};
  std::ostringstream stream;
  stream << map_data << '\0';
  std::string data = stream.str();
  ENetPacket *packet = enet_packet_create(data.c_str(), data.length(),
                                          ENET_PACKET_FLAG_RELIABLE);
  spdlog::info(std::string((char *)packet->data));
  enet_peer_send(event.peer, (enet_uint8)0, packet);
}

void send_actor_data(const ENetHost *server,
                     const std::vector<rapinae::RWActor> &actors) {
  if (server->connectedPeers == 0)
    return;

  std::ostringstream stream;
  stream << "{\"actordata\":[";
  bool first = true;
  for (rapinae::RWActor a : actors) {
    if (!first) stream << ',';
    else first = false;
    stream << rapinae::serialize_to_json(a, true);
  }
  stream << "]}\0";
  std::string data = stream.str();
  spdlog::info("Sending data: {:s}", data);
  for (size_t i = 0; i < server->peerCount; ++i) {
    if (server->peers[i].state != ENetPeerState::ENET_PEER_STATE_CONNECTED)
      continue;

    ENetPacket *packet = enet_packet_create(
        data.c_str(), data.length(), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_peer_send(&(server->peers[i]), (enet_uint8)0, packet);
  }
}

int main() {
  if (enet_initialize() != 0) {
    spdlog::error("An error occurred while initializing ENet.\n");
    return EXIT_FAILURE;
  }

  ENetAddress address;
  ENetHost *server;
  ENetEvent event;
  rapinae::SMap map = rapinae::SMap(500, 500);
  std::vector<rapinae::RWActor> asteroids = {rapinae::RWActor("1")};
  rapinae::RWTimer loop_timer;
  float time_since_last_nw_update = 0.0;
  rapinae::PhysicsProcessor physics_processor(rapinae::Vector2(500, 500));

  setup_asteroids(asteroids);

  /* Bind the server to the default localhost.     */
  /* A specific host address can be specified by   */
  /* enet_address_set_host (& address, "x.x.x.x"); */

  address.host = ENET_HOST_ANY;
  /* Bind the server to port 1234. */
  address.port = 1234;

  server = enet_host_create(
      &address /* the address to bind the server host to */,
      32 /* allow up to 32 clients and/or outgoing connections */,
      2 /* allow up to 2 channels to be used, 0 and 1 */,
      0 /* assume any amount of incoming bandwidth */,
      0 /* assume any amount of outgoing bandwidth */);
  if (server == NULL) {
    fprintf(stderr,
            "An error occurred while trying to create an ENet server host.\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    float delta = loop_timer.getElapsedTimeMs();
    physics_processor.update_velocity(asteroids, delta);
    time_since_last_nw_update += delta;
    loop_timer.set_start();

    enet_host_service(server, &event, 0);
    if (event.type == ENET_EVENT_TYPE_CONNECT)
      send_map_data(event, map);
    if (event.type == ENET_EVENT_TYPE_RECEIVE) {
      spdlog::info("RECV: {:s}", std::string((char *)event.packet->data));
      enet_packet_destroy(event.packet);
    }
    if (event.type == ENET_EVENT_TYPE_DISCONNECT)
      spdlog::info("DISCONNECTED");

    if (time_since_last_nw_update > NETWORK_UPDATE_DELAY_MS) {
      spdlog::info("Trying to send actor data (elapsed time: {:f}ms)", time_since_last_nw_update);
      send_actor_data(server, asteroids);
      time_since_last_nw_update = 0.0;
    }
  }

  enet_host_destroy(server);
  atexit(enet_deinitialize);
}