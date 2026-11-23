# SFS Next – Phase 1 (experimental)
This is a **separate prototype**, not a usable filesystem.
The existing `rom/filesys/SFS/` tree must remain unchanged.

## Scope
- New, distinct `SFNX` magic and v1 header field layout.
- Explicit big-endian on-disk layout proposal (not raw C struct serialization).
- Checked 64-bit block-to-byte and partition offset calculations.
- Portable host-side arithmetic regression tests.

## Run tests
```sh
cd rom/filesys/SFSNext/tests
make test
make clean
```
These tests do not require an AROS cross compiler. They do not prove AROS integration, SMP safety, data integrity, or filesystem mountability.

## Deliberately not implemented
No formatter, writable mount, legacy converter, journaling, checksum implementation, SMP locks, HDToolBox integration or on-disk writes. Header fields are a draft and must not be considered a stable format specification. Define checksum coverage, byte order tests, commit ordering, root redundancy, crash recovery and unknown-feature handling before enabling writes.

## Compatibility and safety
Legacy SFS is untouched; SFS Next uses a separate magic. Never attempt to reinterpret legacy volumes as SFNX or migrate without verified backups. Future readers must reject unknown incompatible features and unknown versions safely.

## Next phase
Implement explicit endian encode/decode with golden byte fixtures; fuzz parsing and reject invalid header fields; then implement a read-only image inspector. Review legacy licenses separately before reusing any source.
