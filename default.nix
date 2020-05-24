with import <nixpkgs> {};
stdenv.mkDerivation {
    name = "dev-environment"; # Probably put a more meaningful name here
    src = ./.;
    buildInputs = [ pkgconfig zlib cmake leptonica opencv tesseract4 gcc ];
}
