# FA.EXE — Compiler / Toolchain Identification

Written 2026-10-31 from static analysis of `FA/FA.EXE` (no symbols, no Rich header).

## Answer

**Microsoft Visual C++ 4.2** — the `cl 10.20.x` / `link.exe 4.20.x` toolchain from mid-1996.

Caveat on terminology: "Visual Studio" as a bundled suite did not exist yet (it began with
Visual Studio 97 / VC++ 5.0, April 1997). VC++ 5.0 *was* already on the market at this
binary's build date — it just was not used.

- Binary: PE32 x86, GUI (subsystem 2), OS version 4.0, 6 sections, ImageBase 0x400000
- SizeOfImage 0x1a3000; FileVersion resource: **1.00F** (final retail build of 1.00)
- TimeDateStamp `0x33ef9c9c` = **1997-08-11 23:13:32 UTC**
- Build host project dir: `E:\atf95\Release\FA.pdb` (internal codename "atf95")
- Release build: FPO data present, `/Zi`-linked (`NB10` PDB reference, debug data externalized to FA.pdb)

## Evidence, itemized

1. **`MajorLinkerVersion.Minor = 4.20`** in the PE optional header.
   Known MS linker-field map of the era: VC++ 2.0 → 2.50, VC++ 4.0 → 3.00,
   VC++ 4.1 → 3.10, **VC++ 4.2 → 4.20**, VC++ 5.0 → 5.0x, VC++ 6.0 → 6.00.

2. **C++ EH funcinfo magic = `0x19930520`** — all 23 occurrences in `.text`/CRT are the
   raw VC4.x exception model. Zero occurrences anywhere of `0x19930521` (VC 5.0) or
   `0x19930522` (VC 6.0). Later-era runtime checkers recognize *both* old and new magic,
   so total absence of the later magics proves no object in the image was compiled by
   VC5+ (CRT and game code are all VC4.x).

3. **Static CRT (libcmt, `/MT`-style)**: characteristic VC4.x kernel32 import set —
   `RtlUnwind`, `TlsAlloc/TlsFree/TlsGetValue/TlsSetValue`, `HeapCreate/HeapAlloc/HeapReAlloc`,
   `GetCPInfo`, `GetOEMCP`, `GetACP`, `LCMapStringW`, `CompareStringW`, `GetStringTypeW`,
   `GetEnvironmentStringsW` + `GetEnvironmentStrings`, `SetUnhandledExceptionFilter`,
   `FatalAppExitA`. No `MSVCRT.DLL` or `CRTDLL.DLL` import.

4. **CRT string fingerprint** (single block at ~0xe4b00): `R6002`–`R6028` runtime error
   list (`R6025 - pure virtual function call` etc.), `Microsoft Visual C++ Runtime Library`,
   `Runtime Error!\n\nProgram: `, `<program name unknown>`,
   `\r\nabnormal program termination\r\n`, and the VC4.x-era locale-name table
   (`united-states`, `english-usa`, `english-uk`, `tur`, `svk`, ...).

5. **No Rich header** (`DanS` signature absent; `e_lfanew = 0x80`, DOS stub has no Rich
   block). The VS97-and-later linkers emit one; its absence is consistent with a 4.20
   linker.

6. **Debug directory** (RVA `0xe5000`, 3 entries):
   - type 4 MISC: `Release/FA.exe` (config)
   - type 3: FPO data, ~0xbaa0 bytes
   - type 2 CodeView `NB10`: `E:\atf95\Release\FA.pdb` (PDB 2.0 format — used by VC4–VC6;
     not a VC5 discriminator on its own)

7. **Corroborating sibling**: `IP.EXE` (Intranet Play) also has linker 4.20 with the
   *identical* timestamp — same build batch/pipeline.

8. **Non-MSVC neighbors** (for context, not user's question): `CDRVDL32.DLL`,
   `CDRVHF32.DLL`, `CDRVXF32.DLL`, `COMMSC32.DLL` are Watcom-built (linker field 2.55,
   Apr 1996); `WAIL32.DLL` (Miles Sound System) has linker field 3.00.

## Limits of precision

The PE header stores only `4.20` — no linker or cl build number — and the Rich header
(where per-tool build numbers otherwise live) is absent. So:

- Proven: the VC++ 4.2 toolchain line (compiler 10.20, linker 4.20).
- NOT distinguishable from the binary alone: retail **VC++ 4.2** (cl 10.20.6166) vs.
  the **VC++ 4.2b** patch-level toolset (updated cl/link/CRT distributed as
  `VC42B.EXE`, `SDK42B.EXE`, `MSDEV42B.EXE`, `42BB1B2.EXE`).
- Feasible follow-up to close that gap: obtain the VC 4.2 / 4.2b patch packages,
  byte-diff the statically-linked CRT and representative codegen in FA.EXE against
  reference objects from each toolset. (Known anchors: retail 4.2 x86 cl = 10.20.6166;
  VC 4.2b Alpha = cl 10.20.7032 / linker 4.20.619x — x86 4.2b build numbers not
  documented in the sources checked.)

## Reference mapping used

- MS linker-version ↔ product: [huntertur KB archive (VC++ RISC Edition version info)](https://helparchive.huntertur.net/document/36364),
  [ReverseEngineering.wiki — Format: PE](https://reverseengineering.wiki/index.php/Format:PE_(Portable_Executable)),
  [Pietrek, "Peering Inside the PE"](https://learn.microsoft.com/en-us/previous-versions/ms809762%28v=msdn.10%29)
- EH funcinfo magics `0x19930520/21/22`: reverse-engineering convention per the MSVC ABI notes
- cl 10.00.5270 = VC4.0, 10.10.6038 = VC4.1, 10.20.6166 = VC4.2 (`_MSC_VER` 1020):
  [Wikipedia — Visual C++](https://en.wikipedia.org/wiki/Visual_C++),
  [VC++/MFC/ATL version history](https://mariusbancila.ro/blog/2015/08/12/version-history-of-vc-mfc-and-atl/)
- VC 4.2b patch packages: [zx.net — Updates & Notes for Vintage Development Tools](https://zx.net.nz/vc/updates/dev.shtml)
- Same identification method applied to a sibling EA product (Wing Commander Win32 ports):
  ["Some Incredible Code"](https://cephalochromoscope.net/a8378b4e-b7aa-4596-9ff1-1243a94e951e)
- FA.EXE RE context: [Fighters Codex — FA Game Architecture](https://fighterscodex.com/fa/architecture/),
  [Reconstruction Matrix](https://fighterscodex.com/fa/reconstruction/)

## Useful related facts

- `FA.SMS` is a binary symbol-map file (~104 kB) covering ~3,829 MSVC-mangled C++
  symbols over `0x401000`–`0x5937E0` — the primary naming asset for the decomp work.
  Community reference places `WinMain` at `0x476120`.
- `FA.EXE` exports a small table (module name `FA.exe`) and imports from `WINMM`,
  `KERNEL32`, `USER32`, `DDRAW`, `wail32.dll`, `CDRVDL32.DLL`, `CDRVHF32.DLL`,
  `ADVAPI32` — statically-linked CRT, custom (non-MFC) UI.
- **`FA_*.LIB` are game assets, not build leftovers.** The shipped `FA_.LIB`,
  `FA_1.LIB` … `FA_23.LIB` files are runtime file archives the game loads (campaign/
  mission data); despite the `.LIB` extension and their COFF/PE-like members with symbol
  references, they played no part in linking FA.EXE and are out of scope for the
  reconstruction work.
- Strings confirm the codebase lineage: `E:\atf95\multi\*.cpp` source paths, `FA97`,
  `EAGAME.%s.` registry keys.