{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (system: let
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.default = pkgs.mkShell {
      name = "brst";

      nativeBuildInputs = with pkgs; [
        pkg-config
      ];

      buildInputs = with pkgs; [
        SDL2
      ];

      packages = with pkgs; [
        valgrind
      ];
    };

    packages.default = pkgs.stdenv.mkDerivation {
      name = "brst";

      src = ./.;

      nativeBuildInputs = with pkgs; [
        pkg-config
      ];

      buildInputs = with pkgs; [
        SDL2
      ];

      installPhase = ''
        mkdir -p $out/bin/
        cp ./brst $out/bin/
      '';
    };
  });
}
