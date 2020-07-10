with import <nixpkgs> {};
with pkgs.python3Packages;
buildPythonPackage rec {
  name = "mypackage";
  src = ./.;
  propagatedBuildInputs = [ python38Packages.numba pyaudio pydub pytest librosa matplotlib  python38Packages.librosa python38Packages.numpy ];
}
