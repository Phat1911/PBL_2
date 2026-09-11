# Project Instructions

## Project Structure

- Read `SPEC.md` before changing the design or implementation.
- Follow the file layout defined in `SPEC.md`.
- Keep network model and services in `include/` and `src/`; keep Qt presentation and interaction in `ui/`.
- Keep Dijkstra, packet queues, transfer retry logic, checksums, failure handling, and JSON persistence out of Qt widget classes.
- Use C++20 and Qt6. The simulator is model-only: do not add real TCP/UDP sockets.

## Coding Conventions

- Prefer simple, readable C++20 syntax suitable for teaching.
- Preserve clear class responsibilities: model entities, graph/routing, transfer, simulation, storage, and UI.
- Use the required data structures visibly: adjacency lists, priority queues, FIFO/priority link queues, hash maps, and ordered chunk storage.
- Keep routing weights and formulas centralized, documented, and testable.
- Explain unfamiliar C++ syntax before introducing it, especially ownership, pointers, references, virtual methods, overrides, destructors, defaults, const methods, and templates.
- Use deterministic defaults and reproducible random seeds for demonstrations and tests.
- Add focused tests for graph, routing, transfer, and failure-recovery behavior.
- Each file has just one class.
- After implement, please mark/comment what is milestones that implementation belong.

## Rules

### Security Constraints

- This is an educational simulator, not production networking software.
- Do not represent the XOR checksum as cryptographic protection; document that CRC-32 is only a stronger non-cryptographic alternative and is not implemented.
- Do not add real network access, credentials, external services, or claims of production reliability or security.
- Validate packet integrity and reject corrupted DATA without acknowledging it successfully.

### Economic and Resource Constraints

- Keep the project local, file-based, and dependency-light: use JSON instead of a database or paid/external service.
- Keep one active file transfer in the initial version; concurrent transfers are future work.
- Use the fixed 1 ms simulation tick and fixed UI playback speed for predictable, low-complexity demonstrations.
- Preserve bounded link queues and the configured model values for bandwidth, latency, loss, and corruption; never measure or consume real network resources.

## Default Workflow

- After any code change, run the relevant tests and show the result before claiming completion.
- For code marked as core logic in `PLAN.md`, explain what it does and what risk or invariant it protects before or with the change.
- Do not deploy, publish, commit, push, or make external changes unless the user explicitly asks.
- Report assumptions, test results, and any remaining risks clearly.
