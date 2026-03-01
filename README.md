# Javino  
### Middleware for Embedded Multi-Agent Robotic Systems

Javino is a bidirectional serial communication middleware designed to integrate Multi-Agent Systems (MAS) with Arduino-based robotic hardware.

It was originally developed to support embedded robotic-agent architectures where:

- 🧠 Agent reasoning runs on Raspberry Pi (e.g., Jason / JADE)
- 🔌 Javino provides a structured communication bridge between both layers
- ⚙ Sensors and actuators run on Arduino

Javino is not just a serial wrapper — it is a protocol designed specifically for reliable MAS ↔ hardware integration.

---

## Architectural Context

Javino was proposed as part of a robotic-agent platform composed of:

- **Raspberry Pi** → hosts agent reasoning (BDI / MAS)
- **Javino** → serial middleware between software and hardware
- **Arduino** → manages sensors and actuators

This separation allows:

- High-level reasoning on powerful hardware
- Deterministic message exchange between layers
- Robust low-level control on microcontrollers

---

## Design Rationale

Embedding MAS into physical robots introduces specific constraints:

1. **Message Boundary Detection**  
   Serial communication does not preserve message structure.

2. **Error Propagation Risk**  
   Corrupted perception data may affect agent belief bases.

3. **Asynchronous Execution**  
   Agents reason at different speeds than microcontrollers react.

4. **Resource Constraints**  
   Arduino boards cannot host BDI reasoning directly.

Javino addresses these issues by:

- Implementing a structured message protocol
- Providing double-sided validation (Arduino + Java)
- Including timeout-based reset mechanisms
- Enforcing deterministic message parsing

The protocol was designed specifically for embedded MAS environments.

---
## Message Protocol

<img width="712" height="350" alt="javino-message-format" src="https://github.com/user-attachments/assets/2fb8b9df-8137-4022-8b40-d9cda3aff766" />


Each Javino message is structured in three fields:

| Field     | Size            | Purpose                          |
|-----------|----------------|----------------------------------|
| Preamble  | 2 bytes (4 hex chars) | Identifies the start of a message |
| Size      | 1 byte (2 hex chars)  | Defines payload length           |
| Payload   | Up to 255 bytes       | Message content                  |

The **preamble** marks message boundaries within the serial stream, while the **size field** enables validation of the payload length before processing.

Upon reception, the receiver (hardware-side or software-side):

1. Validates the preamble
2. Reads the declared payload size
3. Counts received payload bytes
4. Discards the message if:
   - The preamble is invalid
   - The payload size does not match the declared size
   - The transmission is incomplete

This design:

- Prevents serial stream desynchronization
- Detects incomplete or corrupted transmissions
- Ensures deterministic message parsing
- Defines explicit message boundaries over byte-based communication

---

## Communication Modes

Javino provides three interaction patterns adapted to embedded MAS architectures.
### Send Mode (Software → Hardware)

Simplex transmission from software to hardware.


### Listen Mode (Hardware → Software)

The controller continuously pushes sensor data to the software-side.


---

### Request Mode (Half-Duplex: Software ↔ Hardware) — Recommended

The Request Mode implements a **half-duplex request–response interaction pattern** between the software-side (MAS) and the hardware-side (microcontroller).

In this mode:

1. The agent sends a request message to the controller.
2. The hardware processes the request.
3. The hardware returns a single response message.
4. The channel becomes available for the next interaction.

Only one direction is active at a time, ensuring controlled access to the serial port.

Key characteristics:

- 100% correct transmission observed in experimental evaluation
- Independent of controller-side delay configuration
- Prevents uncontrolled data streaming
- Avoids buffer saturation
- Ensures synchronized perception updates

Because the agent explicitly controls when data is requested, this mode provides **deterministic belief updates**, making it the most stable and reliable integration pattern for embedded robotic agents and BDI-based MAS architectures.

---

## Known Constraints

- Use one agent per serial interface
- Prefer request-response interaction
- Keep message sizes reasonable (≤ 255 bytes)
- Not designed for high-frequency real-time streaming

Javino is built for structured, reliable exchange — not raw high-speed streaming.

---

## When to Use Javino

<img width="695" height="556" alt="javino-with-ARGO" src="https://github.com/user-attachments/assets/bc2056b8-55ee-4733-babb-28bd03b72bdc" />


Use Javino if:

- You are embedding Jason or JADE agents into robotic platforms
- You need structured communication with Arduino
- You require deterministic message parsing
- You want to avoid serial desynchronization errors

---


## Academic Background

Javino was introduced, evaluated and improved in:

- [Lazarin & Pantoja (2015) – A Robotic-agent Platform For Embedding Software Agents using Raspberry Pi and Arduino Boards](https://doi.org/10.5753/wesaac.2015.33308)  
- [Junger et al. (2016) – An Analysis of Javino Middleware for Robotic Platforms Using Jason and JADE Frameworks](https://doi.org/10.5753/wesaac.2016.33217)
- [Pantoja, et al. (2016). ARGO: An Extended Jason Architecture that Facilitates Embedded Robotic Agents Programming.](https://doi.org/10.1007/978-3-319-50983-9_8)
- [Lazarin et al. (2024). Dealing with the Unpredictability of Physical Resources in Real-World Multi-agent Systems](https://doi.org/10.1007/978-3-031-55326-4_3)

---

## License
<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br />Javino is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>. The licensor cannot revoke these freedoms as long as you follow the license terms:

* __Attribution__ — You must give __appropriate credit__ like below:

N. Lazarin and C. Pantoja. " A Robotic-agent Platform For Embedding Software Agents using Raspberry Pi and Arduino Boards", in ___Proceedings of the 9th Workshop-School on Agents, Environments, and Applications (WESAAC 2015)___, Niterói/RJ, 2015, pp. 13-20, DOI: [10.5753/wesaac.2015.33308](https://doi.org/10.5753/wesaac.2015.33308).

