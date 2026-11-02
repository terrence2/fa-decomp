#!/usr/bin/env python3
"""End-to-end decompiled-code swap driver (the whole Gate-1 loop).

Config: build/swap.json — a list of entries:
  {"rva": 0xb06c0,                  // FA chunk RVA that this source replaces
   "obj": "WRFog",                  // base name for CL object
   "src": "src/WRFogLayerUpdate.c", // C/C++ source
   "flags": "/c /O2 /Gy /G5",       // cl flags (default /c /O2 /Gy /G5)
   "maps": ["Tgt=$FA$_t_40b0a0+0x90250"]}   -- fitobj relocation remaps

Usage:
  python3 tools/swap.py compile   # CL step only (fast iteration)
  python3 tools/swap.py fit       # fitobj for all entries
  python3 tools/swap.py audit     # provenance classification of patch/tail sites
  python3 tools/swap.py link      # stub regen + rsp + pdb-seed link cycle
  python3 tools/swap.py gate      # audit precondition + fixreloc + gate.py
  python3 tools/swap.py           # everything, in order

Artifacts under build/pilot/ (CL + fit objs), build/stubs_d (stub set).
"""
import json
import os
import subprocess
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])
from peref import IMAGE_BASE

# short dirname: the rsp ceiling (~32KB, LNK1104 truncated-path) is crossed
# at ~423 entries with build/stubs_d; a short name saves ~2.5KB
STUBS = "build/st"
RSP = "build/m0/m0linkD.rsp"
DOCKER = (
    "docker run --rm --user %(uid)d:%(gid)d -e HOME=/tmp -e TZ=UTC "
    "-e LD_PRELOAD=\"/usr/lib/x86_64-linux-gnu/faketime/libfaketime.so.1:"
    "/usr/lib/i386-linux-gnu/faketime/libfaketime.so.1\" "
    "-e FAKETIME=\"%(clock)s\" -e FAKETIME_DISABLE_SHM=1 "
    "-v \"$PWD\":/work -w /work fa-decomp-env bash -c \"%(cmd)s\""
)
DOCKER_PLAIN = (
    "docker run --rm --user %(uid)d:%(gid)d -e HOME=/tmp -e TZ=UTC "
    "-e FAKETIME_DISABLE_SHM=1 "
    "-v \"$PWD\":/work -w /work fa-decomp-env bash -c \"%(cmd)s\""
)


def sh(cmd, desc, check=True, log=None):
    print("== %s" % desc)
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    out = (r.stdout + r.stderr).strip()
    if log:
        open(log, "a").write(out + "\n")
    if out:
        keep = [l for l in out.splitlines() if "ELFCLASS" not in l]
        print("\n".join(keep[-8:]))
    if check and r.returncode:
        raise SystemExit("FAILED (%d): %s\n%s" % (r.returncode, desc, out[-2000:]))
    return r


def entries():
    txt = [
        ln for ln in open("tools/swap.json").read().splitlines()
        if not ln.lstrip().startswith("//")]
    es = json.loads("\n".join(txt))
    for e in es:
        if isinstance(e["rva"], str):
            e["rva"] = int(e["rva"], 0)
    return es

def split_vas(es):
    # mkstub SPLIT_AT / SPLIT_SPAN compare against chunk["va"] (FULL VA,
    # layout.json form) and mkrsp --replace keys against manifest m["va"] —
    # both VA-form; swap.json's rva entries are RVAs. Convert here so the
    # swap set's RVA keys never diverge from the link-side VA keys.
    # (Found while pilot 7: as-written, RVA keys silently no-oped the swap.)
    return ",".join("%#x" % (e["rva"] + IMAGE_BASE) for e in es)


def step_compile(es):
    os.makedirs("build/pilot", exist_ok=True)
    if not es:
        return
    # Chunked containers, serialized CL invocations with __OK__/__FAIL__
    # markers: a failing entry can no longer hide later entries' results
    # (per-entry containers cost ~2s startup each). ONE container for the
    # whole batch crossed Linux MAX_ARG_STRLEN (128KB per exec string,
    # E2BIG "Argument list too long") at 735 entries — ~700 was just
    # under; ~180 entries/chunk keeps each bash -c string far below.
    # Compile needs no clock: obj timestamps don't reach image bytes
    # (coff.build_stub_obj re-packs ts=0; the linker sees only *_fit.obj).
    for e in es:
        p = "build/pilot/%s.obj" % e["obj"]
        if os.path.exists(p):
            os.remove(p)  # so missing-obj after the batch is a true signal
    out = ""
    per = 180
    for i in range(0, len(es), per):
        parts = []
        for e in es[i:i + per]:
            cl = ("wine Z:/opt/msvc420/bin/CL.EXE /nologo "
                  + e.get("flags", "/c /O2 /Gy /G5")
                  + " Z:/work/%s /FoZ:/work/build/pilot/%s.obj"
                  % (e["src"], e["obj"]))
            parts.append('( %s ) && echo __OK__%s || echo __FAIL__%s'
                         % (cl, e["obj"], e["obj"]))
        r = subprocess.run(DOCKER_PLAIN % dict(
            uid=os.getuid(), gid=os.getgid(), cmd="; ".join(parts)),
            shell=True, capture_output=True, text=True)
        out += r.stdout + r.stderr
    out = out.splitlines()
    oks = {l[len("__OK__"):].strip() for l in out if l.startswith("__OK__")}
    fails = {l[len("__FAIL__"):].strip() for l in out
             if l.startswith("__FAIL__")}
    for e in es:
        if e["obj"] in oks and os.path.exists("build/pilot/%s.obj" % e["obj"]):
            print("cl %-20s ok" % e["obj"])
        else:
            fails.add(e["obj"])  # marker absent == failure (crash, OOM, ...)
    for e in es:  # fit each successful entry (per-entry diagnostic context)
        if e["obj"] in fails:
            continue
        _fit(e)
    if fails:
        # re-run each failure alone so its CL diagnostics are attributable
        for e in es:
            if e["obj"] not in fails:
                continue
            r2 = subprocess.run(
                DOCKER_PLAIN % dict(
                    uid=os.getuid(), gid=os.getgid(),
                    cmd=("wine Z:/opt/msvc420/bin/CL.EXE /nologo "
                         + e.get("flags", "/c /O2 /Gy /G5")
                         + " Z:/work/%s /FoZ:/work/build/pilot/%s.obj"
                         % (e["src"], e["obj"]))),
                shell=True, capture_output=True, text=True)
            keep = " ".join(l for l in (r2.stdout + r2.stderr).splitlines()
                            if "ELFCLASS" not in l)
            print("cl %-20s FAILED: %s" % (e["obj"], keep[-400:]))
        raise SystemExit("compile: %d of %d failed: %s"
                         % (len(fails), len(es), ", ".join(sorted(fails))))


def _fit(e):
    args = [sys.executable, "tools/fitobj.py",
            "build/pilot/%s.obj" % e["obj"], "%#x" % e["rva"]]
    for m in e.get("maps", []):
        args += ["--map", m]
    for p in e.get("patch", []):
        args += ["--patch", p]
    if e.get("span"):
        args += ["--span", str(e["span"])]
    for a in e.get("aliases", []):
        args += ["--alias", a]
    if e.get("tail"):
        args += ["--tail-accept"]
    r = subprocess.run(args, capture_output=True, text=True)
    print(r.stdout.strip())
    if r.returncode:
        raise SystemExit("fitobj failed for %s: %s" % (e["obj"], r.stderr[-1500:]))


def _sites(e):
    """(kind, label, directive) for every patch/tail site an entry carries."""
    s = [("patch", "patch[%d]" % i, e["patch"][i])
         for i in range(len(e.get("patch", [])))]
    if e.get("tail"):
        s.append(("tail", "tail", None))
    return s


def _classify(prov, kind, label, directive):
    """Pull the state word out of a provenance string for `label`.
    Provenance strings: 'patch <offs>: <root-caused|toolchain-diff|unexplained>
    ...' (grouped by directive offset, e.g. 'patch 0x39/0x4d: ...') or
    'tail: ...'. Returns (state, text) or None if not mentioned."""
    off = directive.split(",")[0].lower() if directive else None
    for p in prov:
        key = p.split(":")[0].strip().lower()
        hit = (key == "tail" if kind == "tail" else
               off is not None and key.startswith("patch") and off in key)
        if not hit:
            continue
        low = p.lower()
        for st in ("root-caused", "toolchain-diff", "unexplained"):
            if st in low:
                return st, p
        return "unclassified", p
    return None


def step_audit(es):
    """Provenance regression: every entry carrying patch/tail sites must
    classify each; any 'unexplained' (or unclassified/missing) exits nonzero.
    Wired as a gate precondition so an unexplained ad-hoc patch can never
    pass silently (workstream D policy: aggressive)."""
    bad, n = [], 0
    print("== audit: patch/tail provenance")
    for e in es:
        sites = _sites(e)
        prov = e.get("provenance", [])
        # a root-caused-then-eliminated site has "patch": [] but its history
        # is still recorded; provenance-only entries don't count against.
        for kind, label, directive in sites:
            n += 1
            hit = _classify(prov, kind, label, directive)
            if hit is None:
                bad.append("%s %s: NO provenance entry" % (e["obj"], label))
            elif hit[0] == "root-caused":
                # keeping a patch whose provenance says root-caused means the
                # construct now reproduces FA bytes -- directive is stale
                bad.append("%s %s: root-caused but patch/tail still present"
                           % (e["obj"], label))
            elif hit[0] in ("unexplained", "unclassified"):
                bad.append("%s %s: %s -- %s" % (e["obj"], label, hit[0], hit[1]))
            else:
                print("  %-20s %-10s toolchain-diff: %s"
                      % (e["obj"], label, hit[1][:100]))
        if not sites and e.get("provenance"):
            for p in prov:
                if "root-caused" in p.lower() or "eliminated" in p.lower():
                    print("  %-20s %-10s (eliminated; %s...)"
                          % (e["obj"], "patch[]", p[:70]))
    if bad:
        for b in bad:
            print("  FAIL %s" % b)
        raise SystemExit("audit: %d unexplained/unclassified site(s) of %d"
                         % (len(bad), n))
    print("  ok: %d site(s) classified, 0 unexplained" % n)


def step_link(es):
    subprocess.run("rm -rf " + STUBS, shell=True, check=True)
    normal = [e for e in es if not e.get("span")]
    spanned = [e for e in es if e.get("span")]
    # tail word (exe 0x131a09): deterministic function of the swap set and
    # GROUP_SIZE; swept via seed-link-only runs (build/w15/gssweep.py): GS=13
    # at 423 entries (wave-13), GS=7 at 661 entries (wave-15) read 00 00.
    # Re-sweep whenever the swap set size changes.
    env = dict(os.environ, STUB_DIR=STUBS, GROUP_SIZE="7",
               SPLIT_AT=",".join("%#x" % (e["rva"] + IMAGE_BASE)
                                 for e in normal),
               SPLIT_SPAN=",".join("%#x:%s" % (e["rva"] + IMAGE_BASE,
                                               e["span"])
                                   for e in spanned))
    r = subprocess.run([sys.executable, "tools/mkstub.py"], env=env,
                       capture_output=True, text=True)
    print(r.stdout.strip())
    if r.returncode:
        raise SystemExit("mkstub failed: " + r.stderr[-2000:])
    # rsp ceiling mitigations: #1 relative obj paths (343 entries); #2 short
    # STUBS dir build/st (423); #3+#4 stage ALL link inputs under atf95/d
    # (LINK cwd is atf95) and use SHORT stub names from mkstub (no va suffix)
    # -- 661 entries: 36.2KB down to ~21KB. #5 (852 entries): stage the FIT
    # objs under short names d/f%05x.obj too -- 852 long "<Base>_fit.obj"
    # paths inflate both the rsp (31.5KB at the ~32KB LNK1104/LNK1141
    # truncated-path ceiling: "cannot open Z:\opt\msvc420\lib\", "failure
    # during build of exports file") and the /EXPORT LINK /lib spawn's argv;
    # short names save ~15KB of each.
    subprocess.run(
        "mkdir -p atf95/d && rm -f atf95/d/* && "
        "cp build/st/* build/idata/* build/m0/FA.obj atf95/d/",
        shell=True, check=True)
    import shutil
    for i, e in enumerate(es):
        shutil.copyfile("build/pilot/%s_fit.obj" % e["obj"],
                        "atf95/d/f%05x.obj" % i)
    repl = []
    for i, e in enumerate(es):
        repl.append(["--replace", "%#x=d/f%05x.obj"
                     % (e["rva"] + IMAGE_BASE, i)])
    r = subprocess.run([sys.executable, "tools/mkrsp.py", "--stubdir", STUBS,
                        "--out", RSP]
                       + [x for pair in repl for x in pair], check=True)
    # CLOCKS MUST BE FROZEN (no "@" prefix): with FAKETIME="@..." libfaketime
    # ADVANCES from that moment, so the seed's pdb NB10 sig (0x33ef9c68) raced
    # :40/:41 depending on when LINK wrote the pdb (~50/50 across runs —
    # wave-20 "pdb ts :41 flake"). Frozen clocks make every read return the
    # exact time; seed fixes NB10 sig :40, real link rewrites the header ts
    # :32 and preserves the pdb sig. Verified sha-identical 2/2 runs.
    for clock, log in (("1997-08-11 23:12:40", "logD_seed"),
                       ("1997-08-11 23:13:32", "logD_link")):
        # seed link: reset the pdb so its ts comes from THIS run's clock;
        # real link: keep the pdb (updates it, preserving ts, age -> 1)
        stale = "FA.pdb FA.exe FA.lib FA.exp FA.map" \
            if clock.endswith(":40") else "FA.exe FA.lib FA.exp FA.map"
        subprocess.run("cd atf95/Release && rm -f " + stale, shell=True,
                       check=True)
        docker_link = DOCKER % dict(
            uid=os.getuid(), gid=os.getgid(), clock=clock,
            # relative rsp form (from /work/atf95) — the absolute Z:\ form
            # loses backslashes through the python->sh->docker quoting chain
            cmd="cd /work/atf95 && wine Z:/opt/msvc420/bin/LINK.EXE "
                "'@..\\\\build\\\\m0\\\\m0linkD.rsp' "
                "> /work/build/m0/%s 2>&1; echo exit=$?" % log)
        r = subprocess.run(docker_link, shell=True, capture_output=True,
                           text=True)
        # wine does not propagate LNK errors as exit codes (LNK1120 exits 0)
        if not os.path.exists("atf95/Release/FA.exe"):
            raise SystemExit("%s failed: %s"
                             % (log, (r.stdout + r.stderr)[-2000:]))
        print("%s ok" % log)


def step_gate(es=None):
    step_audit(entries())
    subprocess.run([sys.executable, "tools/fixreloc.py"],
                   capture_output=True)
    return subprocess.run([sys.executable, "tools/gate.py"]).returncode


if __name__ == "__main__":
    es = entries()
    steps = sys.argv[1:] or ["compile", "link", "gate"]
    for s in steps:
        rc = {"compile": lambda: step_compile(es) or 0,
              "fit": lambda: ([_fit(e) for e in es], 0)[1],  # list of _fit Nones is truthy!
              "audit": lambda: step_audit(es) or 0,
              "link": lambda: step_link(es) or 0,
              # gate: fail the process if gate.py does (the previous form
              # discarded step_gate's return and exited 0 on GATE 1 FAIL)
              "gate": lambda: step_gate(es)}[s]()
        if rc:
            raise SystemExit(rc)