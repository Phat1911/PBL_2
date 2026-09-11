# Fault-Tolerant File Transmission and Routing Simulator

## 1. Project Purpose

This is an educational PBL2 project written in C++20 with Qt6. It simulates a small computer network that transfers files through routers while demonstrating:

- object-oriented programming;
- data structures and algorithms;
- packet transmission and network behavior;
- fault detection and automatic rerouting;
- file-based persistence instead of a database.

The project is a model-only simulator. It is not production networking software and does not use real TCP or UDP sockets.

The main academic focus is packet transmission and network behavior. Routing, fault-tolerant rerouting, the GUI, DSA, and OOP are required supporting capabilities, with DSA and OOP treated as core implementation milestones.

## 2. Scope

The simulator supports:

- interactive topology editing;
- random topology generation with a reproducible seed;
- clients, routers, and undirected links;
- configurable bandwidth, latency, and packet-loss probability per link;
- optional manual packet loss and corruption injection;
- bandwidth-aware file transmission;
- file chunking and reconstruction;
- individual acknowledgements, checksums, timeouts, and retransmission;
- UDP-like hop-by-hop route probes;
- TCP-like reliable file-transfer behavior;
- manual router/link failure and heartbeat-based failure detection;
- Dijkstra route calculation using an adjacency list and priority queue;
- automatic route recalculation after failures;
- packet logs and transfer statistics;
- JSON file storage for configuration and experiment results;
- start, pause, resume, reset, and single-tick simulation controls.

The initial version supports one active file transfer at a time. Multiple concurrent transfers are a documented future improvement.

## 3. Main Demonstration Scenario

The primary demonstration is one coherent scenario rather than disconnected feature examples:

1. Generate a random topology with a saved random seed.
2. Validate connectivity and display any warnings.
3. Repair the topology or continue intentionally if it is invalid.
4. Select a source client and destination client.
5. Configure bandwidth, latency, packet loss, and corruption values in the UI.
6. Start heartbeat monitoring.
7. Send UDP-like route probes hop by hop and display the discovered path.
8. Run Dijkstra and select the best available route.
9. Start TCP-like file transfer using chunks.
10. Show bandwidth queues, forwarding, checksum validation, individual ACKs, and retransmissions.
11. Manually fail a router or link during transfer.
12. Update the graph immediately and recalculate the route.
13. Drop packets affected by the failure.
14. Retransmit unacknowledged chunks through the replacement route.
15. Show successful recovery and save the experiment results.
16. Support a second controlled scenario where repeated loss reaches the retry limit and the transfer fails.

The intended story is:

`file transfer starts -> network problem occurs -> failure is detected -> route changes -> missing data is retransmitted -> transfer completes or fails with evidence`

## 4. Network Model

### Nodes

- `Client`: starts or receives a file transfer.
- `Router`: forwards packets and participates in heartbeat monitoring.

Both derive from a simple `Node` base class. Nodes have an identifier and active/failed status.

### Links

Links are undirected in the initial version. Each link has:

- one shared status in both directions;
- bandwidth in bytes per millisecond;
- latency in milliseconds;
- packet-loss probability;
- corruption probability;
- a bounded packet queue.

Bandwidth and latency are simulated values selected directly in the UI. They are never read from the real operating system or a real network interface.

For a packet of size `S` bytes on a link with bandwidth `B` bytes/ms:

`transmission time = ceiling(S / B)`

`arrival time = latency + transmission time`

The UI displays configured bandwidth, latency, queue usage, and transfer progress.

### Routing cost

Dijkstra uses a combined, non-negative link score derived from latency, bandwidth, and loss probability. The exact formula and weights are centralized in the routing service and documented in code. The default gives meaningful influence to all three properties while remaining simple to test.

The original configured link cost may also be displayed as an explanatory value, but route selection uses the documented combined score.

## 5. Packet and Protocol Behavior

Packet types are explicit:

- `DATA`: contains one file chunk;
- `ACK`: confirms one received chunk;
- `ROUTE_PROBE`: UDP-like route-discovery packet;
- `HEARTBEAT`: checks router liveness;
- `ROUTE_UPDATE`: records a changed route.

### UDP-like route probing

Before file transfer, route probes travel hop by hop. Each router records that the probe passed through it. The resulting path is visible in the packet log and GUI. This is a simplified application-level model inspired by traceroute, not a real UDP implementation.

### TCP-like file transfer

File transfer uses simulated TCP-like behavior:

- ordered file chunks;
- individual ACK for each valid chunk;
- timeout for missing ACKs;
- retransmission of unacknowledged chunks;
- maximum retry count;
- checksum validation;
- failure reporting when retry limit is reached.

TCP-like describes behavior only. No real sockets are used.

### Checksum

The implementation uses a simple educational XOR checksum over the packet payload. The receiver recalculates the checksum and rejects a mismatch without sending a successful ACK.

CRC-32/IEEE is recorded as a realistic stronger alternative, but it is intentionally not implemented in this project because the academic focus is network behavior, DSA, OOP, and file storage. The XOR checksum is not cryptographically secure.

### Loss and corruption

Each link supports both:

- configured random packet-loss probability;
- configured random corruption probability;
- manual loss injection;
- manual corruption injection.

The default probabilities are `0%`, allowing deterministic demonstrations. The UI can enable probabilities or force a specific packet event.

A lost or corrupted DATA packet does not produce a successful ACK. The sender retransmits after timeout.

### Retransmission defaults

- ACK timeout: `100 ms`;
- maximum attempts: `3`;
- after the final failed attempt: mark the file transfer as failed and preserve statistics.

### Failure handling

Manual router/link failure takes effect immediately. Heartbeat monitoring also detects missing heartbeats and logs the failure.

Default heartbeat settings:

- heartbeat interval: `100 ms`;
- failure timeout: `300 ms`.

When a failure is detected:

1. update the topology graph immediately;
2. recalculate routing tables with Dijkstra;
3. drop packets affected by the failed node or link;
4. leave acknowledged chunks unchanged;
5. retransmit missing chunks through the new route.

Packets are never magically moved to a new route.

## 6. Simulation and UI

The simulator uses a fixed step-based clock with `1 ms` internal ticks. The UI playback speed is a suitable fixed value and is not user-adjustable.

Controls:

- start;
- pause;
- resume;
- reset;
- advance one simulation tick.

The UI provides:

- topology canvas/editor;
- random topology generation controls;
- node and link creation/removal;
- link settings for bandwidth, latency, loss, and corruption;
- file selection and chunk-size setting;
- source and destination selection;
- simulation controls;
- current route and routing-table display;
- packet and event log;
- queue and transfer-progress display;
- sent, delivered, lost, corrupted, retransmitted, and failed counts.

The UI is presentation and interaction code. Network rules belong in core services, not in widget classes.

## 7. Topology Creation and Validation

The main workflow is an interactive topology editor plus random generation. There is no fixed predefined topology requirement.

Random generation accepts at least:

- node count;
- router/client composition;
- connection density;
- random seed.

The same seed and settings reproduce the same topology.

Generated topologies are validated using graph algorithms. Validation reports isolated nodes, unreachable source/destination pairs, and missing alternative routes. The user may repair the topology or continue intentionally with an invalid topology.

## 8. Data Structures and Algorithms

Required core structures:

- adjacency list for the network graph;
- priority queue for Dijkstra;
- FIFO or priority packet queues for links;
- hash maps for node IDs, transfer chunks, ACK status, and statistics;
- ordered chunk storage for file reconstruction.

Queue scheduling is priority-based:

`ACK and ROUTE_PROBE > HEARTBEAT and ROUTE_UPDATE > DATA`

If packets have the same priority, they are processed FIFO.

The DSA implementation must be visible through behavior: displayed routes, queue contents, routing-table changes, retransmission tracking, and statistics. A separate DSA teaching panel is not required in the initial version.

## 9. OOP Architecture

The initial design uses inheritance for network entities and composition for services.

Suggested responsibilities:

- `Node`: common node identity and status;
- `Client`: starts and receives file transfers;
- `Router`: forwards packets and participates in heartbeat handling;
- `Packet`: packet fields and packet-level behavior;
- `Link`: bandwidth, latency, queue, loss, and corruption behavior;
- `NetworkGraph`: nodes, links, adjacency list, and graph validation;
- `RoutingService`: Dijkstra and route recalculation;
- `TransferService`: chunking, ACKs, checksums, timeout, and retransmission;
- `SimulationService`: clock, events, ticks, and failure processing;
- `FileStorageService`: JSON configuration and experiment persistence;
- `MainWindow` or equivalent Qt UI class: user interaction and display only.

The project must avoid one large manager class. Core classes should have clear responsibilities and simple public methods.

## 10. File Layout

The implementation must follow this layout:

```text
pbl/
  CMakeLists.txt
  SPEC.md
  README.md
  config/
    config.json
  data/
    experiments/
  include/
    model/
      Node.h
      Client.h
      Router.h
      Link.h
      Packet.h
      NetworkGraph.h
    services/
      RoutingService.h
      TransferService.h
      SimulationService.h
      FileStorageService.h
    ui/
      MainWindow.h
  src/
    model/
      Node.cpp
      Client.cpp
      Router.cpp
      Link.cpp
      Packet.cpp
      NetworkGraph.cpp
    services/
      RoutingService.cpp
      TransferService.cpp
      SimulationService.cpp
      FileStorageService.cpp
    ui/
      MainWindow.cpp
    main.cpp
  tests/
    test_graph.cpp
    test_routing.cpp
    test_transfer.cpp
    test_failure_recovery.cpp
```

Qt UI code must not contain Dijkstra, transfer retry, or persistence algorithms.

## 11. Persistence

Use separate JSON files:

- `config.json`: nodes, links, bandwidth, latency, loss/corruption settings, seed, and UI-relevant configuration;
- experiment result JSON: packet events, route changes, transfer outcome, timing, and statistics.

JSON is used because it is structured, readable, and easy to reproduce without a database.

## 12. Core Milestones

All of the following are **core logic** milestones:

1. Basic OOP model: `Node`, `Client`, `Router`, `Packet`, and `Link`.
2. Graph representation using an adjacency list.
3. Dijkstra using a priority queue.
4. Bandwidth-aware queues and fixed-tick simulation.
5. File chunking, sequence tracking, XOR checksums, and reconstruction.
6. Individual ACKs, timeout, and retransmission.
7. Packet loss, corruption, and retry-limit behavior.
8. Heartbeat monitoring and failure state.
9. Route recalculation and retransmission after failure.
10. JSON configuration and experiment persistence.
11. The complete coherent demonstration scenario.

Qt widgets, ordinary input validation, styling, and routine UI wiring are supporting work, but must obey the architecture and file layout.

## 13. Beginner C++ Rule

The implementation must use clean, readable C++20 syntax. Avoid advanced syntax unless it is necessary and explained first.

Before using unfamiliar syntax, explain its purpose and a small example, especially:

- `using`;
- `virtual`;
- `override`;
- destructors such as `~ClassName()`;
- `= default`;
- references and pointers;
- ownership and smart pointers;
- `const` methods;
- templates used by standard containers.

Prefer straightforward ownership and data flow. Do not add pointer complexity merely to appear advanced. The learner must be able to explain every core class and rule to the teacher.

## 14. Decisions Made Without Asking

- Model-only simulation was selected because it is deterministic, testable, and appropriate for an educational project.
- A fixed `1 ms` tick was selected because step-based simulation is easier to observe than a fully event-driven engine.
- Manual and configured failures/loss/corruption were included so demonstrations are repeatable while experiments remain possible.
- Hop-by-hop UDP-like probes were selected because they make the chosen route visible.
- Priority scheduling was selected so ACKs and route probes are not unnecessarily delayed behind bulk DATA.
- A combined routing score was selected because bandwidth, latency, and loss all affect file-transfer behavior.
- JSON was selected instead of a database because it satisfies file storage requirements and supports reproducibility.
- XOR was selected instead of CRC-32 because checksum complexity should not distract from the project’s main academic goals.
- One active transfer was selected to keep the first implementation understandable; concurrent transfers are a future learning extension.
- `1024` bytes was selected as the default chunk size because it is easy to observe and retransmit; UI customization is retained for experiments.
- `100 ms` ACK timeout, `3` attempts, `100 ms` heartbeat interval, and `300 ms` failure timeout were selected as simple, visible defaults.
- The main scenario demonstrates successful recovery, with a separate controlled failure case to show retry-limit behavior.
- The UI playback speed is fixed so demonstrations remain predictable.
- The exact formula weights for the combined routing score will be centralized, documented, and tested rather than spread through UI code.

## 15. Limitations

This project does not provide real network performance measurements, real TCP/UDP behavior, production reliability, cryptographic integrity, or production security. Its purpose is to make network behavior and DSA/OOP design observable and explainable in an academic demonstration.
