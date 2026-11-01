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
  python3 tools/swap.py link      # stub regen + rsp + pdb-seed link cycle
  python3 tools/swap.py gate      # fixreloc + gate.py
  python3 tools/swap.py           # everything, in order

Artifacts under build/pilot/ (CL + fit objs), build/stubs_d (stub set).
"""
import json
import os
import subprocess
import sys

sys.path.insert(0, __file__.rsplit("/", 1)[0])

STUBS = "build/stubs_d"
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
    return ",".join("%#x" % e["rva"] for e in es)


def step_compile(es):
    os.makedirs("build/pilot", exist_ok=True)
    for e in es:
        cmd = ("wine Z:/opt/msvc420/bin/CL.EXE /nologo "
               + e.get("flags", "/c /O2 /Gy /G5")
               + " Z:/work/%s /FoZ:/work/build/pilot/%s.obj" % (e["src"], e["obj"]))
        # compile needs no clock: obj timestamps don't reach image bytes
        r = subprocess.run(DOCKER_PLAIN % dict(uid=os.getuid(), gid=os.getgid(),
                                               cmd=cmd), shell=True,
                           capture_output=True, text=True)
        keep = " ".join(l for l in (r.stdout + r.stderr).splitlines()
                        if "ELFCLASS" not in l)
        print("cl %-20s %s" % (e["obj"], keep[-160:] if keep else "ok"))
        if r.returncode:
            raise SystemExit("CL failed for %s" % e["src"])
        _fit(e)


def _fit(e):
    args = [sys.executable, "tools/fitobj.py",
            "build/pilot/%s.obj" % e["obj"], "%#x" % e["rva"]]
    for m in e.get("maps", []):
        args += ["--map", m]
    for p in e.get("patch", []):
        args += ["--patch", p]
    if e.get("tail"):
        args += ["--tail-accept"]
    r = subprocess.run(args, capture_output=True, text=True)
    print(r.stdout.strip())
    if r.returncode:
        raise SystemExit("fitobj failed for %s: %s" % (e["obj"], r.stderr[-1500:]))


def step_link(es):
    subprocess.run("rm -rf " + STUBS, shell=True, check=True)
    env = dict(os.environ, STUB_DIR=STUBS, SPLIT_AT=split_vas(es))
    r = subprocess.run([sys.executable, "tools/mkstub.py"], env=env,
                       capture_output=True, text=True)
    print(r.stdout.strip())
    if r.returncode:
        raise SystemExit("mkstub failed: " + r.stderr[-2000:])
    repl = []
    for e in es:
        repl += ["--replace", "%#x=Z:/work/build/pilot/%s_fit.obj"
                 % (e["rva"], e["obj"])]
    subprocess.run([sys.executable, "tools/mkrsp.py", "--stubdir", STUBS,
                    "--out", RSP] + repl, check=True)
    for clock, log in (("@1997-08-11 23:12:40", "logD_seed"),
                       ("@1997-08-11 23:13:32", "logD_link")):
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
        if "exit=0" not in r.stdout:
            raise SystemExit("%s failed: %s"
                             % (log, (r.stdout + r.stderr)[-2000:]))
        print("%s ok" % log)


def step_gate(es=None):
    subprocess.run([sys.executable, "tools/fixreloc.py"],
                   capture_output=True)
    return subprocess.run([sys.executable, "tools/gate.py"]).returncode


if __name__ == "__main__":
    es = entries()
    steps = sys.argv[1:] or ["compile", "link", "gate"]
    for s in steps:
        {"compile": lambda: step_compile(es),
         "link": lambda: step_link(es),
         "gate": lambda: step_gate(es)}[s]()