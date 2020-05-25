with import <nixpkgs> {};
let
  opencvGtk = opencv.override (old : { enableGtk2 = true; enableFfmpeg = true; });
in
stdenv.mkDerivation {
    name = "ocr";
    src = ./.;
    buildInputs = [ pkgconfig zlib cmake leptonica opencvGtk tesseract4 gcc ];
}
