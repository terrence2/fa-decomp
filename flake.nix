{
  description = "fa-decomp dev shell";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in with pkgs; {
        devShells.default = mkShell rec {
          buildInputs = [
            clang
          ];

          packages = [
            ghidra
            radare2
            ltrace
            python314Packages.ropper
            python314Packages.capstone
          ];

          LD_LIBRARY_PATH = "${lib.makeLibraryPath buildInputs}";
        };
      });
}

