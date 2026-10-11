# Native macOS extraction

From the repository root:

```sh
bash Tools/UndatCLI/undat_macos.sh "/path/to/Fallout 1/MASTER.DAT"
```

An optional second argument selects a different `Fallout1in2` folder.
The script imports the existing `Tools/UndatUI/undat_files.txt` list into `data/`.
It preserves unrelated files; rerunning replaces matching extracted files.

The bundled `ce-dat-tool` runs on Intel and Apple Silicon Macs and has its
third-party dependencies linked statically. No Wine or Homebrew is needed.
Apple system libraries remain dynamically linked.

For a release, place `undat_macos.sh`, `ce-dat-tool`, and `undat_files.txt`
in `Fallout1in2`, then run `bash undat_macos.sh "/path/to/Fallout 1/MASTER.DAT"`.
Playing requires a compatible native engine installed separately.
